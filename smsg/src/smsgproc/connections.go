package main

import (
	"bytes"
	"database/sql"
	"fmt"
	_ "github.com/lib/pq"
	_ "github.com/mattn/go-oci8"
	"io"
	"io/ioutil"
	"net"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"time"
)

type openConn struct {
	conn *Connection
	db   *sql.DB
	stmt *sql.Stmt
	clnt *http.Client
	trnp *http.Transport
}

var OPENCONNS map[string]openConn

var oracleReplacer *strings.Replacer
var postgresReplacer *strings.Replacer

func InitConnections() {
	OPENCONNS = make(map[string]openConn)

	postgresReplacer = strings.NewReplacer("$source", "$1", "$destination", "$2", "$message", "$3")
	oracleReplacer = strings.NewReplacer("$source", ":1", "$destination", ":2", "$message", ":3")

	for conn := range CONFIG.Connections {
		switch CONFIG.Connections[conn].ConnType {
		case "Oracle":
			CONFIG.Connections[conn].connectOracle()
		case "Postgres":
			CONFIG.Connections[conn].connectPostgres()
		case "HTTP":
			CONFIG.Connections[conn].connectHTTP()
		}
	}
}

func Send(message *Message, connID string) {
	if connID == "discard" {
		Release(message.UUID)
		return
	}

	if OPENCONNS[connID].conn.ConnType == "Postgres" || OPENCONNS[connID].conn.ConnType == "Oracle" {
		_, err := OPENCONNS[connID].stmt.Exec(message.Source, message.Destination, message.Content)

		if err == nil {
			Release(message.UUID)
		} else {
			LOG.Errorf("Failed to execute prepared statement for connection ID: %s. Error: %s. Requeuing the message.", connID, err)
			Requeue(message.UUID)
		}
	}

	if OPENCONNS[connID].conn.ConnType == "HTTP" {
		var err error
		var resp *http.Response

		replacer := strings.NewReplacer("$source", url.QueryEscape(strconv.FormatInt(message.Source, 10)),
			"$destination", url.QueryEscape(strconv.FormatInt(message.Destination, 10)),
			"$message", url.QueryEscape(message.Content))
		replacedStmt := replacer.Replace(OPENCONNS[connID].conn.Statement)

		switch OPENCONNS[connID].conn.ReqType {
		case "POST":
			resp, err = OPENCONNS[connID].clnt.Post("http://"+OPENCONNS[connID].conn.Host+":"+strconv.Itoa(OPENCONNS[connID].conn.Port)+OPENCONNS[connID].conn.Path,
				OPENCONNS[connID].conn.ContType, bytes.NewBufferString(replacer.Replace(replacedStmt)))
		case "GET":
			resp, err = OPENCONNS[connID].clnt.Get("http://" + OPENCONNS[connID].conn.Host + ":" + strconv.Itoa(OPENCONNS[connID].conn.Port) + OPENCONNS[connID].conn.Path + replacedStmt)
		}

		if err == nil {
			Release(message.UUID)
		} else {
			LOG.Errorf("Failed to push message to the HTTP connection with identifier \"%s\". Error: %s. Requeuing the message.", connID, err)
			Requeue(message.UUID)
		}

		io.Copy(ioutil.Discard, resp.Body)
		resp.Body.Close()
	}
}

func (conn Connection) connectPostgres() {
	connString := fmt.Sprint("postgres://" + conn.Username + ":" + conn.Password + "@" + conn.Host + ":" + strconv.Itoa(conn.Port) + "/" + conn.Database + "?sslmode=disable")
	db, err := sql.Open("postgres", connString)

	if err != nil {
		LOG.Errorf("Couldn't create a PostgreSQL database object with connection string of %s.", connString)
		CleanExit()
	}

	db.SetMaxIdleConns(1)
	db.SetMaxOpenConns(1)

	pingErr := db.Ping()
	if pingErr != nil {
		LOG.Errorf("Couldn't connect to the PostgreSQL database %s. Error: %s.", connString, pingErr.Error())
		CleanExit()
	}

	stmtString := postgresReplacer.Replace(conn.Statement)
	stmt, stmtErr := db.Prepare(stmtString)
	if stmtErr != nil {
		LOG.Errorf("Couldn't prepare a statement for PostgreSQL database %s. Statement: %s. Error: %s.", connString, stmtString, stmtErr)
		CleanExit()
	}

	OPENCONNS[conn.Identifier] = openConn{conn: &conn, db: db, stmt: stmt}
}

func (conn Connection) connectOracle() {
	connString := fmt.Sprintf(conn.Username + "/" + conn.Password + "@" + conn.Host + ":" + strconv.Itoa(conn.Port) + ":" + conn.Sid)
	db, err := sql.Open("oci8", connString)

	if err != nil {
		LOG.Errorf("Couldn't create an Oracle database object with connection string of %s.", connString)
		CleanExit()
	}

	db.SetMaxIdleConns(1)
	db.SetMaxOpenConns(1)

	pingErr := db.Ping()
	if pingErr != nil {
		LOG.Errorf("Couldn't connect to the Oracle database %s. Error: %s.", connString, pingErr.Error())
		CleanExit()
	}

	stmtString := oracleReplacer.Replace(conn.Statement)
	stmt, stmtErr := db.Prepare(stmtString)
	if stmtErr != nil {
		LOG.Errorf("Couldn't prepare a statement for Oracle database %s. Statement: %s. Error: %s.", connString, stmtString, stmtErr)
		CleanExit()
	}

	OPENCONNS[conn.Identifier] = openConn{conn: &conn, db: db, stmt: stmt}
}

func (conn Connection) connectHTTP() {
	connTest, err := net.Dial("tcp", conn.Host+":"+strconv.Itoa(conn.Port))
	if err != nil {
		LOG.Errorf("%s, port %s does not seem to be responding. Connection ID: %s. Error %s.", conn.Host, strconv.Itoa(conn.Port), conn.Identifier, err)
		CleanExit()
	}
	connTest.Close()

	transport := &http.Transport{
		MaxIdleConnsPerHost: 2,
		IdleConnTimeout:     120 * time.Second,
		DisableCompression:  true,
	}
	client := &http.Client{Transport: transport}

	OPENCONNS[conn.Identifier] = openConn{conn: &conn, clnt: client, trnp: transport}
}
