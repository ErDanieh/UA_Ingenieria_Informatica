with Ada.Text_IO; use Ada.Text_IO;
with pkg_ejercicio2;
with Ada.Integer_Text_IO;


procedure Ejercicio1 is
   s:String := "Comenzando las prácticas de STR";
   numero: Natural:=0;
begin
   Ada.Text_Io.Put("Hola Mundo!!!");
   Ada.Text_Io.Put_Line(s);
   pkg_ejercicio2.otroMensaje;

   --Ejercicio 4a
   begin
      Put("Introduce un numero");
      --Recogemos un entero del usuario en la variable numero
      Ada.Integer_Text_IO.Get(numero);



      case numero is
         when 1 | 2 | 12 => Put_Line("Invierno");
         when 3 | 4 | 5 => Put_Line("Primavera");
         when 6 | 7 | 8 => Put_Line("Verano");
         when 9 | 10 | 11 => Put_Line("Otono");
         when others => Put_Line("Mes incorrecto");
      end case;


   exception
      when CONSTRAINT_ERROR =>
         Put("El numero debe ser > 0");
         New_Line;

   end;

--Ponemos aqui el fin del programa para que no se repita
Put_Line("FIN DEL PROGRAMA");

end Ejercicio1;


--Esto no funciona porque solo puede haber una unidad de compilacion
-- procedure otroMensaje is
--  begin
   --Put_Line("Vamos a iniciarnos en el lenguaje Ada");
--  end otroMensaje
