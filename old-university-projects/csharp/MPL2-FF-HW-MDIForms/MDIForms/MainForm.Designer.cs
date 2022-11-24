namespace MDIForms
{
    partial class MainForm
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.childForm1Button = new System.Windows.Forms.ToolStripMenuItem();
            this.childForm2Button = new System.Windows.Forms.ToolStripMenuItem();
            this.floatingFormButton = new System.Windows.Forms.ToolStripMenuItem();
            this.childFormControlButton = new System.Windows.Forms.ToolStripMenuItem();
            this.minimizeAllButton = new System.Windows.Forms.ToolStripMenuItem();
            this.showAllButton = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.childFormControlButton,
            this.childForm1Button,
            this.childForm2Button,
            this.floatingFormButton});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(642, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // childForm1Button
            // 
            this.childForm1Button.Name = "childForm1Button";
            this.childForm1Button.Size = new System.Drawing.Size(86, 20);
            this.childForm1Button.Text = "Child Form #1";
            this.childForm1Button.Click += new System.EventHandler(this.childForm1Button_Click);
            // 
            // childForm2Button
            // 
            this.childForm2Button.Name = "childForm2Button";
            this.childForm2Button.Size = new System.Drawing.Size(86, 20);
            this.childForm2Button.Text = "Child Form #2";
            this.childForm2Button.Click += new System.EventHandler(this.childForm2Button_Click);
            // 
            // floatingFormButton
            // 
            this.floatingFormButton.Name = "floatingFormButton";
            this.floatingFormButton.Size = new System.Drawing.Size(84, 20);
            this.floatingFormButton.Text = "Floating Form";
            this.floatingFormButton.Click += new System.EventHandler(this.floatingFormButton_Click);
            // 
            // childFormControlButton
            // 
            this.childFormControlButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.minimizeAllButton,
            this.showAllButton});
            this.childFormControlButton.Name = "childFormControlButton";
            this.childFormControlButton.Size = new System.Drawing.Size(107, 20);
            this.childFormControlButton.Text = "Child Form Control";
            // 
            // minimizeAllButton
            // 
            this.minimizeAllButton.Name = "minimizeAllButton";
            this.minimizeAllButton.Size = new System.Drawing.Size(152, 22);
            this.minimizeAllButton.Text = "Minimize All";
            this.minimizeAllButton.Click += new System.EventHandler(this.minimizeAllButton_Click);
            // 
            // showAllButton
            // 
            this.showAllButton.Name = "showAllButton";
            this.showAllButton.Size = new System.Drawing.Size(152, 22);
            this.showAllButton.Text = "Show All";
            this.showAllButton.Click += new System.EventHandler(this.showAllButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 393);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem childForm1Button;
        private System.Windows.Forms.ToolStripMenuItem childForm2Button;
        private System.Windows.Forms.ToolStripMenuItem floatingFormButton;
        private System.Windows.Forms.ToolStripMenuItem childFormControlButton;
        private System.Windows.Forms.ToolStripMenuItem minimizeAllButton;
        private System.Windows.Forms.ToolStripMenuItem showAllButton;
    }
}

