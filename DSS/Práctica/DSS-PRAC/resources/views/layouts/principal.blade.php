<!doctype html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">


<head>
   @include('partials.head')
   <title>UAFit</title>
</head>

<body>
   <!-- Nav -->
   @include('partials.nav')
   <!-- Contenido -->
   @yield('content')

   <!-- Footer -->
   @include('partials.footer')
</body>