using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NotepadQU
{
    public partial class GoTo : Form
    {
        private int lineCount;

        public GoTo(int currentLineCount)
        {
            InitializeComponent();
            lineCount = currentLineCount;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int requestedLineNumber = Int32.Parse(goToTextBox.Text);
            requestedLineNumber -= 1;
            
            if (requestedLineNumber < 0 || requestedLineNumber > lineCount)
            {
                MessageBox.Show("Requested line number is out of bounds.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            (Application.OpenForms["MainForm"] as MainForm).goTo(requestedLineNumber);
            Close();
        }

        private void goToTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button1.PerformClick();
                e.SuppressKeyPress = true;
                e.Handled = true;
            }
        }
    }
}
