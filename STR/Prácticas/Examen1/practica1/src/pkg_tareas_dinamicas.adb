with Ada.Text_IO; use Ada.Text_IO;
package body pkg_tareas_dinamicas is
   task body TareaGeneraAviones is
      tarea_avion : Ptr_TareaAvion;
      ptr_avion : Ptr_T_RecordAvion;
   begin
      for id in T_IdAvion loop
         for aereovia in T_Rango_AereoVia'First..T_Rango_AereoVia'Last - 2 loop
            -- inicializar datos de un nuevo avion
            ptr_avion := new T_RecordAvion;
            ptr_avion.id := id;
            ptr_avion.velocidad.x := VELOCIDAD_VUELO;
            ptr_avion.velocidad.y := 0;
            ptr_avion.aereovia := aereovia;
            ptr_avion.tren_aterrizaje := False;
            -- Crear una tarea para el comportamiento del avion
            tarea_avion := NEW T_TareaAvion(ptr_avion);
         end loop;
      end loop;
   end TareaGeneraAviones;
   TASK BODY T_TareaAvion IS
   begin
      Put_line("TASK Avion: " & T_IdAvion'Image(ptr_avion.id) & " -"
               & T_Rango_AereoVia'Image(ptr_avion.aereovia));
   end T_TareaAvion;
end pkg_tareas_dinamicas;
