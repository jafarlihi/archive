namespace FileManager
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
            this.components = new System.ComponentModel.Container();
            this.mainTreeView = new System.Windows.Forms.TreeView();
            this.mainListView = new System.Windows.Forms.ListView();
            this.addressBar = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.statusSelectedInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSelected = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusDateInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusDate = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSizeInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSize = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSelectedCountInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSelectedCount = new System.Windows.Forms.ToolStripStatusLabel();
            this.mainListViewContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.cmCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.cmPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.cmView = new System.Windows.Forms.ToolStripMenuItem();
            this.cmViewList = new System.Windows.Forms.ToolStripMenuItem();
            this.cmViewTile = new System.Windows.Forms.ToolStripMenuItem();
            this.cmRefresh = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1.SuspendLayout();
            this.mainListViewContextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainTreeView
            // 
            this.mainTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.mainTreeView.Location = new System.Drawing.Point(12, 38);
            this.mainTreeView.Name = "mainTreeView";
            this.mainTreeView.Size = new System.Drawing.Size(185, 398);
            this.mainTreeView.TabIndex = 0;
            this.mainTreeView.AfterExpand += new System.Windows.Forms.TreeViewEventHandler(this.mainTreeView_AfterExpand);
            this.mainTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.mainTreeView_AfterSelect);
            // 
            // mainListView
            // 
            this.mainListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mainListView.Location = new System.Drawing.Point(203, 38);
            this.mainListView.Name = "mainListView";
            this.mainListView.Size = new System.Drawing.Size(689, 398);
            this.mainListView.TabIndex = 1;
            this.mainListView.UseCompatibleStateImageBehavior = false;
            this.mainListView.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.mainListView_ItemSelectionChanged);
            // 
            // addressBar
            // 
            this.addressBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addressBar.Location = new System.Drawing.Point(12, 12);
            this.addressBar.Name = "addressBar";
            this.addressBar.ReadOnly = true;
            this.addressBar.Size = new System.Drawing.Size(880, 20);
            this.addressBar.TabIndex = 2;
            // 
            // statusStrip1
            // 
            this.statusStrip1.BackColor = System.Drawing.Color.DimGray;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusSelectedInfo,
            this.statusSelected,
            this.statusDateInfo,
            this.statusDate,
            this.statusSizeInfo,
            this.statusSize,
            this.statusSelectedCountInfo,
            this.statusSelectedCount});
            this.statusStrip1.Location = new System.Drawing.Point(0, 442);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(904, 22);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "mainStatusBar";
            // 
            // statusSelectedInfo
            // 
            this.statusSelectedInfo.ForeColor = System.Drawing.Color.White;
            this.statusSelectedInfo.Name = "statusSelectedInfo";
            this.statusSelectedInfo.Size = new System.Drawing.Size(59, 17);
            this.statusSelectedInfo.Text = "| Selected:";
            this.statusSelectedInfo.Visible = false;
            // 
            // statusSelected
            // 
            this.statusSelected.ForeColor = System.Drawing.Color.White;
            this.statusSelected.Name = "statusSelected";
            this.statusSelected.Size = new System.Drawing.Size(55, 17);
            this.statusSelected.Text = "[selected]";
            this.statusSelected.Visible = false;
            // 
            // statusDateInfo
            // 
            this.statusDateInfo.ForeColor = System.Drawing.Color.White;
            this.statusDateInfo.Name = "statusDateInfo";
            this.statusDateInfo.Size = new System.Drawing.Size(100, 17);
            this.statusDateInfo.Text = "| Modification date:";
            this.statusDateInfo.Visible = false;
            // 
            // statusDate
            // 
            this.statusDate.ForeColor = System.Drawing.Color.White;
            this.statusDate.Name = "statusDate";
            this.statusDate.Size = new System.Drawing.Size(37, 17);
            this.statusDate.Text = "[date]";
            this.statusDate.Visible = false;
            // 
            // statusSizeInfo
            // 
            this.statusSizeInfo.ForeColor = System.Drawing.Color.White;
            this.statusSizeInfo.Name = "statusSizeInfo";
            this.statusSizeInfo.Size = new System.Drawing.Size(37, 17);
            this.statusSizeInfo.Text = "| Size:";
            this.statusSizeInfo.Visible = false;
            // 
            // statusSize
            // 
            this.statusSize.ForeColor = System.Drawing.Color.White;
            this.statusSize.Name = "statusSize";
            this.statusSize.Size = new System.Drawing.Size(33, 17);
            this.statusSize.Text = "[size]";
            this.statusSize.Visible = false;
            // 
            // statusSelectedCountInfo
            // 
            this.statusSelectedCountInfo.ForeColor = System.Drawing.Color.White;
            this.statusSelectedCountInfo.Name = "statusSelectedCountInfo";
            this.statusSelectedCountInfo.Size = new System.Drawing.Size(89, 17);
            this.statusSelectedCountInfo.Text = "| Selected count:";
            this.statusSelectedCountInfo.Visible = false;
            // 
            // statusSelectedCount
            // 
            this.statusSelectedCount.ForeColor = System.Drawing.Color.White;
            this.statusSelectedCount.Name = "statusSelectedCount";
            this.statusSelectedCount.Size = new System.Drawing.Size(84, 17);
            this.statusSelectedCount.Text = "[selectedCount]";
            this.statusSelectedCount.Visible = false;
            // 
            // mainListViewContextMenu
            // 
            this.mainListViewContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmCopy,
            this.cmPaste,
            this.toolStripSeparator1,
            this.cmView,
            this.cmRefresh});
            this.mainListViewContextMenu.Name = "mainListViewContextMenu";
            this.mainListViewContextMenu.Size = new System.Drawing.Size(153, 120);
            // 
            // cmCopy
            // 
            this.cmCopy.Enabled = false;
            this.cmCopy.Name = "cmCopy";
            this.cmCopy.Size = new System.Drawing.Size(152, 22);
            this.cmCopy.Text = "Copy";
            this.cmCopy.Click += new System.EventHandler(this.cmCopy_Click);
            // 
            // cmPaste
            // 
            this.cmPaste.Enabled = false;
            this.cmPaste.Name = "cmPaste";
            this.cmPaste.Size = new System.Drawing.Size(152, 22);
            this.cmPaste.Text = "Paste";
            this.cmPaste.Click += new System.EventHandler(this.cmPaste_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
            // 
            // cmView
            // 
            this.cmView.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmViewList,
            this.cmViewTile});
            this.cmView.Name = "cmView";
            this.cmView.Size = new System.Drawing.Size(152, 22);
            this.cmView.Text = "View";
            // 
            // cmViewList
            // 
            this.cmViewList.Checked = true;
            this.cmViewList.CheckOnClick = true;
            this.cmViewList.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cmViewList.Name = "cmViewList";
            this.cmViewList.Size = new System.Drawing.Size(90, 22);
            this.cmViewList.Text = "List";
            this.cmViewList.Click += new System.EventHandler(this.cmViewList_Click);
            // 
            // cmViewTile
            // 
            this.cmViewTile.CheckOnClick = true;
            this.cmViewTile.Name = "cmViewTile";
            this.cmViewTile.Size = new System.Drawing.Size(90, 22);
            this.cmViewTile.Text = "Tile";
            this.cmViewTile.Click += new System.EventHandler(this.cmViewTile_Click);
            // 
            // cmRefresh
            // 
            this.cmRefresh.Name = "cmRefresh";
            this.cmRefresh.Size = new System.Drawing.Size(152, 22);
            this.cmRefresh.Text = "Refresh";
            this.cmRefresh.Click += new System.EventHandler(this.cmRefresh_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(904, 464);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.addressBar);
            this.Controls.Add(this.mainListView);
            this.Controls.Add(this.mainTreeView);
            this.DoubleBuffered = true;
            this.Name = "MainForm";
            this.Text = "File Manager";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.mainListViewContextMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView mainTreeView;
        private System.Windows.Forms.ListView mainListView;
        private System.Windows.Forms.TextBox addressBar;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ContextMenuStrip mainListViewContextMenu;
        private System.Windows.Forms.ToolStripMenuItem cmCopy;
        private System.Windows.Forms.ToolStripMenuItem cmPaste;
        private System.Windows.Forms.ToolStripMenuItem cmRefresh;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem cmView;
        private System.Windows.Forms.ToolStripMenuItem cmViewList;
        private System.Windows.Forms.ToolStripMenuItem cmViewTile;
        private System.Windows.Forms.ToolStripStatusLabel statusDateInfo;
        private System.Windows.Forms.ToolStripStatusLabel statusDate;
        private System.Windows.Forms.ToolStripStatusLabel statusSelectedInfo;
        private System.Windows.Forms.ToolStripStatusLabel statusSelected;
        private System.Windows.Forms.ToolStripStatusLabel statusSizeInfo;
        private System.Windows.Forms.ToolStripStatusLabel statusSize;
        private System.Windows.Forms.ToolStripStatusLabel statusSelectedCountInfo;
        private System.Windows.Forms.ToolStripStatusLabel statusSelectedCount;
    }
}

