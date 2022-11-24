namespace MPL2_QueryBrowser
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
            this.connectButton = new System.Windows.Forms.ToolStripMenuItem();
            this.disconnectButton = new System.Windows.Forms.ToolStripMenuItem();
            this.queryTextBox = new System.Windows.Forms.TextBox();
            this.executeQueryInfoLabel = new System.Windows.Forms.Label();
            this.runQueryButton = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.statusInfoLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.databaseSchemaTreeView = new System.Windows.Forms.TreeView();
            this.databaseSchemaInfoLabel = new System.Windows.Forms.Label();
            this.mainDataGrid = new System.Windows.Forms.DataGridView();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectButton,
            this.disconnectButton});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(705, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // connectButton
            // 
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(59, 20);
            this.connectButton.Text = "Connect";
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // disconnectButton
            // 
            this.disconnectButton.Name = "disconnectButton";
            this.disconnectButton.Size = new System.Drawing.Size(71, 20);
            this.disconnectButton.Text = "Disconnect";
            this.disconnectButton.Visible = false;
            this.disconnectButton.Click += new System.EventHandler(this.disconnectButton_Click);
            // 
            // queryTextBox
            // 
            this.queryTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.queryTextBox.Location = new System.Drawing.Point(12, 50);
            this.queryTextBox.Multiline = true;
            this.queryTextBox.Name = "queryTextBox";
            this.queryTextBox.Size = new System.Drawing.Size(490, 99);
            this.queryTextBox.TabIndex = 0;
            // 
            // executeQueryInfoLabel
            // 
            this.executeQueryInfoLabel.AutoSize = true;
            this.executeQueryInfoLabel.Location = new System.Drawing.Point(9, 34);
            this.executeQueryInfoLabel.Name = "executeQueryInfoLabel";
            this.executeQueryInfoLabel.Size = new System.Drawing.Size(78, 13);
            this.executeQueryInfoLabel.TabIndex = 1;
            this.executeQueryInfoLabel.Text = "Execute query:";
            // 
            // runQueryButton
            // 
            this.runQueryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.runQueryButton.Location = new System.Drawing.Point(330, 155);
            this.runQueryButton.Name = "runQueryButton";
            this.runQueryButton.Size = new System.Drawing.Size(172, 23);
            this.runQueryButton.TabIndex = 2;
            this.runQueryButton.Text = "Run Query";
            this.runQueryButton.UseVisualStyleBackColor = true;
            this.runQueryButton.Click += new System.EventHandler(this.runQueryButton_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusInfoLabel,
            this.statusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 360);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(705, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // statusInfoLabel
            // 
            this.statusInfoLabel.Name = "statusInfoLabel";
            this.statusInfoLabel.Size = new System.Drawing.Size(42, 17);
            this.statusInfoLabel.Text = "Status:";
            // 
            // statusLabel
            // 
            this.statusLabel.ForeColor = System.Drawing.Color.Red;
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(77, 17);
            this.statusLabel.Text = "Not connected";
            // 
            // databaseSchemaTreeView
            // 
            this.databaseSchemaTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.databaseSchemaTreeView.Location = new System.Drawing.Point(508, 50);
            this.databaseSchemaTreeView.Name = "databaseSchemaTreeView";
            this.databaseSchemaTreeView.Size = new System.Drawing.Size(185, 128);
            this.databaseSchemaTreeView.TabIndex = 4;
            // 
            // databaseSchemaInfoLabel
            // 
            this.databaseSchemaInfoLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.databaseSchemaInfoLabel.AutoSize = true;
            this.databaseSchemaInfoLabel.Location = new System.Drawing.Point(505, 34);
            this.databaseSchemaInfoLabel.Name = "databaseSchemaInfoLabel";
            this.databaseSchemaInfoLabel.Size = new System.Drawing.Size(131, 13);
            this.databaseSchemaInfoLabel.TabIndex = 5;
            this.databaseSchemaInfoLabel.Text = "Current database schema:";
            // 
            // mainDataGrid
            // 
            this.mainDataGrid.AllowUserToAddRows = false;
            this.mainDataGrid.AllowUserToDeleteRows = false;
            this.mainDataGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mainDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.mainDataGrid.Location = new System.Drawing.Point(12, 184);
            this.mainDataGrid.Name = "mainDataGrid";
            this.mainDataGrid.ReadOnly = true;
            this.mainDataGrid.Size = new System.Drawing.Size(681, 173);
            this.mainDataGrid.TabIndex = 6;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(705, 382);
            this.Controls.Add(this.mainDataGrid);
            this.Controls.Add(this.databaseSchemaInfoLabel);
            this.Controls.Add(this.databaseSchemaTreeView);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.runQueryButton);
            this.Controls.Add(this.executeQueryInfoLabel);
            this.Controls.Add(this.queryTextBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Query Browser";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainDataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem connectButton;
        private System.Windows.Forms.ToolStripMenuItem disconnectButton;
        private System.Windows.Forms.TextBox queryTextBox;
        private System.Windows.Forms.Label executeQueryInfoLabel;
        private System.Windows.Forms.Button runQueryButton;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel statusInfoLabel;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.TreeView databaseSchemaTreeView;
        private System.Windows.Forms.Label databaseSchemaInfoLabel;
        private System.Windows.Forms.DataGridView mainDataGrid;
    }
}

