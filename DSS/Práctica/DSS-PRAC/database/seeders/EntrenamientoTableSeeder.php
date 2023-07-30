<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\Entrenamiento;

class EntrenamientoTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $entrenamiento = new Entrenamiento([
            'name' => 'Pecho',
            'descripcion' => 'Esta es la descripcion del entrenamiento 1.',
            'url_img' => 'https://media.revistagq.com/photos/5ecea90bd6d588d6f671d17c/16:9/w_2560%2Cc_limit/ejercicios-comba.jpg',
            'creator_id' => 3
        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'Pierna',
            'descripcion' => 'Esta es la descripcion del entrenamiento 2.',
            'url_img' => 'https://quieroserdeportista.com/wp-content/uploads/2021/04/Categorias-del-entrenamiento-deportivo1.jpg',
            'creator_id' => 3

        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'Deltoides',
            'descripcion' => 'Esta es la descripcion del entrenamiento 3.',
            'url_img' => 'https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/man-exercising-with-kettlebell-in-the-gym-royalty-free-image-1581347057.jpg?crop=1.00xw:0.446xh;0,0.237xh&resize=768:*',
            'creator_id' => 3

        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'Full Body',
            'descripcion' => 'Esta es la descripcion del entrenamiento 4.',
            'url_img' => 'https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/body-builder-training-in-industrial-urban-gym-royalty-free-image-1581345623.jpg',
            'creator_id' => 3

        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'FullBody Shred Summer',
            'descripcion' => 'Esta es la descripcion del entrenamiento 5.',
            'url_img' => 'http://palomasala.com/wp-content/uploads/2019/01/tipos-de-rutinas-que-podemos-hacer-en-el-gimnasio-1.jpg'
        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'Hard as God Full body ',
            'descripcion' => 'Esta es la descripcion del entrenamiento 6.',
            'url_img' => 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSjOv7fRZYU02_LJbwsnsIqHqFgzA7r98HJeQ&usqp=CAU'
        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }

        $entrenamiento = new Entrenamiento([
            'name' => 'CBUM Workout',
            'descripcion' => 'Esta es la descripcion del entrenamiento 6.',
            'url_img' => 'https://pbs.twimg.com/media/FQhaL_RX0AM4brR?format=jpg&name=large'
        ]);

        try
        {
            $entrenamiento->save();
        }
        catch(\Exception $e){
            echo $e->getMessage();
        }
    }
}
