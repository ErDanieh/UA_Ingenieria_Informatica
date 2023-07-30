<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Musculo extends Model
{
    use HasFactory;

    protected $table = 'musculos';

    public $timestamps = false;

    public function grupoMuscular()
    {
        return $this->belongsTo(GrupoMuscular::class);
    }

}
