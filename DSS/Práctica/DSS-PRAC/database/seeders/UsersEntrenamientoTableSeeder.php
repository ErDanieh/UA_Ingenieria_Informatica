<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\Entrenamiento;
use App\Models\User;

class UsersEntrenamientoTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $entrenamiento = Entrenamiento::where('name', '=', 'Pecho')->first();  
        $usuario = User::where('email', '=', 'ander@uafit.com')->first();
        $entrenamiento->usuarios()->attach($usuario->id);
    }
}
