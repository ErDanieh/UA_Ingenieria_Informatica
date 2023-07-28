using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class CADUsuario
    {
        private String constring;

        public CADUsuario()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }

        public CADUsuario(ENUsuario usuario)
        {
            
        }


        public bool readUsuario(ENUsuario usuario)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Usuario] Where email = '" + usuario.emailUsuario + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["email"].ToString() == usuario.emailUsuario)              
                {
                    usuario.passwordUsuario = search["password"].ToString();
                    usuario.nombreUsuario = search["nombre"].ToString();
                    usuario.edadUsuario = int.Parse(search["edad"].ToString());
                    usuario.apellidoUsuario = search["apellidos"].ToString();
                    usuario.edadUsuario = int.Parse(search["edad"].ToString());
                    usuario.emailUsuario = search["email"].ToString();

                    created = true;
                }

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

        public bool updateUsuario(ENUsuario usuario)
        {
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            bool created = false;

            try
            {
                conection.Open();

                string query = "UPDATE [dbo].[Usuario] SET nombre = '" + usuario.nombreUsuario + "', apellidos = '" + usuario.apellidoUsuario + "', password = '" + usuario.passwordUsuario + "', edad = " + usuario.edadUsuario + " where email = '" + usuario.emailUsuario + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                conection.Close();
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

        public bool createUsuario(ENUsuario usuario)
        {
            bool creado = false;
            SqlConnection conexion = null;
            try
            {
                conexion = new SqlConnection(constring);
                conexion.Open();
                string query = "Insert INTO [dbo].[Usuario] (email, nombre, apellidos, password, edad, tipo, rangoEdad) VALUES ('" + usuario.emailUsuario + "', '" + usuario.nombreUsuario + "', '" + usuario.apellidoUsuario + "', '" + usuario.passwordUsuario + "', " + usuario.edadUsuario + ", " + usuario.tipoUsuario + ", " + usuario.descuentosUsuario.rangoDescuento + ")";
                SqlCommand consulta = new SqlCommand(query, conexion);
                consulta.ExecuteNonQuery();
                creado = true;
            }
            catch (SqlException e)
            {
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            finally
            {
                conexion.Close();
            }
            return creado;
        }

        public bool deleteUsuario(ENUsuario usuario)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Usuario] WHERE email = '" + usuario.emailUsuario + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                created = true;
                conection.Close();
                
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

        public bool addPendientes(ENUsuario usuario, ENPelicula pelicula)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            { 
                conection.Open();
                string query = "Insert INTO [dbo].[Pendientes] (id_usuario, id_pelicula) VALUES ('" + usuario.emailUsuario + "', " + pelicula.idPelicula + ")";
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
            finally { conection.Close(); }
            return created;
        }



        public bool deletePendientes(ENUsuario usuario, ENPelicula pelicula)
        {
            bool deleted = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Pendientes] WHERE id_usuario = '" + usuario.emailUsuario + "' AND id_pelicula = " + pelicula.idPelicula;
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                deleted = true;

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
            finally
            {
                conection.Close();
            }
            return deleted;
        }


        public bool deletePendientesTodas(ENUsuario usuario)
        {
            bool deleted = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Pendientes] WHERE id_usuario = '" + usuario.emailUsuario + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                deleted = true;

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
            finally
            {
                conection.Close();
            }
            return deleted;
        }

        public bool addVistas(ENUsuario usuario, ENPelicula pelicula)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "Insert INTO [dbo].[Vistas] (id_usuario,id_pelicula) VALUES ('" + usuario.emailUsuario + "', " + pelicula.idPelicula + ")";
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

        public bool deleteVistas(ENPelicula pelicula)
        {
            bool deleted = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Vistas] WHERE id_pelicula = '" + pelicula.idPelicula + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                deleted = true;
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
            finally
            {
                conection.Close();
            }
            return deleted;
        }

        public bool deleteVistasTodas(ENUsuario usuario)
        {
            bool deleted = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);

            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Vistas] WHERE id_usuario = '" + usuario.emailUsuario + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
                deleted = true;

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
            finally
            {
                conection.Close();
            }
            return deleted;
        }

        public bool isAdmin(string email)
        {
            string constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
            bool admin = false;
            SqlConnection conection = null;
            try
            {

                conection = new SqlConnection(constring);
                conection.Open();

                string query = "Select tipo From [dbo].[Usuario] Where email = '" + email + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                int tipo = int.Parse(search["tipo"].ToString());
                if (tipo == 1)
                {
                    admin = true;
                }

                search.Close();

            }
            catch (SqlException e)
            {
                admin = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            catch (Exception e)
            {
                admin = false;
                Console.WriteLine("User operation has failed.Error: {0}", e.Message);
            }
            finally
            {
                conection.Close();
            }
            return admin;
        }



        public int getDescuento(ENUsuario usuario)
        {
            return 0;
        }

    }
}