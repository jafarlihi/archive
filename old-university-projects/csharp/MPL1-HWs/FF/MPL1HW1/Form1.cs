using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MPL1HW1
{
    public partial class Form1 : Form
    {
        bool bLive, bProf, bStudy = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void studyClear_Click(object sender, EventArgs e)
        {
            studyBox.Text = "";
        }

        private void liveClear_Click(object sender, EventArgs e)
        {
            liveBox.Text = "";
        }

        private void professionClear_Click(object sender, EventArgs e)
        {
            professionBox.Text = "";
        }

        private void studyNA_Click(object sender, EventArgs e)
        {
            studyBox.Text = "";
            studyBox.ReadOnly = true;
            studySubmit.Enabled = false;
            studyClear.Enabled = false;
            studyNA.Enabled = false;

            bStudy = true;
        }

        private void liveNA_Click(object sender, EventArgs e)
        {
            liveBox.Text = "";
            liveBox.ReadOnly = true;
            liveSubmit.Enabled = false;
            liveClear.Enabled = false;
            liveNA.Enabled = false;

            bLive = true;
        }

        private void professionNA_Click(object sender, EventArgs e)
        {
            professionBox.Text = "";
            professionBox.ReadOnly = true;
            professionSubmit.Enabled = false;
            professionClear.Enabled = false;
            professionNA.Enabled = false;

            bProf = true;
        }

        private void studySubmit_Click(object sender, EventArgs e)
        {
            studyBox.ReadOnly = true;
            studySubmit.Enabled = false;
            studyClear.Enabled = false;
            studyNA.Enabled = false;

            bStudy = true;
        }

        private void liveSubmit_Click(object sender, EventArgs e)
        {
            liveBox.ReadOnly = true;
            liveSubmit.Enabled = false;
            liveClear.Enabled = false;
            liveNA.Enabled = false;

            bLive = true;
        }

        private void professionSubmit_Click(object sender, EventArgs e)
        {
            professionBox.ReadOnly = true;
            professionSubmit.Enabled = false;
            professionClear.Enabled = false;
            professionNA.Enabled = false;

            bProf = true;
        }

        private void resultButton_Click(object sender, EventArgs e)
        {
            if (!(bProf && bLive && bStudy)) {
                MessageBox.Show("Please fill all 3 fields.");
                return;
            }

            resultDear.Text = "Dear ";
            foreach (char c in nameBox.Text.ToUpper())
            {
                resultDear.Text = resultDear.Text + c + " ";
            }
            resultDear.Text = resultDear.Text + " ";
            foreach (char c in surnameBox.Text.ToUpper())
            {
                resultDear.Text = resultDear.Text + c + " ";
            }

            int answered = 0;
            answered = answered + (string.IsNullOrWhiteSpace(studyBox.Text) ? 0 : 1);
            answered = answered + (string.IsNullOrWhiteSpace(liveBox.Text) ? 0 : 1);
            answered = answered + (string.IsNullOrWhiteSpace(professionBox.Text) ? 0 : 1);

            resultQuestions.Text = "You answered " + answered.ToString() + " questions.";

            List<String> dirtyStrings = new List<String>();

            if (!(string.IsNullOrWhiteSpace(studyBox.Text))) {
                dirtyStrings.Add("\"" + studyBox.Text + "\"");
            }
            if (!(string.IsNullOrWhiteSpace(liveBox.Text)))
            {
                dirtyStrings.Add("\"" + liveBox.Text + "\"");
            }
            if (!(string.IsNullOrWhiteSpace(professionBox.Text)))
            {
                dirtyStrings.Add("\"" + professionBox.Text + "\"");
            }

            string answersConcat = "";
            int counter = 0;
            foreach (string ds in dirtyStrings)  {
                counter++;
                if (counter != dirtyStrings.Count)
                {
                    answersConcat = answersConcat + ds + ", ";
                }
                else
                {
                    answersConcat = answersConcat + ds;
                }
            }
            resultAnswers.Text = "Your answers are " + answersConcat + ".";

            answersConcat = studyBox.Text + " " + liveBox.Text + " " + professionBox.Text;
            int wordCount = answersConcat.Split(' ').Length;
            int letterCount = answersConcat.Count(char.IsLetter);
            resultWords.Text = "You used " + wordCount + " words and " + letterCount + " letters.";
        }

        private void resultDynButton_Click(object sender, EventArgs e)
        {
            string answersConcat = studyBox.Text + " " + liveBox.Text + " " + professionBox.Text;
            resultDyn.Text = "letter " + answersConcat.Count(x => x == letterBox.Text[0]).ToString() + " times"; 
        }
    }
}
