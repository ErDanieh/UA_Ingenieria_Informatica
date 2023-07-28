using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    //  ##### Clase que contiene los métodos para trabajar con la Base de Datos respecto a la entidad ENSala #####
    public class CADSala       
    {
        private String constring;

        public CADSala()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }

        public CADSala(ENSala sala)
        {
        }

        public bool createSala(ENSala sala)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Insert INTO [dbo].[Sala] (id_sala , asientos) VALUES ( '" +  sala.salaSala + "' , '" + sala.numAsietosSala + "')";
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

        public bool readSala(ENSala sala)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Sala] Where id_sala= '" + sala.salaSala + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id_sala"].ToString() == sala.salaSala.ToString())
                {
                    created = true;
                    sala.salaSala= int.Parse(search["id_sala"].ToString());
                    sala.numAsietosSala = int.Parse(search["asientos"].ToString());

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

        public bool updateSala(ENSala sala)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();
                string query = "UPDATE [dbo].[Sala]  SET id_sala= '" + sala.salaSala + "' , asientos= '" + sala.numAsietosSala + "' WHERE id_sala= '" + sala.salaSala + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();

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

        public bool deleteSala(ENSala sala)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Sala] WHERE id_sala= '" + sala.salaSala + "'";
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
        public override string ToString()
        {
            return null;
        }
    }
}
