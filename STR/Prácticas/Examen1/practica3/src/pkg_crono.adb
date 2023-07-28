package body pkg_crono is

   task body actualizarCrono1 is
      segundo : Time_Span := Milliseconds(1000);
      Inicio : Time;
      Siguiente : Time;
   begin
      Inicio := Clock;
      Siguiente := Clock + segundo;
         
      loop
         Actualiza_Cronometro(To_Duration(Clock - Inicio));
         delay until Siguiente;
         Siguiente := Siguiente + segundo;
      end loop;
   end;

end pkg_crono;
