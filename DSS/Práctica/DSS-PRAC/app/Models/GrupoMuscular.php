<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class GrupoMuscular extends Model
{
    use HasFactory;

    protected $table = 'grupo_musculars';

    public $timestamps = false;
    
    public function musculos()
    {
        return $this->hasMany(Musculo::class);
    }

    public function ejercicios()
    {
        return $this->belongsToMany(Ejercicio::class);
    }
}
