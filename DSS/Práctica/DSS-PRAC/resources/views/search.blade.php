@extends('home')

@section('content')


<div class="container min-vh-100 px-1 mb-5">
    <h1 class="mt-4">Pagina de busqueda</h1>
    @if($data['entrenamientos']->isEmpty() && $data['ejercicios']->isEmpty() && $data['entrenadores']->isEmpty())

    <div class="container">
        <span>Lo siento... No hemos encontrado ningun resultado para tu busqueda.</span>
    </div>

    @endif

    @if(!$data['entrenamientos']->isEmpty())
    <h2 class="mt-3">Entrenamientos: </h2>
    <div class="row justify-content-around">
        @foreach($data['entrenamientos'] as $entrenamiento)
        <div class="col-md-5 card mt-4 mx-0" style="padding: 0; margin-bottom: 0;">
            <img class="card-img-top" style="height: 20vw; object-fit: cover; width: auto;" src="{{$entrenamiento->url_img}}">
            <div class="card-body">
                <h5 class="card-title">{{$entrenamiento->name}}</h5>
                <p class="card-text">
                    {{$entrenamiento->descripcion}}
                </p>
                <a href="/entrenamientos/{{$entrenamiento->id}}" class="btn btn-primary">Más información</a>
            </div>
        </div>
        @endforeach
    </div>
    @endif

    @if(!$data['ejercicios']->isEmpty())
    <h2 class="mt-3">Ejercicios: </h2>
    <div class="row justify-content-around">
        @foreach($data['ejercicios'] as $ejercicio)
        <div class="col-md-5 card mt-4 mx-0" style="padding: 0; margin-bottom: 0;">
            <img class="card-img-top" style="height: 20vw; object-fit: cover; width: auto;" src="{{$ejercicio->url_img}}">
            <div class="card-body">
                <h5 class="card-title">{{$ejercicio->name}}</h5>
                <p class="card-text">
                    {{$ejercicio->descripcion}}
                </p>
                <a href="/ejercicios/{{$ejercicio->id}}" class="btn btn-primary">Más información</a>
            </div>
        </div>
        @endforeach
    </div>
    @endif

    @if(!$data['entrenadores']->isEmpty())
    <h2 class="mt-3">Entrenadores: </h2>
    <div class="row justify-content-around">
        @foreach($data['entrenadores'] as $entrenador)
        <div class="col-md-5 card mt-4 mx-0" style="padding: 0; margin-bottom: 0;">
            <img class="card-img-top" style="height: 20vw; object-fit: cover; width: auto;" src="{{$entrenador->picture}}">
            <div class="card-body">
                <h5 class="card-title">{{$entrenador->name}}</h5>
                <a href="/entrenadores/{{$entrenador->id}}" class="btn btn-primary">Más información</a>
            </div>
        </div>
        @endforeach
    </div>
    @endif
</div>

@endsection