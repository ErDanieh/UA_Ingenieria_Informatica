<?php

namespace App\Http\Controllers;
use Illuminate\Http\Request;
use Symfony\Component\Console\Input\Input;
use DB;

class SobreNosotrosController extends Controller
{
function getSobreNosotros() 
    {
        return view('sobreNosotros');
    }
}