using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    //  ##### Clase que contiene los métodos para trabajar con la Base de Datos respecto a la entidad ENTicket #####
    public class CADTicket
    {
        private String constring;

        public CADTicket()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }
        public CADTicket(ENTicket ticket)
        {
            //Salu2
        }

        public bool createTicket(ENTicket ticket)   //DONDE TENGO QUE GUARDAR EL TICKET????
        {
            bool created = false;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "Insert INTO [dbo].[Ticket] (id_ticket) VALUES ('" + ticket.asientoTicket + ")";
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

        public bool readTicket(ENTicket ticket) //Donde tengo que leer el ticket??????
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "Select * From [dbo].[Ticket] Where id_ticket = '" + ticket.idTicket + "' ";
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

        public bool updateTicket(ENTicket ticket) //SAME 
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "UPDATE [dbo].[Ticket] SET email= '" + ticket.idTicket + "'";
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

        public bool deleteTicket(ENTicket ticket)   //SAME
        {
            bool created = true;
            SqlConnection conection = null;
            conection = new SqlConnection(constring);
            try
            {
                conection.Open();
                string query = "DELETE * From [dbo].[Ticket] Where id_ticket = '" + ticket.idTicket + "' ";
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

    }
}
