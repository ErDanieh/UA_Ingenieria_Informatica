<?php

namespace App\Mail;

use Illuminate\Bus\Queueable;
use Illuminate\Contracts\Queue\ShouldQueue;
use Illuminate\Mail\Mailable;
use Illuminate\Queue\SerializesModels;
use App\Models\User;

class contactar extends Mailable
{
    use Queueable, SerializesModels;
    public $usuario;
    public $mensaje;
    public function __construct(User $usuario, String $mensaje)
    {
        $this->usuario = $usuario;
        $this->mensaje = $mensaje;
    }

    /**
     * Build the message.
     *
     * @return $this
     */
    public function build()
    {
        return $this->view('mails.contact')->with('mensaje',$this->mensaje);
    }
}
