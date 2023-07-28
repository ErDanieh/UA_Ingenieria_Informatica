using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    //  ##### Clase que contiene los métodos para trabajar con la Base de Datos respecto a la entidad ENGenero #####
    class CADGenero
    {
        private String constring;

        public CADGenero()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }
        public CADGenero(ENGenero genero)
        {

        }
        public bool createGenero(ENGenero genero)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {

                conection.Open();

                string query = "Insert INTO [dbo].[Genero] (genero) VALUES ('" + genero.generoPelicula + ")";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                created = true;

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

        public bool readGenero(ENGenero genero)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Genero] Where genero = '" + genero.generoPelicula + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id"].ToString() == genero.generoPelicula.ToString())
                {
                    genero.generoPelicula = search["genero"].ToString();

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

        public bool updateGenero(ENGenero genero)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Update [dbo].[Genero] set genero= '" + genero.generoPelicula + "WHERE genero= '" + genero.generoPelicula + "'";
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

        public bool deleteGenero(ENGenero genero)
        {
            bool deleted = false;
            try
            {
                SqlConnection conection = null;
                conection = new SqlConnection(constring);
                conection.Open();

                string query = "DELETE FROM [dbo].[Genero] WHERE genero = '" + genero.generoPelicula + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                deleted = true;
                conection.Close();
            }
            catch (SqlException e)
            {
                deleted = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            catch (Exception e)
            {
                deleted = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            return deleted;
        }

        public DataSet todosrGeneros()
        {
            DataSet bdvirtual = new DataSet();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select genero from [dbo].[Genero] ", c);

                da.Fill(bdvirtual);
            }
            catch (SqlException ex)
            {
                Console.WriteLine("The operation has failed.Error: {0}", ex.Message);
            }
            catch (Exception exe)
            {
                Console.WriteLine("The operation has failed.Error: {0}", exe.Message);
            }
            finally
            {
                c.Close();
            }
            return bdvirtual;
        }

    }
}
