<?php

namespace Tests\Unit;

use App\Models\Musculo;
use Tests\TestCase;

class MusculosTest extends TestCase
{

    public function test_obtencion_datos()
    {
        $this->eliminar_elementos_test();
        
        $arrayEsperado = ["Aductores", "Antebrazo", "Biceps", "Cuadriceps", "Deltoides anterior", "Deltoides medio", "Deltoides posterior", "Dorsal", "Femoral", "Gemelos", "Gluteos", "Lumbar", "Oblicuo", "Pectoral mayor", "Pectoral menor", "Recto abdominal", "Redondos", "Serrato", "Trapecio medio", "Trapecio superior", "Triceps"];
        $nameMusculos = Musculo::orderBy('name', 'asc')->pluck('name')->toArray();
        $this->assertEquals($arrayEsperado, $nameMusculos);
    }

    public function test_insertar_dato_mediante_objeto()
    {
        $this->eliminar_elementos_test();

        $musculoEsperado = '{"id":666,"name":"TESTING","grupo_muscular_id":1,"created_at":null,"updated_at":null}';
        $musculo = new Musculo();
        $musculo->id = 666;
        $musculo->grupo_muscular_id = 1;
        $musculo->name = "TESTING";
        $musculo->save();

        $musculoObtenido = Musculo::where('name', '=', 'TESTING')->firstOrFail();  
        $this->assertEquals($musculoEsperado, $musculoObtenido);

        $musculo = Musculo::find(666);
        $musculo->delete();
        
    }

    function eliminar_elementos_test()
    {
        if (Musculo::find(666))
        {
            Musculo::find(666)->delete();
        }
    }
}
