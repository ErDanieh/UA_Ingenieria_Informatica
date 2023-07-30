<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        // \App\Models\User::factory(10)->create();
        $this->call(GrupoMuscularsTableSeeder::class);
        $this->call(MusculosTableSeeder::class);
        $this->call(EjerciciosTableSeeder::class);
        $this->call(EjercicioGrupoMuscularsTableSeeder::class);
        $this->call(UserTableSeeder::class);
        $this->call(EntrenamientoTableSeeder::class);
        $this->call(UsersEntrenamientoTableSeeder::class);
        $this->call(EntrenamientosEjerciciosTableSeeder::class);

    }
}
