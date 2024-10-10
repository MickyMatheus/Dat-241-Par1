using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private Bitmap imagenOriginal;
        public Form1()
        {
            InitializeComponent();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Archivos de imagen|*.jpg;*.png;*.bmp"
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                imagenOriginal = new Bitmap(openFileDialog.FileName);
                pictureBoxOriginal.Image = imagenOriginal;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (imagenOriginal != null)
            {
                Bitmap imagenGrises = ConvertirAEscalaDeGrises(imagenOriginal);
                Bitmap imagenBordes = AplicarFiltroSobel(imagenGrises);
                pictureBoxBordes.Image = imagenBordes;
            }
            else
            {
                MessageBox.Show("Cargue una imagen antes de aplicar el filtro.");
            }
        }
        private Bitmap ConvertirAEscalaDeGrises(Bitmap imagen)
        {
            Bitmap imagenGris = new Bitmap(imagen.Width, imagen.Height);
            for (int y = 0; y < imagen.Height; y++)
            {
                for (int x = 0; x < imagen.Width; x++)
                {
                    Color pixel = imagen.GetPixel(x, y);
                    int valorGris = (int)(pixel.R * 0.3 + pixel.G * 0.59 + pixel.B * 0.11);
                    imagenGris.SetPixel(x, y, Color.FromArgb(valorGris, valorGris, valorGris));
                }
            }
            return imagenGris;
        }
        private Bitmap AplicarFiltroSobel(Bitmap imagen)
        {
            Bitmap imagenBordes = new Bitmap(imagen.Width, imagen.Height);

            int[,] filtroSobelX = {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] filtroSobelY = {
                { -1, -2, -1 },
                {  0,  0,  0 },
                {  1,  2,  1 }
            };

            for (int y = 1; y < imagen.Height - 1; y++)
            {
                for (int x = 1; x < imagen.Width - 1; x++)
                {
                    int pixelSobelX = 0;
                    int pixelSobelY = 0;

                    for (int filtroY = -1; filtroY <= 1; filtroY++)
                    {
                        for (int filtroX = -1; filtroX <= 1; filtroX++)
                        {
                            int pixelValor = imagen.GetPixel(x + filtroX, y + filtroY).R;
                            pixelSobelX += filtroSobelX[filtroY + 1, filtroX + 1] * pixelValor;
                            pixelSobelY += filtroSobelY[filtroY + 1, filtroX + 1] * pixelValor;
                        }
                    }

                    int magnitud = (int)Math.Sqrt((pixelSobelX * pixelSobelX) + (pixelSobelY * pixelSobelY));
                    magnitud = Math.Min(255, Math.Max(0, magnitud));

                    imagenBordes.SetPixel(x, y, Color.FromArgb(magnitud, magnitud, magnitud));
                }
            }

            return imagenBordes;
        }
    }
}
