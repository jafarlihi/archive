using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NotepadQU
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void helpAbout_Click(object sender, EventArgs e)
        {
            new About().ShowDialog(this);
        }

        private void fileExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        public bool WordWrapHandle
        {
            get { return textBox1.WordWrap; }
            set { formatWordWrap.Checked = textBox1.WordWrap = value; }
        }

        private void formatWordWrap_Click(object sender, EventArgs e)
        {
            WordWrapHandle = !WordWrapHandle;
        }

        private void editSelectAll_Click(object sender, EventArgs e)
        {
            textBox1.SelectAll();
        }

        private void editDelete_Click(object sender, EventArgs e)
        {
            textBox1.SelectedText = "";
        }

        private void editUndo_Click(object sender, EventArgs e)
        {
            textBox1.Undo();
        }

        private void editCut_Click(object sender, EventArgs e)
        {
            textBox1.Cut();
        }

        private void editCopy_Click(object sender, EventArgs e)
        {
            textBox1.Copy();
        }

        private void editPaste_Click(object sender, EventArgs e)
        {
            textBox1.Paste();
        }

        private void helpViewHelp_Click(object sender, EventArgs e)
        {
            new About().ShowDialog(this);
        }

        private void formatFont_Click(object sender, EventArgs e)
        {
            var FontForm = new FontDialog();
            FontForm.Font = textBox1.Font;

            if (FontForm.ShowDialog(this) != DialogResult.OK)
                return;

            textBox1.Font = FontForm.Font;
        }

        private void editTimeDate_Click(object sender, EventArgs e)
        {
            textBox1.SelectedText = DateTime.Now.ToShortTimeString() + " " + DateTime.Now.ToShortDateString();
        }

        private void editFind_Click(object sender, EventArgs e)
        {
            new Find().ShowDialog(this);
        }

        public bool StatusBarEnabled
        {
            get { return mainStatusBar.Visible; }
            set { viewStatusBar.Checked = mainStatusBar.Visible = value; }
        }

        private void viewStatusBar_Click(object sender, EventArgs e)
        {
            StatusBarEnabled = !StatusBarEnabled;
        }

        private void fileOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileForm = new OpenFileDialog();
            Stream fileStream = null;

            openFileForm.InitialDirectory = "c:\\";
            openFileForm.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
            openFileForm.FilterIndex = 2;
            openFileForm.RestoreDirectory = true;

            if (openFileForm.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((fileStream = openFileForm.OpenFile()) != null)
                    {
                        using (fileStream) { textBox1.Text = File.ReadAllText(openFileForm.FileName); }
                        pastSearch = false;
                    }
                }
                catch (Exception error)
                {
                    MessageBox.Show("Could not read the file. Error: " + error.Message);
                }
            }
        }

        private void fileNew_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            pastSearch = false;
        }

        private void fileSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileForm = new SaveFileDialog();

            saveFileForm.InitialDirectory = @"C:\";
            saveFileForm.Title = "Save Text File";
            saveFileForm.DefaultExt = "txt";
            saveFileForm.Filter = "Text File (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileForm.FilterIndex = 2;
            saveFileForm.RestoreDirectory = true;

            if (saveFileForm.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileForm.FileName, textBox1.Text);
            }
        }

        private void fileSaveAs_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileForm = new SaveFileDialog();

            saveFileForm.InitialDirectory = @"C:\";
            saveFileForm.Title = "Save Text File";
            saveFileForm.DefaultExt = "txt";
            saveFileForm.Filter = "Text File (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileForm.FilterIndex = 2;
            saveFileForm.RestoreDirectory = true;

            if (saveFileForm.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileForm.FileName, textBox1.Text);
            }
        }

        private void editGoTo_Click(object sender, EventArgs e)
        {
            int currentLineCount = textBox1.Lines.Count();
            new GoTo(currentLineCount).ShowDialog(this);
        }

        public void goTo(int line)
        {
            int position = textBox1.GetFirstCharIndexFromLine(line);
            textBox1.Select(position, 0);
        }

        private void printDocument(object sender, PrintPageEventArgs e)
        {
            Font font = new System.Drawing.Font("Arial", 10, FontStyle.Bold);
            Brush brush = new SolidBrush(Color.Black);
            PointF point = new PointF(10, 10);
            e.Graphics.DrawString(textBox1.Text, font, brush, point);
        }

        private void filePrint_Click(object sender, EventArgs e)
        {
            PrintDialog printDialog = new PrintDialog();
            PrintDocument print = new PrintDocument();

            print.PrintPage += new PrintPageEventHandler(printDocument);
            print.DocumentName = "NotepadQU Document";

            printDialog.Document = print;
            printDialog.AllowSelection = true;
            printDialog.AllowSomePages = true;

            if (printDialog.ShowDialog() == DialogResult.OK) print.Print();
        }

        private void filePageSetup_Click(object sender, EventArgs e)
        {
            var PageSetupForm = new PageSetupDialog();
            PageSetupForm.PageSettings = new PageSettings();

            if (PageSetupForm.ShowDialog(this) != DialogResult.OK) return;
            // TODO: Enumerate and implement PageSetupForm.PageSettings.X properties into MainForm textBox1 here
        }

        public void find(string searchString, bool matchCase, bool directionUp)
        {
            int currentPosition = textBox1.SelectionStart;
            string haystack = "";
            int resultIndex = -1;

            if (directionUp)
            {
                haystack = textBox1.Text.Substring(0, currentPosition);

                if (matchCase) resultIndex = haystack.LastIndexOf(searchString);
                else resultIndex = haystack.LastIndexOf(searchString, StringComparison.CurrentCultureIgnoreCase);
            }
            else
            {
                haystack = textBox1.Text.Substring(currentPosition, textBox1.Text.Length - currentPosition);

                if (textBox1.SelectedText == searchString)
                {
                    if (haystack.Substring(searchString.Length, 2) != "\r\n")
                        haystack = haystack.Substring(searchString.Length, haystack.Length - searchString.Length);
                    else haystack = haystack.Substring(searchString.Length + 2, haystack.Length - searchString.Length - 2);
                }
                // TODO: SelectedText "==" comparison has to be made case-insensitive

                if (matchCase) resultIndex = haystack.IndexOf(searchString);
                else resultIndex = haystack.IndexOf(searchString, StringComparison.CurrentCultureIgnoreCase);

                if (resultIndex != -1) resultIndex += currentPosition;
            }

            if (resultIndex != -1)
            {
                saveLastSearch(searchString, matchCase, directionUp);
                select(resultIndex, searchString.Length);
                // TODO: Auto-scroll to the result if result is invisible in the current scroll state
                return;
            }

            MessageBox.Show("Could not find the requested string in file.");
        }

        public void select(int startIndex, int length)
        {
            textBox1.SelectionStart = startIndex;
            textBox1.SelectionLength = length;
        }

        public string lastSearchString;
        public bool lastMatchCase;
        public bool lastDirectionUp;
        public bool pastSearch = false;

        public void saveLastSearch(string searchString, bool matchCase, bool directionUp)
        {
            lastSearchString = searchString;
            lastMatchCase = matchCase;
            lastDirectionUp = directionUp;
            pastSearch = true;
        }

        private void editFindNext_Click(object sender, EventArgs e)
        {
            if (pastSearch == true)
            {
                find(lastSearchString, lastMatchCase, lastDirectionUp);
            }
            else
            {
                new Find().ShowDialog(this);
            }
        }

        private void editReplace_Click(object sender, EventArgs e)
        {
            // TODO: Implement replacement operation
        }
    }
}
