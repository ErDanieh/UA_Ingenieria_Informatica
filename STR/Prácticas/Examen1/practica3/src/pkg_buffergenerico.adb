--******************** PKG_bufferGenerico.ADB ***************************
-- Paquete que implementa un buffer circular genérico
--***********************************************************************

package body PKG_bufferGenerico is
   procedure Insertar_Ultimo_Item(item: tipo_dato; buffer: in out T_Buffer) is
   begin
      buffer.vector(buffer.top):= item;
      buffer.Top:= buffer.Top+1;
      buffer.num:= buffer.num+1;
   end Insertar_Ultimo_Item;

   procedure Extraer_Primer_Item(item: out tipo_dato; buffer: in out T_Buffer) is
   begin
      buffer.Base:= buffer.Base+1;
      item:= buffer.Vector(buffer.Base);
      buffer.num:= buffer.num-1;
   end Extraer_Primer_Item;

   procedure Actualiza_Item(pos: in tam; item: in tipo_dato; buffer: in out T_Buffer) is
   begin
      buffer.vector(pos) := item;
   END Actualiza_Item;

   FUNCTION Posicion_Primer_Item(buffer: IN T_Buffer) RETURN Tam is
   BEGIN
      RETURN buffer.Base+1;
   end Posicion_Primer_Item;

   FUNCTION Posicion_Ultimo_Item(buffer: IN T_Buffer) RETURN Tam is
   BEGIN
      RETURN buffer.Top-1;
   end Posicion_Ultimo_Item;

   function Consulta_Item(pos: IN Tam; buffer: IN T_Buffer) return Tipo_Dato IS
   BEGIN
      RETURN buffer.vector(pos);
   end Consulta_Item;

   function Vacio(buffer: IN T_Buffer) return boolean IS
   BEGIN
      RETURN buffer.num = 0;
   end Vacio;

   function Lleno(buffer: IN T_Buffer) return boolean IS
   BEGIN
      RETURN buffer.num = Natural(Tam'Last+1);
   end Lleno;

   -- ELIMINAR ESTE PROCEDURE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   procedure Extraer_Posicion_Item(pos: in tam; item: out tipo_dato; buffer: in out T_Buffer) is
   i : Tam;
   BEGIN
      Item := Buffer.Vector(Pos);
      I:= Pos;
      WHILE I /= Posicion_Primer_Item(Buffer) LOOP
         Buffer.Vector(I) := Buffer.Vector(I-1);
         I := I-1;
      end loop;
      buffer.Base:= buffer.Base+1;
      item:= buffer.Vector(buffer.Base);
      buffer.num:= buffer.num-1;
   end Extraer_Posicion_Item;

   procedure Borrar_Item(pos: in tam; buffer: in out T_Buffer) is
   i : Tam;
   BEGIN
      i:= pos;
      WHILE i /= Posicion_Primer_Item(Buffer) LOOP
         Buffer.Vector(i) := Buffer.Vector(i-1);
         i := i-1;
      end loop;
      buffer.Base:= buffer.Base+1;
      buffer.num:= buffer.num-1;
   end Borrar_Item;


   procedure Insertar_Item(pos: in tam; item: in tipo_dato; buffer: in out T_Buffer) is
   i : Tam;
   BEGIN
      i:= Posicion_Ultimo_Item(Buffer);
      WHILE i /= pos LOOP
         Buffer.Vector(i+1) := Buffer.Vector(i);
         i := i-1;
      end loop;
      Buffer.vector(pos) := item;
      buffer.top:= buffer.top+1;
      buffer.num:= buffer.num+1;
   end Insertar_Item;


end PKG_bufferGenerico;
