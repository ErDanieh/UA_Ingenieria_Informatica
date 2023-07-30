<?php

use App\Http\Controllers\MusculosController;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\EjerciciosController;
use App\Http\Controllers\EntrenamientosController;
use App\Http\Controllers\UserController;
use App\Http\Controllers\GrupoMuscularController;
use App\Http\Controllers\HomeController;
use App\Http\Controllers\AdministracionController;
use App\Http\Controllers\ExplorarController;
use App\Http\Controllers\PerfilController;
use App\Http\Controllers\SearchController;
use App\Http\Controllers\TrainerController;
use App\Http\Controllers\PlanesController;
use App\Http\Controllers\SobreNosotrosController;
use App\Models\Ejercicio;
use App\Models\Musculo;


/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', [HomeController::class, 'getHome']); //Devuelve la vista del home



/**
 * Control de usuarios
 */
Route::get('/admin/usuarios/', [UserController::class, 'getUsers'])->middleware(['auth']); //Lista todos los usuarios
Route::get('/admin/usuarios/{id}', [UserController::class, 'getProfile'])->middleware(['auth']);
Route::delete('/admin/usuarios/{id}', [UserController::class, 'deleteUser'])->middleware(['auth']);
Route::put('/admin/usuarios/{id}', [UserController::class, 'editProfile'])->middleware(['auth']);


/**
 * Control de Musculos
 */
Route::get('/admin/musculos', [MusculosController::class, 'getMusculos'])->middleware(['auth']); //Lista todos los usuarios
//Route::post('/admin/musculos/search', [MusculosController::class, 'searchMusculo'])->middleware(['auth'])->name('musculo.search'); //Buscador de usuarios por nombre o email
Route::get('/admin/musculos/{id}', [MusculosController::class, 'getMusculoDetalle'])->middleware(['auth']);
Route::post('/admin/musculos', [MusculosController::class, 'newMusculo'])->middleware(['auth']);
Route::delete('/admin/musculos/{id}', [MusculosController::class, 'deleteMusculo'])->middleware(['auth']);
Route::put('/admin/musculos/{id}', [MusculosController::class, 'editMusculo'])->middleware(['auth']);
/** 
Route::get('/admin/musculos/{id}', function() { #Evitar excepcion al acceder a esta pagina
    return abort(404);
});
 */


/**
 * Control de Ejercicios
 */
Route::get('/admin/ejercicios', [EjerciciosController::class, 'getEjercicios'])->middleware(['auth']); //Lista todos los ejercicios
Route::post('/admin/ejercicios', [EjerciciosController::class, 'newEjercicios'])->middleware(['auth']); //Añade ejercicios
Route::delete('/admin/ejercicios/{id}', [EjerciciosController::class, 'deleteEjercicio'])->middleware(['auth']); //Elimina ejercicios
Route::get('/admin/ejercicios/{id}', [EjerciciosController::class, 'getEjercicioDetalle'])->middleware(['auth']); //Añade ejercicios
Route::put('/admin/ejercicios/{id}', [EjerciciosController::class, 'editEjercicio'])->middleware(['auth']);
//Route::post('/admin/ejercicios/search', [EjerciciosController::class, 'searchEjercicios'])->middleware(['auth'])->name('ejercicio.search');;//Buscar ejercicios nombre

/**
 * Control de gruposMusculares
 */
Route::get('/admin/gruposMusculares', [GrupoMuscularController::class, 'getGruposMusculares'])->middleware(['auth']); //Lista todos los grupos musculares
Route::post('/admin/gruposMusculares', [GrupoMuscularController::class, 'newGruposMusculares'])->middleware(['auth']);
Route::delete('/admin/gruposMusculares/{id}', [GrupoMuscularController::class, 'deleteGrupoMuscular'])->middleware(['auth']);
Route::get('/admin/gruposMusculares/{id}', [GrupoMuscularController::class, 'getGruposMuscularesDetalle'])->middleware(['auth']);
Route::put('/admin/gruposMusculares/{id}', [GrupoMuscularController::class, 'editGruposMusculares'])->middleware(['auth']);
Route::delete('/admin/gruposMusculares/delete/{id}', [GrupoMuscularController::class, 'editMusculosContiene'])->middleware(['auth']);
//Route::post('/admin/gruposMusculares/search', [GrupoMuscularController::class, 'searchGrupoMuscular'])->middleware(['auth'])->name('gruposMusculares.search');;//Buscar ejercicios nombre

/** 
Route::put('/admin/gruposMusculares/{id}', [GrupoMuscularController::class, 'editGruposMusculares'])->middleware(['auth']);
    return abort(404);
});
 */


/**
 * Control de Entrenamientos
 */
