namespace MPL2_QueryBrowser
{
    partial class ConnectForm
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
            this.connectButton = new System.Windows.Forms.Button();
            this.passwordTextBox = new System.Windows.Forms.TextBox();
            this.databaseTextBox = new System.Windows.Forms.TextBox();
            this.portTextBox = new System.Windows.Forms.TextBox();
            this.usernameTextBox = new System.Windows.Forms.TextBox();
            this.serverTextBox = new System.Windows.Forms.TextBox();
            this.portInfoLabel = new System.Windows.Forms.Label();
            this.serverInfoLabel = new System.Windows.Forms.Label();
            this.databaseInfoLabel = new System.Windows.Forms.Label();
            this.usernameInfoLabel = new System.Windows.Forms.Label();
            this.passwordInfoLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(84, 137);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(208, 23);
            this.connectButton.TabIndex = 6;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // passwordTextBox
            // 
            this.passwordTextBox.Location = new System.Drawing.Point(84, 102);
            this.passwordTextBox.Name = "passwordTextBox";
            this.passwordTextBox.Size = new System.Drawing.Size(208, 20);
            this.passwordTextBox.TabIndex = 5;
            // 
            // databaseTextBox
            // 
            this.databaseTextBox.Location = new System.Drawing.Point(84, 40);
            this.databaseTextBox.Name = "databaseTextBox";
            this.databaseTextBox.Size = new System.Drawing.Size(208, 20);
            this.databaseTextBox.TabIndex = 3;
            // 
            // portTextBox
            // 
            this.portTextBox.Location = new System.Drawing.Point(248, 9);
            this.portTextBox.Name = "portTextBox";
            this.portTextBox.Size = new System.Drawing.Size(44, 20);
            this.portTextBox.TabIndex = 2;
            // 
            // usernameTextBox
            // 
            this.usernameTextBox.Location = new System.Drawing.Point(84, 71);
            this.usernameTextBox.Name = "usernameTextBox";
            this.usernameTextBox.Size = new System.Drawing.Size(208, 20);
            this.usernameTextBox.TabIndex = 4;
            // 
            // serverTextBox
            // 
            this.serverTextBox.Location = new System.Drawing.Point(84, 9);
            this.serverTextBox.Name = "serverTextBox";
            this.serverTextBox.Size = new System.Drawing.Size(123, 20);
            this.serverTextBox.TabIndex = 1;
            // 
            // portInfoLabel
            // 
            this.portInfoLabel.AutoSize = true;
            this.portInfoLabel.Location = new System.Drawing.Point(213, 12);
            this.portInfoLabel.Name = "portInfoLabel";
            this.portInfoLabel.Size = new System.Drawing.Size(29, 13);
            this.portInfoLabel.TabIndex = 6;
            this.portInfoLabel.Text = "Port:";
            // 
            // serverInfoLabel
            // 
            this.serverInfoLabel.AutoSize = true;
            this.serverInfoLabel.Location = new System.Drawing.Point(27, 12);
            this.serverInfoLabel.Name = "serverInfoLabel";
            this.serverInfoLabel.Size = new System.Drawing.Size(41, 13);
            this.serverInfoLabel.TabIndex = 7;
            this.serverInfoLabel.Text = "Server:";
            // 
            // databaseInfoLabel
            // 
            this.databaseInfoLabel.AutoSize = true;
            this.databaseInfoLabel.Location = new System.Drawing.Point(12, 43);
            this.databaseInfoLabel.Name = "databaseInfoLabel";
            this.databaseInfoLabel.Size = new System.Drawing.Size(56, 13);
            this.databaseInfoLabel.TabIndex = 8;
            this.databaseInfoLabel.Text = "Database:";
            // 
            // usernameInfoLabel
            // 
            this.usernameInfoLabel.AutoSize = true;
            this.usernameInfoLabel.Location = new System.Drawing.Point(10, 74);
            this.usernameInfoLabel.Name = "usernameInfoLabel";
            this.usernameInfoLabel.Size = new System.Drawing.Size(58, 13);
            this.usernameInfoLabel.TabIndex = 9;
            this.usernameInfoLabel.Text = "Username:";
            // 
            // passwordInfoLabel
            // 
            this.passwordInfoLabel.AutoSize = true;
            this.passwordInfoLabel.Location = new System.Drawing.Point(12, 105);
            this.passwordInfoLabel.Name = "passwordInfoLabel";
            this.passwordInfoLabel.Size = new System.Drawing.Size(56, 13);
            this.passwordInfoLabel.TabIndex = 10;
            this.passwordInfoLabel.Text = "Password:";
            // 
            // ConnectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(311, 168);
            this.Controls.Add(this.passwordInfoLabel);
            this.Controls.Add(this.usernameInfoLabel);
            this.Controls.Add(this.databaseInfoLabel);
            this.Controls.Add(this.serverInfoLabel);
            this.Controls.Add(this.portInfoLabel);
            this.Controls.Add(this.serverTextBox);
            this.Controls.Add(this.usernameTextBox);
            this.Controls.Add(this.portTextBox);
            this.Controls.Add(this.databaseTextBox);
            this.Controls.Add(this.passwordTextBox);
            this.Controls.Add(this.connectButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "ConnectForm";
            this.Text = "Connect";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.TextBox passwordTextBox;
        private System.Windows.Forms.TextBox databaseTextBox;
        private System.Windows.Forms.TextBox portTextBox;
        private System.Windows.Forms.TextBox usernameTextBox;
        private System.Windows.Forms.TextBox serverTextBox;
        private System.Windows.Forms.Label portInfoLabel;
        private System.Windows.Forms.Label serverInfoLabel;
        private System.Windows.Forms.Label databaseInfoLabel;
        private System.Windows.Forms.Label usernameInfoLabel;
        private System.Windows.Forms.Label passwordInfoLabel;
    }
}