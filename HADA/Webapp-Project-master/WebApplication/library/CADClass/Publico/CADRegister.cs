using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlTypes;
using System.Data.SqlClient;
using System.Data.Common;
using System.Data;
using System.Configuration;

namespace library
{
    public class CADRegister
    {
        private String constring;

        public CADRegister(ENRegister register)
        {
                        constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }

        public bool createRegister(ENRegister register)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Insert INTO [dbo].[Asientos] (id, tipo, estado) VALUES ('" + "', '" + ")";
                SqlCommand consulta = new SqlCommand(query, conexion);
                consulta.ExecuteNonQuery();
                creado = true;
            }
            catch (SqlException e)
            {
                creado = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            catch (Exception e)
            {
                creado = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            finally
            {
                conexion.Close();
            }
            return creado;
        }

        public bool readRegister(ENRegister register)
        {
            return false;
        }

        public bool updateRegister(ENRegister register)
        {
            return false;
        }

        public bool deleteRegister(ENRegister register)
        {
            return false;
        }

        public override string ToString()
        {
            return null;
        }
    }
}
