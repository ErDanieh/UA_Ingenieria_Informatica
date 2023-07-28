using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENHorario
    {
        private DateTime id;


        public DateTime idHorario
        {
            get { return id; }
            set { id = value; }
        }

        public ENHorario()
        {
            this.id = new DateTime();
        }

        public ENHorario(ENHorario horario)
        {
            this.id = horario.id;
        }

        public bool readHorario()
        {
            CADHorario horario = new CADHorario();
            return horario.readHorario(this);
        }

        public bool createHorario()
        {
            CADHorario horario = new CADHorario();
            if (!horario.readHorario(this))
            {
                return horario.createHorario(this);
            }

            return false;
        }

        public bool updateHorario()
        {
            ENHorario aux = new ENHorario(this);
            CADHorario horario = new CADHorario();

            aux.id = this.id;

            if (horario.readHorario(this))
            {
                this.id = aux.id;
                return horario.updateHorario(this);
            }

            return false;
        }

        public bool deleteHorario()
        {
            CADHorario horario = new CADHorario();

            if (horario.readHorario(this))
                return horario.deleteHorario(this);

            return false;
        }

        public int diaEmpieza()
        {
            return this.id.Day;
        }

        public int mesEmpieza()
        {
            return this.id.Month;
        }

        public int anyoEmpieza()
        {
            return this.id.Year;
        }

        public int horaEmpieza()
        {
            return this.id.Hour;
        }

        public int minutoEmpieza()
        {
            return this.id.Minute;
        }

        public static bool isValidDate(string txtDate)
        {
            DateTime date;
            return DateTime.TryParse(txtDate, out date);
        }



    }
}