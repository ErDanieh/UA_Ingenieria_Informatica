@extends('layouts.admin')

@section('content')
<script src="../js/users.js"> </script>
<script src="../js/utils.js"> </script>
<div>

    <h1>Músculos</h1>
    {{-- Buscador --}}
    <input type="text" class="form-control" name="search" id="search" autofocus onchange="redirectSearch()" placeholder="Busqueda por nombre."></input>


    <div class="" style="margin: 50px auto;">
        <h2>Añadir músculo</h2>
        <form action="{{ url('/admin/musculos') }}" method="POST">
            @csrf
            <div class="form-group">
                <label for="name">Musculo</label>
                <input class="form-control" placeholder="Nombre del músculo..." required type="text" name="name" id="name">
            </div>
            <div class="form-group" style="margin-top: 10px;">
                <label for="nombreGrupo">Nombre Grupo Muscular</label>
                <select name="grupo" class="form-select">
                    @foreach($gruposMusculares as $grupoMuscular)
                    <option value="{{$grupoMuscular->name}}">{{$grupoMuscular->name}}</option>
                    @endforeach
                </select>
            </div>
            <button class="btn btn-primary" type="submit" style="margin-top: 20px; font-size: 1.2rem;">Añadir Músculo</button>
        </form>
    </div>

    @include('common.alert')
    <select type="text" class="form-control" name="ordered" id="ordered" autofocus onchange="redirectUrlParams('ordered')">
        <option selected disabled> Ordenación</option>
        <option> Ascendente</option>
        <option> Descendente</option>
    </select>

    <h2>Listado de musuculos</h2>
    <div class="table-responsive">
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">Nombre</th>
                    <th scope="col">Grupo Muscular</th>
                    <th scope="col">Editar</th>
                    <th scope="col">Eliminar</th>
                </tr>
            </thead>
            <tbody>
                @foreach($musculos as $musculo)
                <tr>
                    <td> {{$musculo->name}} </td>
                    <td>
                        {{$musculo->grupoMuscular->name}}
                    </td>
                    <td>
                        <button class="btn btn-success" type="submit" onclick="showProfile({{$musculo->id}})">Editar</button>
                    </td>
                    <td>
                        <form action="{{url('/admin/musculos', $musculo->id)}}" class="mr-4" method="POST">
                            @csrf
                            {{ method_field('DELETE') }}
                            <button class="btn btn-danger" type="submit">Eliminar</button>
                        </form>
                    </td>
                </tr>
                @endforeach
            </tbody>
        </table>
        <div class="text-center d-flex justify-content-center m-5">
            @if(request()->search!=null && request()->ordered!=null)
            {{ $musculos->appends(['search'=>request()->search, 'ordered'=>request()->ordered])->links() }}

            @elseif(request()->search!=null && request()->ordered==null)
            {{ $musculos->appends(['search'=>request()->search])->links() }}

            @elseif(request()->search==null && request()->ordered!=null)
            {{ $musculos->appends(['ordered'=>request()->ordered])->links() }}
            @else 
            {{ $musculos->links() }}

            @endif
        </div>

    </div>




</div>
@endsection