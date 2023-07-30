@extends('home')

@section('content')
<div class="container min-vh-100">


    <h1>{{$ejercicio->name}}</h1>
    <div class="row">
        <img src="{{$ejercicio->url_img}}" class="col-md-7 rounded" style="object-fit: cover;" />
        <p class="col-md-4 h3 mt-2">{{$ejercicio->descripcion}}</p>
    </div>


    <h2 class="mt-4">Puedes encontrar este ejercicio en:</h2>
    <div class="container">
        <div class="row">
            @foreach($ejercicio->entrenamientos as $entrenamiento)
            <div class="col-md-3">
                <a href="/entrenamientos/{{$entrenamiento->id}}" style="color: inherit; text-decoration: inherit;">
                    <div class="card">
                        <div class="card-body">
                            <h4 class="card-title">{{$entrenamiento->name}}</h4>
                            <p class="card-text">{{Str::limit($entrenamiento->descripcion, 50)}}</p>
                        </div>
                    </div>
                </a>
            </div>
            @endforeach
        </div>
    </div>

</div>

@endsection