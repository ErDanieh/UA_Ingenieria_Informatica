with Ada.Numerics.Discrete_Random; --paquete random generico
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Text_IO; use Ada.Text_IO;


--Este procedure imprime un numero aleatorio cada vez que se le da al intro

procedure ejercicio6 is
   subtype T_Digito is Integer range 0..9;
   package Pkg_DigitoAleatorio is new Ada.Numerics.Discrete_Random (T_Digito);
   generador_digito : pkg_DigitoAleatorio.Generator; -- declarar generador de 
   --valores aleatorios tipo T_Digito
   digito: T_Digito;

begin
   pkg_DigitoAleatorio.Reset (Generador_Digito); -- Inicializa generador números aleatorios
   loop
      digito:= Pkg_DigitoAleatorio.Random(generador_digito);
      --Se esta utilizando el paque de Integer_Text_IO ya que se le pasa un entero
      Put(digito);
      Skip_Line;
   end loop;
   
end ejercicio6;
