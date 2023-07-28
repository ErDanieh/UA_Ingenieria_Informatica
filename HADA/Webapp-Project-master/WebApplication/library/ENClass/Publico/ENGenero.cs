using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENGenero
    {

        private string id_genero;

        public string generoPelicula
        {
            get { return id_genero; }
            set { id_genero = value; }
        }

        public ENGenero(ENGenero genero)
        {
            this.id_genero = genero.id_genero;
        }

        public ENGenero(string id_genero)
        {
            this.id_genero = id_genero;
        }


        public bool readGenero()
        {
            CADGenero genero = new CADGenero();
            return genero.readGenero(this);
        }

        public bool createGenero()
        {
            CADGenero genero = new CADGenero();
            if (!genero.readGenero(this))
            {
                return genero.createGenero(this);
            }

            return false;
        }



        public bool updateGenero()
        {
            ENGenero aux = new ENGenero(this);
            CADGenero genero = new CADGenero();

            if (genero.readGenero(this))
            {
                this.id_genero = aux.id_genero;
               
                return genero.updateGenero(this);
            }

            return false;
        }

        public bool deleteGenero()
        {
            CADGenero genero = new CADGenero();

            if (genero.readGenero(this)) return genero.deleteGenero(this);

            return false;
        }

        public static DataSet todosrGeneros()
        {
            CADGenero sesion = new CADGenero();
            return sesion.todosrGeneros();
        }

        public override string ToString()
        { 
            return "Genero: " + id_genero;
        }

    }
}
