using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MPL2_QueryBrowser
{
    public partial class ConnectForm : Form
    {
        public ConnectForm()
        {
            InitializeComponent();
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            try
            {
                MainForm mainForm = (MainForm)this.Owner;
                mainForm.Connect(serverTextBox.Text, Convert.ToInt16(portTextBox.Text), 
                    databaseTextBox.Text, usernameTextBox.Text, passwordTextBox.Text);
                Close();
            }
            catch (Exception error) { MessageBox.Show(error.Message); }
        }
    }
}
