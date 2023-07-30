@extends('layouts.admin') @section('content') <script src="../js/users.js"> </script>
<div>
    <h1>Grupos Musculares</h1>
    <script src="../js/utils.js"> </script>
    {{-- Buscador --}}
    <input type="text" class="form-control" name="search" id="search" autofocus onchange="redirectSearch()" placeholder="Busqueda por nombre."></input>


    <div class="" style="margin: 50px auto;">
        <h2>Añadir grupo muscular</h2>
        <form action="{{ url('/admin/gruposMusculares') }}" method="POST"> @csrf <div class="form-group">
                <label for="name">Grupo Muscular</label>
                <input class="form-control" placeholder="Nombre del grupo muscular..." required type="text" name="name" id="name">
            </div>
            <div class="form-group">
                <label for="descripcion">
                    Descripción de grupo muscular
                </label>
                <input class="form-control" placeholder="Descripción del grupo muscular..." required type="text" name="descripcion" id="descripcion">
            </div>
            <button class="btn btn-primary" type="submit" style="margin-top: 20px; font-size: 1.2rem;">
                Añadir grupo muscular
            </button>
        </form>
    </div>

    @include('common.alert')
    <select type="text" class="form-control" name="ordered" id="ordered" autofocus onchange="redirectUrlParams('ordered')">
        <option selected disabled> Ordenación</option>
        <option> Ascendente</option>
        <option> Descendente</option>
    </select>
    <h2>Listado de grupos musculares</h2>
    <div class="table-responsive">
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">Nombre</th>
                    <th scope="col">Descripción</th>
                    <th scope="col">Editar</th>
                    <th scope="col">Eliminar</th>
                </tr>
            </thead>
            <tbody class="align-middle">
                @foreach($gruposMusculares as $grupo)
                <tr>
                    <td>{{$grupo->name }}</td>
                    <td>{{$grupo->descripcion }}</td>
                    <td>
                        <button class="btn btn-success" type="submit" onclick="showProfile({{$grupo->id}})">Editar</button>
                    </td>
                    <td>
                        <form action="{{url('/admin/gruposMusculares', $grupo->id)}}" method="POST">
                            @csrf {{ method_field('DELETE') }}
                            <button class="btn btn-danger" type="submit">Eliminar</button>
                        </form>
                    </td>
                </tr> @endforeach
            </tbody>
        </table>
        <div class="text-center d-flex justify-content-center m-5">
        @if(request()->search!=null && request()->ordered!=null)
            {{ $gruposMusculares->appends(['search'=>request()->search, 'ordered'=>request()->ordered])->links() }}

            @elseif(request()->search!=null && request()->ordered==null)
            {{ $gruposMusculares->appends(['search'=>request()->search])->links() }}

            @elseif(request()->search==null && request()->ordered!=null)
            {{ $gruposMusculares->appends(['ordered'=>request()->ordered])->links() }}
            @else 
            {{ $gruposMusculares->links() }}

            @endif
        </div>
    </div>
</div> @endsection