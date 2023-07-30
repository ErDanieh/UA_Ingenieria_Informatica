<?php

namespace App\Models;

use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;
use Laravel\Sanctum\HasApiTokens;
use Session;

class User extends Authenticatable
{
    use HasApiTokens, HasFactory, Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array<int, string>
     */
    protected $fillable = [
        'name',
        'email',
        'password',
        'is_trainer',
        'is_admin'
    ];

    /**
     * The attributes that should be hidden for serialization.
     *
     * @var array<int, string>
     */
    protected $hidden = [
        'password',
        'remember_token',

    ];

    /**
     * The attributes that should be cast.
     *
     * @var array<string, string>
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];


    public function entrenamientos()
    {
        return $this->belongsToMany('App\Models\Entrenamiento');
    }

    /** 
    static public function isLoggedIn() {
        if (Session::has('userid')){
            if (User::find(Session::get('userid')))
                return true;
            else {
                // Session is stuck, needs reflushing, this will happen only mid-debugging, due to closing / serving the app.
                Session::flush();
                Session::regenerate();
            }
        }

        return false;
    }
    */
}
