package body pkg_crono2 is

   task body actualizarCrono is
      Inicio : Time;
      periodo : constant Duration := 5.0;
      Siguiente : Time;   
   begin
      Inicio:= Clock;
      Siguiente := Clock + periodo;
      loop
         Actualiza_Cronometro(Clock - Inicio);
         delay until Siguiente;
         Siguiente := Siguiente + periodo;
      end loop;
     
   end;

end pkg_crono2;
