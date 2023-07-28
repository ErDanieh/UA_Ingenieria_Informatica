package body pkg_protegidos is
   
   function Posicion_Rejilla(pos_x : T_CoordenadaX) return T_Rango_Rejilla_X is
   begin
      return T_Rango_Rejilla_X(pos_x * TAM_X_REJILLA / (X_INICIO_DER_AVION+1));
   end Posicion_Rejilla;
   
   protected body OP_Aerovia is
      --Comprueba si esta libre
      function esLibre(posX : T_Rango_Rejilla_X) return Boolean is
      begin
         return not aire(posX);
      end esLibre;
      
      --Cambia el valor a ocupado
      procedure ocupar(posX : T_Rango_Rejilla_X) is 
      begin 
         aire(posX) := True;
      end ocupar;

      --Cambia el valor a libre
      procedure librar(posX : T_Rango_Rejilla_X) is 
      begin 
         aire(posX) := False;
      end librar;

      procedure cambiar(bloq: T_Rango_Rejilla_X; lib: T_Rango_Rejilla_X) is
      begin
         librar(lib);
         ocupar(lib);
      end cambiar;
      
      function cantidad return contador is
      begin 
         return conta;
      end cantidad;
      
      procedure incrementarAviones is
      begin 
         conta := conta + 1;
      end incrementarAviones;
      
      procedure decrementarAviones is
      begin
         conta := conta - 1;
      end decrementarAviones;
      
      -- Cuando accedemos a la unidad protegida, creamos una barrera.
      entry AeroviaDisponible(posX: T_Rango_Rejilla_X) when
      not aire(T_Rango_Rejilla_X'First) 
        and not aire(T_Rango_Rejilla_X'Last) 
        and not aire(T_Rango_Rejilla_X'First + 1) 
        and not aire(T_Rango_Rejilla_X'Last - 1) and
        conta <= MAX_AVIONES_AEROVIA is
      begin
         -- Logica a ejecutar si pasa la barrera.
         if posX = T_Rango_Rejilla_X'First then
            aire(T_Rango_Rejilla_X'First) := True;
         else
            aire(T_Rango_Rejilla_X'Last) := True;
         end if;    
         incrementarAviones;
      end AeroviaDisponible;

   end OP_Aerovia;
end pkg_protegidos;
