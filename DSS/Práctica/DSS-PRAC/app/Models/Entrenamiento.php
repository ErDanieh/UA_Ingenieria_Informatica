<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Entrenamiento extends Model
{
    use HasFactory;

    protected $table = 'entrenamientos';

    public $timestamps = false;


    public function usuarios()
    {
        return $this->belongsToMany('App\Models\User');
    }

    public function ejercicios()
    {
        return $this->belongsToMany('App\Models\Ejercicio');
    }

}
