using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CalculadoraLibrary;



namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button_Click(object sender, EventArgs e)
        {
            Button boton = (Button)sender;
            txtDisplay.Text += boton.Text; 
        }
        private void operador_Click(object sender, EventArgs e)
        {
            Button boton = (Button)sender;
            txtDisplay.Text += " " + boton.Text + " ";
        }
        // Botón "=" (calcular resultado)
        private void btnIgual_Click(object sender, EventArgs e)
        {
            try
            {
                Calculadora calc = new Calculadora();
                string expresion = txtDisplay.Text;
                double resultado = 0;
                //verifica que opcion esta marcada
                if (rdbInfijo.Checked)
                {
                    resultado = calc.EvaluarInfijo(expresion);
                }
                else if (rdbPrefijo.Checked)
                {
                    resultado = calc.EvaluarPrefijo(expresion);
                }
                txtDisplay.Text = resultado.ToString();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error al evaluar la expresión: " + ex.Message);
            }
        }


        // Botón "C" (borrar todo)
        private void btnClear_Click(object sender, EventArgs e)
        {
            txtDisplay.Clear();
            resultado = 0;
            operador = "";
            operadorPresionado = false; 
        }
    }
}
