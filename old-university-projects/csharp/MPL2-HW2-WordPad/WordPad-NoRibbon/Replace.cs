using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WordPad_NoRibbon
{
    public partial class Replace : Form
    {
        int Start = 0;

        public Replace()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string searchString = textBox1.Text;
            string replaceString = textBox2.Text;
            bool matchCase = findCase.Checked;
            bool matchWord = findWord.Checked;

            (Application.OpenForms["Form1"] as Form1).replaceAll(searchString, replaceString, matchCase, matchWord);
            (Application.OpenForms["Form1"]).Focus();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 formMain = (Form1)this.Owner;
            RichTextBoxFinds option = RichTextBoxFinds.None;

            if (findCase.Checked)
                option |= RichTextBoxFinds.MatchCase;

            if (findWord.Checked)
                option |= RichTextBoxFinds.WholeWord;

            Start = formMain.MyFind(textBox1.Text, Start, option);

            if (Start < 0)
            {
                MessageBox.Show("Given string is not found!");

                Start = 0;
            }
            else
                Start++;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form1 formMain = (Form1)this.Owner;

            if (!formMain.MyReplace(textBox2.Text))
            {
                button1.PerformClick();
                formMain.MyReplace(textBox2.Text);
            }
        }
    }
}
