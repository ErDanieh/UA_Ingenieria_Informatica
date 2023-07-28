with Glib;             use Glib;
with Gtk.Enums;        use Gtk.Enums;
with Gtk.Style;        use Gtk.Style;
with Cairo;             use Cairo;
with Gdk.Pixbuf;       use Gdk.Pixbuf;
with Gtkada.Style;      use Gtkada.Style;
with Gdk.Color;
with Gdk.Cairo;
with Gdk.Event;        use Gdk.Event;
with Gdk.Window;       use Gdk.Window;
with Gdk.Rectangle;    use Gdk.Rectangle;
with Gtk.Drawing_Area; use Gtk.Drawing_Area;
with Gtk.Handlers;     use Gtk.Handlers;
pragma Elaborate_All (Gtk.Handlers);


package body Double_Buffer is

   package Event_Cb is new Gtk.Handlers.Return_Callback
     (Widget_Type => Gtk_Double_Buffer_Record,
      Return_Type => Boolean);
   package Void_Cb is new Gtk.Handlers.Callback
     (Widget_Type => Gtk_Double_Buffer_Record);

   function Configure (Buffer        : access Gtk_Double_Buffer_Record'Class;
                       Event         : Gdk.Event.Gdk_Event)
                      return Boolean;

   function Expose (Buffer        : access Gtk_Double_Buffer_Record'Class;
                    Event         : Gdk.Event.Gdk_Event)
                   return Boolean;

   function Create_Internal_Pixmap
     (Buffer : access Gtk_Double_Buffer_Record'Class)
     return Gdk.Pixbuf.Gdk_Pixbuf;

   procedure Destroy_Cb (Buffer : access Gtk_Double_Buffer_Record'Class);



   procedure Gtk_New (Buffer : out Gtk_Double_Buffer) is
   begin
      Buffer := new Gtk_Double_Buffer_Record;
      Double_Buffer.Initialize (Buffer);
   end Gtk_New;


   procedure Initialize (Buffer : Gtk_Double_Buffer) is
   begin

      Gtk.Drawing_Area.Initialize (Buffer);

      Event_Cb.Connect (Buffer, "configure_event",
                        Event_Cb.To_Marshaller (Configure'Access));
      Event_Cb.Connect (Buffer, "draw",
                        Event_Cb.To_Marshaller (Expose'Access));
      Void_Cb.Connect (Buffer, "destroy",
                       Void_Cb.To_Marshaller (Destroy_Cb'Access));

   end Initialize;



   function Create_Internal_Pixmap
     (Buffer : access Gtk_Double_Buffer_Record'Class)
     return Gdk.Pixbuf.Gdk_Pixbuf
   is
   begin
      return Gdk.Pixbuf.Gdk_New(Colorspace_RGB,
                                     Width => CANVAS_WIDTH, Height => CANVAS_HEIGHT);
   end Create_Internal_Pixmap;



   function Configure (Buffer        : access Gtk_Double_Buffer_Record'Class;
                       Event         : Gdk.Event.Gdk_Event)
                      return Boolean
   is
      Old_Pixmap : Gdk.Pixbuf.Gdk_Pixbuf := Buffer.Pixmap;
      Old_Triple : Gdk.Pixbuf.Gdk_Pixbuf := Buffer.Triple_Buffer;
      Old_Pixmap_cairo_context : Cairo.Cairo_Context;
      Old_Triple_cairo_context : Cairo.Cairo_Context;
      use type Cairo.Cairo_Context;

   begin
      Old_Pixmap_cairo_context := Gdk.Cairo.Create(Get_Window(Buffer));

      Buffer.Pixmap := Create_Internal_Pixmap (Buffer);


      if Buffer.Use_Triple_Buffer then
         Old_Triple_cairo_context := Gdk.Cairo.Create(Get_Window(Buffer));
         Buffer.Triple_Buffer := Create_Internal_Pixmap (Buffer);
      end if;


      if Old_Pixmap /= Gdk.Pixbuf.Null_Pixbuf then

         if Buffer.Back_Store then
            declare
               Old_Width  : Gint;
               Old_Height : Gint;

            begin
               Old_Width := Get_Width(Old_Pixmap);
               Old_Height := Get_Height(Old_Pixmap);

               Draw_Rectangle (Old_Pixmap_cairo_context,
                          Gdk.Color.Null_Color,
                          Filled => True,
                          X => 0,  Y => 0,
                               Width => Old_Width, Height => Old_Height);

               Gdk.Cairo.Set_Source_Pixbuf(Old_Pixmap_cairo_context, Old_Pixmap, 0.0, 0.0);

            end;
         end if;

         Gdk.Pixbuf.Unref(Old_Pixmap);
      end if;

      if Old_Triple /= Gdk.Pixbuf.Null_Pixbuf then

         if Buffer.Back_Store then
            declare
               Old_Width  : Gint;
               Old_Height : Gint;

            begin
               Old_Width := Get_Width(Old_Triple);
               Old_Height := Get_Height(Old_Triple);

               Draw_Rectangle (Old_Triple_cairo_context,
                          Gdk.Color.Null_Color,
                          Filled => True,
                          X => 0,  Y => 0,
                          Width => Old_Width, Height => Old_Height);

               Gdk.Cairo.Set_Source_Pixbuf(Old_Triple_cairo_context, Old_Triple, 0.0, 0.0);

            end;
         end if;

         Gdk.Pixbuf.Unref (Old_Triple);
      end if;

      return True;
   end Configure;



   procedure Destroy_Cb (Buffer : access Gtk_Double_Buffer_Record'Class) is
      use type Gdk.Pixbuf.Gdk_Pixbuf;
   begin
      if Buffer.Pixmap /= Gdk.Pixbuf.Null_Pixbuf then
         Gdk.Pixbuf.Unref (Buffer.Pixmap);
      end if;

      if Buffer.Triple_Buffer /= Gdk.Pixbuf.Null_Pixbuf then
         Gdk.Pixbuf.Unref (Buffer.Triple_Buffer);
      end if;
   end Destroy_Cb;



   function Expose (Buffer        : access Gtk_Double_Buffer_Record'Class;
                    Event         : Gdk.Event.Gdk_Event)
                   return Boolean
   is
      Area : Gdk.Rectangle.Gdk_Rectangle := Event.Expose.Area;

      Old_Pixmap : Gdk.Pixbuf.Gdk_Pixbuf := Buffer.Pixmap;
      Old_Triple : Gdk.Pixbuf.Gdk_Pixbuf := Buffer.Triple_Buffer;
      Old_Pixmap_cairo_context : Cairo.Cairo_Context;
      Old_Triple_cairo_context : Cairo.Cairo_Context;

   begin

      Old_Pixmap_cairo_context := Gdk.Cairo.Create(Get_Window(Buffer));


      if Buffer.Use_Triple_Buffer then

         Old_Triple_cairo_context := Gdk.Cairo.Create(Get_Window(Buffer));

         if Gdk.Event.Events_Pending then
            if Buffer.Is_Frozen then
               Buffer.Should_Update_On_Screen := True;
            else
               Gdk.Cairo.Set_Source_Pixbuf(Old_Triple_cairo_context, Old_Pixmap, 0.0, 0.0);

            end if;
         end if;

         Gdk.Cairo.Set_Source_Pixbuf(Old_Pixmap_cairo_context, Old_Triple, 0.0, 0.0);

      elsif not Buffer.Is_Frozen then
          Gdk.Cairo.Set_Source_Pixbuf(Old_Pixmap_cairo_context, Old_Pixmap, 0.0, 0.0);

      else
         Buffer.Should_Update_On_Screen := True;
      end if;


      return False;
   end Expose;



   function Get_Pixmap (Buffer : access Gtk_Double_Buffer_Record)
                        return Cairo.Cairo_Context is --Gdk.Drawable.Gdk_Drawable is
      ventana : Gdk.Gdk_Window;
      context : Cairo.Cairo_Context;
   begin
      ventana := Get_Window(Gtk_Drawing_Area(Buffer));
      context := Gdk.Cairo.Create(ventana);

      Gdk.Cairo.Set_Source_Pixbuf(context, Buffer.Pixmap, 0.0, 0.0);

      return context;

   end Get_Pixmap;



   procedure Set_Back_Store (Buffer : access Gtk_Double_Buffer_Record;
                             Back_Store : Boolean := True) is
   begin
      Buffer.Back_Store := Back_Store;
   end Set_Back_Store;



   procedure Freeze (Buffer : access Gtk_Double_Buffer_Record) is
   begin
      Buffer.Is_Frozen := True;
   end Freeze;



   procedure Thaw (Buffer : access Gtk_Double_Buffer_Record) is
      context : Cairo.Cairo_Context :=  Gdk.Cairo.Create(Get_Window(Buffer));
      Pixmap : Gdk.Pixbuf.Gdk_Pixbuf := Buffer.Pixmap;
   begin
      Buffer.Is_Frozen := False;

      if Buffer.Should_Update_On_Screen then
         Gdk.Cairo.Set_Source_Pixbuf(context, Pixmap, 0.0, 0.0);

      end if;
   end Thaw;



   procedure Set_Triple_Buffer (Buffer : access Gtk_Double_Buffer_Record;
                                Use_Triple_Buffer : Boolean := True) is
      context : Cairo.Cairo_Context := Gdk.Cairo.Create(Get_Window(Buffer));

      use type Gdk.Gdk_Window;
   begin
      Buffer.Use_Triple_Buffer := Use_Triple_Buffer;

      if not Use_Triple_Buffer
        and then Buffer.Triple_Buffer /= null
      then
         Gdk.Pixbuf.Unref (Buffer.Triple_Buffer);
      end if;


      if Use_Triple_Buffer then
         Buffer.Triple_Buffer := Create_Internal_Pixmap (Buffer);

         Gdk.Cairo.Set_Source_Pixbuf(context, Buffer.Triple_Buffer, 0.0, 0.0);

      end if;
   end Set_Triple_Buffer;

end Double_Buffer;
