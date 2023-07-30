@extends('layouts.admin')

@section('content')
<div class="container">

    <div class="row">
        <div class="card card-content card-body" style="width: 30%; min-width: min-content; margin: 10px; ">
            <div class="media d-flex justify-content-between align-items-center">
                <div class="media-body text-left">
                    <h3 class="success">
                        {{ App\Http\Controllers\AdministracionController::numUsers();}}
                    </h3>
                    <span>Usuarios</span>
                </div>
                <i class="fa-solid fa-user fa-4x justify-content-right" style="padding-bottom: -20px;"></i>
            </div>
        </div>

        <div class="card card-content card-body" style="width: 30%; min-width: min-content; margin: 10px; ">
            <div class="media d-flex justify-content-between align-items-center">
                <div class="media-body text-left">
                    <h3 class="success">
                        {{ App\Http\Controllers\AdministracionController::numEntrenadores();}}
                    </h3>
                    <span>Entrenadores</span>
                </div>
                <i class="fa-solid fa-id-card success fa-4x justify-content-right" style="padding-bottom: -20px;"></i>
            </div>
        </div>

    </div>

    <div class="row">

        <div class="card card-content card-body" style="width: 30%; min-width: min-content; margin: 10px; ">
            <div class="media d-flex justify-content-between align-items-center">
                <div class="media-body text-left">
                    <h3 class="success">
                        {{ App\Http\Controllers\AdministracionController::numEntrenamientos();}}
                    </h3>
                    <span>Entrenamientos</span>
                </div>
                <i class="fa-solid fa-bolt fa-4x justify-content-right" style="padding-bottom: -20px;"></i>
            </div>
        </div>
        <div class="card card-content card-body" style="width: 30%; min-width: min-content; margin: 10px;">
            <div class="media d-flex justify-content-between align-items-center">
                <div class="media-body text-left">
                    <h3 class="success">
                        {{ App\Http\Controllers\AdministracionController::numEjercicios();}}
                    </h3>
                    <span>Ejercicios</span>
                </div>
                <i class="fa-solid fa-dumbbell success fa-4x justify-content-right" style="padding-bottom: -20px;"></i>
            </div>
        </div>
    </div>
</div>
@endsection