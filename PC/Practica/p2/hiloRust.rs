use std::thread;
use std::sync::{Mutex,Arc};

fn main(){
    //Valores esperados para el computo final
    let expected = 250000;
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for i in 0..5 {
        let counter = counter.clone();
        let handle = thread::spawn(move || {

            //Necesitamos hacer un lock para acceder a los datos
            let mut num = counter.lock().unwrap(); 
            for _ in 0..50000 {
                *num += 1;
            }
            println!("Hilo {}: Contador: {}", i, *num);
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }
    println!();
    println!("Valor contador: {}\nEsperado: {}", *counter.lock().unwrap(), expected);
}