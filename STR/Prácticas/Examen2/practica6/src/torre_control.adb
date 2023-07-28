package body torre_control is

   task body TorreDeControl is
      pista : T_PistaAterrizaje := PISTA1;
   begin
      delay 20.0;

      loop
         --En bucle se pregunta si hay alguna petición de solicitardescenso
         --sino la hay pregunta si hay de solcitarAterrizaje
         select
            accept SolicitarDescenso
              (avion      : in     T_RecordAvion;
               concedido : out Boolean;
               pistaAvion :    out T_PistaAterrizaje)
            do

               if avion.aereovia = T_Rango_AereoVia'Last
               then
                  requeue TorreDeControl.SolicitarAterrizaje;
                  end if;

               -- Comprobamos si no hay 5 aviones ya ocupandola.
               if arrayAerovias (avion.aereovia + 1).cantidad /= MAX_AVIONES_AEROVIA
               then

                  concedido := True;

                  -- Comprobamos que la aerovia no sea la ultima.
                  if avion.aereovia + 1 /= T_Rango_AereoVia'Last then
                     -- si no lo es, actualizamos la cantidad de aviones en la aerovia siguiente, y la actual.
                     arrayAerovias (avion.aereovia + 1).incrementarAviones;

                  else
                     concedido := false;
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
         or
              --Solicitud de aterrizajes
            accept SolicitarAterrizaje (avion : in T_RecordAvion; concedido : out Boolean) do
               --La torre de control deriva al avion a la solicitud de aterrizaje

               if avion.pista = PISTA1 AND not OPP1.aterrizando then
                  concedido := true;
                   OPP1.PreguntarPista(avion);
               elsif avion.pista = PISTA2 AND not OPP2.aterrizando then
                  concedido := true;
                   OPP2.PreguntarPista(avion);
               else
                  concedido := false;
               end if;

            end SolicitarAterrizaje;

            delay 2.0;
            end select;
         end loop;

      end TorreDeControl;


   end torre_control;
