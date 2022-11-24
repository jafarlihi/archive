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
    public partial class Find : Form
    {
        public Find()
        {
            InitializeComponent();
        }

        private void findCancelButton_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void findFindButton_Click(object sender, EventArgs e)
        {
            string searchString = findFinderTextBox.Text;
            bool matchCase = findCase.Checked;
            bool directionUp = findRadioUp.Checked ? true : false;

            (Application.OpenForms["MainForm"] as MainForm).find(searchString, matchCase, directionUp);
            (Application.OpenForms["MainForm"]).Focus();
        }

        private void findFinderTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                findFindButton.PerformClick();
                e.SuppressKeyPress = true;
                e.Handled = true;
            }
        }
    }
}
