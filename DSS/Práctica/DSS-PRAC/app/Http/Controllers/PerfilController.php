<?php

namespace App\Http\Controllers;

use App\Models\User;
use App\Models\Entrenamiento;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;


class PerfilController extends Controller
{
    function getPerfil()
    {
        return view("user.perfil")->with('misEntrenamientos', User::find(Auth::id())->entrenamientos);
    }

    function updateProfilePicture(Request $req)
    {
        $picture = $req->input('picture');
        $UsuarioEditar = User::findOrFail(auth::user()->id);
        if ($picture != null) {
            //echo $req->input('picture');
            $UsuarioEditar->picture = $picture;
            $UsuarioEditar->save();
            return redirect()->back()->with('exito', 'Se ha cambiado');
        }
        return redirect()->back()->with('ERROR', 'No se ha cambiado');
    }
}
