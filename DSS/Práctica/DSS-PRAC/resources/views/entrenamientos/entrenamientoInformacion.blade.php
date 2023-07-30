@extends('layouts.principal')

@section('content')
<div class="container min-vh-100">

    <div class="row">

        <h1 class="display-1">{{$entrenamiento->name}}</h1>
        <img src="{{$entrenamiento->url_img}}" class="col-md-8 " style="object-fit: cover;" />

        @if(!auth::guest() && auth::user()->id == $entrenamiento->creator_id)
        <div class="container col-md-4">

            <form action="{{ url('/trainer/entrenamientos',$entrenamiento->id)}}" method="POST" class="form-group">
                <h2>Modificar ejercicio</h2>

                @csrf
                {{ method_field('PUT') }}
                <div class="row">
                    <label for="name">Nombre entrenamiento</label>
                    <input name="name" id="name" value="{{$entrenamiento->name}}" class="form-control">
                </div>

                <div class="row">
                    <label for="descripcion">Descripción del entrenamiento</label>
                    <textarea name="descripcion" id="descripcion" class="form-control">{{$entrenamiento->descripcion}}</textarea>
                </div>

                <div class="row">
                    <label for="urlImagen">Imagen del entrenamiento</label>
                    <input name="urlImagen" id="urlImagen" class="form-control" value="{{$entrenamiento->url_img}}" />
                </div>

                <div class="row mt-4">
                    <button type="submit" class="mb-3 btn btn-warning">Editar entrenamiento</button>
                </div>
            </form>

            <form action="{{url('/trainer/entrenamientos', $entrenamiento->id)}}" method="POST" class="form-group">
                <div class="row">
                    @csrf
                    {{ method_field('DELETE') }}
                    <button type="submit" class="mb-3 btn btn-danger">Eliminar</button>
                </div>
            </form>
        </div>

        <div class="row mt-4">
            @include('common.alert')
        </div>

        <div class="row">
            <h2 class="mt-4">Añadir un ejercicio</h2>
            <form action="{{route('entrenamiento.addEjercicio', $entrenamiento->id)}}" method="POST" class="container">
                @csrf
                <div class="row">
                    <select name="grupo" class="form-select">
                        <option disabled selected> Ejercicios </option>
                        @foreach($ejercicios as $ejercicio)
                        <option value="{{$ejercicio->id}}">{{$ejercicio->name}}</option>
                        @endforeach
                    </select>
                    <button type="submit" class="btn btn-success col-md-3 mt-2">Añadir Ejercicio</button>
                </div>
            </form>
        </div>
        @else
        <div class="container col-md-4">
            <p class="h4">Seguidores: {{$entrenamiento->seguidores}}</p>
            <p class="h2">{{$entrenamiento->descripcion}}</p>
        </div>
        @endif

    </div>


    @if(!auth::guest() && auth::user()->id == $entrenamiento->creator_id)
    <div class="row">
        <h2 class="mt-4">Ejercicios del entrenamiento</h2>
        <div class="table-responsive">
            <table class="table">
                <thead>
                    <tr>
                        <th scope="col">Nombre</th>
                        <th scope="col">Descripción</th>
                        <th scope="col">Eliminar</th>
                    </tr>
                </thead>
                <tbody>
                    @foreach($entrenamiento->ejercicios as $ejercicio)
                    <tr>
                        <td>{{$ejercicio->name }}</td>
                        <td>{{$ejercicio->descripcion }}</td>
                        <td>
                            <form action="{{route('entrenamiento.disociateEjercicio', ['id' =>  $entrenamiento->id , 'idEjercicio' =>  $ejercicio->id ])}}" method="POST">
                                @csrf
                                {{ method_field('POST') }}
                                <button class="btn btn-danger" type="submit">Quitar</button>
                            </form>
                        </td>
                    </tr>
                    @endforeach
                </tbody>
            </table>
        </div>
    </div>
    @else
    <div class="row">
        <h2 class="mt-4">Ejercicios del entrenamiento</h2>
        <div class="table-responsive">
            <table class="table">
                <thead>
                    <tr>
                        <th scope="col">Nombre</th>
                        <th scope="col">Descripción</th>
                    </tr>
                </thead>
                <tbody>
                    @foreach($entrenamiento->ejercicios as $ejercicio)
                    <tr>
                        <td><a href="/ejercicios/{{$ejercicio->id}}" style="color: inherit; text-decoration: inherit;"> {{$ejercicio->name }}</a></td>
                        <td>{{$ejercicio->descripcion }}</td>
                    </tr>
                    @endforeach
                </tbody>
            </table>
        </div>
    </div>
    @endif



    @if(auth::user()->id != $entrenamiento->creator_id)
    <div class="row container">
        <div class="row">
            @if(auth::user()->entrenamientos->contains($entrenamiento->id))
            <form action="{{url('/entrenamientos', $entrenamiento->id)}}" method="POST" class="col w-100">
                @csrf
                {{ method_field('PUT') }}
                <button type="submit" class="btn btn-danger">Dejar de seguir Entrenamiento</button>
            </form>
            @else

            <form action="{{url('/entrenamientos', $entrenamiento->id)}}" method="POST" class="col w-100">
                @csrf
                {{ method_field('POST') }}
                <button type="submit" class="btn btn-success">Seguir Entrenamiento</button>
            </form>
            @endif
        </div>
    </div>
    @endif


</div>
@endsection