using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library.CADClass.Privado
{
    public class CADComprar
    {
        private String constring;

        public CADComprar()
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }
        public CADComprar(ENComprar comprar)
        {
            //Sal2
        }

        public bool createComprar(ENComprar comprar) // Que tabla guarda las compras? 
        {
            CADTicket cTicket = new CADTicket();
            CADUsuario cUsuario = new CADUsuario();
            return cTicket.createTicket(comprar.ticketComprar) && cUsuario.createUsuario(comprar.usuarioComprar) ;
        }

        public bool readComprar(ENComprar comprar)
        {
            CADTicket cTicket = new CADTicket();
            CADUsuario cUsuario = new CADUsuario();
            return cTicket.readTicket(comprar.ticketComprar) && cUsuario.readUsuario(comprar.usuarioComprar);
        }

        public bool updateComprar(ENComprar comprar)
        {
            CADTicket cTicket = new CADTicket();
            CADUsuario cUsuario = new CADUsuario();
            return cTicket.updateTicket(comprar.ticketComprar) && cUsuario.updateUsuario(comprar.usuarioComprar);
        }

        public bool deleteComprar(ENComprar comprar)
        {
            CADTicket cTicket = new CADTicket();
            CADUsuario cUsuario = new CADUsuario();
            return cTicket.deleteTicket(comprar.ticketComprar) && cUsuario.deleteUsuario(comprar.usuarioComprar);
        }


        public override string ToString()
        {
            return null;
        }
    }
}