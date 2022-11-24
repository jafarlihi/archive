namespace WordPad_NoRibbon
{
    partial class Find
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.findCase = new System.Windows.Forms.CheckBox();
            this.findCancelButton = new System.Windows.Forms.Button();
            this.findFindButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.findFinderTextBox = new System.Windows.Forms.TextBox();
            this.findWord = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // findCase
            // 
            this.findCase.AutoSize = true;
            this.findCase.Location = new System.Drawing.Point(20, 80);
            this.findCase.Name = "findCase";
            this.findCase.Size = new System.Drawing.Size(82, 17);
            this.findCase.TabIndex = 10;
            this.findCase.Text = "Match case";
            this.findCase.UseVisualStyleBackColor = true;
            // 
            // findCancelButton
            // 
            this.findCancelButton.Location = new System.Drawing.Point(288, 40);
            this.findCancelButton.Name = "findCancelButton";
            this.findCancelButton.Size = new System.Drawing.Size(75, 23);
            this.findCancelButton.TabIndex = 9;
            this.findCancelButton.Text = "Cancel";
            this.findCancelButton.UseVisualStyleBackColor = true;
            this.findCancelButton.Click += new System.EventHandler(this.findCancelButton_Click);
            // 
            // findFindButton
            // 
            this.findFindButton.Location = new System.Drawing.Point(288, 10);
            this.findFindButton.Name = "findFindButton";
            this.findFindButton.Size = new System.Drawing.Size(75, 23);
            this.findFindButton.TabIndex = 8;
            this.findFindButton.Text = "Find Next";
            this.findFindButton.UseVisualStyleBackColor = true;
            this.findFindButton.Click += new System.EventHandler(this.findFindButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Find what:";
            // 
            // findFinderTextBox
            // 
            this.findFinderTextBox.Location = new System.Drawing.Point(95, 12);
            this.findFinderTextBox.Name = "findFinderTextBox";
            this.findFinderTextBox.Size = new System.Drawing.Size(178, 20);
            this.findFinderTextBox.TabIndex = 6;
            this.findFinderTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.findFinderTextBox_KeyDown);
            // 
            // findWord
            // 
            this.findWord.AutoSize = true;
            this.findWord.Location = new System.Drawing.Point(20, 57);
            this.findWord.Name = "findWord";
            this.findWord.Size = new System.Drawing.Size(135, 17);
            this.findWord.TabIndex = 11;
            this.findWord.Text = "Match whole word only";
            this.findWord.UseVisualStyleBackColor = true;
            // 
            // Find
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(380, 103);
            this.Controls.Add(this.findWord);
            this.Controls.Add(this.findCase);
            this.Controls.Add(this.findCancelButton);
            this.Controls.Add(this.findFindButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.findFinderTextBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Find";
            this.Text = "Find";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.CheckBox findCase;
        private System.Windows.Forms.Button findCancelButton;
        private System.Windows.Forms.Button findFindButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox findFinderTextBox;
        private System.Windows.Forms.CheckBox findWord;
    }
}