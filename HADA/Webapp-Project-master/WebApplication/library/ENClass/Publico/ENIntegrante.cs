using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENIntegrante
    {

        private string nombre;

        private string apellido;

        private bool director;

        private ENPelicula[] aparece;

        public string nombreIntegrante
        {
            get { return nombre; }
            set { nombre = value; }
        }

        public string apellidoIntegrante
        {
            get { return apellido; }
            set { apellido = value; }
        }

        public ENPelicula[] apareceIntegrante
        {
            get { return aparece; }
            set { aparece = value; }
        }

        public bool directorIntegrante
        {
            get { return director; }
            set { director = value; }
        }


        public ENIntegrante()
        {
            this.nombre = "";
            this.apellido = "";
            this.director = false;
            this.aparece = null;
        }



        public ENIntegrante(string nombre, string apellido, bool director, ENPelicula[] peliculas)
        {
            this.nombre = nombre;
            this.apellido = apellido;
            this.director = director;
            this.aparece = peliculas;
        }

        public ENIntegrante(ENIntegrante integrante)
        {
            this.nombre = integrante.nombre;
            this.apellido = integrante.apellido;
            this.director = integrante.director;
            this.aparece = integrante.aparece;
        }


        public bool readIntegrante()
        {
            CADIntegrante integrante = new CADIntegrante();
            return integrante.readIntegrante(this);
        }

        public bool createIntegrante()
        {
            CADIntegrante integrante = new CADIntegrante();
            if (!integrante.readIntegrante(this))
            {
                return integrante.createIntegrante(this);
            }

            return false;
        }



        public bool updateIntegrante()
        {
            ENIntegrante aux = new ENIntegrante();
            CADIntegrante integrante = new CADIntegrante();

            if (integrante.readIntegrante(this))
            {
                this.nombre = aux.nombre;
                this.apellido = aux.apellido;
                this.director = aux.director;
                this.aparece = aux.aparece;
                return integrante.updateIntegrante(this);
            }

            return false;
        }

        public bool deleteIntegrante()
        {
            CADIntegrante integrante = new CADIntegrante();

            if (integrante.readIntegrante(this)) return integrante.deleteIntegrante(this);

            return false;
        }

        public override string ToString()
        {
            return "Nombre: " + nombre + "Apellido: " + apellido + " Es director: " + director.ToString() + "Aparece en: " + aparece;
        }
    }
}
