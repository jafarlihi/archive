using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MDIForms
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            IsMdiContainer = true;
        }

        private void minimizeAllButton_Click(object sender, EventArgs e)
        {
            Form[] childFormArray = this.MdiChildren;
            foreach (Form childForm in childFormArray) childForm.WindowState = FormWindowState.Minimized;
        }

        private void showAllButton_Click(object sender, EventArgs e)
        {
            Form[] childFormArray = this.MdiChildren;
            foreach (Form childForm in childFormArray) childForm.WindowState = FormWindowState.Normal;
        }

        private void floatingFormButton_Click(object sender, EventArgs e)
        {
            FloatingForm ff = new FloatingForm();
            ff.Show();
        }

        private void childForm1Button_Click(object sender, EventArgs e)
        {
            ChildForm1 cf1 = new ChildForm1();
            cf1.MdiParent = this;
            cf1.Show();
        }

        private void childForm2Button_Click(object sender, EventArgs e)
        {
            ChildForm2 cf2 = new ChildForm2();
            cf2.MdiParent = this;
            cf2.Show();
        }
    }
}
