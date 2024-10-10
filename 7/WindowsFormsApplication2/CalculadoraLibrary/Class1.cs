using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculadoraLibrary
{
    public class Class1
    {
    }
    public class Calculadora
    {
        public string ConvertirInfijoAPrefijo(string expresionInfija)
        {
            string expresionReversa = InvertirCadena(expresionInfija);
            expresionReversa = CambiarParentesis(expresionReversa);
            string expresionPosfija = ConvertirInfijoAPosfijo(expresionReversa);
            string expresionPrefija = InvertirCadena(expresionPosfija);
            return expresionPrefija;
        }

        public double EvaluarPrefijo(string expresionPrefija)
        {
            Stack<double> pila = new Stack<double>();

            for (int i = expresionPrefija.Length - 1; i >= 0; i--)
            {
                char caracter = expresionPrefija[i];

                if (Char.IsDigit(caracter))
                {
                    pila.Push(Convert.ToDouble(caracter.ToString()));
                }
                else if (EsOperador(caracter))
                {
                    double operando1 = pila.Pop();
                    double operando2 = pila.Pop();

                    double resultado = Operar(caracter, operando1, operando2);
                    pila.Push(resultado);
                }
            }

            return pila.Pop();
        }
        public double EvaluarInfijo(string expresionInfija)
        {
            //El método ConvertirInfijoAPrefijo toma la expresión infija, 
            //reorganiza los operadores y operandos en una notación prefija.
            string expresionPrefija = ConvertirInfijoAPrefijo(expresionInfija);
            //Se evalua por metodo prefijo
            return EvaluarPrefijo(expresionPrefija);
        }
        private string InvertirCadena(string expresion)
        {
            char[] array = expresion.ToCharArray();
            Array.Reverse(array);
            return new string(array);
        }
        private string CambiarParentesis(string expresion)
        {
            return expresion.Replace('(', 'x').Replace(')', '(').Replace('x', ')');
        }

        private string ConvertirInfijoAPosfijo(string expresionInfija)
        {
            Stack<char> pila = new Stack<char>();
            string resultado = "";

            foreach (char caracter in expresionInfija)
            {
                if (Char.IsLetterOrDigit(caracter))
                {
                    resultado += caracter;
                }
                else if (caracter == '(')
                {
                    pila.Push(caracter);
                }
                else if (caracter == ')')
                {
                    while (pila.Count > 0 && pila.Peek() != '(')
                    {
                        resultado += pila.Pop();
                    }
                    pila.Pop(); 
                }
                else if (EsOperador(caracter))
                {
                    while (pila.Count > 0 && Prioridad(caracter) <= Prioridad(pila.Peek()))
                    {
                        resultado += pila.Pop();
                    }
                    pila.Push(caracter);
                }
            }

            // Vaciar la pila
            while (pila.Count > 0)
            {
                resultado += pila.Pop();
            }

            return resultado;
        }

        // Función para operar los operandos
        private double Operar(char operador, double operando1, double operando2)
        {
            switch (operador)
            {
                case '+':
                    return operando1 + operando2;
                case '-':
                    return operando1 - operando2;
                case '*':
                    return operando1 * operando2;
                case '/':
                    return operando1 / operando2;
                default:
                    throw new ArgumentException("Operador inválido");
            }
        }

        // Verificar si el carácter es un operador
        private bool EsOperador(char caracter)
        {
            return caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/';
        }

        // Asignar prioridad a los operadores
        private int Prioridad(char operador)
        {
            if (operador == '+' || operador == '-')
                return 1;
            else if (operador == '*' || operador == '/')
                return 2;
            return 0;
        }
    }
}
