namespace MPL2_Paint
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.fileNew = new System.Windows.Forms.ToolStripMenuItem();
            this.fileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.fileSave = new System.Windows.Forms.ToolStripMenuItem();
            this.fileSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.fileSetWallpaper = new System.Windows.Forms.ToolStripMenuItem();
            this.fileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.viewZoomIn = new System.Windows.Forms.ToolStripMenuItem();
            this.viewZoomOut = new System.Windows.Forms.ToolStripMenuItem();
            this.view100Zoom = new System.Windows.Forms.ToolStripMenuItem();
            this.statusCheckBox = new System.Windows.Forms.CheckBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.mousePositionInfoLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.mousePositionLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.mainColor1Indicator = new System.Windows.Forms.ToolStripTextBox();
            this.mainColor1Button = new System.Windows.Forms.ToolStripButton();
            this.mainColor2Indicator = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.thicknessLabel = new System.Windows.Forms.ToolStripLabel();
            this.thicknessComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.switchModeFreehand = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.switchModeLine = new System.Windows.Forms.ToolStripButton();
            this.switchModeRectangle = new System.Windows.Forms.ToolStripButton();
            this.switchModeEllipse = new System.Windows.Forms.ToolStripButton();
            this.mainPictureBox = new System.Windows.Forms.PictureBox();
            this.imageResolutionInfoLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.imageResolutionLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.separatorLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.toolStripMenuItem2});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(710, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileNew,
            this.fileOpen,
            this.fileSave,
            this.fileSaveAs,
            this.fileSetWallpaper,
            this.fileExit});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(35, 20);
            this.toolStripMenuItem1.Text = "File";
            // 
            // fileNew
            // 
            this.fileNew.Name = "fileNew";
            this.fileNew.Size = new System.Drawing.Size(153, 22);
            this.fileNew.Text = "New";
            this.fileNew.Click += new System.EventHandler(this.fileNew_Click);
            // 
            // fileOpen
            // 
            this.fileOpen.Name = "fileOpen";
            this.fileOpen.Size = new System.Drawing.Size(153, 22);
            this.fileOpen.Text = "Open";
            this.fileOpen.Click += new System.EventHandler(this.fileOpen_Click);
            // 
            // fileSave
            // 
            this.fileSave.Name = "fileSave";
            this.fileSave.Size = new System.Drawing.Size(153, 22);
            this.fileSave.Text = "Save";
            this.fileSave.Click += new System.EventHandler(this.fileSave_Click);
            // 
            // fileSaveAs
            // 
            this.fileSaveAs.Name = "fileSaveAs";
            this.fileSaveAs.Size = new System.Drawing.Size(153, 22);
            this.fileSaveAs.Text = "Save as";
            this.fileSaveAs.Click += new System.EventHandler(this.fileSaveAs_Click);
            // 
            // fileSetWallpaper
            // 
            this.fileSetWallpaper.Name = "fileSetWallpaper";
            this.fileSetWallpaper.Size = new System.Drawing.Size(153, 22);
            this.fileSetWallpaper.Text = "Set as wallpaper";
            this.fileSetWallpaper.Click += new System.EventHandler(this.fileSetWallpaper_Click);
            // 
            // fileExit
            // 
            this.fileExit.Name = "fileExit";
            this.fileExit.Size = new System.Drawing.Size(153, 22);
            this.fileExit.Text = "Exit";
            this.fileExit.Click += new System.EventHandler(this.fileExit_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.viewZoomIn,
            this.viewZoomOut,
            this.view100Zoom});
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(41, 20);
            this.toolStripMenuItem2.Text = "View";
            // 
            // viewZoomIn
            // 
            this.viewZoomIn.Name = "viewZoomIn";
            this.viewZoomIn.Size = new System.Drawing.Size(131, 22);
            this.viewZoomIn.Text = "Zoom in";
            this.viewZoomIn.Click += new System.EventHandler(this.viewZoomIn_Click);
            // 
            // viewZoomOut
            // 
            this.viewZoomOut.Name = "viewZoomOut";
            this.viewZoomOut.Size = new System.Drawing.Size(131, 22);
            this.viewZoomOut.Text = "Zoom out";
            this.viewZoomOut.Click += new System.EventHandler(this.viewZoomOut_Click);
            // 
            // view100Zoom
            // 
            this.view100Zoom.Name = "view100Zoom";
            this.view100Zoom.Size = new System.Drawing.Size(131, 22);
            this.view100Zoom.Text = "100% zoom";
            this.view100Zoom.Click += new System.EventHandler(this.view100Zoom_Click);
            // 
            // statusCheckBox
            // 
            this.statusCheckBox.AutoSize = true;
            this.statusCheckBox.Checked = true;
            this.statusCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.statusCheckBox.Location = new System.Drawing.Point(90, 4);
            this.statusCheckBox.Name = "statusCheckBox";
            this.statusCheckBox.Size = new System.Drawing.Size(74, 17);
            this.statusCheckBox.TabIndex = 1;
            this.statusCheckBox.Text = "Status bar";
            this.statusCheckBox.UseVisualStyleBackColor = true;
            this.statusCheckBox.CheckedChanged += new System.EventHandler(this.statusCheckBox_CheckedChanged);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mousePositionInfoLabel,
            this.mousePositionLabel,
            this.separatorLabel,
            this.imageResolutionInfoLabel,
            this.imageResolutionLabel,
            this.toolStripStatusLabel2});
            this.statusStrip1.Location = new System.Drawing.Point(0, 442);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(710, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // mousePositionInfoLabel
            // 
            this.mousePositionInfoLabel.Name = "mousePositionInfoLabel";
            this.mousePositionInfoLabel.Size = new System.Drawing.Size(82, 17);
            this.mousePositionInfoLabel.Text = "Mouse Position:";
            // 
            // mousePositionLabel
            // 
            this.mousePositionLabel.Name = "mousePositionLabel";
            this.mousePositionLabel.Size = new System.Drawing.Size(29, 17);
            this.mousePositionLabel.Text = "X : Y";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(419, 17);
            this.toolStripStatusLabel2.Spring = true;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainColor1Indicator,
            this.mainColor1Button,
            this.mainColor2Indicator,
            this.toolStripButton2,
            this.thicknessLabel,
            this.thicknessComboBox,
            this.switchModeFreehand,
            this.toolStripButton4,
            this.switchModeLine,
            this.switchModeRectangle,
            this.switchModeEllipse});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(710, 25);
            this.toolStrip1.TabIndex = 4;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // mainColor1Indicator
            // 
            this.mainColor1Indicator.BackColor = System.Drawing.Color.Black;
            this.mainColor1Indicator.Name = "mainColor1Indicator";
            this.mainColor1Indicator.ReadOnly = true;
            this.mainColor1Indicator.Size = new System.Drawing.Size(25, 25);
            // 
            // mainColor1Button
            // 
            this.mainColor1Button.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.mainColor1Button.Image = ((System.Drawing.Image)(resources.GetObject("mainColor1Button.Image")));
            this.mainColor1Button.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.mainColor1Button.Name = "mainColor1Button";
            this.mainColor1Button.Size = new System.Drawing.Size(23, 22);
            this.mainColor1Button.Click += new System.EventHandler(this.mainColor1Button_Click);
            // 
            // mainColor2Indicator
            // 
            this.mainColor2Indicator.BackColor = System.Drawing.Color.White;
            this.mainColor2Indicator.Name = "mainColor2Indicator";
            this.mainColor2Indicator.ReadOnly = true;
            this.mainColor2Indicator.Size = new System.Drawing.Size(25, 25);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Click += new System.EventHandler(this.mainColor2Button_Click);
            // 
            // thicknessLabel
            // 
            this.thicknessLabel.Name = "thicknessLabel";
            this.thicknessLabel.Size = new System.Drawing.Size(57, 22);
            this.thicknessLabel.Text = "Thickness:";
            // 
            // thicknessComboBox
            // 
            this.thicknessComboBox.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.thicknessComboBox.Name = "thicknessComboBox";
            this.thicknessComboBox.Size = new System.Drawing.Size(75, 25);
            this.thicknessComboBox.Text = "1";
            this.thicknessComboBox.TextChanged += new System.EventHandler(this.thicknessComboBox_TextChanged);
            // 
            // switchModeFreehand
            // 
            this.switchModeFreehand.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.switchModeFreehand.Image = ((System.Drawing.Image)(resources.GetObject("switchModeFreehand.Image")));
            this.switchModeFreehand.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.switchModeFreehand.Name = "switchModeFreehand";
            this.switchModeFreehand.Size = new System.Drawing.Size(23, 22);
            this.switchModeFreehand.Click += new System.EventHandler(this.switchModeFreehand_Click);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton4.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton4.Image")));
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton4.Click += new System.EventHandler(this.switchModeEraser_Click);
            // 
            // switchModeLine
            // 
            this.switchModeLine.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.switchModeLine.Image = ((System.Drawing.Image)(resources.GetObject("switchModeLine.Image")));
            this.switchModeLine.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.switchModeLine.Name = "switchModeLine";
            this.switchModeLine.Size = new System.Drawing.Size(23, 22);
            this.switchModeLine.Click += new System.EventHandler(this.switchModeLine_Click);
            // 
            // switchModeRectangle
            // 
            this.switchModeRectangle.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.switchModeRectangle.Image = ((System.Drawing.Image)(resources.GetObject("switchModeRectangle.Image")));
            this.switchModeRectangle.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.switchModeRectangle.Name = "switchModeRectangle";
            this.switchModeRectangle.Size = new System.Drawing.Size(23, 22);
            this.switchModeRectangle.Click += new System.EventHandler(this.switchModeRectangle_Click);
            // 
            // switchModeEllipse
            // 
            this.switchModeEllipse.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.switchModeEllipse.Image = ((System.Drawing.Image)(resources.GetObject("switchModeEllipse.Image")));
            this.switchModeEllipse.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.switchModeEllipse.Name = "switchModeEllipse";
            this.switchModeEllipse.Size = new System.Drawing.Size(23, 22);
            this.switchModeEllipse.Click += new System.EventHandler(this.switchModeEllipse_Click);
            // 
            // mainPictureBox
            // 
            this.mainPictureBox.BackColor = System.Drawing.SystemColors.Control;
            this.mainPictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPictureBox.Location = new System.Drawing.Point(0, 49);
            this.mainPictureBox.Name = "mainPictureBox";
            this.mainPictureBox.Size = new System.Drawing.Size(710, 393);
            this.mainPictureBox.TabIndex = 5;
            this.mainPictureBox.TabStop = false;
            this.mainPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.mainPictureBox_MouseDown);
            this.mainPictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.mainPictureBox_MouseMove);
            this.mainPictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.mainPictureBox_MouseUp);
            // 
            // imageResolutionInfoLabel
            // 
            this.imageResolutionInfoLabel.Name = "imageResolutionInfoLabel";
            this.imageResolutionInfoLabel.Size = new System.Drawing.Size(94, 17);
            this.imageResolutionInfoLabel.Text = "Image Resolution:";
            // 
            // imageResolutionLabel
            // 
            this.imageResolutionLabel.Name = "imageResolutionLabel";
            this.imageResolutionLabel.Size = new System.Drawing.Size(29, 17);
            this.imageResolutionLabel.Text = "X : Y";
            // 
            // separatorLabel
            // 
            this.separatorLabel.Name = "separatorLabel";
            this.separatorLabel.Size = new System.Drawing.Size(11, 17);
            this.separatorLabel.Text = "|";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(710, 464);
            this.Controls.Add(this.mainPictureBox);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.statusCheckBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Paint";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainPictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem fileNew;
        private System.Windows.Forms.ToolStripMenuItem fileOpen;
        private System.Windows.Forms.ToolStripMenuItem fileSave;
        private System.Windows.Forms.ToolStripMenuItem fileSaveAs;
        private System.Windows.Forms.ToolStripMenuItem fileSetWallpaper;
        private System.Windows.Forms.ToolStripMenuItem fileExit;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem viewZoomIn;
        private System.Windows.Forms.ToolStripMenuItem viewZoomOut;
        private System.Windows.Forms.ToolStripMenuItem view100Zoom;
        private System.Windows.Forms.CheckBox statusCheckBox;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel mousePositionInfoLabel;
        private System.Windows.Forms.ToolStripStatusLabel mousePositionLabel;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripTextBox mainColor1Indicator;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripTextBox mainColor2Indicator;
        private System.Windows.Forms.ToolStripButton mainColor1Button;
        private System.Windows.Forms.ToolStripLabel thicknessLabel;
        private System.Windows.Forms.ToolStripComboBox thicknessComboBox;
        private System.Windows.Forms.ToolStripButton switchModeFreehand;
        private System.Windows.Forms.ToolStripButton toolStripButton4;
        private System.Windows.Forms.ToolStripButton switchModeLine;
        private System.Windows.Forms.ToolStripButton switchModeRectangle;
        private System.Windows.Forms.ToolStripButton switchModeEllipse;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.PictureBox mainPictureBox;
        private System.Windows.Forms.ToolStripStatusLabel imageResolutionInfoLabel;
        private System.Windows.Forms.ToolStripStatusLabel imageResolutionLabel;
        private System.Windows.Forms.ToolStripStatusLabel separatorLabel;
    }
}

