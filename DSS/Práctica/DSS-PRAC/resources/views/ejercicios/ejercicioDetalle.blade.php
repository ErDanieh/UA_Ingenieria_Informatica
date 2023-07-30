@extends('layouts.admin')

@section('content')


<div class=" d-flex justify-content-between ">
    <h1>Editar ejercicio</h1>
    <a href={{ URL::previous() }} class="btn btn-primary" style="height: min-content; font-size: 1.2rem;"> Atras </a>
</div>
<h3>Nombre: {{$ejercicio->name}}</h3>
<h3>Descripción: {{$ejercicio->descripcion}}</h3>
<img src="{{$ejercicio->url_img}}" style="height: 300px; width: 250px; object-fit:cover; border-radius: 10px;" />
@include('common.alert')
<div class="">
    <form action="{{ url('/admin/ejercicios',$ejercicio->id)}}" method="POST">
        @csrf
        {{ method_field('PUT') }}
        <div class="form-group">
            <label for="name">Nombre del ejercicio</label>
            <input class="form-control" type="text" name="name" id="name" value="{{$ejercicio->name}}">
        </div>
        <div class="form-group">
            <label for="descripcion">Descripción del ejercicio</label>
            <textarea class="form-control" type="text" name="descripcion" id="descripcion">{{$ejercicio->descripcion}}</textarea>
        </div>
        <div class="form-group">

            <label for="urlImagen">Imagen del ejercicio</label>
            <input class="form-control" type="text" name="urlImagen" id="urlImagen" value="{{$ejercicio->url_img}}"></textarea>
        </div>
        <button class="btn btn-primary" type="submit" style="margin-top: 20px;">Editar ejercicio</button>
    </form>
</div>

@endsection