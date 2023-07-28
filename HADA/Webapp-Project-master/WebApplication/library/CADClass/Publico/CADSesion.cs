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
    public class CADSesion
    {
        private String constring;

        public CADSesion()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();

        }

        public CADSesion(ENSesion sesion)
        {

        }

        public bool crearSesion(ENSesion sesion)
        {

            bool created;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "Insert INTO [dbo].[Sesion] (id_sala, id_hora, id_pelicula) VALUES ('" + sesion.salaSesion.salaSala + "', '" + sesion.horaSesion.idHorario + "', " + sesion.peliculaSesion.idPelicula + ")";
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


        public bool deleteSesion(ENSesion sesion)
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
               
                conection.Open();
                string query = "DELETE FROM [dbo].[Sesion] WHERE id_sala = '" + sesion.salaSesion + "', id_hora= '" + sesion.horaSesion + "' and id_pelicula= '" + sesion.peliculaSesion + "'";
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

        public bool readSesion(ENSesion sesion)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "Select * From [dbo].[Sesion] WHERE id_sala = '" + sesion.salaSesion + "', id_hora = '" + sesion.horaSesion + "', id_pelicula = '" + sesion.peliculaSesion + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                SqlDataReader search = consulta.ExecuteReader();
                search.Read();

                if (search["id_sala"].ToString() == sesion.salaSesion.ToString() && search["id_hora"].ToString() == sesion.horaSesion.ToString() && search["id_pelicula"].ToString()== sesion.peliculaSesion.ToString())
                {
                    ENPelicula pelicula = new ENPelicula();
                    pelicula.idPelicula = int.Parse(search["id_pelicula"].ToString());
                    ENHorario horario = new ENHorario();
                    horario.idHorario = DateTime.Parse(search["id_hora"].ToString());
                    ENSala sala = new ENSala();
                    sala.salaSala = int.Parse(search["id_sala"].ToString());

                    sesion.horaSesion = horario;
                    sesion.salaSesion = sala;
                    sesion.peliculaSesion = pelicula;
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

        public bool updateSesion(ENSesion sesion) // TODO: cammbiar para que se updateen todos los datos, no solo horario. 
        {                                         // Si se da el caso de que queremos cambiar solo el horario, pasremmos el resto de parammetros
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);// iguales
            try
            {
                conection.Open();

                string query = "UPDATE [dbo].[Sesion] SET id_hora = '" + sesion.horaSesion + "' id_sala= '" + sesion.salaSesion + "' , id_pelicula= " + sesion.peliculaSesion + "' WHERE id_sala = '" + sesion.salaSesion + "', id_hora = '" + sesion.horaSesion + "'";
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


        // TODO: Creo que con el updateSesion, pasandole todos los valores no se necesita los de modificar. Los dejo por si acaso.
        public bool modificarHorario(ENSesion sesion)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "UPDATE [dbo].[Sesion] SET id_hora = '" + sesion.horaSesion + "' WHERE id_sala = '" + sesion.salaSesion + "', id_hora = '" + sesion.horaSesion + "', id_pelicula = '" + sesion.peliculaSesion + "'";
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


        public bool modificarSala(ENSesion sesion)
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();

                string query = "UPDATE [dbo].[Sesion] SET id_sala = '" + sesion.horaSesion + "' WHERE id_sala = '" + sesion.salaSesion + "', id_hora = '" + sesion.horaSesion + "', id_pelicula = '" + sesion.peliculaSesion + "'";
                SqlCommand consulta = new SqlCommand(query, conection);
                consulta.ExecuteNonQuery();
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

        public DataSet diasSesionesPelicula(int idPelicula)
        {
            DataSet bdvirtual = new DataSet();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("SET LANGUAGE Spanish; " +
                    " select DISTINCT FORMAT(id_hora, 'dddd, dd, MMMM') as id_hora, FORMAT(id_hora, 'yyyy-MM-dd') as id_values " +
                    " from [dbo].[Sesion] " +
                    " WHERE id_pelicula = " + idPelicula, c);

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

        public DataTable mostrarHorarios(int idPelicula)
        {

            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                //Dani es MrBack-End  Mr.Ander no sabe Programar <3
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Sesion] WHERE id_pelicula = " + idPelicula, c);

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



        public DataSet mostrarHoras(int idPelicula, string dia)
        {
            DataSet bdvirtual = new DataSet();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                //Dani es MrBack-End  Mr.Ander no sabe Programar <3
                SqlDataAdapter da = new SqlDataAdapter("SET LANGUAGE Spanish; " +
                    " select FORMAT(id_hora, 'HH:mm') as id_hora " +
                    " from [dbo].[Sesion] " +
                    " WHERE id_pelicula = " + idPelicula +
                    " AND FORMAT(id_hora, 'yyyy-MM-dd') = '" +
                    dia + "'", c);

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

        public DataTable mostrarAsientos(string idSesion , int idPelicula )
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select *  from [dbo].[Tener] WHERE id_sesionHora = '" + idSesion + "' AND id_pelicula = '" + idPelicula  + "'",c);
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

        public DataTable mostrarAsientos2()
        {
            DataTable bdvirtual = new DataTable();

            SqlConnection c = new SqlConnection(constring);
            try
            {
                SqlDataAdapter da = new SqlDataAdapter("select * from [dbo].[Asientos]" , c);

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
