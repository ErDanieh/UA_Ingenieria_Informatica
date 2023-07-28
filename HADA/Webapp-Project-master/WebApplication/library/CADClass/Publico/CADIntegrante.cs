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
    //  ##### Clase que contiene los métodos para trabajar con la Base de Datos respecto a la entidad ENIntegrante #####
    class CADIntegrante
    {
        private string constring;

        public CADIntegrante()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }
        public CADIntegrante(ENIntegrante integrante)
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }

        public bool createIntegrante(ENIntegrante integrante)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Insert INTO [dbo].[Integrante] (nombre, apellidos, director) VALUES ('" + integrante.nombreIntegrante + "', '" + integrante.apellidoIntegrante + "', '" + integrante.directorIntegrante + ")";
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

        public bool readIntegrante(ENIntegrante integrante)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Integrante] Where nombre = '" + integrante.nombreIntegrante + "' and apellidos= '" + integrante.apellidoIntegrante + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["nombre"].ToString() == integrante.nombreIntegrante.ToString() && search["apellidos"].ToString() == integrante.apellidoIntegrante.ToString())
                {
                    integrante.nombreIntegrante = search["nombre"].ToString();
                    integrante.apellidoIntegrante = search["apellidos"].ToString();
                    integrante.directorIntegrante = bool.Parse(search["director"].ToString());
                }
                else created = false;

                search.Close();

            }
            catch (SqlException e)
            {
                created = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            catch (Exception e)
            {
                created = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            finally
            {
                conection.Close();
            }
            return created;
        }

        public bool updateIntegrante(ENIntegrante integrante)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Update [dbo].[Integrante] set director= '" + integrante.directorIntegrante + "WHERE nombre= '" + integrante.nombreIntegrante + "' and apellidos= '" + integrante.apellidoIntegrante + "'";
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

        public bool deleteIntegrante(ENIntegrante integrante)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Integrante] WHERE nombre= '" + integrante.nombreIntegrante + "' and apellidos= '" + integrante.apellidoIntegrante + "'";
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
    }
}
