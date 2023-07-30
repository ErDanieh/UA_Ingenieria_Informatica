@extends('home')

@section('content')
<div style="width: 900px; margin: auto; margin-bottom: 35vh;">
    <h1>Perfil del entrenador</h1>

    <div style="margin-top: 50px; display: flex; flex-direction: row; justify-content: space-between;">
        <img src={{$user->picture}} style="height: 300px; width: 250px; object-fit:cover; border-radius: 10px;" />

        <div style="display: flex; flex-direction: column; margin-right: min(100px); justify-content: center;">
            <label>Email de contacto:</label>
            <h3>{{$user->email}}</h3>
            <label>Nombre del entrenador:</label>
            <h3>{{$user->name}}</h3>
            <label>Se unio:</label>
            <h3>{{$user->created_at}}</h3>
        </div>

    </div>

    <form action="{{url('/entrenadores', $user->id)}}" class="mr-4" method="POST">
        @csrf
        {{ method_field('POST') }}
        <input class="form-control" placeholder="Escriba aqui el mensaje..." required type="text" name="mensaje" id="mensaje">
        <button class="btn btn-danger m-3" type="submit">Enviar</button>
    </form>

    @include('common.alert')


</div>
@endsection