<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\GrupoMuscular;
use App\Models\Musculo;
use DB;

class MusculosTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('musculos')->delete();

        $grupoMuscularPectoral = GrupoMuscular::where('name', '=', 'Pectorales')->first();  
        $grupoMuscularDeltoides = GrupoMuscular::where('name', '=', 'Deltoides')->first();  
        $grupoMuscularEspalda = GrupoMuscular::where('name', '=', 'Espalda')->first();  
        $grupoMuscularGluteos = GrupoMuscular::where('name', '=', 'Glúteos')->first();  
        $grupoMuscularTrapecios = GrupoMuscular::where('name', '=', 'Trapecios')->first();  
        $grupoMuscularAbdominales = GrupoMuscular::where('name', '=', 'Abdominales')->first();  
        $grupoMuscularBrazo = GrupoMuscular::where('name', '=', 'Brazo')->first();  
        $grupoMuscularPierna = GrupoMuscular::where('name', '=', 'Piernas')->first();  


        $grupoMuscularPectoral->musculos()->saveMany(
            [new Musculo(['name' => 'Pectoral mayor' ]),
            new Musculo([ 'name' => 'Pectoral menor' ]) ]
        );

        $grupoMuscularDeltoides->musculos()->saveMany(
            [new Musculo([ 'name' => 'Deltoides anterior' ]),
            new Musculo(['name' => 'Deltoides medio' ]),
            new Musculo( ['name' => 'Deltoides posterior' ])]
        );

        $grupoMuscularDeltoides->musculos()->saveMany(
            [new Musculo([ 'name' => 'Dorsal']),
            new Musculo([ 'name' => 'Lumbar']),
            new Musculo([ 'name' => 'Redondos']),
            new Musculo([ 'name' => 'Serrato'])]
        );

        $musculoGluteo = new Musculo(['name' => 'Gluteos']);
        $musculoGluteo->grupoMuscular()->associate($grupoMuscularGluteos);
        $musculoGluteo->save();
        
        $grupoMuscularDeltoides->musculos()->saveMany(
            [new Musculo(['name' => 'Trapecio superior']),
            new Musculo(['name' => 'Trapecio medio'])]
        );

        $grupoMuscularAbdominales->musculos()->saveMany(
            [new Musculo(['name' => 'Recto abdominal' ]),
            new Musculo([ 'name' => 'Oblicuo' ])]
        );

        $grupoMuscularBrazo->musculos()->saveMany(
            [new Musculo([ 'name' => 'Biceps' ]),
            new Musculo([ 'name' => 'Triceps' ]),
            new Musculo([ 'name' => 'Antebrazo'])]
        );

        $grupoMuscularPierna->musculos()->saveMany(
            [new Musculo(['name' => 'Femoral' ]),
            new Musculo([ 'name' => 'Cuadriceps' ]),
            new Musculo([ 'name' => 'Gemelos' ]),
            new Musculo([ 'name' => 'Aductores'])]
        );
                
    }
}
