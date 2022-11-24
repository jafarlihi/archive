using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FileManager
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            PopulateDrives();
            InitializeImageLists();
            InitListViewOptions();
        }

        private void InitListViewOptions()
        {
            mainListView.View = View.List;
            mainListView.ContextMenuStrip = mainListViewContextMenu;
            mainListView.MouseDoubleClick += new MouseEventHandler(mainListView_MouseDoubleClick);
        }

        private void InitializeImageLists()
        {
            ImageList listViewImageList = new ImageList();

            listViewImageList.Images.Add("directory", Properties.Resources.folder_256);
            listViewImageList.Images.Add("exe", Properties.Resources.exe_256);
            listViewImageList.Images.Add("image", Properties.Resources.image_2_256);
            listViewImageList.Images.Add("text", Properties.Resources.text_file_3_256);
            listViewImageList.Images.Add("audio", Properties.Resources.audio_file_256);
            listViewImageList.Images.Add("video", Properties.Resources.video_file_256);
            listViewImageList.Images.Add("file", Properties.Resources.blank_file_256);

            mainListView.LargeImageList = listViewImageList;

            ImageList listViewImageListSmall = listViewImageList;
            listViewImageListSmall.ImageSize = new Size(16, 16);
            mainListView.SmallImageList = listViewImageListSmall;
        }

        private void PopulateDrives()
        {
            mainTreeView.Nodes.Clear();
            string[] drives = Environment.GetLogicalDrives();

            foreach (string drive in drives)
            {
                TreeNode node = new TreeNode(drive);
                mainTreeView.Nodes.Add(node);
                mainTreeView.Nodes[mainTreeView.Nodes.Count - 1].Nodes.Add("");
            }
        }

        private void ExpandTree(TreeNode node)
        {
            node.Nodes.Clear();
            string address = node.FullPath;
            DirectoryInfo directory = new DirectoryInfo(address);
            DirectoryInfo[] subDirectories = directory.GetDirectories();

            mainTreeView.BeginUpdate();
            foreach (DirectoryInfo subDirectory in subDirectories)
            {
                TreeNode currentNode = node.Nodes.Add(subDirectory.Name);
                try { if (subDirectory.GetDirectories().Length > 0) { currentNode.Nodes.Add(""); } }
                catch { }
            }
            mainTreeView.EndUpdate();
        }

        private void mainTreeView_AfterExpand(object sender, TreeViewEventArgs e)
        {
            ExpandTree(e.Node);
        }

        private void AddFiles(FileInfo[] files)
        {
            foreach (FileInfo file in files)
            {
                switch (file.Extension.ToLower())
                {
                    case ".exe": mainListView.Items.Add(file.Name, "exe"); break;
                    case ".png": case ".bmp": case ".jpg": case ".jpeg": case ".svg": mainListView.Items.Add(file.Name, "image"); break;
                    case ".txt": case ".pdf": case ".doc": case ".rtf": case ".ini": mainListView.Items.Add(file.Name, "text"); break;
                    case ".mp3": case ".wav": case ".flac": mainListView.Items.Add(file.Name, "audio"); break;
                    case ".mp4": case ".avi": case ".flv": case ".wmv": case ".mov": mainListView.Items.Add(file.Name, "video"); break;
                    default: mainListView.Items.Add(file.Name, "file"); break;
                }
            }
        }

        private void PopulateListView(DirectoryInfo directory)
        {
            try
            {
                mainListView.Items.Clear();

                DirectoryInfo[] subDirectories = directory.GetDirectories();
                foreach (DirectoryInfo subDirectory in subDirectories) { mainListView.Items.Add(subDirectory.Name, "directory"); }

                FileInfo[] files = directory.GetFiles();
                AddFiles(files);
            }
            catch (Exception error) { MessageBox.Show(error.ToString()); }
        }

        private void mainTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            addressBar.Text = e.Node.FullPath;
            PopulateListView(new DirectoryInfo(e.Node.FullPath));
        }

        private void mainListView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            ListViewHitTestInfo hitInfo = mainListView.HitTest(e.X, e.Y);
            ListViewItem hitItem = hitInfo.Item;

            if (hitItem != null) {
                var selected = mainTreeView.SelectedNode.FullPath + "\\" + hitItem.Text;
                DirectoryInfo directory = new DirectoryInfo(selected);

                if (directory.Exists) {
                    PopulateListView(directory);

                    try
                    {
                        var selectedNode = mainTreeView.SelectedNode.Nodes.OfType<TreeNode>().First(node => node.Text.Equals(hitItem.Text));
                        mainTreeView.SelectedNode = selectedNode;
                        selectedNode.Expand();
                    }
                    catch { }
                }
                else
                {
                    try { System.Diagnostics.Process.Start(selected); }
                    catch (Exception error) { MessageBox.Show(error.ToString()); }
                }
            }
        }

        private void cmViewList_Click(object sender, EventArgs e)
        {
            if (mainListView.View != View.List)
            {
                cmViewTile.Checked = false;
                mainListView.View = View.List;
            } else { cmViewList.Checked = true; }
        }

        private void cmViewTile_Click(object sender, EventArgs e)
        {
            if (mainListView.View != View.Tile)
            {
                cmViewList.Checked = false;
                mainListView.View = View.Tile;
            } else { cmViewTile.Checked = true; }
        }

        static double ConvertBytesToMegabytes(long bytes) { return (bytes / 1024f) / 1024f; }

        private void mainListView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            cmCopy.Enabled = false;

            statusSelectedCountInfo.Visible = false; statusSelectedCount.Visible = false;
            statusSelectedInfo.Visible = false; statusSelected.Visible = false;
            statusDateInfo.Visible = false; statusDate.Visible = false;
            statusSizeInfo.Visible = false; statusSize.Visible = false;

            if (mainListView.SelectedItems.Count > 1)
            {
                cmCopy.Enabled = true;

                statusSelectedCount.Text = Convert.ToString(mainListView.SelectedItems.Count);
                statusSelectedCountInfo.Visible = true;
                statusSelectedCount.Visible = true;
            }
            else
            {
                statusSelectedCountInfo.Visible = false;
                statusSelectedCount.Visible = false;

                if (mainListView.SelectedItems.Count == 1)
                {
                    cmCopy.Enabled = true;

                    string selectionPath = mainTreeView.SelectedNode.FullPath + "\\" + mainListView.SelectedItems[0].Text;
                    FileInfo selectionInfo = new FileInfo(selectionPath);

                    string selection = mainListView.SelectedItems[0].Text;
                    string date = Convert.ToString(selectionInfo.LastWriteTime);

                    statusSelected.Text = selection;
                    statusSelectedInfo.Visible = true;
                    statusSelected.Visible = true;

                    statusDate.Text = date;
                    statusDateInfo.Visible = true;
                    statusDate.Visible = true;

                    try
                    {
                        statusSize.Text = Convert.ToString(ConvertBytesToMegabytes(selectionInfo.Length)) + " MB";
                        statusSizeInfo.Visible = true;
                        statusSize.Visible = true;
                    } catch { statusSizeInfo.Visible = false; statusSize.Visible = false; }
                }
            }
        }

        private void cmRefresh_Click(object sender, EventArgs e)
        {
            mainListView.Refresh();
        }

        private void CopyFiles(string[] ListFilePaths)
        {
            System.Collections.Specialized.StringCollection FileCollection = new System.Collections.Specialized.StringCollection();
            foreach (string FileToCopy in ListFilePaths) { FileCollection.Add(FileToCopy); }
            Clipboard.SetFileDropList(FileCollection);
        }

        private void cmCopy_Click(object sender, EventArgs e)
        {
            List<string> files = new List<string>();
            foreach (ListViewItem file in mainListView.SelectedItems)
            {
                files.Add(mainTreeView.SelectedNode.FullPath + "\\" + file.Text);
            }
            CopyFiles(files.ToArray());

            cmPaste.Enabled = true;
        }

        private void cmPaste_Click(object sender, EventArgs e)
        {
            var files = Clipboard.GetFileDropList();
            foreach (string file in files)
            {
                int fileStringPosition = file.LastIndexOf("\\") + 1;
                string fileName = file.Substring(fileStringPosition, file.Length - fileStringPosition);

                File.Copy(file, mainTreeView.SelectedNode.FullPath + "\\" + fileName);
            }
            PopulateListView(new DirectoryInfo(mainTreeView.SelectedNode.FullPath));
        }
    }
}
