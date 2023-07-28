using library.CADClass.Privado;
using System;
using System.Configuration;
using System.Data.SqlClient;

namespace library
{
    public class CADAdministrador
    {

        private String constring;

        public CADAdministrador()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }

        public bool createAdministrador(ENAdministrador admin)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            { 
                conection.Open();
                string query = "Insert INTO [dbo].[Usuario] (email) VALUES ('" + admin.emailAdmin + ")"; // En admin no hay nigun atributo aparte de admin 
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

        public bool readAdministrador(ENAdministrador admin)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "Select * From [dbo].[Usuario] Where email = '" + admin.emailAdmin + "' ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
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

        public bool updateAdministrador(ENAdministrador admin)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "UPDATE [dbo].[Usuario] SET email= '" + admin.emailAdmin + "'";
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

        public bool deleteAdministrador(ENAdministrador admin)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "DELETE FROM [dbo].[Usuario] WHERE email = '" + admin.emailAdmin + "'";
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


        public bool crearSesion(ENSesion sesion)
        {
            CADSesion csesion = new CADSesion();
            return csesion.deleteSesion(sesion);
        }

        public bool eliminarSesion(ENSesion sesion)
        {
            CADSesion csesion = new CADSesion();
            return csesion.deleteSesion(sesion);
        }

        public bool deleteAsientos(ENAsiento asiento)
        {
            CADAsiento cAsiento = new CADAsiento();
            return cAsiento.deleteAsiento(asiento);
        }

        public bool updateSesion(ENSesion sesion)
        {
            CADSesion cSesion = new CADSesion();
            return cSesion.updateSesion(sesion);
        }

        public bool eliminarUsuarios(ENUsuario usuario)
        {
            CADUsuario cUser = new CADUsuario();
            return cUser.deleteUsuario(usuario);
        }

        public bool eliminarPelicula(ENPelicula pelicula)        
        {
            CADPelicula cPelicula = new CADPelicula();
            return cPelicula.deletePelicula(pelicula);
        }

        public bool crearTicket(ENTicket ticket)              
        {
            CADTicket cTicket = new CADTicket();
            return cTicket.createTicket(ticket);
        }

        public bool eliminarHorario(ENHorario horario)
        {
            CADHorario cHorario = new CADHorario();
            return cHorario.deleteHorario(horario);
        }

        public bool mostrarTodosUsuarios(ENUsuario usuario)
        {
            bool created = true;
            try
            {
                SqlConnection conection = null;
                conection = new SqlConnection(constring);
                conection.Open();

                string query = "Select email From [dbo].[Usuario] ";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
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
            return created;
        }

        public bool readUsuario(ENUsuario usuario) 
        {
            CADUsuario cUser = new CADUsuario();
            return cUser.readUsuario(usuario);
        }

        public bool crearDescuento(ENDescuento descuento)
        {
            CADDescuento cDescuento = new CADDescuento();
            return cDescuento.createDescuento(descuento);
        }

        public bool modificarDescuento(ENDescuento descuento) 
        {
            CADDescuento cDescuento = new CADDescuento();
            return cDescuento.updateDescuento(descuento);
        }

        public bool eliminarDescuento(ENDescuento descuento)
        {
            CADDescuento cDescuento = new CADDescuento();
            return cDescuento.deleteDescuento(descuento);
        }

        public bool crearGenero(ENGenero genero)
        {
            CADGenero cGenero = new CADGenero();
            return cGenero.createGenero(genero);
        }

        public bool deleteGenero(ENGenero genero)
        {
            CADGenero cGenero = new CADGenero();
            return cGenero.deleteGenero(genero);
        }
    }
}