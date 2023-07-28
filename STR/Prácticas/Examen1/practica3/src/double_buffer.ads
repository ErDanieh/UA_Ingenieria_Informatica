with Gtk.Drawing_Area;
with Cairo;
with Gdk.Pixbuf;
with pkg_tipos; USE pkg_tipos;

package Double_Buffer is

   type Gtk_Double_Buffer_Record is new
     Gtk.Drawing_Area.Gtk_Drawing_Area_Record with private;
   type Gtk_Double_Buffer is access all Gtk_Double_Buffer_Record'Class;

   procedure Gtk_New (Buffer : out Gtk_Double_Buffer);
   procedure Initialize (Buffer : Gtk_Double_Buffer);

   procedure Freeze (Buffer : access Gtk_Double_Buffer_Record);

   procedure Thaw (Buffer : access Gtk_Double_Buffer_Record);

   function Get_Pixmap (Buffer : access Gtk_Double_Buffer_Record)
                       return Cairo.Cairo_Context;

   procedure Set_Back_Store (Buffer : access Gtk_Double_Buffer_Record;
                             Back_Store : Boolean := True);

   procedure Set_Triple_Buffer (Buffer : access Gtk_Double_Buffer_Record;
                                Use_Triple_Buffer : Boolean := True);


private

   type Gtk_Double_Buffer_Record is new
     Gtk.Drawing_Area.Gtk_Drawing_Area_Record
   with record
      Pixmap                  : Gdk.Pixbuf.Gdk_Pixbuf := Gdk.Pixbuf.Null_Pixbuf;
      Triple_Buffer           : Gdk.Pixbuf.Gdk_Pixbuf := Gdk.Pixbuf.Null_Pixbuf;
      Is_Frozen               : Boolean := False;
      Back_Store              : Boolean := False;
      Should_Update_On_Screen : Boolean := False;
      Use_Triple_Buffer       : Boolean := False;
   end record;


end Double_Buffer;
