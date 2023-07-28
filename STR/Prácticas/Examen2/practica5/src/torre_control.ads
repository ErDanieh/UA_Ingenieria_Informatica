with PKG_tipos;
use PKG_tipos;
with pkg_protegidos;
use pkg_protegidos;

package torre_control is

   task TorreDeControl is
      entry SolicitarDescenso(avion: in T_RecordAvion; concedido: out Boolean; pistaAvion: out T_PistaAterrizaje);
   end TorreDeControl;


end torre_control;
