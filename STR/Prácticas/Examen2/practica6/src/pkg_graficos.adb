--************************ PAQUETE PKG_GRAFICOS ***************************
-- Este paquete se encarga de implementar la interfaz gráfica
--*************************************************************************

with Double_Buffer;     use Double_Buffer;
with Gdk.Color;         use Gdk.Color;
with Gtk.Enums;         use Gtk.Enums;
with Gtk.Box;           use Gtk.Box;
with Gtk.Button;        use Gtk.Button;
with Gtk.Widget;        use Gtk.Widget;
with Ada.Float_Text_IO;
with pango.layout; use pango.layout;
with Pango.Font;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
with Gdk.Pixbuf;
with Gdk.Window; use Gdk.Window;
with Gdk; use Gdk;
with Gtk.Grid;
with Gtk.Alignment;
with GNAT.OS_Lib;

package body PKG_graficos is

   ------------------------------------------------------------------------
   -- Procedure que se encarga de redibujar y capturar eventos en la
   -- interfaz gráfica
   ------------------------------------------------------------------------
   procedure Simular_Sistema IS
   BEGIN
      Gtk.Main.Main;
   END Simular_Sistema;


   ------------------------------------------------------------------------
   -- Procedure que se encarga de inicializar la interfaz gráfica
   ------------------------------------------------------------------------
   procedure Inicializar_Interfaz_Grafica is
      Win        : Gtk_Window;
      Buffer     : Gtk_Double_Buffer;
      Vbox, Hbox : Gtk_Box;
      Id         : G_Source_Id;
      Button     : Gtk_Button;
      inbuilt_font : Pango.Font.Pango_Font_Description;
      TAM_BUTTON_EXIT : constant GLib.Gint := 20;
      alinea_button : Gtk.Alignment.Gtk_Alignment;
   begin
      -- ventana principal
      Gtk.Window.Gtk_New (Win, Window_Toplevel);
      Set_Title (Win, "PRACTICA STR: CONTROL DE TRAFICO AEREO");
      Win.Set_Default_Size(CANVAS_WIDTH, CANVAS_HEIGHT);--+TAM_BUTTON_EXIT);
      Void_Cb.Connect (Win, "destroy", Void_Cb.To_Marshaller (Quit'Access));


      -- botón Exit
      Gtk_New (Button, "EXIT");
      Destroyed.Object_Connect (Button,
                                "clicked",
                                Destroyed.To_Marshaller (Quit'Access),
                                Slot_Object => Win);

      Button.Set_Size_Request(100, TAM_BUTTON_EXIT);
      Gtk.Alignment.Gtk_New(alinea_button, 0.5, 0.5, 0.0, 0.0);
      alinea_button.Add(Button);


      --  Double buffer
      Double_Buffer.Gtk_New(Buffer);
      Buffer.Set_Size_Request(CANVAS_WIDTH, CANVAS_HEIGHT);


      -- Asociar widgets a la ventana principal y mostrarla
      Gtk_New_Hbox (Hbox, Homogeneous =>  True, Spacing => 10);
      Gtk_New_Vbox (Vbox, Homogeneous => False, Spacing => 0);

      Pack_Start (Vbox, Buffer);
      Pack_Start (Vbox, alinea_button);--, Expand => False, Fill => False);

      Pack_Start (Hbox, Vbox);


      Win.Add(Hbox);

      Show_All (Win);

      Id := Main_Context_Sources.Timeout_Add (PERIODICIDAD_REDIBUJAR_MILISEGUNDOS,
                                              Draw_Complex_Buffer'Access,
                                              Gtk_Drawing_Area (Buffer));


      Gdk_New(pangoLayout, Get_Pango_Context(Buffer));
      inbuilt_font := Pango.Font.From_String("Courier");
      Pango.Layout.Set_Font_Description(pangoLayout, inbuilt_font);


      -- INICIALIZACIÓN DEL ESTADO DE TODOS LOS OBJETOS VISUALIZADOS
      Inicializar_Buffer_Aviones;

   end Inicializar_Interfaz_Grafica;


   ------------------
   -- Draw_Complex --
   ------------------
   procedure Draw_Complex (Pixmap : Cairo_Context) is
   begin

      Draw_Rectangle (Pixmap, Gris_Fondo_Gc, Filled => True,
                      X     => 0,   Y      => 0,
                      Width => CANVAS_WIDTH, Height => CANVAS_HEIGHT);


      -- DIBUJAR EN EL CANVAS EL ESTADO ACTUAL DE TODOS LOS OBJETOS
      Dibujar_Canvas(Pixmap);

   end Draw_Complex;


   -------------------------
   -- Draw_Complex_Buffer --
   -------------------------
   function Draw_Complex_Buffer (Area : Gtk_Drawing_Area) return Boolean is
      Buffer : Gtk_Double_Buffer := Gtk_Double_Buffer (Area);

   begin
      Draw_Complex (Get_Pixmap (Buffer));

      Double_Buffer.Thaw(Buffer);

      return True;
   end Draw_Complex_Buffer;



   ----------
   -- Quit --
   ----------
   procedure Quit (Win : access Gtk_Window_Record'Class) is
      pragma Warnings (Off, Win);
   begin
      Gnat.OS_Lib.OS_Exit(0);
      --Gtk.Main.Main_Quit;
      --Ada.Task_Identification.Abort_Task(Ada.Task_Identification.Current_Task);
   end Quit;


   ------------------------------------------------------------------------
   -- Procedure que inicializa el buffer de aviones
   ------------------------------------------------------------------------
   procedure Inicializar_Buffer_Aviones is
      avion : T_RecordAvion;
   BEGIN
      for aereovia IN T_Rango_AereoVia loop
         FOR i IN T_RangoBufferAviones LOOP
            avion.id := 0;
            avion.pos.x := 0;
            avion.pos.y := y_aereovia(aereovia);
            avion.velocidad := (0, 0);
            avion.color:= T_ColorAvion'First;
            avion.aereovia := aereovia;
            Pkg_Buffer_aviones.Actualiza_Item(i, avion, buffer_aviones(aereovia));
         END LOOP;
      END LOOP;

   exception
      when event: others =>
         PKG_debug.Escribir("ERROR en Inicializar_Buffer_Aviones: " & Exception_Name(Exception_Identity(event)));

   end Inicializar_Buffer_Aviones;


   ------------------------------------------------------------------------
   -- Función que devuelve la posición de un avion dentro del buffer
   -----------------------------------------------------------------------
   FUNCTION Posicion_Buffer(Id : T_IdAvion; aereovia_inicial: T_Rango_AereoVia;
                            Buffer: Pkg_Buffer_aviones.T_Buffer) RETURN T_RangoBufferAviones is
      avion_aux     : T_RecordAvion;
      pos           : T_RangoBufferAviones;
   BEGIN
      BEGIN
         pos := Pkg_Buffer_aviones.Posicion_Primer_Item(Buffer);
         avion_aux := Pkg_Buffer_aviones.Consulta_Item(pos, Buffer);
         WHILE avion_aux.Id /= Id or avion_aux.aereovia_inicial /= aereovia_inicial LOOP
            pos := pos+1;
            avion_aux := Pkg_Buffer_aviones.Consulta_Item(pos, Buffer);
         END LOOP;
      exception
         when event: others =>
            PKG_debug.Escribir("ERROR en Posicion_Buffer: " & Exception_Name(Exception_Identity(event)));
      end;

      RETURN(Pos);
   END Posicion_Buffer;


   FUNCTION Posicion_Buffer(Id : T_IdAvion; aereovia_inicial: T_Rango_AereoVia;
                            Buffer: Pkg_Buffer_aviones_en_pista.T_Buffer) RETURN T_RangoBufferAvionesAterrizando is
      avion_aux     : T_RecordAvion;
      pos           : T_RangoBufferAvionesAterrizando;
   BEGIN
      BEGIN
         pos := Pkg_Buffer_aviones_en_pista.Posicion_Primer_Item(Buffer);
         avion_aux := Pkg_Buffer_aviones_en_pista.Consulta_Item(pos, Buffer);
         WHILE avion_aux.Id /= Id or avion_aux.aereovia_inicial /= aereovia_inicial LOOP
            pos := pos+1;
            avion_aux := Pkg_Buffer_aviones_en_pista.Consulta_Item(pos, Buffer);
         END LOOP;
      exception
         when event: others =>
            PKG_debug.Escribir("ERROR en Posicion_Buffer en pista: " & Exception_Name(Exception_Identity(event)));
      end;

      RETURN(Pos);
   END Posicion_Buffer;

   ------------------------------------------------------------------------
   -- Hacer aparecer el objeto especificado en el sistema
   ------------------------------------------------------------------------
   PROCEDURE Aparece(avion : in T_RecordAvion) is
   BEGIN
      Pkg_Buffer_Aviones.Insertar_Ultimo_Item(avion, buffer_aviones(avion.aereovia));
   END Aparece;

   PROCEDURE Aparece_En_Pista(avion : in T_RecordAvion) is
   BEGIN
      Pkg_Buffer_aviones_en_pista.Insertar_Ultimo_Item(avion, buffer_aviones_en_pista);
   END Aparece_En_Pista;


   ------------------------------------------------------------------------
   -- Eliminar el objeto especificado
   ------------------------------------------------------------------------
   PROCEDURE Desaparece(avion : in T_RecordAvion) IS
      pos : T_RangoBufferAviones;
   BEGIN
      -- Buscar posición del avion dentro del buffer
      pos := Posicion_Buffer(avion.id, avion.aereovia_inicial, Buffer_Aviones(avion.aereovia));
      Pkg_Buffer_Aviones.Borrar_Item(pos, buffer_aviones(avion.aereovia));
   exception
      when event: others =>
         PKG_debug.Escribir("ERROR en Desaparece avion: " & Exception_Name(Exception_Identity(event)));

   end Desaparece;


   PROCEDURE Desaparece_En_Pista(avion : in T_RecordAvion) IS
      pos : T_RangoBufferAvionesAterrizando;
   BEGIN
      -- Buscar posición del avion dentro del buffer
      pos := Posicion_Buffer(avion.id, avion.aereovia_inicial, buffer_aviones_en_pista);
      Pkg_Buffer_aviones_en_pista.Borrar_Item(pos, buffer_aviones_en_pista);
   exception
      when event: others =>
         PKG_debug.Escribir("ERROR en Desaparece avion en pista: " & Exception_Name(Exception_Identity(event)));

   end Desaparece_En_Pista;

   ------------------------------------------------------------------------
   -- Función que devuelve las coordenadas de la posición inicial de un objeto
   ------------------------------------------------------------------------
   FUNCTION Pos_Inicio(aereovia : T_Rango_AereoVia) RETURN T_Punto IS
   BEGIN
      if aereovia mod 2 = 0 then
         RETURN (X=>X_INICIO_DER_AVION, Y=>y_aereovia(aereovia));
      else
         RETURN (X=>0, Y=>y_aereovia(aereovia));
      end if;
   END Pos_Inicio;


   FUNCTION Pos_Inicio(pista : T_PistaAterrizaje) RETURN T_Punto IS
   BEGIN
      return (X=>x_pista(T_PistaAterrizaje'Pos(pista))+TAM_AVION+20, Y=>Y_INICIO_PISTA);
   END Pos_Inicio;

   function Pos_Inicio(pos_x: T_CoordenadaX; aereovia: T_Rango_AereoVia) return T_Punto is
   begin
      return (X => pos_x, Y => y_aereovia(aereovia));
   end Pos_Inicio;


   ------------------------------------------------------------------------
   -- Actualiza la posición de un objeto dependiendo de su velocidad
   ------------------------------------------------------------------------
   PROCEDURE Actualiza_Movimiento(avion : IN OUT T_RecordAvion) IS
      avion_cercano : T_RecordAvion;
      dist_obstaculo : Integer;
      pos           : T_RangoBufferAviones;
   BEGIN
      avion.pos.x := Nueva_PosicionX(avion.pos.x, avion.velocidad.x);

      -- Buscar posición del avion dentro del buffer
      pos := Posicion_Buffer(avion.Id, avion.aereovia_inicial, buffer_aviones(avion.aereovia));
      Pkg_Buffer_aviones.Actualiza_Item(pos, avion, buffer_aviones(avion.aereovia));

      Detectar_Avion_Mas_Cercano(avion, avion_cercano, dist_obstaculo);

      IF (avion.id /= avion_cercano.id or avion.aereovia_inicial /= avion_cercano.aereovia_inicial) and dist_obstaculo < TAM_AVION then
         PKG_debug.Escribir("colision entre: " & T_IdAvion'Image(avion.id) & "-" & T_Rango_AereoVia'Image(avion.aereovia_inicial)
                            & "  " & T_IdAvion'Image(avion_cercano.id) & "-" & T_Rango_AereoVia'Image(avion_cercano.aereovia_inicial)& "   distancia:"&Integer'Image(dist_obstaculo));
         RAISE DETECTADA_COLISION;
      END IF;

   end Actualiza_Movimiento;


   PROCEDURE Actualiza_Movimiento_En_Pista(avion : IN OUT T_RecordAvion) IS
      pos : T_RangoBufferAvionesAterrizando;
   BEGIN
      avion.pos.y := Nueva_PosicionY(avion.pos.y, avion.velocidad.y);

      -- Buscar posición del avion dentro del buffer
      pos := Posicion_Buffer(avion.Id, avion.aereovia_inicial, buffer_aviones_en_pista);
      Pkg_Buffer_aviones_en_pista.Actualiza_Item(pos, avion, buffer_aviones_en_pista);

   end Actualiza_Movimiento_En_Pista;



   ------------------------------------------------------------------------
   -- comprueba si se ya llegado al final de la pista de aterrizaje
   ------------------------------------------------------------------------
   function Fin_Aterrizaje(pos_y : T_CoordenadaY) return Boolean is
   begin
      return pos_y = T_CoordenadaY'Last;
   end Fin_Aterrizaje;


   ------------------------------------------------------------------------
   -- actualiza el valor del cronómetro
   ------------------------------------------------------------------------
   PROCEDURE Actualiza_Cronometro(tiempo_transcurrido: Duration) IS
   BEGIN
      Ada.Float_Text_IO.put(Hora_segundos, Float(tiempo_transcurrido), 3, 0);
   END Actualiza_Cronometro;



   ----------------------------------------
   -- PROCEDIMIENTOS Y FUNCIONES PRIVADAS :
   ----------------------------------------


   ------------------------------------------------------------------------
   -- Procedimiento que devuelve el avion mas cercano y la distancia al mismo
   -- Si no hay avion cercano, devuelve la velocidad del propio avion y distancia = 0
   ------------------------------------------------------------------------
   PROCEDURE Detectar_Avion_Mas_Cercano(avion : IN T_RecordAvion; avion_cercano : OUT T_RecordAvion;
                                        distancia : OUT Integer) IS
      avion_aux      : T_RecordAvion;
      min_dist_x     : T_CoordenadaX := T_CoordenadaX'Last;
      dist_x         : Integer;
   BEGIN
      avion_cercano := avion;
      distancia := 0;

      for pos in Pkg_Buffer_Aviones.Posicion_Primer_Item(buffer_aviones(avion.aereovia))..Pkg_Buffer_Aviones.Posicion_Ultimo_Item(buffer_aviones(avion.aereovia)) loop

         avion_aux := Pkg_Buffer_Aviones.Consulta_Item(T_RangoBufferAviones(pos), buffer_aviones(avion.aereovia));

         if avion.id /= avion_aux.id or avion.aereovia_inicial /= avion_aux.aereovia_inicial then
            dist_x := abs(avion_aux.pos.x - avion.pos.x);

            if dist_x < min_dist_x then
               min_dist_x := dist_x;
               avion_cercano := avion_aux;
               distancia := min_dist_x;
            end if;
         end if;

      end loop;


   exception
      when event: others =>
         PKG_debug.Escribir("ERROR en Detectar_Avion_Mas_Cercano: " & Exception_Name(Exception_Identity(event)));

   END Detectar_Avion_Mas_Cercano;


   ------------------------------------------------------------------------
   -- calcula la nueva posición de la coordenad X, comprobando los límites de una aereovía
   -- y teniendo en cuenta un movimiento cíclico en la misma
   ------------------------------------------------------------------------
   function Nueva_PosicionX(pos_actual_x : T_CoordenadaX; vel_x : T_RangoVelocidad) return T_CoordenadaX is
      nueva_pos_x : Integer;
   begin
      nueva_pos_x := pos_actual_x + Integer(vel_x);
      IF nueva_pos_x < 0 THEN
         nueva_pos_x := X_INICIO_DER_AVION;
      ELSIF nueva_pos_x > X_INICIO_DER_AVION THEN
         nueva_pos_x := 1;
      END IF;

      return T_CoordenadaX(nueva_pos_x);
   end Nueva_PosicionX;


   ------------------------------------------------------------------------
   -- calcula la nueva posición de la coordenada Y, comprobando el límite
   -- de la pista de aterrizaje
   ------------------------------------------------------------------------
   function Nueva_PosicionY(pos_actual_y : T_CoordenadaY; vel_y: T_RangoVelocidad) return T_CoordenadaY is
      nueva_pos_y : Integer;
   begin
      nueva_pos_y := pos_actual_y + Integer(vel_y);
      IF nueva_pos_y > T_CoordenadaY'Last THEN
         nueva_pos_y := T_CoordenadaY'Last;
      END IF;

      return T_CoordenadaY(nueva_pos_y);
   end Nueva_PosicionY;



   ------------------------------------------------------------------------
   -- Procedure que se encarga de dibujar en el canvas todos los objetos
   -- de la interfaz gráfica (parte estática y dinámica de la interfaz)
   ------------------------------------------------------------------------
   procedure Dibujar_Canvas(Pixmap : Cairo_Context) is
      pos_primer_avion : T_RangoBufferAviones;
      pos_ultimo_avion : T_RangoBufferAviones;
      pos_avion        : T_RangoBufferAviones;
      Item_avion       : T_RecordAvion;
      pos_primer_avion_en_pista : T_RangoBufferAvionesAterrizando;
      pos_ultimo_avion_en_pista : T_RangoBufferAvionesAterrizando;
      pos_avion_en_pista        : T_RangoBufferAvionesAterrizando;

   begin

      -- dibujar aereovias
      set_text(pangoLayout, "aereovias");
      Draw_Layout(pixmap, Black_Gc, 1, ALTURA_AEREOVIA-20, pangoLayout);
      for i in T_Rango_AereoVia loop
         set_text(pangoLayout, T_Rango_AereoVia'Image(i));
         Draw_Layout(pixmap, Black_Gc, 0, Gint(y_aereovia(i)), pangoLayout);
         Draw_Line(Pixmap, Black_Gc, 1, Gint(i*ALTURA_AEREOVIA), 5, Gint(i*ALTURA_AEREOVIA));
      end loop;
      Draw_Line(Pixmap, Black_Gc, 1, Gint((T_Rango_AereoVia'Last+1)*ALTURA_AEREOVIA), 5, Gint((T_Rango_AereoVia'Last+1)*ALTURA_AEREOVIA));


      Dibujar_Pistas_Aterrizaje(Pixmap);


      -- dibujar aviones en aereovias
      FOR aereovia IN T_Rango_AereoVia LOOP
         if not Pkg_Buffer_aviones.Vacio(buffer_aviones(aereovia)) then
            pos_primer_avion := Pkg_Buffer_aviones.Posicion_Primer_Item(buffer_aviones(aereovia));
            pos_ultimo_avion := Pkg_Buffer_aviones.Posicion_Ultimo_Item(buffer_aviones(aereovia));
            pos_avion := pos_primer_avion;
            loop
               Item_avion := Pkg_Buffer_aviones.Consulta_Item(pos_avion, buffer_aviones(aereovia));

               Dibujar_Avion(Pixmap, Item_avion);

               exit when pos_avion = pos_ultimo_avion;

               pos_avion := pos_avion+1;
            END LOOP;
         end if;
      end loop;

      -- dibujar aviones en pistas de aterrizaje
      if not Pkg_Buffer_aviones_en_pista.Vacio(buffer_aviones_en_pista) then
         pos_primer_avion_en_pista := Pkg_Buffer_aviones_en_pista.Posicion_Primer_Item(buffer_aviones_en_pista);
         pos_ultimo_avion_en_pista := Pkg_Buffer_aviones_en_pista.Posicion_Ultimo_Item(buffer_aviones_en_pista);
         pos_avion_en_pista := pos_primer_avion_en_pista;
         loop
            Item_avion := Pkg_Buffer_aviones_en_pista.Consulta_Item(pos_avion_en_pista, buffer_aviones_en_pista);

            Dibujar_Avion(Pixmap, Item_avion);

            exit when pos_avion_en_pista = pos_ultimo_avion_en_pista;

            pos_avion_en_pista := pos_avion_en_pista+1;
         end loop;
      end if;

      Dibujar_Canvas_Cronometro(Pixmap);

   end Dibujar_Canvas;


   ------------------------------------------------------------------------
   -- Dibujar en el canvas las pistas de aterrizaje
   ------------------------------------------------------------------------
   procedure Dibujar_Pistas_Aterrizaje(Pixmap: Cairo_Context) is
   begin
      -- Dibujar asfalto
      Draw_Rectangle (Pixmap, Grey_Gc, Filled => True,
                      X     => X_INICIO_PISTA1,  Y      => Y_INICIO_PISTA,
                      Width => ANCHO_PISTA, Height => LONGITUD_PISTA);

      Draw_Rectangle (Pixmap, Grey_Gc, Filled => True,
                      X     => X_INICIO_PISTA2,  Y      => Y_INICIO_PISTA,
                      Width => ANCHO_PISTA, Height => LONGITUD_PISTA);

      -- Dibujar las líneas discontínuas centrales
      Cairo.Set_Line_Width(Pixmap, 3.0);
      for i in 1..(LONGITUD_PISTA-40) / 5 loop
         if i rem 2 /= 0 then
            Draw_Line(Pixmap, White_Gc, Gint(X_INICIO_PISTA1+ANCHO_PISTA/2), Gint(Y_INICIO_PISTA + ((i-1)* 5)),
                      Gint(X_INICIO_PISTA1+ANCHO_PISTA/2), Gint(Y_INICIO_PISTA + ((i-1)* 5 +5)));
            Draw_Line(Pixmap, White_Gc, Gint(X_INICIO_PISTA2+ANCHO_PISTA/2), Gint(Y_INICIO_PISTA + ((i-1)* 5)),
                      Gint(X_INICIO_PISTA2+ANCHO_PISTA/2), Gint(Y_INICIO_PISTA + ((i-1)* 5 +5)));
         end if;
      end loop;
      Cairo.Set_Line_Width(Pixmap, 2.0); -- restaurar valor por defecto

      -- Dibujar líneas contínuas de los límites
      Draw_Rectangle (Pixmap, White_Gc, Filled => False,
                      X     => X_INICIO_PISTA1,  Y      => Y_INICIO_PISTA,
                      Width => ANCHO_PISTA, Height => LONGITUD_PISTA);

      Draw_Rectangle (Pixmap, White_Gc, Filled => False,
                      X     => X_INICIO_PISTA2,  Y      => Y_INICIO_PISTA,
                      Width => ANCHO_PISTA, Height => LONGITUD_PISTA);

      -- Dibujar las líneas finales de pista
      Cairo.Set_Line_Width(Pixmap, 5.0);
      for i in 1..6 loop
         Draw_Line(Pixmap, White_Gc, Gint(X_INICIO_PISTA1+i*14), Gint(Y_INICIO_PISTA + LONGITUD_PISTA -20),
                   Gint(X_INICIO_PISTA1+i*14), Gint(Y_INICIO_PISTA + LONGITUD_PISTA));
         Draw_Line(Pixmap, White_Gc, Gint(X_INICIO_PISTA2+i*14), Gint(Y_INICIO_PISTA + LONGITUD_PISTA -20),
                   Gint(X_INICIO_PISTA2+i*14), Gint(Y_INICIO_PISTA + LONGITUD_PISTA));
      end loop;
      Cairo.Set_Line_Width(Pixmap, 2.0); -- restaurar valor por defecto

      -- Dibujar los números de pista
      set_text(pangoLayout, "1");
      Draw_Layout(pixmap, Red_Gc, Gint(X_INICIO_PISTA1+ANCHO_PISTA/2-3), Gint(Y_INICIO_PISTA+LONGITUD_PISTA-35), pangoLayout);
      set_text(pangoLayout, "2");
      Draw_Layout(pixmap, Green_Gc, Gint(X_INICIO_PISTA2+ANCHO_PISTA/2-3), Gint(Y_INICIO_PISTA+LONGITUD_PISTA-35), pangoLayout);


   end Dibujar_Pistas_Aterrizaje;


   ------------------------------------------------------------------------
   -- Dibujar en el canvas el chasis de un avion
   ------------------------------------------------------------------------
   procedure Dibujar_Avion(Pixmap: Cairo_Context; avion: T_RecordAvion) is
      x : Gint;
      y : Gint;
      dir : Gint;
      color: Gtkada.Style.Cairo_Color;
      x_identificador : Gint;
   begin
      color := Convertir_Color_GC(avion.color);
      if avion.velocidad.x > 0 then
         dir := 1;
         x_identificador := Gint(avion.Pos.X) -10;
      else
         dir := -1;
         x_identificador := Gint(avion.Pos.X) - TAM_AVION -22;
      end if;

      x := Gint(avion.Pos.X-15);
      y := Gint(avion.Pos.Y-3);
      Cairo.Move_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+25*dir;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+6*dir;
      y := y+3;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-3*dir;
      y := y+3;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-15*dir;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-20*dir;
      y := y+15;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+10*dir;
      y := y-15;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-15*dir;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+2*dir;
      y := y-2;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-4*dir;
      y := y-8;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+3*dir;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+4*dir;
      y := y+4;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+8*dir;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x-6*dir;
      y := y-12;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      x := x+15*dir;
      y := y+12;
      Cairo.Line_To(Pixmap, Gdouble(x), Gdouble(y));
      Cairo.Close_Path(Pixmap);
      Cairo.Set_Source_Rgb(Pixmap, color.Red, color.Green, color.Blue);
      Cairo.Fill(Pixmap);

      -- Dibujar identificador del avion
      set_text(pangoLayout, T_IdAvion'Image(avion.id));
      Draw_Layout(pixmap, White_Gc, x_identificador, Gint(avion.Pos.Y-20), pangoLayout);
      set_text(pangoLayout,T_Rango_AereoVia'Image(avion.aereovia_inicial));
      Draw_Layout(pixmap, Black_Gc, x_identificador+20, Gint(avion.Pos.Y-20), pangoLayout);

      if avion.tren_aterrizaje then
         Dibujar_Tren_Aterrizaje(Pixmap, avion);
      end if;

   end Dibujar_Avion;


   procedure Dibujar_Tren_Aterrizaje(Pixmap: Cairo_Context; avion: T_RecordAvion) is
   begin

      -- dibujar la rueda delantera y trasera
      if avion.velocidad.x <= 0 then
         Dibujar_Rueda(Pixmap, Black_Gc, Grey_Gc, Gint(avion.pos.x-40),  Gint(avion.pos.y+2),  6, 2);
         Dibujar_Rueda(Pixmap, Black_Gc, Grey_Gc, Gint(avion.pos.x-20),  Gint(avion.pos.y+2),  6, 2);
      else
         Dibujar_Rueda(Pixmap, Black_Gc, Grey_Gc, Gint(avion.pos.x+5),  Gint(avion.pos.y+2),  6, 2);
         Dibujar_Rueda(Pixmap, Black_Gc, Grey_Gc, Gint(avion.pos.x)-15,  Gint(avion.pos.y+2),  6, 2);
      end if;

   end Dibujar_Tren_Aterrizaje;


   ------------------------------------------------------------------------
   -- Función que convierte un color a su correspondiente del
   -- contexto gráfico
   ------------------------------------------------------------------------
   FUNCTION Convertir_Color_GC(Color : T_Color) RETURN Gtkada.Style.Cairo_Color IS
   BEGIN
      CASE Color IS
         WHEN Red    => RETURN(Red_Gc);
         WHEN Green  => RETURN(Green_Gc);
         WHEN Blue   => RETURN(Blue_Gc);
         WHEN Yellow => RETURN(Yellow_Gc);
         WHEN Black  => RETURN(Black_Gc);
         WHEN White  => RETURN(White_Gc);
         WHEN Grey   => RETURN(Grey_Gc);
         WHEN Cyan   => RETURN(Cyan_Gc);
         WHEN Orange   => RETURN(Orange_Gc);
      END CASE;
   end Convertir_Color_GC;



   ------------------------------------------------------------------------
   -- Dibujar en el canvas las líneas determinadas por un conjunto de puntos
   ------------------------------------------------------------------------
   procedure Dibujar_Lineas(Pixmap : Cairo_Context; color : Gtkada.Style.Cairo_Color; flecha : Gdk_Points_Array; n_puntos : Integer) is
   begin
      for i in 1..n_puntos-1 loop
         Draw_Line(Pixmap, color, flecha(i).x, flecha(i).y, flecha(i+1).x, flecha(i+1).y);
      end loop;
   end Dibujar_Lineas;


   ------------------------------------------------------------------------
   -- Dibujar en el canvas una rueda
   ------------------------------------------------------------------------
   procedure Dibujar_Rueda(Pixmap: Cairo_Context; color_neumatico: Gtkada.Style.Cairo_Color;
                           color_llanta: Gtkada.Style.Cairo_Color; x: Gint; y: Gint;
                           diametro_neumatico:Gint; diametro_llanta: Gint) is
   begin
      Draw_Rectangle(Pixmap, color_neumatico, Filled => True,
                     X => x, Y => y, Width => diametro_neumatico, Height => diametro_neumatico,
                     Corner_Radius => Gdouble(diametro_neumatico)/2.0);
      Draw_Rectangle(Pixmap, color_llanta, Filled => True,
                     X => x+2, Y => y+2, Width => diametro_llanta, Height => diametro_llanta,
                     Corner_Radius => Gdouble(diametro_llanta)/2.0);
   end Dibujar_Rueda;


   ------------------------------------------------------------------------
   -- Procedure que se encarga de dibujar el cronómetro
   ------------------------------------------------------------------------
   PROCEDURE Dibujar_Canvas_Cronometro(Pixmap : Cairo_Context) IS
   BEGIN
      -- Dibujar el cronómetro
      Draw_Rectangle (Pixmap, White_Gc, Filled => True,
                      X => Gint(X_CRONOMETRO),  Y => Gint(Y_CRONOMETRO-15),
                      Width => 65, Height => 20);

      -- Imprimir el valor del cronómetro como texto
      set_text(pangoLayout, hora_segundos);
      Draw_Layout(Pixmap, Black_Gc, Gint(X_CRONOMETRO), Gint(Y_CRONOMETRO-15), pangoLayout);
   END Dibujar_Canvas_Cronometro;




   --***************************************************************
   -- SENTENCIAS DE INICIALIZACIÓN DEL PAQUETE
   --***************************************************************
BEGIN
   PKG_debug.Escribir("Inicializando Entorno Gráfico...");

   -- Inicializar el entorno gráfico
   --Gtk.Main.Set_Locale;
   Gtk.Main.Init;
   Inicializar_Interfaz_Grafica;


   PKG_debug.Escribir("Entorno Gráfico Inicializado.");
end PKG_graficos;
