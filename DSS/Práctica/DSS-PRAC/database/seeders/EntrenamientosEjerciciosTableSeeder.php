<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\Entrenamiento;
use App\Models\Ejercicio;

class EntrenamientosEjerciciosTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $entrenamiento = Entrenamiento::where('name', '=', 'Pecho')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho plano con mancuerna.')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho con mancuerna inclinado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'Pierna')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Extensión de cuadriceps')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Curl Femoral')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevación de gemelos en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'Deltoides')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas inclinado hacia delante')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'Full Body')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho con mancuerna inclinado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Extensión de cuadriceps')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas inclinado hacia delante')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'FullBody Shred Summer')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho plano con mancuerna.')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho con mancuerna inclinado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'Hard as God Full body ')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Extensión de cuadriceps')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Curl Femoral')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevación de gemelos en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas inclinado hacia delante')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);

        $entrenamiento = Entrenamiento::where('name', '=', 'CBUM Workout')->first();
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Elevaciones laterales')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Apertura de mancuernas')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho plano con mancuerna.')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press de pecho con mancuerna inclinado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Press Militar con mancuernas sentado')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
        $ejercicio = Ejercicio::where('name', '=', 'Abductor en máquina')->first();
        $entrenamiento->ejercicios()->attach($ejercicio->id);
    }
}
