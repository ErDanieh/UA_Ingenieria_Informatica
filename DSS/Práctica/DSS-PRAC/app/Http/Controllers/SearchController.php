<?php

namespace App\Http\Controllers;

use App\Models\Ejercicio;
use App\Models\Entrenamiento;
use App\Models\User;
use Illuminate\Http\Request;

class SearchController extends Controller
{
    function getSearch(Request $req)
    {

        try {
            $searchRequest = request()->q;
            $entrenamientosSearch = Entrenamiento::where('name', 'like', "%{$searchRequest}%")->take(4)->get();
            $ejerciciosSearch = Ejercicio::where('name', 'like', "%{$searchRequest}%")->take(4)->get();
            $entrenadoresSearch = User::where([
                ['is_trainer', '=', '1'],
                ['name', 'like', "%{$searchRequest}%"]
                ]
            )->take(4)->get();

            $data = [
                'entrenamientos' => $entrenamientosSearch,
                'ejercicios' => $ejerciciosSearch,
                'entrenadores' => $entrenadoresSearch
            ];

        } catch (\Throwable $th) {
            abort(503);
        }

        return view('search')->with('data', $data);
    }
}
