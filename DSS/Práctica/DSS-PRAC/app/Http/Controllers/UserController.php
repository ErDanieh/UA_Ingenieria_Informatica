<?php

namespace App\Http\Controllers;


use Illuminate\Http\Request;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Validator;

class UserController extends Controller
{
    /**
     * Lista todos los usuarios
     *  */
    function getUsers()
    {
        $busquedaRequest = request()->search;
        // $musculos = Musculo::paginate(10);
        return view('user.users')->with('users', User::where('name', 'LIKE', "%{$busquedaRequest}%")->orWhere('email', 'LIKE', "%{$busquedaRequest}%")
            ->simplePaginate(10));
        //return view('musculos.musculos', compact('musculos'));
    }

    function getEntrenadores()
    {

        return view('entrenadoresGeneral')->with('entrenadores', User::where('is_trainer', 'LIKE', "1")->simplePaginate(10));
    }

    function getEntrenadoresProfile($id)
    {
        return view('trainers.trainerProfile')->with('user', User::findOrFail($id));
    }
    /**Busca usuarios por nombre o email
     * 
     */
    function searchUsers(Request $req)
    {
        return view('user.users')->with('users', User::where('name', 'LIKE', "%{$req->input('search')}%")
            ->orWhere('email', 'LIKE', "%{$req->input('search')}%")
            ->simplePaginate(10));
    }

    /**
     * Devuelve la vista del perfil del usuario
     */
    function getProfile($id)
    {
        return view('user.profile')->with('user', User::findOrFail($id));
    }

    function deleteUser($id)
    {
        $usuario = User::findOrFail($id);
        if ($usuario != null) {
            $usuario->delete();
            return redirect()->back()->with('exito', 'Usuario eliminado con exito');
        }
        return redirect()->back()->with('error', 'Error no existe el usuario');


        return redirect()->back();
    }

    function deleteUserFromProfile()
    {
        $UsuarioEditar = User::findOrFail(auth::user()->id);
        if ($UsuarioEditar != null) {
            $UsuarioEditar->delete();
            return redirect('/');
        }
    }

    function editProfile(Request $req, $id)
    {

        $validator = Validator::make($req->all(), [
            'grupo' => 'max:255',
            'name' => 'max:255',
        ]);

        if ($validator->fails()) {
            return redirect()->back()->with('error', 'Rellene todos los campos. (Maximo 255)');
        }

        $UsuarioEditar = User::findOrFail($id);
        if (
            $req->input('name') == null && $req->input('email') == null && $req->input('password') == null &&
            (!isset($_POST['beTrainer']) && $UsuarioEditar->is_trainer == 0 || isset($_POST['beTrainer']) && $UsuarioEditar->is_trainer == 1)
            && (!isset($_POST['beAdmin']) && $UsuarioEditar->is_admin == 0 || isset($_POST['beAdmin']) && $UsuarioEditar->is_admin == 1)
        ) {
            return redirect()->back()->with('error', 'No se han introducido nuevos valores');
        }

        if ($UsuarioEditar != null) {

            if ($req->input('name') != null) {
                $UsuarioEditar->name = $req->input('name');
            }

            if ($req->input('email') != null) {
                if (User::where('email', '=', $req->input('email'))->count() == 0) {
                    $UsuarioEditar->email = $req->input('email');
                } else {
                    return redirect()->back()->with('error', 'Ese email ya ha sido registrado');
                }
            }

            if ($req->input('password') != null) {
                $UsuarioEditar->password = bcrypt($req->input('password'));
            }

            if (!isset($_POST['beTrainer']))
                $UsuarioEditar->is_trainer = 0;
            else
                $UsuarioEditar->is_trainer = 1;

            if (!isset($_POST['beAdmin']))
                $UsuarioEditar->is_admin = 0;
            else
                $UsuarioEditar->is_admin = 1;

            $UsuarioEditar->save();
            return redirect()->back()->with('exito', 'Perfil editado');
        }
        return redirect()->back()->with('error', 'Error el perfil no existe');
    }
}
