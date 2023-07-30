<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Entrenamiento;

class ExplorarController extends Controller
{
    function getExplorar()
    {
        return view("explorar")->with('entrenamientos', Entrenamiento::simplePaginate(6));
    }
}
