<?php

namespace App\Http\Controllers;

use App\Models\Entrenamiento;
use App\Models\Ejercicio;
use App\Models\GrupoMuscular;
use App\Models\User;
use App\ServiceLayer\ServicioUsuario;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Validator;

class EntrenamientosController extends Controller
{
    /**
     * Lista todos los entrenamientos
     *  */
    function getEntrenamientos()
    {

        $busquedaRequest = request()->search;
        $busquedaOrder = request()->ordered;
        //echo $busquedaOrder;
        if ($busquedaOrder == "Ascendente") {
            return view('entrenamientos.entrenamientos')
                ->with('entrenamientos', Entrenamiento::where('name', 'LIKE', "%{$busquedaRequest}%")
                    ->orderBy('name', 'ASC')
                    ->simplePaginate(10))
                ->with('gruposMusculares', GrupoMuscular::all())
                ->with('ejercicios', Ejercicio::all());
        } elseif ($busquedaOrder == "Descendente") {
            return view('entrenamientos.entrenamientos')
                ->with('entrenamientos', Entrenamiento::where('name', 'LIKE', "%{$busquedaRequest}%")
                    ->orderBy('name', 'DESC')
                    ->simplePaginate(10))
                ->with('gruposMusculares', GrupoMuscular::all())
                ->with('ejercicios', Ejercicio::all());
        }
        return view('entrenamientos.entrenamientos')
            ->with('entrenamientos', Entrenamiento::where('name', 'LIKE', "%{$busquedaRequest}%")
                ->simplePaginate(10))
            ->with('ejercicios', Ejercicio::all());
    }

    /**
     * Devuelve la vista del entrenamiento detallado.
     * ADMINISTRADOR
     */
    function getEntrenamientoDetalle($id)
    {
        try {
            return view('entrenamientos.entrenamientoDetalle')
                ->with('entrenamiento', Entrenamiento::findOrFail($id))
                ->with('ejercicios', Ejercicio::all());
        } catch (\Throwable $th) {
            return abort(503, 'Internal server error');
        }
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
                $EntrenamientoNuevo->save();

                return redirect("/admin/entrenamientos/" . strval($EntrenamientoNuevo->id))->with('exito', 'al añadir el entrenamiento');
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
                return redirect()->back()->with('exito', 'Entrenamiento eliminado');
            }
            return redirect()->back()->with('error', 'Error no existe el Entrenamiento');
        } catch (\Throwable $th) {
            return abort(503, 'Internal server error');
        }
    }

    function editEntrenamiento(Request $req, $id)
    {


        $validator = Validator::make($req->all(), [
            'name' => 'max:255',
            'descripcion' => 'max:255',
            'urlImagen' => 'max:255'
        ]);

        if ($validator->fails()) {
            return redirect()->back()->with('error', 'Rellene todos los campos. (Maximo 255)');
        }

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


    /**
     * E.imina un ejercicio de un entrenamiento
     */
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

    function anadirAUsuario($idEntrenamiento)
    {
        $resultadoOperacion = ServicioUsuario::procesarSeguirEntrenamiento($idEntrenamiento);

        if ($resultadoOperacion) {
            return redirect()->back()->with('exito', 'Has seguido al entrenamiento con exito');
        }

        return redirect()->back()->with('ERROR', 'Fallo al seguir al entrenamiento');
    }


    function quitarAUsuario($idEntrenamiento)
    {
        $resultadoOperacion = ServicioUsuario::procesarDejarSeguirEntrenamiento($idEntrenamiento);

        if ($resultadoOperacion) {
            return redirect()->back()->with('ERROR', 'Fallo al dejar de seguir al entrenamiento');
        }

        return redirect()->back()->with('exito', 'Has seguido al entrenamiento con exito');
    }


    function searchEntreamiento(Request $req)
    {
        return view('entrenamientos.entrenamientos')->with('entrenamientos', Entrenamiento::where('name', 'LIKE', "%{$req->input('search')}%")
            ->simplePaginate(10));
    }



    function getInformacionEntrenamiento($id)
    {
        try {
            $entrenamiento = Entrenamiento::findOrFail($id);
        } catch (\Throwable $th) {
            return abort('404');
        }
        return view('entrenamientos.entrenamientoInformacion')
            ->with('entrenamiento', $entrenamiento)
            ->with('ejercicios', Ejercicio::all());
    }
}
