namespace NotepadQU
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
            this.findFinderTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.findFindButton = new System.Windows.Forms.Button();
            this.findCancelButton = new System.Windows.Forms.Button();
            this.findCase = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.findRadioDown = new System.Windows.Forms.RadioButton();
            this.findRadioUp = new System.Windows.Forms.RadioButton();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // findFinderTextBox
            // 
            this.findFinderTextBox.Location = new System.Drawing.Point(90, 14);
            this.findFinderTextBox.Name = "findFinderTextBox";
            this.findFinderTextBox.Size = new System.Drawing.Size(178, 20);
            this.findFinderTextBox.TabIndex = 0;
            this.findFinderTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.findFinderTextBox_KeyDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Find what:";
            // 
            // findFindButton
            // 
            this.findFindButton.Location = new System.Drawing.Point(283, 12);
            this.findFindButton.Name = "findFindButton";
            this.findFindButton.Size = new System.Drawing.Size(75, 23);
            this.findFindButton.TabIndex = 2;
            this.findFindButton.Text = "Find Next";
            this.findFindButton.UseVisualStyleBackColor = true;
            this.findFindButton.Click += new System.EventHandler(this.findFindButton_Click);
            // 
            // findCancelButton
            // 
            this.findCancelButton.Location = new System.Drawing.Point(283, 42);
            this.findCancelButton.Name = "findCancelButton";
            this.findCancelButton.Size = new System.Drawing.Size(75, 23);
            this.findCancelButton.TabIndex = 3;
            this.findCancelButton.Text = "Cancel";
            this.findCancelButton.UseVisualStyleBackColor = true;
            this.findCancelButton.Click += new System.EventHandler(this.findCancelButton_Click);
            // 
            // findCase
            // 
            this.findCase.AutoSize = true;
            this.findCase.Location = new System.Drawing.Point(12, 75);
            this.findCase.Name = "findCase";
            this.findCase.Size = new System.Drawing.Size(82, 17);
            this.findCase.TabIndex = 4;
            this.findCase.Text = "Match case";
            this.findCase.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.findRadioDown);
            this.groupBox1.Controls.Add(this.findRadioUp);
            this.groupBox1.Location = new System.Drawing.Point(158, 42);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(110, 50);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Direction";
            // 
            // findRadioDown
            // 
            this.findRadioDown.AutoSize = true;
            this.findRadioDown.Location = new System.Drawing.Point(51, 20);
            this.findRadioDown.Name = "findRadioDown";
            this.findRadioDown.Size = new System.Drawing.Size(53, 17);
            this.findRadioDown.TabIndex = 1;
            this.findRadioDown.TabStop = true;
            this.findRadioDown.Text = "Down";
            this.findRadioDown.UseVisualStyleBackColor = true;
            // 
            // findRadioUp
            // 
            this.findRadioUp.AutoSize = true;
            this.findRadioUp.Checked = true;
            this.findRadioUp.Location = new System.Drawing.Point(7, 20);
            this.findRadioUp.Name = "findRadioUp";
            this.findRadioUp.Size = new System.Drawing.Size(39, 17);
            this.findRadioUp.TabIndex = 0;
            this.findRadioUp.TabStop = true;
            this.findRadioUp.Text = "Up";
            this.findRadioUp.UseVisualStyleBackColor = true;
            // 
            // Find
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(370, 106);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.findCase);
            this.Controls.Add(this.findCancelButton);
            this.Controls.Add(this.findFindButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.findFinderTextBox);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Find";
            this.Text = "Find";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox findFinderTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button findFindButton;
        private System.Windows.Forms.Button findCancelButton;
        private System.Windows.Forms.CheckBox findCase;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton findRadioDown;
        private System.Windows.Forms.RadioButton findRadioUp;
    }
}