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
                        
            delay(Duration(Pkg_generadorRetardo.random(generador_retardo)));
            --Anadir delay generando numero aleatorio
            
            
         end loop;
      end loop;
      
  
      
      
   end TareaGeneraAviones;
   
   
   --Tarea que contiene la logica de los aviones
   
   TASK BODY T_TareaAvion IS
      avion: T_RecordAvion;
      pos_siguiente: T_CoordenadaX;
   begin
      avion:= ptr_avion.all;
      
      --Generamos el avion
      Put_line("TASK Avion: " & T_IdAvion'Image(ptr_avion.id) & " -"
               & T_Rango_AereoVia'Image(ptr_avion.aereovia));
        
      Escribir("Informacion del vuelo: " & avion.id'Image);
      arrayAerovias(avion.aereovia).AeroviaDisponible(Posicion_Rejilla(avion.pos.X));
      Aparece(avion);
      
      --Bucle de movimientos del avion
      loop
         pos_siguiente:= Nueva_PosicionX(avion.pos.X, avion.velocidad.X);
         if Posicion_Rejilla(avion.pos.X) /= Posicion_Rejilla(pos_siguiente) then
            arrayAerovias(avion.aereovia).cambiar(Posicion_Rejilla(pos_siguiente), Posicion_Rejilla(avion.pos.X));
            Actualiza_Movimiento(avion);
         else
            Actualiza_Movimiento(avion);
         end if;
         delay Duration(RETARDO_MOVIMIENTO);
      end loop;
      
      --En el caso de que se choque salta excepcion
   exception
      when event : DETECTADA_COLISION =>
         Desaparece(avion);
         Escribir("ERROR en TASK ...: " & Exception_Name(Exception_Identity(event)));
      when event: others =>
         PKG_debug.Escribir("ERROR en TASK: " & avion.id'Image & ", Excepcion: " & Exception_Name(Exception_Identity(event)));
         
      
   end T_TareaAvion;

end GeneraAviones;
