package body torre_control is

   task body TorreDeControl is
      pista : T_PistaAterrizaje := PISTA1;
   begin
      delay 20.0;

      loop
         accept SolicitarDescenso
           (avion      : in     T_RecordAvion;
            concedido : out Boolean;
            pistaAvion :    out T_PistaAterrizaje)
         do

            -- Comprobamos si no hay 5 aviones ya ocupandola.
            if arrayAerovias (avion.aereovia + 1).cantidad /= MAX_AVIONES_AEROVIA
            then

               concedido := True;

               -- Comprobamos que la aerovia no sea la ultima.
               if avion.aereovia + 1 /= T_Rango_AereoVia'Last then
                  -- si no lo es, actualizamos la cantidad de aviones en la aerovia siguiente, y la actual.
                  arrayAerovias (avion.aereovia + 1).incrementarAviones;

               end if;

               -- Si el avion no tiene pista de aterrizaje asignada, se lo asignamos.
               if avion.pista = SIN_PISTA then
                  pistaAvion := pista;
                  pista      := (if pista = PISTA1 then PISTA2 else PISTA1);

               end if;

            else
               -- Si la rejilla no esta libre o la aerovia esta llena, false.
               concedido := False;

            end if;
         end SolicitarDescenso;

         delay 2.0;

      end loop;
   end TorreDeControl;


end torre_control;
