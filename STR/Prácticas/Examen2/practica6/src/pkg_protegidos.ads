with PKG_tipos;
use PKG_tipos;
with Ada.Text_IO;
use Ada.Text_IO;

package pkg_protegidos is
   --Contador para ver cuantos aviones tenemos
   subtype contador is Integer range 0..MAX_AVIONES_AEROVIA;
   function Posicion_Rejilla(pos_x : T_CoordenadaX) return T_Rango_Rejilla_X;
   
   --Un objeto protegido para cada aerovia
   --Necesitamos hacer 6 tipos protegidos por ahora solo 4
   protected type OP_Aerovia is
      
      --Comprueba si una coordenada esta libre o no
      function esLibre(posX : T_Rango_Rejilla_X) return Boolean;
      procedure ocupar(posX : T_Rango_Rejilla_X);
      procedure librar(posX : T_Rango_Rejilla_X);
      procedure cambiar(bloq : T_Rango_Rejilla_X; lib: T_Rango_Rejilla_X);
      
      --Funciones para el contador de aviones
      function cantidad return contador;
      procedure incrementarAviones;
      procedure decrementarAviones;
      
      --Condicion para la entrada al espacio protegido
      entry AeroviaDisponible(posX : T_Rango_Rejilla_X);
      
   private
      --Aerovia
      aire:  T_Rejilla_Ocupacion :=(others => false); 
      --Contador de aviones
      conta: contador := 0;
   end OP_Aerovia;
   
   
   protected type OP_Pista is
      
      function aterrizando return Boolean;
      procedure liberarPista;
      entry PreguntarPista(avion: in T_RecordAvion);
      
      
   private
      --Estado de la pista de aterrizaje
      Ocupado : Boolean;
      
   end OP_Pista;
      
   
   --Objeto protegido que contiene las aerovias
   arrayAerovias: array (T_Rango_AereoVia) of OP_Aerovia;   
   --Objetos protegidos de las pistas 
   OPP1 : OP_Pista;
   OPP2: OP_Pista;
     
   
   
end pkg_protegidos;