Route::get('/admin/entrenamientos', [EntrenamientosController::class, 'getEntrenamientos'])->middleware(['auth']); //Lista todos los entrenamientos
Route::post('/admin/entrenamientos', [EntrenamientosController::class, 'newEntrenamiento'])->middleware(['auth']);
Route::get('/admin/entrenamientos/{id}', [EntrenamientosController::class, 'getEntrenamientoDetalle'])->middleware(['auth']);
Route::delete('/admin/entrenamientos/{id}', [EntrenamientosController::class, 'deleteEntrenamiento'])->middleware(['auth']);
Route::put('/admin/entrenamientos/{id}', [EntrenamientosController::class, 'editEntrenamiento'])->middleware(['auth']);
Route::post('/admin/entrenamientos/{id}/ejercicio/{idEjercicio}/disociate', [EntrenamientosController::class, 'eliminarEjercicioDeEntrenamiento'])->middleware(['auth'])->name('entrenamiento.disociateEjercicio');
Route::post('/admin/entrenamientos/{id}/ejercicio/add', [EntrenamientosController::class, 'addEjercicioEntrenamiento'])->middleware(['auth'])->name('entrenamiento.addEjercicio');
//Route::get('/trainer/entrenamientos', [EntrenamientosController::class, 'getEntrenamientos'])->middleware(['auth']); //Lista todos los entrenamientos
//Route::post('/trainer/entrenamientos', [EntrenamientosController::class, 'newEntrenamiento'])->middleware(['auth']);

/**
 * Controlador del home
 */
Route::get('/home', [App\Http\Controllers\HomeController::class, 'getHome'])->middleware(['dbcheck'])->name('home');
Route::get('/entrenadores', [UserController::class, 'getEntrenadores']); //Lista todos los usuarios
Route::get('/entrenadores/{id}', [UserController::class, 'getEntrenadoresProfile'])->middleware('auth'); //Lista todos los usuarios
Route::post('/entrenadores/{id}', [TrainerController::class,'sendMail'])->middleware('auth');



Route::get('/trainer', [TrainerController::class, 'getTrainerAll'])->middleware('dbcheck')->middleware('auth');
Route::post('/trainer', [TrainerController::class, 'newEntrenamiento'])->middleware(['auth']);
Route::get('/trainer/entrenamientos/{id}', [TrainerController::class, 'getEntrenamientoDetalle'])->middleware(['auth']);
Route::put('/trainer/entrenamientos/{id}', [TrainerController::class, 'editEntrenamiento'])->middleware(['auth']);
Route::delete('/trainer/entrenamientos/{id}', [TrainerController::class, 'deleteEntrenamiento'])->middleware(['auth']);
Route::post('/trainer/entrenamientos/{id}/ejercicio/{idEjercicio}/disociate', [TrainerController::class, 'eliminarEjercicioDeEntrenamiento'])->middleware(['auth'])->name('entrenamiento.disociateEjercicio');
Route::post('/trainer/entrenamientos/{id}/ejercicio/add', [TrainerController::class, 'addEjercicioEntrenamiento'])->middleware(['auth'])->name('entrenamiento.addEjercicio');
Route::post('/trainer/ejercicioCreation', [EjerciciosController::class, 'newEjercicios'])->middleware('auth');




Route::get('/perfil', [PerfilController::class, 'getPerfil'])->middleware(['dbcheck'])->middleware(['auth'])->name('perfil');
Route::put('/perfil', [PerfilController::class, 'updateProfilePicture'])->middleware(['dbcheck'])->middleware(['auth']);
Route::delete('/perfil', [UserController::class, 'deleteUserFromProfile'])->middleware(['dbcheck'])->middleware(['auth']);

Route::get('/entrenamientos', [ExplorarController::class, 'getExplorar'])->middleware(['dbcheck']);

Route::get('/entrenamientos/{idEntrenamiento}', [EntrenamientosController::class, 'getInformacionEntrenamiento'])->middleware(['dbcheck'])->middleware('auth');
Route::post('/entrenamientos/{idEntrenamiento}', [EntrenamientosController::class, 'anadirAUsuario'])->middleware(['dbcheck']);
Route::put('/entrenamientos/{idEntrenamiento}', [EntrenamientosController::class, 'quitarAUsuario'])->middleware(['dbcheck']);

Route::get('/admin', [AdministracionController::class, 'getAdministracion'])->middleware(['dbcheck'])->middleware(['auth']); //Lista todos los entrenamientos

Route::get('/ejercicios', [EjerciciosController::class, 'getExplorarEjercicios'])->middleware(['dbcheck']);
Route::get('/ejercicios/{idEjercicio}', [EjerciciosController::class, 'getInformacionEjercicio'])->middleware(['dbcheck'])->middleware('auth');


Route::get('/search', [SearchController::class, 'getSearch'])->middleware(['dbcheck']);

Route::get('/planes', [PlanesController::class, 'getPlanes'])->middleware(['dbcheck']);

Route::get('/sobreNosotros', [SobreNosotrosController::class, 'getSobreNosotros'])->middleware(['dbcheck']);


Auth::routes();
