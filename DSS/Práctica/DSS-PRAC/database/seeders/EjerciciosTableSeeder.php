<?php

namespace Database\Seeders;
use App\Models\Ejercicio;
use Illuminate\Database\Seeder;
use DB;

class EjerciciosTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('ejercicios')->delete();

        $ejercio = new Ejercicio(
            ['name' => 'Press de pecho plano con mancuerna.',
             'descripcion' => 'Nos tumbaremos en un banco colocado de manera plana y empujaremos las mancuernas hacia arriba a la altura de nuestro pecho.',
             'url_img' => 'https://i.blogs.es/85d668/bench-press-1/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Press de pecho con mancuerna inclinado',
             'descripcion' => 'Nos tumbaremos en un banco colocado de manera inclinada y empujaremos las mancuernas hacia arriba a la altura de nuestro pecho.',
             'url_img' => 'https://www.entrenamientos.com/media/cache/exercise_375/uploads/exercise/press-pectoral-con-mancuernas-en-banco-inclinado-7131.png']
        );
        $ejercio->save();
        $ejercio = new Ejercicio(
            ['name' => 'Apertura de mancuernas',
             'descripcion' => 'Nos tumbaremos en un banco colocado de manera plana, subiremos los brazos y los abriremos y cerraremos con las mancuernas en las manos.',
             'url_img' => 'https://i.blogs.es/5c0b8f/aperturas/450_1000.jpg']
        );
        $ejercio->save();
        $ejercio = new Ejercicio(
            ['name' => 'Apertura de mancuernas inclinado hacia delante',
             'descripcion' => 'Situaremos los brazos  perpendicularmente al suelo mientras quelas palmas de las manos deben estar una frente a la otra. Retraiga sus omoplatos.',
             'url_img' => 'https://www.entrenamientos.com/media/cache/exercise_375/uploads/exercise/aperturas-con-mancuernas-inclinado-adelante-1928.png']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Cruces en polea alta',
             'descripcion' => 'En las poleas mixtas colocaremos los agarres arriba y cruzaremos los brazos formando una X',
             'url_img' => 'https://i.blogs.es/6ab47e/cruce2/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Cruces en polea baja',
             'descripcion' => 'En las poleas mixtas colocaremos los agarres baja y cruzaremos los brazos formando una X',
             'url_img' => 'https://i.blogs.es/6ab47e/cruce2/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Extensión de cuadriceps ',
             'descripcion' => 'Eleveramos las piernas en la máquina de extensión de cuadriceps',
             'url_img' => 'https://i.blogs.es/c32e1e/guia1/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Curl Femoral',
             'descripcion' => 'Eleveramos las piernas en la máquina de curl de femoral',
             'url_img' => 'https://i.blogs.es/58b557/curl-piernas/1366_2000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Elevación de gemelos en máquina',
             'descripcion' => 'Nos pondremos de puntillas con el peso en los hombros en la máquina de elevación de gemelos',
             'url_img' => 'https://i.blogs.es/310362/elevacion2/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Abductor en máquina',
             'descripcion' => 'Cerraremos las piernas en abductor en máquina de manera controlada.',
             'url_img' => 'https://i.blogs.es/9c62f8/abductores/1366_2000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Press Militar con mancuernas sentado',
             'descripcion' => 'En un banco sentados con el respaldo a 90 grados elevaremos de manera vertical las mancuernas por encima de la cabeza.',
             'url_img' => 'https://i.blogs.es/6485db/pres-hombro/450_1000.jpg']
        );
        $ejercio->save();

        $ejercio = new Ejercicio(
            ['name' => 'Elevaciones laterales',
             'descripcion' => 'Eleveramos las mancuernas a los lados de nuestro cuerpo de manera controlada.',
             'url_img' => 'https://i.blogs.es/7ad688/ejercicio21-3/450_1000.jpg']
        );
        $ejercio->save();

    }
}
