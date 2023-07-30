@extends('layouts.admin')


@section('content')

<div>
    <div class=" d-flex justify-content-between ">
        <h1>Editar usuario.</h1>
        <a href={{ URL::previous() }} class="btn btn-primary" style="height: min-content; font-size: 1.2rem;"> Atras </a>
    </div>
    <h3>Nombre: {{$user->name}}</h3>
    <h3>Email: {{$user->email}}</h3>

    @if($user->is_admin)
    <h3>Administrador</h3>
    @endif

    @if($user->is_trainer)
    <h3>Entrenador</h3>
    @endif

    @include('common.alert')

    <div class="" style="margin-top: 20px;">
        <form action="{{ url('/admin/usuarios',$user->id)}}" method="POST">
            @csrf
            {{ method_field('PUT') }}
            <div class="form-group">
                <label for="name">Nuevo nombre de usuario</label>
                <input class="form-control" type="text" name="name" id="name">
            </div>

            <div class="form-group">
                <label for="email">Nuevo email</label>
                <input class="form-control" type="email" name="email" id="email"></textarea>
            </div>

            <div class="form-group">
                <label for="password">Nueva contraseña</label>
                <input class="form-control" type="password" name="password" id="password"></textarea>
            </div>

            <div>
                @if($user->is_admin)
                <label for="beAdmin">Quitar rol de administrador</label>
                <input type="checkbox" name="beAdmin" id="beAdmin" value="0" checked>
                @else
                <label for="beAdmin">Atribuir rol de administrador</label>
                <input type="checkbox" name="beAdmin" id="beAdmin" value="1">
                @endif
            </div>
            <div>
                @if($user->is_trainer)
                <label for="beTrainer">Quitar rol de entrenador</label>
                <input type="checkbox" name="beTrainer" id="beTrainer" value="0" checked>
                @else
                <label for="beTrainer">Atribuir rol de entrenador</label>
                <input type="checkbox" name="beTrainer" id="beTrainer" value="1">
                @endif
            </div>
            <button class="btn btn-primary" type="submit" style="margin-top: 20px;" name="submit">Editar usuario</button>
        </form>


    </div>
</div>
@endsection