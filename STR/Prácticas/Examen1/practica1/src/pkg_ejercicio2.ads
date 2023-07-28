with Ada.Text_IO,Ada.Float_Text_IO;
package pkg_ejercicio2 is
   --Esto ya era un enumerado creo
   type TdiasSemana is (Lunes, Martes, Miercoles,
                        Jueves, Viernes,
                        Sabado, Domingo);
   --Transformamos el TdiasSemana en un enumerado legible para poder hacer input output
   package enumerado_TdiasSemana is new Ada.Text_IO.Enumeration_IO(Enum => TdiasSemana);

   numAlumnos: Integer := 19;
   procedure otroMensaje;
   function getNotaMedia return Float;

private
   notaMedia: Float:=6.12;
end pkg_ejercicio2;
