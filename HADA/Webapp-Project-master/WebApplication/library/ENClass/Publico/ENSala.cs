using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENSala
    {

        private int sala;

        private int numAsientos;

        public int salaSala
        {
            get { return sala; }
            set { sala = value; }
        }

        public int numAsietosSala
        {
            get { return numAsientos; }
            set { numAsientos = value; }
        }

        public ENSala()
        {
            this.sala = 0;
            this.numAsientos = 0;
        }

        public ENSala(int sala, int numAsientos)
        {
            this.sala = sala;
            this.numAsientos = numAsientos;
        }

        public ENSala(ENSala sala)
        {
            this.sala = sala.sala;
            this.numAsientos = sala.numAsientos;
        }

        public bool readSala()
        {
            CADSala sala = new CADSala();
            return sala.readSala(this);
        }

        public bool createSala()
        {
            CADSala sala = new CADSala();
            if (!sala.readSala(this))
            {
                return sala.createSala(this);
            }

            return false;
        }

        public bool updateSala()
        {
            ENSala aux = new ENSala(this);
            CADSala sala = new CADSala();

            aux.sala = this.sala;
            aux.numAsientos = this.numAsientos;

            if (sala.readSala(this))
            {
                this.sala = aux.salaSala;
                this.numAsientos = aux.numAsientos;

                return sala.updateSala(this);
            }

            return false;
        }

        public bool deleteSala()
        {
            CADSala sala = new CADSala();

            if (sala.readSala(this)) 
                return sala.deleteSala(this);

            return false;
        }


        public override string ToString()
        {
            return "Sala: " + sala + ". Capacidad: " + numAsientos;
        }
    }
}
