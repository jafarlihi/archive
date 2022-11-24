using System;
using System.Windows.Forms;

namespace MPL2_Paint
{
    public partial class NewImageDialog : Form
    {
        public NewImageDialog()
        {
            InitializeComponent();
        }

        private void createButton_Click(object sender, EventArgs e)
        {
            if (widthTextBox.Text != "" || heightTextBox.Text != "") {
                try
                {
                    int width = Convert.ToInt32(widthTextBox.Text);
                    int height = Convert.ToInt32(heightTextBox.Text);

                    (Application.OpenForms["MainForm"] as MainForm).NewImage(width, height);
                    this.Close();
                }
                catch
                {
                    MessageBox.Show("Please specify width and height of a new image in integers.");
                }
            }
        }
    }
}
