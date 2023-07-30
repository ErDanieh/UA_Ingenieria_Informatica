@extends('home')
@section('content')

<!--Se mostrarán todos los entrenamientos que haya creado un entrenador!-->
<div class="container min-vh-100">
    @include('common.alert')

    <h1>Trainer Zone</h1>

    <div class="" style="margin: 50px auto;">
        <h2>Añadir un entrenamiento nuevo</h2>
        <form action="{{ url('/trainer')}}" method="POST">
            @csrf
            <div class="form-group">
                <label for="name">Nombre entrenamiento</label>
                <input class="form-control" placeholder="Nombre del entrenamiento..." required type="text" name="name" id="name">
            </div>

            <div class="form-group">
                <label for="descripcion">Descripción del entrenamiento</label>
                <input class="form-control" placeholder="Descripción del entrenamiento..." required type="text" name="descripcion" id="descripcion">
            </div>

            <div class="form-group">
                <label for="urlImagen">Imagen del entrenamiento</label>
                <input class="form-control" placeholder="URL de la imagen..." required type="text" name="urlImagen" id="urlImagen">
            </div>
            <button class="btn btn-success mt-4" type="submit" >
                Añadir entrenamiento
            </button>
        </form>
    </div>

    <div class="" style="margin: 50px auto;">
        <h2>Crear un ejercicio nuevo</h2>
        <form action="{{ url('/trainer/ejercicioCreation') }}" method="POST">
            @csrf
            <div class="form-group">
                <label for="name">Ejercicio</label>
                <input class="form-control" placeholder="Nombre del ejercicio..." required type="text" name="name" id="name">
            </div>
            <div class="form-group">
                <label for="descripcion">Descripción del ejercicio</label>
                <input class="form-control" placeholder="Descripción del ejercicio..." required type="text" name="descripcion" id="descripcion">
            </div>
            <div class="form-group">
                <label for="urlImagen">Imagen del ejercicio</label>
                <input class="form-control" placeholder="URL de la imagen" required type="text" name="urlImagen" id="urlImagen">
            </div>
            <button class="btn btn-success mt-4" type="submit" onclick="alert('Recuerde que no podrá editar ni eliminar el ejercico una vez creado')">Añadir Ejercicio</button>
        </form>
    </div>
    <div class="row">
        @foreach($entrenamientos as $entrenamiento)
        @if($entrenamiento->creator_id == auth::user()->id)
        <div class="col card" style="margin: 10px; max-width: 46%;">
            <div class="card-body">
                <h5 class="card-title">{{$entrenamiento->name}}</h5>
                <p class="card-text">{{Str::limit($entrenamiento->descripcion, 50)}}</p>
                <a href="/entrenamientos/{{$entrenamiento->id}}" class="btn btn-primary">Más información</a>
            </div>

        </div>
        @endif
        @endforeach
    </div>

</div>

@endsection