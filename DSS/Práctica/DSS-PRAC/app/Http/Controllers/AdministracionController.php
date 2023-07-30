<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

use App\Models\User;
use App\Models\Entrenamiento;
use App\Models\Ejercicio;
use App\Models\Musculo;
use App\Models\GrupoMuscular;
use Illuminate\Support\Facades\DB;


class AdministracionController extends Controller
{

    static function comprobarBD()
    {

        try {
            DB::connection()->getPdo();
        } catch (\Exception $e) {

            die(view("errordb"));
        }
    }

    function getAdministracion()
    {
        return view("admin.admin");
    }

    static function numUsers()
    {
        try {
            return User::all()->count();
        } catch (\Throwable $th) {
            die(view("errordb"));

        }
    }

    static function numEntrenadores()
    {
        try {
            return User::where('is_trainer', '=', 1)->count();
        } catch (\Throwable $th) {
        }
    }

    static function numEntrenamientos()
    {
        try {
            return Entrenamiento::all()->count();
        } catch (\Throwable $th) {
            //throw $th;
        }
    }

    static function numEjercicios()
    {
        try {
            return Ejercicio::all()->count();
        } catch (\Throwable $th) {
            //throw $th;
        }
    }

    static function numMusculos()
    {
        try {
            return Musculo::all()->count();
        } catch (\Throwable $th) {
            //throw $th;
        }
    }

    static function grupoMuscular()
    {
        try {
            return GrupoMuscular::all()->count();
        } catch (\Throwable $th) {
            //throw $th;
        }
    }
}
