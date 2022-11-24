using Microsoft.Win32;
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;


namespace MPL2_Paint
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            InitializeImage();
            InitializeTrackBar();
            UpdatePens();
        }

        private void InitializeImage(int width = 750, int height = 450)
        {
            Bitmap newImageBitmap = new Bitmap(width, height);
            using (Graphics g = Graphics.FromImage(newImageBitmap)) g.Clear(Color.White);

            mainPictureBox.Image = newImageBitmap;
            UpdateResolutionInfo();
        }

        private void UpdateResolutionInfo()
        {
            imageResolutionLabel.Text = mainPictureBox.Image.Width + " x " + mainPictureBox.Image.Height;
        }

        private void Erase()
        {
            globalZoom = 5;
            firstZoom = true;
            referenceImage = null;
            mainPictureBox.Image = null;
            mainPictureBox.Invalidate();
        }

        public void NewImage(int width, int height)
        {
            Erase();
            InitializeImage(width, height);
            UpdateResolutionInfo();
        }

        private void fileNew_Click(object sender, EventArgs e)
        {
            new NewImageDialog().ShowDialog(this);
        }

        private void fileOpen_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dialog = new OpenFileDialog())
            {
                dialog.Title = "Open Image";
                dialog.Filter = "jpg files (*.jpg)|*.jpg|png files (*.png)|*.png|bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";

                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    Erase();
                    mainPictureBox.Image = Image.FromFile(dialog.FileName);
                }
            }
        }

        private void fileSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.FileName = "untitled.jpg";
            dialog.Filter = "jpg file (*.jpg)|*.jpg|png file (*.png)|*.png|bmp file (*.bmp)|*.bmp|All files (*.*)|*.*";

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                int width = Convert.ToInt32(mainPictureBox.Image.Width);
                int height = Convert.ToInt32(mainPictureBox.Image.Height);
                Bitmap bmp = new Bitmap(width, height);
                mainPictureBox.DrawToBitmap(bmp, new Rectangle(0, 0, width, height));

                ImageFormat saveFormat;

                switch (dialog.Filter)
                {
                    case ".jpg":
                        saveFormat = ImageFormat.Jpeg;
                        break;
                    case ".png":
                        saveFormat = ImageFormat.Png;
                        break;
                    case ".bmp":
                        saveFormat = ImageFormat.Bmp;
                        break;
                    default:
                        saveFormat = ImageFormat.Bmp;
                        break;
                }

                bmp.Save(dialog.FileName, saveFormat);
            }
        }

        private void fileSaveAs_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.FileName = "untitled.jpg";
            dialog.Filter = "jpg file (*.jpg)|*.jpg|png file (*.png)|*.png|bmp file (*.bmp)|*.bmp|All files (*.*)|*.*";

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                int width = Convert.ToInt32(mainPictureBox.Image.Width);
                int height = Convert.ToInt32(mainPictureBox.Image.Height);
                Bitmap bmp = new Bitmap(width, height);
                mainPictureBox.DrawToBitmap(bmp, new Rectangle(0, 0, width, height));

                ImageFormat saveFormat;

                switch (dialog.Filter)
                {
                    case ".jpg":
                        saveFormat = ImageFormat.Jpeg;
                        break;
                    case ".png":
                        saveFormat = ImageFormat.Png;
                        break;
                    case ".bmp":
                        saveFormat = ImageFormat.Bmp;
                        break;
                    default:
                        saveFormat = ImageFormat.Bmp;
                        break;
                }

                bmp.Save(dialog.FileName, saveFormat);
            }
        }

        private void fileExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        int globalZoom = 5;
        bool firstZoom = true;
        Image referenceImage = null;

        // Note: This is not a real zoom as it changes resolution of an image instead of changing zoom factor of the control.
        public Image ZoomImage(Image image, float size)
        {
            float sizeProcessed = size / 5;

            if (firstZoom)
            {
                firstZoom = false;
                referenceImage = image;
                Bitmap newBitmap = new Bitmap(image, Convert.ToInt32(image.Width * sizeProcessed), Convert.ToInt32(image.Height * sizeProcessed));
                return newBitmap;
            }
            else
            {
                Bitmap newBitmap = new Bitmap(referenceImage, Convert.ToInt32(referenceImage.Width * sizeProcessed), Convert.ToInt32(referenceImage.Height * sizeProcessed));
                return newBitmap;
            }
        }

        private void InitializeTrackBar()
        {
            TrackBar tb = new TrackBar();

            ToolStripControlHost controlHost = new ToolStripControlHost(tb);
            statusStrip1.Items.Add(controlHost);

            tb.TickFrequency = 1;
            tb.Minimum = 1;
            tb.Maximum = 10;
            tb.Value = globalZoom;

            tb.ValueChanged += (sender, eventArgs) =>
            {
                globalZoom = tb.Value;
                mainPictureBox.Image = ZoomImage(mainPictureBox.Image, tb.Value);
                UpdateResolutionInfo();
            };
        }

        private void viewZoomIn_Click(object sender, EventArgs e)
        {
            if (globalZoom < 10)
            {
                mainPictureBox.Image = ZoomImage(mainPictureBox.Image, ++globalZoom);
                UpdateResolutionInfo();
                // TODO: Update statusStrip1's TrackBar value
            }
        }

        private void viewZoomOut_Click(object sender, EventArgs e)
        {
            if (globalZoom > 1)
            {
                mainPictureBox.Image = ZoomImage(mainPictureBox.Image, --globalZoom);
                UpdateResolutionInfo();
                // TODO: Update statusStrip1's TrackBar value
            }
        }

        private void view100Zoom_Click(object sender, EventArgs e)
        {
            globalZoom = 5;
            mainPictureBox.Image = ZoomImage(mainPictureBox.Image, globalZoom);
            UpdateResolutionInfo();
            // TODO: Update statusStrip1's TrackBar value
        }

        public bool statusBarEnabled
        {
            get { return statusStrip1.Visible; }
            set { statusCheckBox.Checked = statusStrip1.Visible = value; }
        }

        private void statusCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            statusBarEnabled = !statusBarEnabled;
        }

        enum pencilType { freehand, eraser, line, rectangle, ellipse };
        pencilType currentPencil = pencilType.freehand;

        int lineThickness = 1;

        Color mainColor1 = Color.Black;
        Color mainColor2 = Color.White;

        private void switchModeFreehand_Click(object sender, EventArgs e)
        {
            currentPencil = pencilType.freehand;
            UpdatePens();
        }

        private void switchModeEraser_Click(object sender, EventArgs e)
        {
            currentPencil = pencilType.eraser;
            UpdatePens();
        }

        private void switchModeLine_Click(object sender, EventArgs e)
        {
            currentPencil = pencilType.line;
            UpdatePens();
        }

        private void switchModeRectangle_Click(object sender, EventArgs e)
        {
            currentPencil = pencilType.rectangle;
            UpdatePens();
        }

        private void switchModeEllipse_Click(object sender, EventArgs e)
        {
            currentPencil = pencilType.ellipse;
            UpdatePens();
        }

        private void thicknessComboBox_TextChanged(object sender, EventArgs e)
        {
            try { lineThickness = Convert.ToInt32(thicknessComboBox.Text); }
            catch { thicknessComboBox.Text = "1"; }

            UpdatePens();
        }

        private void UpdateColorIndicators()
        {
            mainColor1Indicator.BackColor = mainColor1;
            mainColor2Indicator.BackColor = mainColor2;
        }

        private void mainColor1Button_Click(object sender, EventArgs e)
        {
            ColorDialog colorWheel = new ColorDialog();
            if (colorWheel.ShowDialog() == DialogResult.OK)
            {
                mainColor1 = colorWheel.Color;
                UpdateColorIndicators();
                UpdatePens();
            }
        }

        private void mainColor2Button_Click(object sender, EventArgs e)
        {
            ColorDialog colorWheel = new ColorDialog();
            if (colorWheel.ShowDialog() == DialogResult.OK)
            {
                mainColor2 = colorWheel.Color;
                UpdateColorIndicators();
                UpdatePens();
            }
        }

        Pen drawPen;

        private void UpdatePens()
        {
            if (currentPencil != pencilType.eraser) drawPen = new Pen(mainColor1, lineThickness);
            else drawPen = new Pen(mainColor2, lineThickness);
        }

        bool currentlyMouseDown = false;
        Point previousMousePosition, originalDownPosition;

        private void mainPictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            originalDownPosition = e.Location;
            previousMousePosition = originalDownPosition;
            currentlyMouseDown = true;
        }

        private void mainPictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (currentlyMouseDown)
            {
                if (currentPencil == pencilType.line)
                {
                    using (Graphics g = Graphics.FromImage(mainPictureBox.Image)) g.DrawLine(drawPen, originalDownPosition, e.Location);
                    mainPictureBox.Refresh();
                }
                else if (currentPencil == pencilType.rectangle)
                {
                    Rectangle rectangle = new Rectangle(originalDownPosition.X <= previousMousePosition.X ? originalDownPosition.X : previousMousePosition.X,
                        originalDownPosition.Y <= previousMousePosition.Y ? originalDownPosition.Y : previousMousePosition.Y,
                        Math.Abs(originalDownPosition.X - previousMousePosition.X), Math.Abs(originalDownPosition.Y - previousMousePosition.Y));

                    using (Graphics g = Graphics.FromImage(mainPictureBox.Image))
                    {
                        g.DrawRectangle(drawPen, rectangle);
                        using (Brush brush = new SolidBrush(mainColor2)) g.FillRectangle(brush, rectangle);
                    }

                    mainPictureBox.Refresh();
                }
                else if (currentPencil == pencilType.ellipse)
                {
                    Rectangle rectangle = new Rectangle(originalDownPosition.X <= previousMousePosition.X ? originalDownPosition.X : previousMousePosition.X,
                        originalDownPosition.Y <= previousMousePosition.Y ? originalDownPosition.Y : previousMousePosition.Y, 
                        Math.Abs(originalDownPosition.X - previousMousePosition.X), Math.Abs(originalDownPosition.Y - previousMousePosition.Y));

                    using (Graphics g = Graphics.FromImage(mainPictureBox.Image))
                    {
                        g.DrawEllipse(drawPen, rectangle);
                        using (Brush brush = new SolidBrush(mainColor2)) g.FillEllipse(brush, rectangle);
                    }
                    mainPictureBox.Refresh();
                }
            }

            currentlyMouseDown = false;
            referenceImage = mainPictureBox.Image;
        }

        private void mainPictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            Point position = mainPictureBox.PointToClient(Cursor.Position);
            mousePositionLabel.Text = position.X + " x " + position.Y;

            if (currentlyMouseDown)
            {
                if (currentPencil == pencilType.freehand || currentPencil == pencilType.eraser)
                {
                    using (Graphics g = Graphics.FromImage(mainPictureBox.Image)) g.DrawLine(drawPen, previousMousePosition, e.Location);
                    mainPictureBox.Refresh();
                }
            }

            previousMousePosition = e.Location;
        }

        private void fileSetWallpaper_Click(object sender, EventArgs e)
        {
            DesktopWallpaper.Set(mainPictureBox.Image);
        }
    }

    public sealed class DesktopWallpaper
    {
        DesktopWallpaper() { }

        const int SPI_SETDESKWALLPAPER = 20;
        const int SPIF_UPDATEINIFILE = 0x01;
        const int SPIF_SENDWININICHANGE = 0x02;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern int SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni);

        public static void Set(Image image)
        {
            string tempFolder = Path.Combine(Path.GetTempPath(), "wallpaper.bmp");
            image.Save(tempFolder, ImageFormat.Bmp);

            RegistryKey key = Registry.CurrentUser.OpenSubKey(@"Control Panel\Desktop", true);
            key.SetValue(@"WallpaperStyle", 1.ToString());
            key.SetValue(@"TileWallpaper", 0.ToString());

            SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, tempFolder, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
        }
    }
}
