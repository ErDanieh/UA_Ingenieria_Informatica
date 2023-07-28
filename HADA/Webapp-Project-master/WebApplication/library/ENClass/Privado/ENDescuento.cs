using library.CADClass.Privado;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENDescuento
    {

        private int rango;

        private int descuento;


        public int rangoDescuento
        {
            get { return rango; }
            set { rango = value; }
        }

        public int descuentoDescuento
        {
            get { return descuento; }
            set { descuento = value; }
        }

        public ENDescuento(int rango)
        {
            this.rango = rango;
            readDescuento();
        }

        public ENDescuento(ENDescuento descuento)
        {
            this.rango = descuento.rango;
            this.descuento = descuento.descuento;
        }

        public bool createDescuento()
        {
            CADDescuento descuento = new CADDescuento();
            if (!descuento.readDescuento(this))
            {
                return descuento.createDescuento(this);
            }

            return false;
        }

        public bool readDescuento()
        {
            CADDescuento descuento = new CADDescuento();
            return descuento.readDescuento(this);
        }

        public bool updateDescuento()
        {
            ENDescuento aux = new ENDescuento(this);
            CADDescuento descuento = new CADDescuento();

            if (descuento.readDescuento(this))
            {
                this.descuento = aux.descuento;

                return descuento.updateDescuento(this);
            }

            return false;
        }

        public bool deleteDescuento()
        {
            CADDescuento descuento = new CADDescuento();

            if (descuento.readDescuento(this))
                return descuento.deleteDescuento(this);

            return false;
        }

        public override string ToString()
        {
            string h = "";
            return h;
        }
    }
}
