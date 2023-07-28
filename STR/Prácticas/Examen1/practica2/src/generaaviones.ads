with PKG_tipos;
use PKG_tipos;

with Ada.Numerics.Discrete_Random; --paquete random generico
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Text_IO; use Ada.Text_IO;
with PKG_graficos;
use PKG_graficos;
with PKG_debug;
use PKG_debug;
with Ada.Exceptions;
use Ada.Exceptions;



package GeneraAviones is
   TASK TareaGeneraAviones;
   -- Tipo tarea encargada del comportamiento de un avion
   TASK TYPE T_TareaAvion(ptr_avion : Ptr_T_RecordAvion);
   --Puntero al avion para poder pasarle datos
   type Ptr_TareaAvion is access T_TareaAvion;
end GeneraAviones;
