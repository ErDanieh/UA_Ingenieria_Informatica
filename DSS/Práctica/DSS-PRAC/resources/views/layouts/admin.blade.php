<!doctype html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">

<head>
   @include('partials.head')
   <title>UAFit - Administración</title>
</head>

@section('title', 'Page Title')
<body>
   <div class="container-fluid">
      <div class="row flex-nowrap">
         <!-- Nav -->
         @include('partials.sidebar')

         <div class="content" style="width: 1100px; margin: auto; margin-left: 25%; margin-top: 5vh;">
            <!-- Contenido -->
            @yield('content')
         </div>
      </div>


   </div>


</body>