@extends('layouts.principal')

@section('content')

<header class="masthead" style="overflow: hidden;">
  <div class="container px-5">
    <div class="row gx-5 align-items-center">
      <div class="col-lg-6">
        <!-- Mashead text and app badges-->
        <div class="mb-5 mb-lg-0 text-center text-lg-start">
          <h1 class="display-1 lh-1 mb-3">La aplicación para ponerte en forma.</h1>
          <p class="lead fw-normal text-muted mb-5">Una aplicación accesible e intuitiva para no perder el ritmo!</p>
        </div>
      </div>
      <div class="col-lg-4">
        <!-- Masthead device mockup feature-->
        <img src="images/studio-display-mockup-template.png" alt="..." style="height: 50rem; " />
      </div>
    </div>
  </div>
</header>

<aside class="text-center" style="background: linear-gradient(45deg, #2937f0, #9f1ae2) !important; padding: 40px;">
  <div class="container px-5">
    <div class="row gx-5 justify-content-center">
      <div class="col-xl-8">
        <div class="h2 fs-1 text-white mb-4">" Una solución intuitiva y práctica para cualquier persona que quiera llevar su entrenamiento a otro nivel "</div>
        <img src="images/elpais_logo.png" alt="..." style="height: 2.4rem; filter: brightness(0) invert(1);" />
      </div>
    </div>
  </div>
</aside>

<section id="features" style="padding: 50px; overflow: hidden;">
  <div class="container px-5">
    <div class="row gx-5 align-items-center">
      <div class="col-lg-8 order-lg-1 mb-5 mb-lg-0">
        <div class="container-fluid px-5">
          <div class="row gx-5">
            <div class="col-md-6 mb-5">
              <!-- Feature item-->
              <div class="text-center">
                <i class="bi bi-compass mb-3 fa-2x"></i>
                <h3 class="font-alt">Descubre</h3>
                <p class="text-muted mb-0">Descubre los mejores entrenamientos!</p>
              </div>
            </div>
            <div class="col-md-6 mb-5">
              <!-- Feature item-->
              <div class="text-center">
                <i class="bi-patch-check mb-3 fa-2x"></i>
                <h3 class="font-alt">Entrenadores</h3>
                <p class="text-muted mb-0">Busca entre los mejores entrenadores</p>
              </div>
            </div>
          </div>
          <div class="row">
            <div class="col-md-6 mb-5 mb-md-0">
              <!-- Feature item-->
              <div class="text-center">
                <i class="bi bi-graph-up mb-3 fa-2x"></i>
                <h3 class="font-alt">Progresa</h3>
                <p class="text-muted mb-0">Monitoriza tus avanzes!</p>
              </div>
            </div>
            <div class="col-md-6">
              <!-- Feature item-->
              <div class="text-center">
                <i class="bi bi-share mb-3 fa-2x"></i>
                <h3 class="font-alt">Comparte</h3>
                <p class="text-muted mb-0">Comparte tus resultados en tus redes sociales!</p>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="col-lg-4 order-lg-0">
        <img src="images/iphone-cover-image.png" alt="..." style="height: 30rem;" />
      </div>
    </div>
  </div>
</section>

@endsection