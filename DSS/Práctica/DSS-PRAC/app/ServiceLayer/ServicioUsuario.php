<?php

namespace App\ServiceLayer;

use Illuminate\Support\Facades\DB;

use App\BusinessLogicLayer\DomainModel\ActiveRecord\Order;
use App\BusinessLogicLayer\DomainModel\ActiveRecord\OrderLine;
use App\BusinessLogicLayer\DomainModel\ActiveRecord\Product;
use App\Models\Entrenamiento;
use App\Models\User;
use Illuminate\Support\Facades\Auth;

class ServicioUsuario
{

    public static function procesarSeguirEntrenamiento($idEntrenamiento)
    {

        DB::beginTransaction();
        try {
            $entrenamiento = Entrenamiento::findOrFail($idEntrenamiento);
            $usuario = User::findOrFail(auth::user()->id);
            $entrenamiento->usuarios()->attach($usuario);
            $entrenamiento->seguidores += 1;
            $entrenamiento->save();
        } 
        catch (\Throwable $th) {
            DB::rollBack();
            return false;
        }

        DB::commit();
        return true;
    }

    public static function procesarDejarSeguirEntrenamiento($idEntrenamiento)
    {

        DB::beginTransaction();
        try {
            $entrenamiento = Entrenamiento::findOrFail($idEntrenamiento);
            $usuario = User::findOrFail(auth::user()->id);
            $entrenamiento->usuarios()->detach($usuario);
            $entrenamiento->seguidores -= 1;
            $entrenamiento->save();
        } 
        catch (\Throwable $th) {
            DB::rollBack();
            return false;
        }

        DB::commit();
        return true;
    }
}
