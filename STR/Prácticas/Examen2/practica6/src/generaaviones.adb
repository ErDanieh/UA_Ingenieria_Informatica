package body GeneraAviones is
   
   task body TareaGeneraAviones is
      
      --Puntero al avion
      tarea_avion : Ptr_TareaAvion;
      --Puntero a los datos del avion
      ptr_avion : Ptr_T_RecordAvion;
      
      --Rango de aparicion aleatorio
      package Pkg_generadorRetardo is new Ada.Numerics.Discrete_Random (T_RetardoAparicionAviones);
      generador_retardo: Pkg_generadorRetardo.Generator;
      --retardo : T_RetardoAparicionAviones;
      
      
      --Rango de color aleatorio
      package Pkg_generadorColor is new Ada.Numerics.Discrete_Random (T_ColorAparicionAvion);
      generador_color: Pkg_generadorColor.Generator;
      --retardo : T_RetardoAparicionAviones;
      
      
   begin
      --Resetear las semillas
      Pkg_generadorRetardo.Reset(generador_retardo);
      Pkg_generadorColor.Reset(generador_color);
    
      for id in T_IdAvion loop
         for aereovia in T_Rango_AereoVia'First..T_Rango_AereoVia'Last - 2 loop
            
            -- inicializar datos de un nuevo avion
            ptr_avion := new T_RecordAvion;
            
            --Datos del avion
            ptr_avion.id := id;
            ptr_avion.velocidad.x := VELOCIDAD_VUELO;
            ptr_avion.velocidad.y := 0;
            ptr_avion.aereovia := aereovia;
            ptr_avion.tren_aterrizaje := False;
            ptr_avion.aereovia_inicial := aereovia;
            ptr_avion.pista := SIN_PISTA;
            ptr_avion.color := Pkg_generadorColor.random(generador_color);
            ptr_avion.pos := Pos_Inicio(aereovia);
                  
            --Cambia la dirección de vuelo del avion
            if ptr_avion.aereovia rem 2 = 0 then
               ptr_avion.velocidad.X := VELOCIDAD_VUELO;
            else
               ptr_avion.velocidad.X := -VELOCIDAD_VUELO;
            end if;
            -- Crear una tarea para el comportamiento del avion 
            tarea_avion := NEW T_TareaAvion(ptr_avion);
            --Anadir delay generando numero aleatorio            
            delay(Duration(Pkg_generadorRetardo.random(generador_retardo)));
            
         end loop;
      end loop;      
   end TareaGeneraAviones;
   
   
   --Tarea que contiene la logica de los aviones
   
   task body T_TareaAvion is
      -- Variables que usaremos en todo el contexto de esta task.
      rejillaSiguiente : T_Rango_Rejilla_X;
      rejillaActual    : T_Rango_Rejilla_X;

      -- Tenemos implicitamente ptr_avion (avion en la especificacion), pasado por parametro.
      avion : T_RecordAvion;

      -- Variables que pasaremos por *referencia* a la torre de control ( entrySolicitarDescenso accept de 'SolicitarDescenso' ).
      descensoConcedido : Boolean := False;
      aterrizajeConcedido: Boolean := False;
      pista             : T_PistaAterrizaje;

      -- Procedura de avanzar ( Mueve el avion sobre la misma aerovia ).
      procedure avanza is
      begin
         -- rejillas actuales y siguientes.
         rejillaSiguiente := Posicion_Rejilla (Nueva_PosicionX (avion.pos.X, avion.velocidad.X));
         rejillaActual := Posicion_Rejilla (avion.pos.X);

         -- Si el siguiente pixel (X) hace parte de otra rejilla, elibera la actual y ocupa la siguiente.
         if rejillaActual /= rejillaSiguiente then
            arrayAerovias (avion.aereovia).cambiar
              (rejillaSiguiente, rejillaActual);
         end if;

         -- En cualquier caso, hacemos avanzar el avion.
         Actualiza_Movimiento (avion);
         delay Duration (RETARDO_MOVIMIENTO);

      end avanza;

      -- Procedura de bajada ( cambio de aerovia ).
      procedure baja is
      begin
         rejillaActual := Posicion_Rejilla (avion.pos.X);

         -- Ocupamos la rejilla de la aerovia de abajo.
         arrayAerovias (avion.aereovia).librar (rejillaActual);
         arrayAerovias (avion.aereovia + 1).ocupar (rejillaActual);

         -- Borramos el avion de la aerovia actual.
         Desaparece (avion);

         -- Actualizamos los datos.
         avion.aereovia    := avion.aereovia + 1;
         avion.velocidad.X := (if avion.aereovia rem 2 = 0 then VELOCIDAD_VUELO else -VELOCIDAD_VUELO);

         -- La funcion de Pos_Inicio nos la da el enunciado, hay que ponerlo en graficos ads y adb.
         avion.pos := Pos_Inicio (avion.pos.X, avion.aereovia);

         -- Si no tiene piesta, asigna el color dependiendo de la pista asignada por la torre de control.
         if avion.pista = SIN_PISTA then
            avion.pista := pista;
            avion.color := (if pista = PISTA1 then Green else Red);
         end if;

         -- Renderizamos el avion, con los nuevos datos ahora aprecera en la nueva aerovia.
         Aparece (avion);

         -- Y decrementamos el numero de aviones de la aerovia de la cual descendemos.
         arrayAerovias (avion.aereovia - 1).decrementarAviones;

      end baja;
      
      procedure descender is
      begin
         arrayAerovias (avion.aereovia).librar(Posicion_Rejilla (avion.pos.X));
         Desaparece(avion);
         
         avion.velocidad.X := 0;
         avion.velocidad.Y := VELOCIDAD_VUELO;
         
         Aparece_En_Pista(avion);
         
         
      end descender;

   begin
      Escribir("--- Inicio Tarea T_TareaAvion:" & ptr_avion.id'Image & " ---" & ptr_avion.aereovia'Image);
      avion := ptr_avion.all;

      -- Comprobamos si la rejilla donde aparecemos esta libre, si no lo esta esperamos, si lo esta, la ocupamos y aparecemos.
      Escribir(" -- Comprobando Disponibilidad de Despegue: " & arrayAerovias (avion.aereovia).esLibre(Posicion_Rejilla (avion.pos.X))'Image & ASCII.CR & ASCII.LF);
      arrayAerovias (avion.aereovia).AeroviaDisponible(Posicion_Rejilla (avion.pos.X));
      Aparece (avion);

      loop
         if not aterrizajeConcedido then
            select
               -- Preguntamos a otra task ( torre de control ) si se puede bajar. Las variables 'descensoConcedido' y 'pista', se pasan por referencia.
               TorreDeControl.SolicitarDescenso (avion, descensoConcedido, pista);
               Escribir
                 ("--- Descenso de:" & avion.id'Image &
                    ", desde la aerovia:" & avion.aereovia'Image &
                    ". Hay sitio en la aerovia?: " & descensoConcedido'Image);

               rejillaActual := Posicion_Rejilla (avion.pos.X);

               -- Comprobamos si se puede bajar ( resultado de la torre de control ) y si la misma rejilla ( y las contiguas ) de la siguiente aerovia estan libres.
               if descensoConcedido and
                 arrayAerovias (avion.aereovia + 1).esLibre (rejillaActual) and
                 arrayAerovias (avion.aereovia + 1).esLibre (rejillaActual - 1) and
                 arrayAerovias (avion.aereovia + 1).esLibre (rejillaActual + 1)
               then

                  Escribir
                    (" -- Descenso de:" & avion.id'Image &
                       ", desde la aerovia:" & avion.aereovia'Image &
                       ". Descenso confirmado." & ASCII.CR & ASCII.LF);

                  -- Comprobamos que la siguiente aerovia es la ultima, y si lo es y estamos encima de la pista comenzamos descenso
                  if avion.aereovia = T_Rango_AereoVia'Last AND Pos_Inicio(avion.pista).X = avion.pos.X then
                     --Solicitamos aterrizaje a torre de control
                     TorreDeControl.SolicitarAterrizaje(avion, aterrizajeConcedido);
                  end if;

                  -- En caso de poder bajar y no es la ultima aerovia, bajamos.
                  baja;

               else
                  -- Si no podemos bajar, avanzamos, y decrementamos el contador de la aerovia destino ( Que ha sido incrementado por la torre de control ).
                  Escribir
                    (" -- Descenso de:" & avion.id'Image &
                       ", desde la aerovia:" & avion.aereovia'Image &
                       ". Descenso cancelado." & ASCII.CR & ASCII.LF);
                  arrayAerovias (avion.aereovia + 1).decrementarAviones;
                  avanza;

               end if;
         
               
            then abort
               -- Mientras que el servidor ( torre de control ) tarda en responder, avanzamos.
               avanza;

            end select;
         else
            Escribir
              ("  - Descendiendo:" & avion.id'Image &
                 ", desde aerovia:" & avion.aereovia'Image &
                 ", en pista: " & avion.pista'Image & ASCII.CR & ASCII.LF);
            descender;
           end if;
         end loop;

      exception
         when event : DETECTADA_COLISION =>
            Desaparece (avion);
            Escribir ("--- !!! Se ha estrellado el avion:" & avion.id'Image);

         when event : others =>
            Escribir
              ("--- !!! Error en avion:" & avion.id'Image & "Aerovia: " &
                 avion.aereovia'Image & ",Error:," & ",Excepcion: " &
                 Exception_Name (Exception_Identity (event)));

      end T_TareaAvion;

   end GeneraAviones;
