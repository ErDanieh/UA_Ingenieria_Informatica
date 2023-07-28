package body esperaAleatoriaCalendar is
   
   procedure esperaCalendarLocal is
      --Variable para  el clock
      Inicio: Time;
      --Paquete para el random
      package pkg_randomPeriodo is new Ada.Numerics.Discrete_Random(rango);
      generadorRandom : pkg_randomPeriodo.Generator;
      valorGenerado : Integer;
     
   begin
      pkg_randomPeriodo.reset(generadorRandom);
      Inicio:= Clock;
      loop
         valorGenerado := pkg_randomPeriodo.Random(generadorRandom);
         Inicio := Inicio + Duration(valorGenerado);
         Put_Line("Vamos a esperar: " & valorGenerado'Image);
         delay until Inicio;
      end loop;
   end;
   
   procedure esperaCalendarDesviada is 
      periodo: constant duration:= 5.0;
      siguiente: Time;
   begin
      siguiente:= clock + periodo;
      loop
         Put_Line("Vamos a esperar:");
         delay periodo;
      end loop;
   end;
   
   
end esperaAleatoriaCalendar;
