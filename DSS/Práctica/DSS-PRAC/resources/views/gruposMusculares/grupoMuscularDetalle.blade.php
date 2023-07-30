@extends('layouts.admin')

@section('content')
<script src="../js/users.js"> </script>
<div>


    <div class=" d-flex justify-content-between ">
        <h1>Editar grupo muscular.</h1>
        <a href={{ URL::previous() }} class="btn btn-primary" style="height: min-content; font-size: 1.2rem;"> Atras </a>
    </div>
    <h3>Nombre: {{$grupo->name}}</h3>
    <h3>Descripcion: {{$grupo->descripcion}}</h3>
    @include('common.alert')
    <div class="" style="margin-top: 20px;">
        <form action="{{ url('/admin/gruposMusculares',$grupo->id)}}" method="POST">
            @csrf
            {{ method_field('PUT') }}
            <div class="form-group">
                <label for="name">Nombre del grupo</label>
                <input class="form-control" placeholder="Nuevo nombre del grupo muscular..." required type="text" name="name" id="name">
            </div>

            <div class="form-group">
                <label for="descripcion">Descripción del grupo</label>
                <input class="form-control" placeholder="Nueva descripción del grupo muscular..." required type="text" name="descripcion" id="descripcion">
            </div>
            <div class="text-right">
                <button class="btn btn-primary" type="submit" style="margin-top: 20px;">Editar grupo muscular</button>
            </div>
        </form>
    </div>


    <h2 style="margin-top: 40px;">Listado de músculos del grupo muscular</h2>
    <div>
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">Nombre</th>
                    <th scope="col">Eliminar</th>
                </tr>
            <tbody>
                @foreach($grupo->musculos as $musculo)
                <tr>

                    <td>
                        {{$musculo->name}}
                    </td>
                    <td>
                        <form action="{{ url('/admin/gruposMusculares/delete',$musculo->id)}}" method="POST">
                            @csrf
                            {{ method_field('DELETE') }}
                            <button class="btn btn-danger" type="submit" style="margin-top: 20px;">Eliminar</button>
                        </form>
                    </td>
                </tr>
                @endforeach

            </tbody>
            </thead>
        </table>
    </div>
</div>
@endsection