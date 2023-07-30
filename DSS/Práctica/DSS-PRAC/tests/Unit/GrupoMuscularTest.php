<?php

namespace Tests\Unit;

use App\Models\GrupoMuscular;
use Illuminate\Database\Eloquent\Collection;
use Tests\TestCase;


class GrupoMuscularTest extends TestCase
{
    /**
     * A basic unit test example.
     *
     * @return void
     */
    public function test_a_Grupo_muscular_has_many_musculos()
    {
        $grupoMuscular = new GrupoMuscular;

        $this->assertInstanceOf(Collection::class, $grupoMuscular->musculos);
    }

    public function test_obtencion_datos()
    {
        $this->eliminar_elementos_test();

        $arrayEsperado = ["Pectorales", "Deltoides", "Espalda", "Glúteos", "Trapecios", "Abdominales", "Brazo", "Piernas"];
        $grupoMuscular = GrupoMuscular::pluck('name')->toArray();
        $this->assertEquals($arrayEsperado, $grupoMuscular);
    }

    public function test_insertar_dato_mediante_objeto()
    {
        $this->eliminar_elementos_test();

        $grupoMuscularEsperado = '{"id":666,"name":"TESTING","descripcion":"Descripion TESTING","created_at":null,"updated_at":null}';
        $grupoMuscular = new GrupoMuscular();
        $grupoMuscular->id = 666;
        $grupoMuscular->name = "TESTING";
        $grupoMuscular->descripcion = "Descripion TESTING";
        $grupoMuscular->save();

        $grupoMuscularObtenido = GrupoMuscular::where('name', '=', 'TESTING')->firstOrFail();  
        $grupoMuscular = GrupoMuscular::find(666);
        $grupoMuscular->delete();
        $this->assertEquals($grupoMuscularEsperado, $grupoMuscularObtenido);
    }
    function eliminar_elementos_test()
    {
        if (GrupoMuscular::find(666))
        {
            GrupoMuscular::find(666)->delete();
        }
    }
}
