package body esperaAleatoriaRealTime is

   procedure desviacionLocal is
      subtype rango is Natural range 1..7;
      package pkg_randomPeriodo is new Ada.Numerics.Discrete_Random(rango);
      generador_Random : pkg_randomPeriodo.generator;
      periodo : Integer;
   begin
      pkg_randomPeriodo.Reset(generador_Random);
      loop
         periodo:= pkg_randomPeriodo.Random(generador_Random);
         Put_Line("Voy a esperar:" & periodo'Image);
         delay Duration(periodo);
      end loop;
   end;
   
   procedure desviacionAcumulativa is 
      subtype rango is Natural range 1..7;
      package pkg_generaPeriodo is new Ada.Numerics.Discrete_Random(rango);
      generador_Random : pkg_generaPeriodo.Generator;
      periodo : Integer := 1;
      Siguiente: Time;
   begin
      pkg_generaPeriodo.Reset(generador_Random);
      Siguiente := Clock + Seconds(periodo);
      loop
         periodo:= pkg_generaPeriodo.Random(generador_Random);
         Put_Line("Vamos a esperar:" & periodo'Image);
         delay until Siguiente;
         Siguiente := Siguiente + Seconds(periodo);
         
      end loop;
      
   end;
   

end esperaAleatoriaRealTime;
