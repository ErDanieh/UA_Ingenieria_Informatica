with Ada.Text_IO;
use Ada.Text_IO;

package body pkg_ejercicio2 is
   procedure otroMensaje is
   begin
      Put_Line("Vamos a iniciarnos en el lenguaje Ada");
   end otroMensaje;

   function getNotaMedia return Float is
   begin
      return notaMedia;
   end getNotaMedia;

end pkg_ejercicio2;
