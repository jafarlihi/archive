package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"time"

	"github.com/gocarina/gocsv"
)

type Transaction struct {
	ID              string  `csv:"id"`
	Amount          float64 `csv:"amount"`
	BankCountryCode string  `csv:"bank_country_code"`
}

type TransactionInfo struct {
	id        string
	fradulent bool
}

var latencies = map[string]int{}

func max(a int, b int) int {
	if a > b {
		return a
	}
	return b
}

func processTransaction(transaction Transaction) bool {
	// Mock for bank API call
	time.Sleep(time.Duration(latencies[transaction.BankCountryCode]) * time.Millisecond)
	rand.Seed(time.Now().UnixNano())
	return rand.Intn(2) == 1
}

func processTransactions(transactions []Transaction) []TransactionInfo {
	results := []TransactionInfo{}
	for _, transaction := range transactions {
		result := TransactionInfo{id: transaction.ID}
		result.fradulent = processTransaction(transaction)
		results = append(results, result)
	}
	return results
}

func prioritize(transactions []*Transaction, totalTime int) []*Transaction {
	var result []*Transaction
	table := make([][]int, len(transactions)+1)
	for i := range table {
		table[i] = make([]int, totalTime+1)
	}

	// Construct the table
	// Amounts are multiplied by 100 and converted to int to lose the fraction, for easier processing
	for i := 0; i <= len(transactions); i++ {
		for j := 0; j <= totalTime; j++ {
			if i == 0 || j == 0 {
				table[i][j] = 0
			} else if latencies[transactions[i-1].BankCountryCode] <= j {
				table[i][j] = max(int(transactions[i-1].Amount*100)+table[i-1][j-latencies[transactions[i-1].BankCountryCode]], table[i-1][j])
			} else {
				table[i][j] = table[i-1][j]
			}
		}
	}

	totalAmount := table[len(transactions)][totalTime]
	fmt.Println("Maximum amount:", float64(totalAmount)/100.0)
	j := totalTime

	// Backtrack on table and pick items
	for i := len(transactions); i > 0 && totalAmount > 0; i-- {
		if totalAmount == table[i-1][j] {
			continue
		} else {
			result = append(result, transactions[i-1])
			totalAmount -= int(transactions[i-1].Amount * 100)
			j -= latencies[transactions[i-1].BankCountryCode]
		}
	}

	return result
}

func main() {
	latenciesFile, err := os.Open("latencies.json")
	if err != nil {
		panic(err)
	}
	defer latenciesFile.Close()
	latenciesBytes, _ := ioutil.ReadAll(latenciesFile)
	err = json.Unmarshal(latenciesBytes, &latencies)
	if err != nil {
		panic(err)
	}

	transactionsFile, err := os.Open("transactions.csv")
	if err != nil {
		panic(err)
	}
	defer transactionsFile.Close()
	transactions := []*Transaction{}
	err = gocsv.UnmarshalFile(transactionsFile, &transactions)
	if err != nil {
		panic(err)
	}

	chosenTransactions := prioritize(transactions, 1000)
	fmt.Println("Transactions chosen for 1000ms total time:")
	for _, t := range chosenTransactions {
		fmt.Printf("%+v\n", t)
	}

	fmt.Println()

	fmt.Println("For 50ms:")
	_ = prioritize(transactions, 50)
	fmt.Println("For 60ms:")
	_ = prioritize(transactions, 60)
	fmt.Println("For 90ms:")
	_ = prioritize(transactions, 90)
	fmt.Println("For 1000ms:")
	_ = prioritize(transactions, 1000)
}
