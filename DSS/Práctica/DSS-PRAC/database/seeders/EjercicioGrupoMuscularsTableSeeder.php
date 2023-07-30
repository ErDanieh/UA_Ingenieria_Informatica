<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\Ejercicio;
use App\Models\GrupoMuscular;
use DB;

class EjercicioGrupoMuscularsTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('ejercicio_grupo_muscular')->delete();


        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho plano con mancuerna.')->first();  
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);

        

        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho con mancuerna inclinado')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Cruces en polea alta')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Cruces en polea baja')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Extensión de cuadriceps')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Piernas')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Curl Femoral')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Piernas')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);



        $ejercicio = Ejercicio::where('name', '=', 'Elevación de gemelos en máquina')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Piernas')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Piernas')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Deltoides')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);


        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Deltoides')->first();
        $ejercicio->grupoMusculares()->attach($grupoMuscularPectoral->id);
        
        //$grupoMuscularPectoral->ejercicios()->attach($ejercicio->id);
        
    }
}
