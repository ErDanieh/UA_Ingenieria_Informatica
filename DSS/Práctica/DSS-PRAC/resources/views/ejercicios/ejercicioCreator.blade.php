@extends('home')

@section('content')

<h1>Creador de ejercicios</h1>
<div class="" style="margin: 50px auto;">
    <h2>Añadir ejercicio</h2>
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
        <button class="btn btn-primary" type="submit" style="margin-top: 20px; font-size: 1.2rem;" onclick="alert('Recuerde que no podrá editar ni eliminar el ejercico una vez creado')">Añadir Ejercicio</button>
    </form>
</div>

@include('common.alert')
@endsection