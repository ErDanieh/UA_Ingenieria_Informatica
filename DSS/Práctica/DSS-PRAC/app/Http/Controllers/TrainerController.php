<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Entrenamiento;
use App\Models\Ejercicio;
use App\Models\User;
use App\Mail\contactar;
use App\Models\GrupoMuscular;
use Illuminate\Support\Facades\Mail;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Validator;

class TrainerController extends Controller
{
    function getTrainerAll()
    {
        $busquedaRequest = request()->search;
        $busquedaOrder = request()->ordered;
        return view('trainers.trainer')->with('entrenamientos', Entrenamiento::where('name', 'LIKE', "%{$busquedaRequest}%")->simplePaginate(10));
    }

    function newEntrenamiento(Request $req)
    {

        $validator = Validator::make($req->all(), [
            'name' => 'required|max:255',
            'descripcion' => 'required|max:255',
            'urlImagen' => 'required|max:255'
        ]);

        if ($validator->fails()) {
            return redirect()->back()->with('error', 'Rellene todos los campos. (Maximo 255)');
        }

        try {
            $nombreEntrenamiento = $req->input('name');
            $descripcionEntrenamiento = $req->input('descripcion');
            $urlImagenEntrenamiento = $req->input('urlImagen');

            $EntrenamientoNoEsperado = Entrenamiento::where('name', '=', $nombreEntrenamiento)->first();

            if ($EntrenamientoNoEsperado == null) {
                $EntrenamientoNuevo = new Entrenamiento();
                $EntrenamientoNuevo->name = $nombreEntrenamiento;
                $EntrenamientoNuevo->descripcion = $descripcionEntrenamiento;
                $EntrenamientoNuevo->url_img = $urlImagenEntrenamiento;
                $EntrenamientoNuevo->creator_id = auth::user()->id;
                $EntrenamientoNuevo->save();

                return redirect("/entrenamientos/" . strval($EntrenamientoNuevo->id))->with('exito', 'al añadir el entrenamiento');
            } else {
                return redirect()->back()->with('error', 'Error ya existe el Entrenamiento');
            }
        } catch (\Throwable $th) {
            return abort(503, 'Internal server error');
        }
    }

    function editEntrenamiento(Request $req, $id)
    {

        try {
            $EntrenamientoEditar = Entrenamiento::findOrFail($id);
            if ($EntrenamientoEditar != null) {

                if ($req->input('name') != null) {
                    $EntrenamientoEditar->name = $req->input('name');
                }

                if ($req->input('descripcion') != null) {
                    $EntrenamientoEditar->descripcion = $req->input('descripcion');
                }

                if ($req->input('urlImagen') != null) {
                    $EntrenamientoEditar->url_img = $req->input('urlImagen');
                }

                $EntrenamientoEditar->save();

                return redirect()->back()->with('exito', 'Entrenamiento editado');
            } else {
                return redirect()->back()->with('error', 'Error ya existe el Entrenamiento');
            }
        } catch (\Throwable $th) {
            return abort(503, 'Internal server error');
        }
    }

    function deleteEntrenamiento($id)
    {
        try {
            $EntrenamientoEsperado = Entrenamiento::where('id', '=', $id)->first();

            if ($EntrenamientoEsperado != null) {
                $EntrenamientoEsperado->delete();
                return redirect('/entrenamientos')->with('exito', 'Entrenamiento eliminado');
            }
            return redirect()->back()->with('error', 'Error no existe el Entrenamiento');
        } catch (\Throwable $th) {
            return abort(503, 'Internal server error');
        }
    }


    function eliminarEjercicioDeEntrenamiento($idEntrenamiento, $idEjercicio)
    {

        try {
            $entrenamiento = Entrenamiento::findOrFail($idEntrenamiento);
            $ejercicio = Ejercicio::findOrFail($idEjercicio);
            $ejercicio->entrenamientos()->detach($entrenamiento);
            return redirect()->back()->with('exito', 'Ejercicio eliminado del entrenamiento.');
        } catch (\Throwable $th) {
            return redirect()->back()->with('error', 'No se ha podido eliminar el ejercicio del entrenamiento-');
        }
    }

    function addEjercicioEntrenamiento(Request $req, $idEntrenamiento)
    {
        try {
            $entrenamiento = Entrenamiento::findOrFail($idEntrenamiento);
            $ejercicio = Ejercicio::findOrFail($req->grupo);
            $entrenamiento->ejercicios()->attach($ejercicio);
            $entrenamiento->save();
            return redirect()->back()->with('exito', 'Ejercicio anadido al entrenamiento.');
        } catch (\Throwable $th) {
            return redirect()->back()->with('error', 'No se ha podido anadir el ejercicio');
        }
    }

    function getEntrenamientoDetalle($id)
    {
        try {
            $entrenamiento = Entrenamiento::findOrFail($id);
        } catch (\Throwable $th) {
            return abort('404');
        }
        return view('entrenamientos.entrenamientoInformacion')
            ->with('entrenamiento', $entrenamiento)
            ->with('gruposMusculares', GrupoMuscular::all());
    }

    function getEjercicioCreator()
    {
        return view('ejercicios.ejercicioCreator');
    }

    function sendMail(Request $req, $id)
    {
        try {
            $usuario = auth::user();
            Mail::to(User::findOrFail($id)->email)->send(new contactar($usuario, $req->input('mensaje')));
            return redirect()->back()->with('exito', 'Email enviado con exito');
        } catch (\Throwable $th) {
            return redirect()->back()->with('error', 'Error al enviar el email');
        }
    }
}
