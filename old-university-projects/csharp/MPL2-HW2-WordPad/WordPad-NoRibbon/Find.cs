using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WordPad_NoRibbon
{
    public partial class Find : Form
    {
        int Start = 0;

        public Find()
        {
            InitializeComponent();
        }

        private void findFindButton_Click(object sender, EventArgs e)
        {
            /*
            string searchString = findFinderTextBox.Text;
            bool matchCase = findCase.Checked;
            bool matchWord = findWord.Checked;

            (Application.OpenForms["Form1"] as Form1).find(searchString, matchCase, matchWord);
            (Application.OpenForms["Form1"]).Focus();
            */

            Form1 formMain = (Form1)this.Owner;
            RichTextBoxFinds option = RichTextBoxFinds.None;

            if (findCase.Checked)
                option |= RichTextBoxFinds.MatchCase;

            if (findWord.Checked)
                option |= RichTextBoxFinds.WholeWord;

            Start = formMain.MyFind(findFinderTextBox.Text, Start, option);

            if (Start < 0)
            {
                MessageBox.Show("Given string is not found!");

                Start = 0;
            }
            else
                Start++;
        }

        private void findCancelButton_Click(object sender, EventArgs e)
        {
            Hide();
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
