using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks; 

namespace hada_p1
{
    class Program
    {
        static void Main(string[] args)
        {
            String conver;
            String nu;
            double number;
            double result;
            String resp;
            bool re;
            do
            {
                Console.WriteLine("Desde donde quieres convertir? minutos/segundos/Horas:");
                conver = Console.ReadLine();
                Console.WriteLine("Introduce el número a convertir:");
                nu = Console.ReadLine();
                number = double.Parse(nu);
                if (conver.Equals("minutos") == true)
                {

                    result = HadaP1.Minutes2Seconds(number);
                    Console.WriteLine(result);
                }

                if (conver.Equals("segundos") == true)
                {
                    result = HadaP1.Seconds2Minutes(number);
                    Console.WriteLine(result);
                }

                if (conver.Equals("Horas") == true)
                {
                    result = HadaP1.Hours2Minutes(number);
                    Console.WriteLine(result);
                }

                Console.WriteLine("Desea realizar otra conversión? :");
                resp = Console.ReadLine();
                if (resp.Equals("si") == true)
                {
                    re = true;
                }
                else
                {
                    re = false;
                }

            } while (re==true);
        }
    }
}
