using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace frontend
{
    public partial class Form1 : Form
    {

        private int x0, y0;
        private int scale = 3;
        private readonly int[] cellLen = new int[7] { 1, 5, 10, 20, 50, 100, 200 };
        private Point[] arr = new Point[0];
        private string file;
        private float widthLine = 0.2f;
        public Form1()
        {
            InitializeComponent();
            x0 = sheet.Width / 2;
            y0 = sheet.Height / 2;
        }

        private void Start_Click(object sender, EventArgs e)
        {
            StartDialog(file, "runfromfile");
        }
        
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen blackPen = new Pen(Color.LightSlateGray, widthLine);
            int r = cellLen[scale];
            int height = sheet.Height;
            int width = sheet.Width;
            int kx = width / r;
            int ky = height / r;

            

            for (int i = y0; i <= height; i += r)
            {
                g.DrawLine(blackPen, 0, i, width, i);
            }
            for (int i = y0; i >= 0; i -= r)
            {
                g.DrawLine(blackPen, 0, i, width, i);
            }
            

            for (int i = x0; i <= width; i += r)
            {
                g.DrawLine(blackPen, i, 0, i, height);
            }
            for (int i = x0; i >= 0; i -= r)
            {
                g.DrawLine(blackPen, i, 0, i, height);
            }

            Pen arrowPen = new Pen(Color.Black, widthLine * 10);
            arrowPen.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
            g.DrawLine(arrowPen, x0, height, x0, 0);
            g.DrawLine(arrowPen, 0, y0, width, y0);

            Pen rpen = new Pen(Color.Purple, 2);
            int h, w;
            w = h = r / 2;
            for (int i = 0; i < arr.Length; i++)
            {
                g.DrawEllipse(rpen, arr[i].X * r + x0 - w / 2, arr[i].Y * r + y0 - h / 2, w, h);
            }
        }
       
        private void OpenFileButton_Click(object sender, EventArgs e)
        {
            StreamReader myStream = null;
            OpenFileDialog openFileDialog1   = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "c:\\";
            openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            file = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = new StreamReader(openFileDialog1.OpenFile())) != null)
                    {
                        using (myStream)
                        {
                            // Insert code to read the stream here.
                            file = myStream.ReadToEnd();
                        }
                    }
                    FileName.Text = openFileDialog1.FileName;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }


        private void StartDialog(string buf, string path)
        {
            HttpWebResponse res = (HttpWebResponse)SendFile(buf, path);
        }

        private void GenSeqButton_Click(object sender, EventArgs e)
        {
            Random rnd = new Random();
            arr = new Point[10];
            for (int i = 0; i < 10; i++)
            {
                int x, y;
                x = rnd.Next(-10, 10);
                y = rnd.Next(-10, 10);
                arr[i].X = x;
                arr[i].Y = y;
            }
            sheet.Refresh();
        }

        private WebResponse SendFile(string buf, string path)
        {
            WebResponse res = null;
            try
            {
                string site = "http://localhost:8080/" + path;
                HttpWebRequest req = (HttpWebRequest)HttpWebRequest.Create(site);
                req.Method = "POST";
                req.ContentLength = buf.Length;
                using (StreamWriter stream = new StreamWriter(req.GetRequestStream()))
                {
                    stream.Write(buf);
                    stream.Close();
                }
                res = req.GetResponse();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
            }
            return res;
        }
    }
}
