using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WordPad_NoRibbon
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            statusStrip1.BringToFront();
            InitFontsComboBox();
            InitFontSizesComboBox();
            InitTrackBar();
        }

        private void InitTrackBar()
        {
            TrackBar tb = new TrackBar();
            ToolStripControlHost myControlHost = new ToolStripControlHost(tb);
            statusStrip1.Items.Add(myControlHost);
            tb.TickFrequency = 5;
            tb.Minimum = 1;
            tb.Maximum = 63;
            tb.Value = 1;

            tb.ValueChanged += (sender, eventArgs) =>
            {
                richTextBox1.ZoomFactor = tb.Value;
            };
        }

        public void InitFontsComboBox()
        {
            foreach (FontFamily oneFontFamily in FontFamily.Families)
            {
                toolStripComboBox1.Items.Add(oneFontFamily.Name);
            }

            toolStripComboBox1.SelectedIndex = 6;
        }

        public void InitFontSizesComboBox()
        {
            toolStripComboBox2.Items.AddRange(new string[] { "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72" });
            toolStripComboBox2.SelectedIndex = 3;
        }

        public bool StatusBarEnabled
        {
            get { return statusStrip1.Visible; }
            set { checkBox1.Checked = statusStrip1.Visible = value; }
        }

        private void checkBox1_Click(object sender, EventArgs e)
        {
            StatusBarEnabled = !StatusBarEnabled;
        }

        public bool WordWrapHandle
        {
            get { return richTextBox1.WordWrap; }
            set { checkBox2.Checked = richTextBox1.WordWrap = value; }
        }
        
        private void checkBox2_Click(object sender, EventArgs e)
        {
            WordWrapHandle = !WordWrapHandle;
        }

        private void toolStripMenuItem9_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectedText = DateTime.Now.ToShortTimeString() + " " + DateTime.Now.ToShortDateString();
        }

        private void toolStripMenuItem5_Click(object sender, EventArgs e)
        {
            richTextBox1.Paste();
        }

        private void toolStripMenuItem7_Click(object sender, EventArgs e)
        {
            richTextBox1.Cut();
        }

        private void toolStripMenuItem8_Click(object sender, EventArgs e)
        {
            richTextBox1.Copy();
        }

        private void printDocument(object sender, PrintPageEventArgs e)
        {
            Font font = new System.Drawing.Font("Arial", 10, FontStyle.Bold);
            Brush brush = new SolidBrush(Color.Black);
            PointF point = new PointF(10, 10);
            e.Graphics.DrawString(richTextBox1.Text, font, brush, point);
        }

        private void toolStripMenuItem13_Click(object sender, EventArgs e)
        {
            PrintDialog printDialog = new PrintDialog();
            PrintDocument print = new PrintDocument();

            print.PrintPage += new PrintPageEventHandler(printDocument);
            print.DocumentName = "WordPad Document";

            printDialog.Document = print;
            printDialog.AllowSelection = true;
            printDialog.AllowSomePages = true;

            if (printDialog.ShowDialog() == DialogResult.OK) print.Print();
        }

        private void toolStripMenuItem14_Click(object sender, EventArgs e)
        {
            var PageSetupForm = new PageSetupDialog();
            PageSetupForm.PageSettings = new PageSettings();

            if (PageSetupForm.ShowDialog(this) != DialogResult.OK) return;
        }

        private void toolStripMenuItem30_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
        }

        private void toolStripMenuItem31_Click(object sender, EventArgs e)
        {
            if (richTextBox1.ZoomFactor + (float)0.5 < 64)
            richTextBox1.ZoomFactor = richTextBox1.ZoomFactor + (float)0.5;
        }

        private void toolStripMenuItem32_Click(object sender, EventArgs e)
        {
            if (richTextBox1.ZoomFactor - (float)0.5 > 0.015625)
            richTextBox1.ZoomFactor = richTextBox1.ZoomFactor - (float)0.5;
        }

        private void toolStripMenuItem33_Click(object sender, EventArgs e)
        {
            richTextBox1.ZoomFactor = 1;
        }

        private void toolStripMenuItem11_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            if (currentFont.Size + 1 < System.Single.MaxValue)
            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size + 1);
        }

        private void toolStripMenuItem12_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            if (currentFont.Size - 1 > 0)
            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size - 1);
        }

        private void toolStripMenuItem16_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            FontStyle updatedFontStyle;

            if (richTextBox1.SelectionFont.Bold == true) updatedFontStyle = FontStyle.Regular;
            else updatedFontStyle = FontStyle.Bold;

            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size, updatedFontStyle);
        }

        private void toolStripMenuItem17_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            FontStyle updatedFontStyle;

            if (richTextBox1.SelectionFont.Italic == true) updatedFontStyle = FontStyle.Regular;
            else updatedFontStyle = FontStyle.Italic;

            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size, updatedFontStyle);
        }

        private void toolStripMenuItem18_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            FontStyle updatedFontStyle;

            if (richTextBox1.SelectionFont.Underline == true) updatedFontStyle = FontStyle.Regular;
            else updatedFontStyle = FontStyle.Underline;

            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size, updatedFontStyle);
        }

        private void toolStripMenuItem19_Click(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;
            FontStyle updatedFontStyle;

            if (richTextBox1.SelectionFont.Strikeout == true) updatedFontStyle = FontStyle.Regular;
            else updatedFontStyle = FontStyle.Strikeout;

            richTextBox1.SelectionFont = new Font(currentFont.FontFamily, currentFont.Size, updatedFontStyle);
        }

        private void toolStripMenuItem20_Click(object sender, EventArgs e)
        {
            if (richTextBox1.SelectionCharOffset != -4) richTextBox1.SelectionCharOffset = -4;
            else richTextBox1.SelectionCharOffset = 0;
        }

        private void toolStripMenuItem21_Click(object sender, EventArgs e)
        {
            if (richTextBox1.SelectionCharOffset != 4) richTextBox1.SelectionCharOffset = 4;
            else richTextBox1.SelectionCharOffset = 0;
        }

        private void toolStripMenuItem24_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
            richTextBox1.SelectionAlignment = HorizontalAlignment.Left;
        }

        private void toolStripMenuItem25_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
            richTextBox1.SelectionAlignment = HorizontalAlignment.Center;
        }

        private void toolStripMenuItem26_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
            richTextBox1.SelectionAlignment = HorizontalAlignment.Right;
        }

        private void toolStripMenuItem27_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
            richTextBox1.SelectionAlignment = HorizontalAlignment.Center;
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            var lineCount = richTextBox1.Lines.Count();
            var characterCount = richTextBox1.Text.Length;

            string label1Template = "Line count: {0} | Character count: {1}";
            toolStripStatusLabel1.Text = string.Format(label1Template, lineCount, characterCount);
        }

        private void toolStripMenuItem28_Click(object sender, EventArgs e)
        {
            new Find().ShowDialog(this);
        }

        private void toolStripMenuItem29_Click(object sender, EventArgs e)
        {
            new Replace().ShowDialog(this);
        }

        public int MyFind(string str, int start, RichTextBoxFinds option)
        {
            int startPosition = richTextBox1.Find(str, start, option);

            if (startPosition < 0)
                return -1;

            select(startPosition, str.Length);

            return startPosition;
        }

        public bool MyReplace(string str)
        {
            if (richTextBox1.SelectedText == null || richTextBox1.SelectedText.Length <= 0)
                return false;

            richTextBox1.SelectedText = str;
            richTextBox1.HideSelection = false;
            richTextBox1.ScrollToCaret();

            return true;
        }

        public void findNext(string searchString, bool matchCase)
        {
            int currentPosition = richTextBox1.SelectionStart;
            string haystack = "";
            int resultIndex = -1;

            haystack = richTextBox1.Text.Substring(currentPosition, richTextBox1.Text.Length - currentPosition);

            if (richTextBox1.SelectedText == searchString)
            {
                if (haystack.Substring(searchString.Length, 2) != "\r\n")
                    haystack = haystack.Substring(searchString.Length, haystack.Length - searchString.Length);
                else haystack = haystack.Substring(searchString.Length + 2, haystack.Length - searchString.Length - 2);
            }
                // TODO: SelectedText "==" comparison has to be made case-insensitive

            if (matchCase) resultIndex = haystack.IndexOf(searchString);
            else resultIndex = haystack.IndexOf(searchString, StringComparison.CurrentCultureIgnoreCase);

            if (resultIndex != -1) resultIndex += currentPosition;

            if (resultIndex != -1)
            {
                select(resultIndex, searchString.Length);
                // TODO: Auto-scroll to the result if result is invisible in the current scroll state
                return;
            }

            MessageBox.Show("Could not find the requested string in file.");
        }

        public void find(string searchString, bool matchCase, bool matchWord)
        {
            int resultIndex;

            //if (richTextBox1.SelectedText == searchString)
            //{
                findNext(searchString, matchCase);
                return;
            //}

            if (!matchWord) resultIndex = richTextBox1.Find(searchString, matchCase ? RichTextBoxFinds.MatchCase : RichTextBoxFinds.None);
            else resultIndex = richTextBox1.Find(searchString, matchCase ? RichTextBoxFinds.MatchCase | RichTextBoxFinds.WholeWord : RichTextBoxFinds.None | RichTextBoxFinds.WholeWord);
            // TODO: Find next. Remove current selection from the search.

            int resultLength = searchString.Length;
            
            select(resultIndex, resultLength);
        }

        public void select(int startIndex, int length)
        {
            if (startIndex != -1)
            {
                richTextBox1.SelectionStart = startIndex;
                richTextBox1.SelectionLength = length;
                richTextBox1.HideSelection = false;
                richTextBox1.ScrollToCaret();
            }
        }

        public static string ReplaceString(string str, string oldValue, string newValue, StringComparison comparison)
        {
            StringBuilder sb = new StringBuilder();

            int previousIndex = 0;
            int index = str.IndexOf(oldValue, comparison);
            while (index != -1)
            {
                sb.Append(str.Substring(previousIndex, index - previousIndex));
                sb.Append(newValue);
                index += oldValue.Length;

                previousIndex = index;
                index = str.IndexOf(oldValue, index, comparison);
            }
            sb.Append(str.Substring(previousIndex));

            return sb.ToString();
        }

        public void replaceAll(string searchString, string replaceString, bool matchCase, bool matchWord)
        {
            if (matchCase) richTextBox1.Text = richTextBox1.Text.Replace(searchString, replaceString);
            else richTextBox1.Text = ReplaceString(richTextBox1.Text, searchString, replaceString, StringComparison.CurrentCultureIgnoreCase);
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileForm = new SaveFileDialog();

            saveFileForm.InitialDirectory = @"C:\";
            saveFileForm.Title = "Save WordPad File";
            saveFileForm.DefaultExt = "rtf";
            saveFileForm.Filter = "Rich Text File (*.rtf)|*.rtf|All files (*.*)|*.*";
            saveFileForm.FilterIndex = 2;
            saveFileForm.RestoreDirectory = true;

            if (saveFileForm.ShowDialog() == DialogResult.OK)
            {
                richTextBox1.SaveFile(saveFileForm.FileName, RichTextBoxStreamType.RichText);
            }
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileForm = new SaveFileDialog();

            saveFileForm.InitialDirectory = @"C:\";
            saveFileForm.Title = "Save WordPad File";
            saveFileForm.DefaultExt = "rtf";
            saveFileForm.Filter = "Rich Text File (*.rtf)|*.rtf|All files (*.*)|*.*";
            saveFileForm.FilterIndex = 2;
            saveFileForm.RestoreDirectory = true;

            if (saveFileForm.ShowDialog() == DialogResult.OK)
            {
                richTextBox1.SaveFile(saveFileForm.FileName, RichTextBoxStreamType.RichText);
            }
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileForm = new OpenFileDialog();
            Stream fileStream = null;

            openFileForm.InitialDirectory = "c:\\";
            openFileForm.Filter = "Rich Text Files (*.rtf)|*.rtf|All Files (*.*)|*.*";
            openFileForm.FilterIndex = 2;
            openFileForm.RestoreDirectory = true;

            if (openFileForm.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((fileStream = openFileForm.OpenFile()) != null)
                    {
                        using (fileStream) { richTextBox1.LoadFile(openFileForm.FileName); }
                    }
                }
                catch (Exception error)
                {
                    MessageBox.Show("Could not read the file. Error: " + error.Message);
                }
            }
        }

        private void toolStripComboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (toolStripComboBox3.SelectedIndex)
            {
                case 0:
                    richTextBox1.SelectionBackColor = Color.Red;
                    break;
                case 1:
                    richTextBox1.SelectionBackColor = Color.Black;
                    break;
                case 2:
                    richTextBox1.SelectionBackColor = Color.Orange;
                    break;
                case 3:
                    richTextBox1.SelectionBackColor = Color.Blue;
                    break;
                case 4:
                    richTextBox1.SelectionBackColor = Color.Green;
                    break;
                case 5:
                    richTextBox1.SelectionBackColor = Color.Pink;
                    break;
                case 6:
                    richTextBox1.SelectionBackColor = Color.Yellow;
                    break;
            }
        }

        private void toolStripMenuItem34_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionBackColor = Color.Transparent;
        }

        private void toolStripComboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (toolStripComboBox4.SelectedIndex)
            {
                case 0:
                    richTextBox1.SelectionColor = Color.Red;
                    break;
                case 1:
                    richTextBox1.SelectionColor = Color.Black;
                    break;
                case 2:
                    richTextBox1.SelectionColor = Color.Orange;
                    break;
                case 3:
                    richTextBox1.SelectionColor = Color.Blue;
                    break;
                case 4:
                    richTextBox1.SelectionColor = Color.Green;
                    break;
                case 5:
                    richTextBox1.SelectionColor = Color.Pink;
                    break;
                case 6:
                    richTextBox1.SelectionColor = Color.Yellow;
                    break;
            }
        }

        private void toolStripComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Font currentFont = richTextBox1.SelectionFont;

            var convertor = new FontConverter();
            Font newFont = convertor.ConvertFrom(toolStripComboBox1.Items[toolStripComboBox1.SelectedIndex]) as Font;

            richTextBox1.SelectionFont = new Font(newFont, currentFont.Style);
        }

        private void toolStripComboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectedSize = Int32.Parse(toolStripComboBox2.SelectedItem.ToString());

            richTextBox1.SelectionFont = new System.Drawing.Font(
                richTextBox1.SelectionFont.FontFamily.Name,
                selectedSize,
                richTextBox1.SelectionFont.Style,
                System.Drawing.GraphicsUnit.Point,
                ((byte)(0)));
        }

        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            DataFormats.Format bitmap = DataFormats.GetFormat(DataFormats.Bitmap);
            StringCollection clipboardCollection = Clipboard.GetFileDropList();

            Image image = Image.FromFile(clipboardCollection[0]);
            Clipboard.Clear();
            Clipboard.SetImage(image);
            if (Clipboard.ContainsImage())
            {
                richTextBox1.Paste(bitmap);
                Clipboard.Clear();
            }
        }

        private void toolStripMenuItem15_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileForm = new OpenFileDialog();
            DataFormats.Format bitmap = DataFormats.GetFormat(DataFormats.Bitmap);

            openFileForm.InitialDirectory = "c:\\";
            openFileForm.Filter = "JPG images (*.jpg)|*.jpg|PNG images (*.png)|*.png|All Files (*.*)|*.*";
            openFileForm.RestoreDirectory = true;

            if (openFileForm.ShowDialog() == DialogResult.OK)
            {
                Image image = Image.FromFile(openFileForm.FileName);
                Clipboard.SetImage(image);
                richTextBox1.Paste(bitmap);
            }
        }

        private void toolStripMenuItem35_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileForm = new OpenFileDialog();
            DataFormats.Format bitmap = DataFormats.GetFormat(DataFormats.Bitmap);

            openFileForm.InitialDirectory = "c:\\";
            openFileForm.Filter = "JPG images (*.jpg)|*.jpg|PNG images (*.png)|*.png|All Files (*.*)|*.*";
            openFileForm.RestoreDirectory = true;

            if (openFileForm.ShowDialog() == DialogResult.OK)
            {
                richTextBox1.SelectedRtf = "";
                Image image = Image.FromFile(openFileForm.FileName);
                Clipboard.SetImage(image);
                richTextBox1.Paste(bitmap);
            }
        }

        private void toolStripMenuItem36_Click(object sender, EventArgs e)
        {
            // TODO: Resize picture
        }

        private void richTextBox1_SelectionChanged(object sender, EventArgs e)
        {
            if (richTextBox1.SelectionType == RichTextBoxSelectionTypes.Object)
            {
                toolStripMenuItem35.Enabled = true;
                toolStripMenuItem36.Enabled = true;
            }
            else
            {
                toolStripMenuItem35.Enabled = false;
                toolStripMenuItem36.Enabled = false;
            }
        }
    }
}
