--******************* PKG_tipos.ADS ***************************
-- Paquete con declaraciones globales de constantes y tipos
--*************************************************************

PACKAGE PKG_tipos IS

   MIN_VELOCIDAD_AVION  : CONSTANT := -10;
   MAX_VELOCIDAD_AVION : CONSTANT := 10;
   VELOCIDAD_VUELO     : CONSTANT := 5;
   VELOCIDAD_INICIO_ATERRIZAJE : CONSTANT := 4;

   type T_RangoVelocidad is new integer range MIN_VELOCIDAD_AVION..MAX_VELOCIDAD_AVION;


   -- tiempo de espera utilizado para simular el movimiento de todos los
   -- vehículos
   RETARDO_MOVIMIENTO : CONSTANT Duration := 0.1;

   -- Excepción lanzada si se detecta una colisión entre aviones
   DETECTADA_COLISION : EXCEPTION;


   -- colores de los objetos del sistema
   TYPE T_Color IS (Red, Green, Blue, Yellow, Cyan, Orange, White, Black, Grey);

   -- pista asignada a un avión
   TYPE T_PistaAterrizaje IS (SIN_PISTA, PISTA1, PISTA2);


   -----------------------------------------------------------------
   -- DECLARACIONES DE TIPOS y CONSTANTES para la interfaz gráfica
   -----------------------------------------------------------------

   -----------------------------------------------------------------
   -- DECLARACIONES DE CONSTANTES
   -----------------------------------------------------------------

   -- Tamaño de la ventana principal
   CANVAS_WIDTH  : constant := 800;
   CANVAS_HEIGHT : constant := 550;

   ALTURA_AEREOVIA : CONSTANT := 50;
   NUM_AEREOVIAS : CONSTANT := 6;
   MAX_AVIONES_AEROVIA : CONSTANT := 5;
   NUM_INICIAL_AVIONES_AEROVIA : CONSTANT := 3;
   MAX_AVIONES_ATERRIZANDO : CONSTANT := 2;

   X_INICIO_DER_AVION : constant := CANVAS_WIDTH;-- -200;

   TAM_AVION : CONSTANT := 50;

   Y_INICIO_PISTA : CONSTANT := ALTURA_AEREOVIA*(NUM_AEREOVIAS+1);
   LON_PISTA : CONSTANT := CANVAS_HEIGHT - Y_INICIO_PISTA;


   -----------------------------------------------------------------
   -- DECLARACIONES DE TIPOS
   -----------------------------------------------------------------

   -- tamaño de cada buffer por aerovia
   TYPE T_RangoBufferAviones IS mod MAX_AVIONES_AEROVIA;
   TYPE T_RangoBufferAvionesAterrizando IS mod MAX_AVIONES_ATERRIZANDO;


   -- velocidad de los aviones en los ejes X e Y
   TYPE T_Velocidad IS
   RECORD
      X : T_RangoVelocidad;
      Y : T_RangoVelocidad;
   end record;

   -- subtipos y tipos para las coordenadas (x,y) de un objeto en el
   -- área de dibujo
   subtype T_CoordenadaX is integer range 0..CANVAS_WIDTH;
   SUBTYPE T_CoordenadaY IS Integer RANGE 0..CANVAS_HEIGHT;

   TYPE T_Punto IS
   RECORD
      X : T_CoordenadaX;
      Y : T_CoordenadaY;
   end record;


   -----------------------------------------------------------------
   -- DECLARACIONES DE TIPOS y CONSTANTES para los AVIONES
   -----------------------------------------------------------------
   TAM_X_REJILLA : constant := X_INICIO_DER_AVION/TAM_AVION;
   TYPE T_Rango_Rejilla_X IS mod TAM_X_REJILLA;

   type T_Rejilla_Ocupacion is array (T_Rango_Rejilla_X) of Boolean;

   -- rango de la frecuencia (en segundos) de aparición de los aviones
   subtype T_RetardoAparicionAviones is integer range 2..6;

   -- rango del número de aereovias de distintas altitudes
   type T_Rango_AereoVia is new integer range 1..NUM_AEREOVIAS;

   -- identificador numérico de cada avion
   TYPE T_IdAvion IS MOD NUM_INICIAL_AVIONES_AEROVIA;

   subtype T_ColorAvion  IS T_Color range Red..Orange;
   subtype T_ColorAparicionAvion  IS T_ColorAvion range Blue..Orange;

   subtype T_Rango_Pista is integer range 1..2;

   -- tipo registro para almacenar los datos de un avion
   type T_RecordAvion is
   record
      id        : T_IdAvion;  -- identificador del avion
      pos       : T_Punto;    -- posicion (x,y) del avion
      velocidad : T_Velocidad;
      color     : T_ColorAvion;
      aereovia  : T_Rango_AereoVia;
      aereovia_inicial  : T_Rango_AereoVia;
      pista : T_PistaAterrizaje;
      tren_aterrizaje : Boolean;
   end record;

   type Ptr_T_RecordAvion is access T_RecordAvion;

end PKG_tipos;

