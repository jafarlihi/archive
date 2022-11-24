using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace MPL2_QueryBrowser
{
    public partial class MainForm : Form
    {
        private MySqlConnection connection;

        public MainForm()
        {
            InitializeComponent();
        }

        private void connection_StateChanged(object sender, StateChangeEventArgs e)
        {
            if (new ConnectionState[] { ConnectionState.Executing,
                ConnectionState.Fetching, ConnectionState.Open }.Contains(e.CurrentState))
            { UpdateConnectionStatus(true); } else { UpdateConnectionStatus(false); }
        }

        private void UpdateConnectionStatus(bool state)
        {
            if (state == true)
            {
                connectButton.Visible = false;
                disconnectButton.Visible = true;
                statusLabel.Text = "Connected";
                statusLabel.ForeColor = Color.Green;
            }
            else
            {
                databaseSchemaTreeView.Nodes.Clear();
                connectButton.Visible = true;
                disconnectButton.Visible = false;
                statusLabel.Text = "Not connected";
                statusLabel.ForeColor = Color.Red;
            }
        }

        private bool CloseConnection()
        {
            try
            {
                connection.Close();
                UpdateConnectionStatus(false);
                return true;
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
                return false;
            }
        }

        private void PopulateConnectionDetails()
        {
            string query = "SHOW TABLES;";

            try
            {
                MySqlCommand command = new MySqlCommand(query, connection);
                MySqlDataReader reader = command.ExecuteReader();

                while (reader.Read()) { databaseSchemaTreeView.Nodes.Add(reader.GetString(0)); }

                reader.Close();
               
                foreach (TreeNode node in databaseSchemaTreeView.Nodes)
                {
                    query = "DESCRIBE " + node.Text + ";";
                    command = new MySqlCommand(query, connection);
                    reader = command.ExecuteReader();

                    while (reader.Read()) { node.Nodes.Add(reader.GetString(0) + " - " + reader.GetString(1)); }

                    reader.Close();
                }

            } catch (Exception error){ MessageBox.Show(error.Message); }
        }

        public void Connect(string server, int port, string database, string username, string password)
        {
            string connectionString;
            connectionString = "SERVER=" + server + ";" + "DATABASE=" +
                database + ";" + "UID=" + username+ ";" + "PASSWORD=" + password + ";";

            try
            {
                connection = new MySqlConnection(connectionString);
                connection.StateChange += new StateChangeEventHandler(connection_StateChanged);
                connection.Open();
                PopulateConnectionDetails();
            }
            catch (Exception error) { MessageBox.Show(error.Message); }
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            new ConnectForm().Show(this);
        }

        private void disconnectButton_Click(object sender, EventArgs e)
        {
            CloseConnection();
            UpdateConnectionStatus(false);
        }

        // dirty af
        private void runQueryButton_Click(object sender, EventArgs e)
        {
            MySqlDataAdapter adapter = new MySqlDataAdapter();

            try
            { adapter = new MySqlDataAdapter(queryTextBox.Text, connection); }
            catch (Exception error) { MessageBox.Show(error.Message); }

            try
            {
                DataSet set = new DataSet();
                adapter.Fill(set);
                mainDataGrid.DataSource = set.Tables[0];
                mainDataGrid.Refresh();
            } catch { }
        }
    }
}
