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
    public class CADAsiento
    {
        private string constring;
        public CADAsiento()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }
        public CADAsiento(ENAsiento asiento)
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }

        public bool createAsiento(ENAsiento asiento)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Insert INTO [dbo].[Asientos] (id, tipo, estado) VALUES ('" + asiento.idAsiento + "', '" + asiento.tipoAsiento + "', '" + asiento.estadoAsiento + ")";
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

        public bool readAsiento(ENAsiento asiento)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Asientos] Where id = '" + asiento.idAsiento + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id"].ToString() == asiento.idAsiento.ToString())
                {
                    asiento.idAsiento = int.Parse(search["id"].ToString());
                    asiento.estadoAsiento = bool.Parse(search["estado"].ToString());
                    asiento.tipoAsiento = char.Parse(search["tipo"].ToString());
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

        public bool updateAsiento(ENAsiento asiento)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Update [dbo].[Asientos] set tipo= '" + asiento.tipoAsiento + "', estado=" + asiento.estadoAsiento + "WHERE id= '" + asiento.idAsiento + "'"; 
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

        public bool deleteAsiento(ENAsiento asiento)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Asientos] WHERE id= '" + asiento.idAsiento + "'";
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

        public bool read_fila(ENAsiento asiento)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select fila From [dbo].[Asientos] Where id = '" + asiento.idAsiento + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id"].ToString() == asiento.idAsiento.ToString())
                {
                    asiento.idFila = int.Parse(search["fila"].ToString());
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

        public DataTable mostrarAsientos()
        {

            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Asientos]", c);

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