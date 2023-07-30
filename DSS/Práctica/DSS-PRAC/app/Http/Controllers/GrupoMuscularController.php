<?php

namespace App\Http\Controllers;

use App\Models\GrupoMuscular;
use App\Models\Musculo;
use Illuminate\Http\Request;
use App\Http\Controllers\MusculosController;
use Illuminate\Support\Facades\Validator;

class GrupoMuscularController extends Controller
{
    /**
     * Lista todos los usuarios
     *  */
    function getGruposMusculares()
    {
        $busquedaRequest = request()->search;
        $busquedaOrder = request()->ordered;
        //echo $busquedaOrder;
        if ($busquedaOrder == "Ascendente") {
            return view('gruposMusculares.gruposMusculares')->with('gruposMusculares', GrupoMuscular::where('name', 'LIKE', "%{$busquedaRequest}%")
                ->orderBy('name', 'ASC')
                ->simplePaginate(10));
        } elseif ($busquedaOrder == "Descendente") {
            return view('gruposMusculares.gruposMusculares')->with('gruposMusculares', GrupoMuscular::where('name', 'LIKE', "%{$busquedaRequest}%")
                ->orderBy('name', 'DESC')
                ->simplePaginate(10));
        }
        return view('gruposMusculares.gruposMusculares')->with('gruposMusculares', GrupoMuscular::where('name', 'LIKE', "%{$busquedaRequest}%")
            ->simplePaginate(10));

    }

    /**
     * Proceso para añadir un nuevo musculo.
     */
    function newGruposMusculares(Request $req)
    {

        $validator = Validator::make($req->all(), [
            'name' => 'required|max:255',
            'descripcion' => 'required|max:255',
        ]);

        if ($validator->fails()) {
            return redirect()->back()->with('error', 'Rellene todos los campos. (Maximo 255)');
        }

        $nombre = $req->input('name');
        $grupoMuscularNoEsperado = GrupoMuscular::where('name', '=', $nombre)->first();

        if ($grupoMuscularNoEsperado == null) {
            $grupoMuscularNuevo = new GrupoMuscular();
            $grupoMuscularNuevo->name = $nombre;
            $grupoMuscularNuevo->descripcion = $req->input('descripcion');
            $grupoMuscularNuevo->save();

            return redirect()->back()->with('exito', 'Grupo Muscular insertado con exito');
        } else {
            return redirect()->back()->with('error', 'Error ese grupo muscular ya ha sido añadido');
        }
    }


    function deleteGrupoMuscular($id)
    {
        $grupoMuscularEsperado = GrupoMuscular::findOrFail($id);

        if ($grupoMuscularEsperado != null) {
            $grupoMuscularEsperado->delete();
            return redirect()->back()->with('exito', 'Grupo Muscular eliminado con exito');
        }
        return redirect()->back()->with('error', 'Error ese grupo muscular no existe');
    }

    function getGruposMuscularesDetalle($id)
    {
        return view('gruposMusculares.grupoMuscularDetalle')->with('grupo', GrupoMuscular::findOrFail($id));
    }

    function editGruposMusculares(Request $req, $id)
    {
        $grupoEditar = GrupoMuscular::findOrFail($id);
        if ($grupoEditar != null) {

            if ($req->input('name') != null) {
                $grupoEditar->name = $req->input('name');
            }

            if ($req->input('descripcion') != null) {
                $grupoEditar->descripcion = $req->input('descripcion');
            }


            $grupoEditar->save();

            return redirect()->back()->with('exito', 'Grupo muscular editado');
        } else {
            return redirect()->back()->with('error', 'Error no existe el Grupo muscular');
        }
    }

    function editMusculosContiene($idMusculo)
    {
        return MusculosController::deleteMusculo($idMusculo);
    }


    function searchGrupoMuscular(Request $req)
    {
        return view('gruposMusculares.gruposMusculares')->with('gruposMusculares', GrupoMuscular::where('name', 'LIKE', "%{$req->input('search')}%")
            ->simplePaginate(10));
    }
}
