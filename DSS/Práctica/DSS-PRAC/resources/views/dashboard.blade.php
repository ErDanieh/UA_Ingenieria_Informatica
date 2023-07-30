@extends('layouts.admin')

@section('content')
<div id="carouselExampleIndicators" class="carousel slide" data-ride="carousel">
  <ol class="carousel-indicators">
    <li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
  </ol>
  <div class="carousel-inner" style="height: 95vh;">
    <div class="carousel-item active" style="height: inherit; object-fit: cover; background-image:  URL('images/cover-image.jpg'); background-position: center;" >
      <a href="/login" class="btn btn-warning">ADMINISTRADOR</a>

    </div>
  </div>
</div>
@endsection