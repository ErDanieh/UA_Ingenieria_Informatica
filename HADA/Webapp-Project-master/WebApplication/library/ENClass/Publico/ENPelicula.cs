using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENPelicula
    {

        private int id;

        private string nombre;

        private string descripcion;

        private int duracion;

        private string img;

        private string trailer;

        private DateTime fechaEstreno;

        private int valoracion; // Lo sacamos de la bse de datos

        private ENGenero genero;



        public int idPelicula
        {
            get { return id; }
            set { id = value; }
        }

        public DateTime fechaEstrenoPelicula
        {
            get { return fechaEstreno; }
            set { fechaEstreno = value; }
        }

        public string trailerPelicula
        {
            get { return trailer; }
            set { trailer = value; }
        }

        public string nombrePelicula
        {
            get { return nombre; }
            set { nombre = value; }
        }
        public int duracionPelicula
        {
            get { return duracion; }
            set { duracion = value; }
        }
        public int valoracionPelicula
        {
            get { return valoracion; }
            set { valoracion = value; }
        }
        public string descripcionPelicula
        {
            get { return descripcion; }
            set { descripcion = value; }
        }
        public string imgPelicula
        {
            get { return img; }
            set { img = value; }
        }

        public ENGenero generoPelicula
        {
            get { return genero; }
            set { genero = value; }
        }


        public ENPelicula()
        {
            this.id = 0;
            this.nombre = "";
            this.descripcion = "";
            this.duracion = 0;
            this.img = "";
            this.valoracion = 0;
            this.trailer = "";

        }

        public ENPelicula(ENPelicula pelicula)
        {
            this.id = pelicula.id;
            this.nombre = pelicula.nombre;
            this.descripcion = pelicula.descripcion;
            this.duracion = pelicula.duracion;
            this.img = pelicula.img;
            this.valoracion = pelicula.valoracion;
            this.genero = pelicula.genero;
            this.trailer = pelicula.trailer;
        }

        public ENPelicula(int id, string nombre, string descripcion, int duracion, string img,string trailer, int valoracion, ENGenero genero)
        {
            this.id = id;
            this.nombre = nombre;
            this.descripcion = descripcion;
            this.duracion = duracion;
            this.img = img;
            this.valoracion = valoracion;
            this.genero = genero;
            this.trailer = trailer;

        }

        public bool readPelicula()
        {
            CADPelicula pelicula = new CADPelicula();
            return pelicula.readPelicula(this);
        }

        public bool createPelicula()
        {
            CADPelicula pelicula = new CADPelicula();
            if (!pelicula.readPelicula(this))
            {
                return pelicula.createPelicula(this);
            }

            return false;
        }



        public bool updatePelicula()
        {
            ENPelicula aux = new ENPelicula(this);
            CADPelicula pelicula = new CADPelicula();

            if (pelicula.readPelicula(this))
            {
                this.id = aux.id;
                this.nombre = aux.nombre;
                this.descripcion = aux.descripcion;
                this.duracion = aux.duracion;
                this.img = aux.img;
                this.valoracion = aux.valoracion;
                this.trailer = aux.trailer;
                this.genero = aux.genero;


                return pelicula.updatePelicula(this);
            }

            return false;
        }

        public bool deletePelicula()
        {
            CADPelicula pelicula = new CADPelicula();

            if (pelicula.readPelicula(this)) return pelicula.deletePelicula(this);

            return false;
        }

        public bool deletePeliculaPendientes()
        {
            CADPelicula pelicula = new CADPelicula();

            if (pelicula.readPelicula(this)) return pelicula.deletePeliculaPendientes(this);

            return false;
        }


        public bool deletePeliculaSesion()
        {
            CADPelicula pelicula = new CADPelicula();

            if (pelicula.readPelicula(this)) return pelicula.deletePeliculaSesion(this);

            return false;
        }


        public bool deletePeliculaTener()
        {
            CADPelicula pelicula = new CADPelicula();

            if (pelicula.readPelicula(this)) return pelicula.deletePeliculaTener(this);

            return false;
        }

        /// <summary>
        /// Muestra todas las peliculas de la base de Datos
        /// </summary>
        /// <returns></returns>
        public static DataTable mostrarPeliculas()
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarPeliculas();
            return d;
        }

        /// <summary>
        /// Muestra todas las peliculas de la base de Datos
        /// </summary>
        /// <returns></returns>
        public static DataTable mostrarDESC()
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarDESC();
            return d;
        }

        public static DataTable mostrarASC()
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarASC();
            return d;
        }


        public static DataTable mostrarMisPelis(string email)
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarMisPelis(email);
            return d;
        }

        public static DataTable mostrarPelisVistas(string email)
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarPelisVistas(email);
            return d;
        }

        /// <summary>
        /// Obtiene las peliculas que comienzan por el parametro de entrada
        /// </summary>
        /// <param name="pelicula"></param>
        /// <returns></returns>
        public static DataTable mostrarSelect(string nombrePelicula)
        {
            DataTable d = new DataTable();
            CADPelicula pelicula = new CADPelicula();
            d = pelicula.mostrarSelect(nombrePelicula);
            return d;
        }


        /// <summary>
        /// Nos muestra todos los juegos de la misma categoria
        /// </summary>
        /// <param name="genero"></param>
        /// <returns></returns>
        public static DataTable muestraGenero(string genero)
        {
            CADPelicula peli = new CADPelicula();
            DataTable peliculas;
            peliculas = peli.muestraGenero(genero);

            return peliculas;
        }

        public static DataTable muestraGeneroOrdenado(string genero, string orden)
        {
            CADPelicula peli = new CADPelicula();
            DataTable peliculas = peli.muestraGeneroOrdenado(genero, orden);
            return peliculas;
        }

        public static DataSet mostrarHoras(int idPelicula, string dia)
        {
            CADSesion sesion = new CADSesion();
            return sesion.mostrarHoras(idPelicula, dia);
        }




        public override string ToString()
        {
            return "id: " + this.id + " Nombre: " + this.nombre + " Descripcion: " + this.descripcion + " Duracion: " + this.duracion + " Imagine: "
                + this.img + " Valoración: " + this.valoracion + " Genero: " + this.genero;
        }

    }
}
