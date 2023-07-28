using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENSesion
    {
        private int id;

        private ENHorario horario;

        private ENSala sala;

        private ENPelicula pelicula;

        private ENAsiento[] asientos;

        private int disponibles;


        public int idSesion
        {
            get { return id; }
            set { id = value; }
        }

        public int disponibleSesion
        {
            get { return disponibles; }
            set { disponibles = value; }
        }

        public ENHorario horaSesion
        {
            get { return horario; }
            set { horario = value; }
        }

        public ENSala salaSesion
        {
            get { return sala; }
            set { sala = value; }
        }

        public ENPelicula peliculaSesion
        {
            get { return pelicula; }
            set { pelicula = value; }
        }

        public ENAsiento[] asientosSesion
        {
            get { return asientos; }
            set { asientos = value; }
        }

        public ENSesion()
        {
            this.id = 0;
            this.horario = new ENHorario();
            this.sala = new ENSala();
            this.pelicula = new ENPelicula();
           // for(int i = 0; i<= 42; i++)
            //{
              //  this.asientos.Append(new ENAsiento());
            //}
           this.disponibles = 42;
        }

        public ENSesion(ENSesion sesion)
        {
            this.id = sesion.id;
            this.horario = sesion.horario;
            this.sala = sesion.sala;
            this.pelicula = sesion.pelicula;
            this.asientos = sesion.asientos;
            this.disponibles = sesion.disponibles;
        }

        public ENSesion(int id, ENHorario horario, ENSala sala, ENPelicula pelicula, ENAsiento[] asientos, int disponibles)
        {
            this.id = id;
            this.horario = horario;
            this.sala = sala;
            this.pelicula = pelicula;
            this.asientos = asientos;
            this.disponibles = disponibles;
        }

        public bool sesionLLena()
        {
            return disponibles == 0;
        }


        public bool readSesion()
        {
            CADSesion sesion = new CADSesion();
            return sesion.readSesion(this);
        }

        public bool createSesion()
        {
            CADSesion sesion = new CADSesion();
            if (!sesion.readSesion(this))
            {
                return sesion.crearSesion(this);
            }

            return false;
        }



        public bool updateSesion()
        {
            ENSesion aux = new ENSesion(this);
            CADSesion sesion = new CADSesion();

            if (sesion.readSesion(this))
            {
                this.id = aux.id;
                this.horario = aux.horario;
                this.sala = aux.sala;
                this.pelicula = aux.pelicula;
                this.asientos = aux.asientos;
                this.disponibles = aux.disponibles;
                return sesion.updateSesion(this);
            }

            return false;
        }

        public bool deleteSesion()
        {
            CADSesion sesion = new CADSesion();

            if (sesion.readSesion(this)) 
                return sesion.deleteSesion(this);

            return false;
        }

        public static DataTable mostrarHorarios(int idPelicula)
        {
            CADSesion sesion = new CADSesion();
            return sesion.mostrarHorarios(idPelicula);
        }




        public static DataSet diasSesionesPelicula(int idPelicula)
        {
            CADSesion sesion = new CADSesion();
            return sesion.diasSesionesPelicula(idPelicula);
        }

        public static DataSet mostrarHoras(int idPelicula, string dia)
        {
            CADSesion sesion = new CADSesion();
            return sesion.mostrarHoras(idPelicula, dia);
        }

        public static DataTable mostrarAsientos( string idsesion , int idPelicula  )
        {
            CADSesion sesion = new CADSesion();
            return sesion.mostrarAsientos( idsesion, idPelicula);

        }
        public static DataTable mostrarAsientos2()
        {
            CADSesion sesion = new CADSesion();

            return sesion.mostrarAsientos2();
        }


        public override string ToString()
        {
            return "Id: " + this.id + ". Horario: " + horario;
        }

    }
}
