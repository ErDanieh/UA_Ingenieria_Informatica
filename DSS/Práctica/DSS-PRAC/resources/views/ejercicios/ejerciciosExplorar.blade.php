@extends('home')


@section('content')
<script src="../js/utils.js"> </script>

<div class="container min-vh-100 px-1 mb-5">

    <h1 class="mt-4">Pagina de ejercicios</h1>
    <div class="row justify-content-around">
        @foreach($ejercicios as $ejercicio)
        <div class="col-md-5 card mt-4 mx-4" style="padding: 0;">
            <img class="card-img-top" style="height: 15vw; object-fit: cover; width: auto;" src="{{$ejercicio->url_img}}" alt="Card image cap">
            <div class="card-body">
                <h5 class="card-title">{{$ejercicio->name}}</h5>
                <p class="card-text">{{Str::limit($ejercicio->descripcion, 50)}}</p>
                <a href="/ejercicios/{{$ejercicio->id}}" class="btn btn-primary">Más información</a>
            </div>

        </div>
        @endforeach
    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $ejercicios->links() }}
    </div>
</div>
@endsection