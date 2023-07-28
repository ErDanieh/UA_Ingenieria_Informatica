with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Float_Text_IO;
with pkg_ejercicio2;
with ADA.IO_EXCEPTIONS;

procedure ejercicio3 is
   diaS : pkg_ejercicio2.TdiasSemana;
   pos : Natural;
   valor : pkg_ejercicio2.TdiasSemana;

begin
   Ada.Float_Text_IO.Put(pkg_ejercicio2.getNotaMedia);
   New_Line;

   --Bucle donde la variable dia adquiere valores enteros
   for dia in pkg_ejercicio2.TdiasSemana loop
      --Imprimimo el valor de la posicion de dia
      pkg_ejercicio2.enumerado_TdiasSemana.Put(dia);
      New_Line;
   end loop;

   New_Line;

   --Recogemos un valor del usuario en este caso un string
   Put(Item => "Introduce un dia cualquiera");
   New_Line;

   --Buscamos dentro del enumerado el item sino es parte del salta excepcion
   pkg_ejercicio2.enumerado_TdiasSemana.Get(diaS);


   --Sacamos la posicion del valor introducido
   pos:= pkg_ejercicio2.TdiasSemana'Pos(diaS);
   --Ada.Integer_Text_IO.Put(pos);
   --Obtenemos el valor de la posicion dentro del tipo
   valor:= pkg_ejercicio2.TdiasSemana'Val(pos);

   if pos > 0 then
      Put("No hay clase de STR");
   else
      Put("Si hay clase de STR");
   end if;

   New_Line;

   Put("Has seleccionado el dia");
   New_Line;
   --Imprimimos el valor del enumerado
   pkg_ejercicio2.enumerado_TdiasSemana.Put(Item => valor);
   --Sino se introduce un valor del enumerado salta una excepcion


exception
   when ADA.IO_EXCEPTIONS.DATA_ERROR =>
      Put("No esta en el enumerado");


end ejercicio3;
