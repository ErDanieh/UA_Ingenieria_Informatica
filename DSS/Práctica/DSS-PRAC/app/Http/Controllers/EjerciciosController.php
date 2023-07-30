<?php

namespace App\Http\Controllers;

use App\Models\Ejercicio;
use App\Models\GrupoMuscular;
use Illuminate\Http\Request;
use Symfony\Component\Console\Input\Input;
use DB;
use Illuminate\Support\Facades\Validator;

class EjerciciosController extends Controller
{
    /**
     * Lista todos los ejercicios
     *  */
    function getEjercicios(Request $req)
    {

        try {
            $busquedaRequest = request()->search;
            $grupoMuscularFilter = request()->gm;
            $resultado = Ejercicio::simplePaginate(10);


            try {
                if ($grupoMuscularFilter != null) {
                    $grupoMuscular = GrupoMuscular::where('name', '=', $grupoMuscularFilter)->first();
                    $resultado = $grupoMuscular->ejercicios()->simplePaginate(10);
                }
                if ($busquedaRequest != null) {
                    $ejerciciosFIltradosNombre = Ejercicio::where('name', 'like', "%{$busquedaRequest}%");
                    $resultado = $ejerciciosFIltradosNombre->simplePaginate(10);  
                }
            } catch (\Throwable $th) {
                return view('ejercicios.ejercicios')
                    ->with('ejercicios', Ejercicio::simplePaginate(10))
                    ->with('gruposMusculares', GrupoMuscular::all());
            }

            return view('ejercicios.ejercicios', ['ejercicios' => $resultado])
                    ->with('ejercicios', $resultado)
                    ->with('gruposMusculares', GrupoMuscular::all());

        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }

    function getExplorarEjercicios() 
    {
        return view('ejercicios.ejerciciosExplorar')->with('ejercicios', Ejercicio::simplePaginate(6));
    }

    function getInformacionEjercicio($idEjercicio)
    {
        try {
            $ejercicio = Ejercicio::findOrFail($idEjercicio);

        } catch (\Throwable $th) {
            abort(404);
        }

        return view('ejercicios.ejercicioInformacion')->with('ejercicio', $ejercicio);
    }


    /**
     * Añade ejercicios
     */
    function newEjercicios(Request $req)
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
            $nombreEjercicio = $req->input('name');
            $descripcionEjercicio = $req->input('descripcion');
            $urlImagenEjercicio = $req->input('urlImagen');

            $ejercicio = Ejercicio::where('name', '=', $nombreEjercicio)->first();

            if ($ejercicio == null) {
                $ejercicioNuevo = new Ejercicio();
                $ejercicioNuevo->name = $nombreEjercicio;
                $ejercicioNuevo->descripcion = $descripcionEjercicio;
                $ejercicioNuevo->url_img = $urlImagenEjercicio;
                $ejercicioNuevo->save();

                return redirect()->back()->with('exito', 'Ejercicio insertado con exito');
            } else {
                return redirect()->back()->with('error', 'Error ya existe el ejercicio');
            }
        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }

    function deleteEjercicio($id)
    {
        try {
            $ejercicioEsperado = Ejercicio::findOrFail($id);

            if ($ejercicioEsperado != null) {
                $ejercicioEsperado->delete();
                return redirect()->back()->with('exito', 'Ejercicio eliminado con exito');
            }
            return redirect()->back()->with('error', 'Error no existe el ejercicio');
        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }


    function getEjercicioDetalle($id)
    {
        try {
            return view('ejercicios.ejercicioDetalle')->with('ejercicio', Ejercicio::findOrFail($id));
        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }

    function editEjercicio(Request $req, $id)
    {
        try {
            $EjercicioEditar = Ejercicio::findOrFail($id);
            if ($EjercicioEditar != null) {

                if ($req->input('name') != null) {
                    $EjercicioEditar->name = $req->input('name');
                }

                if ($req->input('descripcion') != null) {
                    $EjercicioEditar->descripcion = $req->input('descripcion');
                }

                if ($req->input('urlImagen') != null) {
                    $EjercicioEditar->url_img = $req->input('urlImagen');
                }

                $EjercicioEditar->save();

                return redirect()->back()->with('exito', 'Ejercicio editado');
            } else {
                return redirect()->back()->with('error', 'Error ya existe el Ejercicio');
            }
        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }

    function searchEjercicios(Request $req)
    {
        try {
            return view('ejercicios.ejercicios')->with('ejercicios', Ejercicio::where('name', 'LIKE', "%{$req->input('search')}%")
                ->simplePaginate(10));
        } catch (\Throwable $th) {
            return abort(503, 'Internal Error');
        }
    }

}
