@extends('layouts.admin')


@section('content')

<!--Metodo para mostrar los perfiles una vez clickado el usuario -->
<!--if is admin extiende a layouts.admon sino extiende a layout.general-->
<script src="../js/users.js"> </script>

<div>

    <h1>Usuarios</h1>

    @include('common.alert')

    <h2>Listado de usuarios</h2>

    <script src="../js/utils.js"> </script>
    {{-- Buscador --}}
    <input type="text" class="form-control" name="search" id="search" autofocus onchange="redirectSearch()" placeholder="Busqueda por nombre y correo electronico."></input>


    {{-- Listado de usuarios --}}
    <div class="table-responsive">
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">Nombre</th>
                    <th scope="col">Email</th>
                    <th scope="col">Administrador</th>
                    <th scope="col">Entrenador</th>
                    <th scope="col">Editar</th>
                    <th scope="col">Eliminar</th>
                </tr>
            </thead>

            <tbody class="align-middle">
                @foreach($users as $user)
                <tr>
                    <td onclick="showProfile({{$user->id}})">{{$user->name}}</td>
                    <td onclick="showProfile({{$user->id}})">{{$user->email}}</td>
                    @if($user->is_admin == '1')
                    <td>X</td>
                    @else
                    <td></td>
                    @endif
                    @if($user->is_trainer == '1')
                    <td>X</td>
                    @else
                    <td></td>
                    @endif
                    <td>
                        <button class="btn btn-success" type="submit" onclick="showProfile({{$user->id}})">Editar</button>
                    </td>
                    <td>
                        <form action="{{url('/admin/usuarios', $user->id)}}" class="mr-4" method="POST">
                            @csrf
                            {{ method_field('DELETE') }}
                            <button class="btn btn-danger m-3" type="submit">Eliminar</button>
                        </form>
                    </td>
                </tr>
                @endforeach
            </tbody>


    </div>


    {{-- Paginacion --}}
    <div class="text-center d-flex justify-content-center m-5">
        @if(request()->search!=null)
        {{ $users->appends(['search'=>request()->search])->links() }}
        @else
        {{ $users->links() }}
        @endif
    </div>


</div>

@endsection