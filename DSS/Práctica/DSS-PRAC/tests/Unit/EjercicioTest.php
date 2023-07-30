<?php

namespace Tests\Unit;

use App\Models\Ejercicio;
use Illuminate\Database\Eloquent\Collection;
use Tests\TestCase;

class EjercicioTest extends TestCase
{
    /**
     * A basic unit test example.
     *
     * @return void
     */
    public function test_a_Ejercicio_has_many_Grupo_Muscular()
    {
        $ejercicio = new Ejercicio();

        $this->assertInstanceOf(Collection::class, $ejercicio->grupoMusculares);
    }

    public function test_Ejercicios_select()
    {
        $this->eliminar_elementos_test();
        
        $arrayEsperado = [
            "Press de pecho plano con mancuerna."
        , "Press de pecho con mancuerna inclinado"
        , "Apertura de mancuernas"
        , "Cruces en polea alta"
        , "Cruces en polea baja"
        , "Extensión de cuadriceps "
        , "Curl Femoral"
        , "Elevación de gemelos en máquina"
        , "Abductor en máquina"
        , "Press Militar con mancuernas sentado"
        , "Elevaciones laterales"];
        $grupoMuscular = Ejercicio::pluck('name')->toArray();
        $this->assertEquals($arrayEsperado, $grupoMuscular);
        
    }

    public function test_insertar_dato_mediante_objeto()
    {
        $this->eliminar_elementos_test();

        $ejercicioEsperado = '{"id":666,"name":"TESTING","descripcion":"Descripion TESTING","url_img":"URL Test","created_at":null,"updated_at":null}';
        $ejercicio = new Ejercicio();
        $ejercicio->id = 666;
        $ejercicio->name = "TESTING";
        $ejercicio->descripcion = "Descripion TESTING";
        $ejercicio->url_img = "URL Test";
        $ejercicio->save();

        $ejercicioObtenido = Ejercicio::where('name', '=', 'TESTING')->firstOrFail();  
        $ejercicio = Ejercicio::find(666);
        $ejercicio->delete();
        $this->assertEquals($ejercicioEsperado, $ejercicioObtenido);
    }

    function eliminar_elementos_test()
    {
        if (Ejercicio::find(666))
        {
            Ejercicio::find(666)->delete();
        }
    }
}
