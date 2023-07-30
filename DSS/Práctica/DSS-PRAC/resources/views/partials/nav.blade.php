<script src="/js/utils.js"> </script>
<header class="p-3 mb-3 border-bottom">
  <div class="container">
    <div class="d-flex flex-wrap align-items-center justify-content-center justify-content-lg-start">
      <a href="/" class="d-flex align-items-center mb-2 mb-lg-0 text-dark text-decoration-none">
        <svg class="bi me-2" width="40" height="32" role="img" aria-label="Bootstrap">
          <use xlink:href="#bootstrap" />
        </svg>
      </a>

      <ul class="nav col-12 col-lg-auto me-lg-auto mb-2 justify-content-center mb-md-0">
        <li><a href="/" class="nav-link px-2 link-secondary">Inicio</a></li>
        <li><a href="/entrenamientos" class="nav-link px-2 link-dark"> Entrenamientos</a></li>
        <li><a href="/ejercicios" class="nav-link px-2 link-dark">Ejercicios</a></li>
        <li><a href="/entrenadores" class="nav-link px-2 link-dark">Entrenadores</a></li>
        <li><a href="/sobreNosotros" class="nav-link px-2 link-dark">¿Qué es UAFit?</a></li>
      

        @if (!Auth::guest())
        @if (Auth::user()->is_admin == '1')
        <li><a href="/admin" class="nav-link px-2 link-dark">Administrar</a></li>
        @endif
        @if(Auth::user()->is_trainer == '1')
        <li><a href="/trainer" class="nav-link px-2 link-secondary">Zona Trainer</a></li>
        @endif
        @endif


      </ul>

      <div class="col-12 col-lg-auto mb-3 mb-lg-0 me-lg-3">
        <input id="search" type="search" class="form-control disabled" placeholder="Buscar..." aria-label="Search" onchange="buscadorHome()">
      </div>


      @if (Auth::guest())
      <div>
        <a type="button" class="btn btn-primary" href="login">Login</a>
        <a type="button" class="btn btn-primary" href="register">Registrarse</a>
      </div>
      @else
      <div class="dropdown text-end">
        <a href="#" class="d-block link-dark text-decoration-none dropdown-toggle" id="dropdownUser1" data-bs-toggle="dropdown" aria-expanded="false">
          <img src={{Auth::user()->picture}} alt="mdo" width="32" height="32" class="rounded-circle">
        </a>
        <ul class="dropdown-menu text-small" aria-labelledby="dropdownUser1" style="cursor: pointer;">
          <li><a class="dropdown-item" href="/perfil">Perfil</a></li>
          <li>
            <hr class="dropdown-divider">
          </li>
          <li><a class="dropdown-item" onclick="event.preventDefault();document.getElementById('logout-form').submit();">Cerrar sesión</a></li>
          <form id="logout-form" action="{{ route('logout') }}" method="POST" style="display: none;">
            {{ csrf_field() }}
          </form>
        </ul>
      </div>
      @endif



    </div>
  </div>
</header>