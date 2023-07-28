using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using library;
using System.Data.Common;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Configuration;
using System.Data;


namespace library
{
    //  ##### Clase que contiene los métodos para trabajar con la Base de Datos respecto a la entidad ENPelicula #####
    public class CADPelicula
    {
        private String constring;

        public CADPelicula()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }
        public CADPelicula(ENPelicula pelicula)
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }

        public bool createPelicula(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Insert INTO [dbo].[Pelicula] (id, nombre, descripcion, duracion, miniatura, trailer ,valoracion, fecha_estreno ,id_genero) VALUES (" + pelicula.idPelicula + ", '" + pelicula.nombrePelicula + "', '" + pelicula.descripcionPelicula + "', " + pelicula.duracionPelicula + ", '" + pelicula.imgPelicula + "', '" + pelicula.trailerPelicula + "', " + pelicula.valoracionPelicula + ", '" + pelicula.fechaEstrenoPelicula + "', '" + pelicula.generoPelicula.generoPelicula + "')";
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

        public bool readPelicula(ENPelicula pelicula)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Pelicula] Where id = " + pelicula.idPelicula + " ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id"].ToString() == pelicula.idPelicula.ToString())
                {
                    pelicula.idPelicula = int.Parse(search["id"].ToString());
                    pelicula.nombrePelicula = search["nombre"].ToString();
                    pelicula.descripcionPelicula = search["descripcion"].ToString();
                    pelicula.duracionPelicula = int.Parse(search["duracion"].ToString());
                    pelicula.imgPelicula = search["miniatura"].ToString();
                    pelicula.trailerPelicula = search["trailer"].ToString();
                    pelicula.valoracionPelicula = int.Parse(search["valoracion"].ToString());
                    pelicula.generoPelicula = new ENGenero(search["id_genero"].ToString());
                    pelicula.fechaEstrenoPelicula = DateTime.Parse(search["fecha_estreno"].ToString());
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

        public bool updatePelicula(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "Update [dbo].[Pelicula] set nombre= '" + pelicula.nombrePelicula + "', descripcion= '" + pelicula.descripcionPelicula + "' , duracion= " + pelicula.duracionPelicula + ", miniatura= '" + pelicula.imgPelicula + "', trailer= '" + pelicula.trailerPelicula + "', valoracion=" + pelicula.valoracionPelicula + ", fecha_estreno= '" + pelicula.fechaEstrenoPelicula + "' , id_genero= '" + pelicula.generoPelicula.generoPelicula + "' WHERE id= '" + pelicula.idPelicula + "'";
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

        public bool deletePeliculaTener(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Tener] WHERE id_pelicula= '" + pelicula.idPelicula + "'";
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


        public bool deletePeliculaSesion(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Sesion] WHERE id_pelicula= '" + pelicula.idPelicula + "'";
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

        public bool deletePeliculaPendientes(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Pendientes] WHERE id_pelicula= '" + pelicula.idPelicula + "'";
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


        public bool deletePelicula(ENPelicula pelicula)
        {
            bool creado = false;
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            try
            {
                conexion.Open();
                String query = "DELETE FROM [dbo].[Pelicula] WHERE id= '" + pelicula.idPelicula + "'";
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

        public DataTable mostrarPeliculas()
        {

            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula]", c);

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

        public DataTable mostrarSelect(string nombrePelicula)
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] where nombre LIKE lower('%" + nombrePelicula + "%')", constring);

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


        public DataTable muestraGenero(string generoPelicula)
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                if (generoPelicula == "")
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula]", constring);
                    da.Fill(bdvirtual);
                }
                else
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] where id_genero LIKE '" + generoPelicula + "%'", constring);
                    da.Fill(bdvirtual);
                }


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

        public DataTable muestraGeneroOrdenado(string generoPelicula, string orden)
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                if (generoPelicula != "" && orden != "")
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] where id_genero LIKE '" + generoPelicula + "%' order by valoracion " + orden, constring);
                    da.Fill(bdvirtual);
                }

                else if (generoPelicula != "" && orden == "")
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] where id_genero LIKE '" + generoPelicula + "%'", constring);
                    da.Fill(bdvirtual);
                }

                else if (generoPelicula == "" && orden != "")
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] order by valoracion " + orden, constring);
                    da.Fill(bdvirtual);
                }
                else
                {
                    SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula]", constring);
                    da.Fill(bdvirtual);
                }
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


        public DataTable mostrarDESC()
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] order by valoracion DESC ", constring);

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


        public DataTable mostrarASC()
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula] order by valoracion ASC ", constring);

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

        public DataTable mostrarMisPelis(string email)
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula], [dbo].[Pendientes] where id_pelicula=id and id_usuario= '" + email + "' ", constring);

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

        public DataTable mostrarPelisVistas(string email)
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Pelicula], [dbo].[Vistas] where id_pelicula=id and id_usuario= '" + email + "' ", constring);

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

        public override string ToString()
        {
            return null;
        }
    }
}
