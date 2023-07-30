@extends('home')

@section('content')
<script src="../js/utils.js"> </script>

<style type="text/css">
.card-img-top{
    transition: transform .6s ease; /* Animation */
}
.card-img-top:hover {
    transform: scale(1.5);
    transition: transform .6s ease;
}
.img-container{
    overflow: hidden; /* [1.2] Hide the overflowing of child elements */
}
</style>

<div class="container min-vh-100 px-1 mb-5">

    <h1 class="mt-4">Pagina de explorar</h1>
    <div class="row justify-content-around">
        @foreach($entrenamientos as $entrenamiento)
        <div class="card col-md-5 card mt-4 mx-4" style="padding: 0; ">
            <div class="img-container">
                <img class="card-img-top" style="height: 15vw; object-fit: cover; " src="{{$entrenamiento->url_img}}" alt="Card image cap">
            </div>
            <div class="card-body">
                <h5 class="card-title">{{$entrenamiento->name}}</h5>
                <p class="card-text">{{Str::limit($entrenamiento->descripcion, 50)}}</p>
                <a href="/entrenamientos/{{$entrenamiento->id}}" class="btn btn-primary">Más información</a>
            </div>

        </div>
        @endforeach
    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $entrenamientos->links() }}
    </div>
</div>
@endsection