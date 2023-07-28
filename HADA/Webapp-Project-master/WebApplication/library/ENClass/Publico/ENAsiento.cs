using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENAsiento
    {

        private int id; //Número del asiento

        private int fila;   // Numero de fila 

        private bool estado; //Ocupado o no

        private char tipo; //P premium, M minubalidos, D defecto

        private ENSesion sesion; //Sesion a la que pertenece

        public int idAsiento
        {
            get { return id; }
            set { id = value; }
        }

        public int idFila
        {
            get { return fila; }
            set { fila = value; }
        }


        public bool estadoAsiento
        {
            get { return estado; }
            set { estado = value; }
        }

        public char tipoAsiento
        {
            get { return tipo; }
            set { tipo = value; }
        }

        public ENSesion sesionAsiento
        {
            get { return sesion; }
            set { sesion = value; }
        }

        public ENAsiento()
        {
            this.id = 0;
            this.estado = false;
            this.tipo = 'D';
            this.sesion = new ENSesion();
        }

        public ENAsiento(int id, bool estado, char tipo, ENSesion sesion)
        {
            this.id = id;
            this.estado = estado;
            this.tipo = tipo;
            this.sesion = sesion;
        }

        public ENAsiento(ENAsiento asiento)
        {
            this.id = asiento.id;
            this.estado = asiento.estado;
            this.tipo = asiento.tipo;
            this.sesion = asiento.sesion;
        }


        public bool readAsiento()
        {
            CADAsiento asiento = new CADAsiento();
            return asiento.readAsiento(this);
        }

        public bool createAsiento()
        {
            CADAsiento asiento = new CADAsiento();
            if (!asiento.readAsiento(this))
            {
                return asiento.createAsiento(this);
            }

            return false;
        }
        public static DataTable mostrarAsientos()
        {
            DataTable d = new DataTable();
            CADAsiento asiento = new CADAsiento();
            d = asiento.mostrarAsientos();
            return d;
        }



        public bool updateAsiento()
        {
            ENAsiento aux = new ENAsiento(this);
            CADAsiento asiento = new CADAsiento();

            if (asiento.readAsiento(this))
            {
                this.estado = aux.estado;
                this.tipo = aux.tipo;
                return asiento.updateAsiento(this);
            }

            return false;
        }

        public bool deleteAsiento()
        {
            CADAsiento asiento = new CADAsiento();

            if (asiento.readAsiento(this)) return asiento.deleteAsiento(this);

            return false;
        }


        public bool read_fila()
        {
            CADAsiento asiento = new CADAsiento();
            return asiento.read_fila(this);
        }
        

        public override string ToString()
        {
            return "Sesion: " + sesion.idSesion.ToString() + "Ocupado: " + estado.ToString() + " Tipo: " + tipo.ToString() + "Id: " + id.ToString();
        }
    }
}
