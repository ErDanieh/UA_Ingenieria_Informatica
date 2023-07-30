<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\GrupoMuscular;
use DB;

class GrupoMuscularsTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('grupo_musculars')->delete();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Pectorales',
            'descripcion' => 'Abarcan la parte superior delantera del torso, divididos usualmente en pectorales superiores, medios e inferiores. En la parte central encontramos la raya o cesura del pecho, que se trabaja usualmente con ejercicios como la mariposa (pec deck), las aperturas y los cruzamientos en polea.'],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Deltoides',
            'descripcion' => 'Los hombros. Se dividen en zonas anterior, media y posterior, cada una con sus ejercicios específicos. Los hombros otorgan amplitud a la figura y refuerzan la sensación de una cintura estrecha. Los hombros caídos, sin entrenar o mal entrenados o poco desarrollados son pobres estéticamente y crean una apariencia de ausencia de volumen muscular en la zona alta del torso.'],
        );
        $grupoMuscular->save();
        
        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Espalda',
            'descripcion' => 'No sólo los dorsales componen la espalda, sino también el romboides, que le da volumen a la parte media, y los lumbares, que fortifican la parte baja. La zona más trabajada de la espalda, son los músculos dorsales, que al ser exhibidos dan sensación de amplitud. '],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Glúteos',
            'descripcion' => 'La zona muscular preferida de las damas, también es cultivada estéticamente por los varones, aun cuando a éstos no les guste admitirlo.'],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Trapecios',
            'descripcion' => 'El toque final a la zona alta del torso, unos trapecios excesivamente desarrollados pueden hacer que tus hombros luzcan más pequeños.'],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Abdominales',
            'descripcion' => 'La zona muscular que todos desean tener libre de grasa para que el mundo se deslumbre, y pocos saben entrenar correctamente. '],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Brazo',
            'descripcion' => 'Uno de los grupos musculares más apreciados a la hora de entrenar.'],
        );
        $grupoMuscular->save();

        $grupoMuscular = new GrupoMuscular(
            ['name' => 'Piernas',
            'descripcion' => 'Un grupo muscular a veces totalmente descuidado por los atletas, las piernas bien desarrolladas evitan una apariencia despareja entre éstas y el torso. Las principales zonas dentro de este importante grupo son']
        );
        $grupoMuscular->save();
    }
}
