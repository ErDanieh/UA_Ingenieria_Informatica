public class ThreadConHerencia extends Thread{
    String palabra;
    int veces = 10;
    
    public ThreadConHerencia(String palabra){
        this.palabra = palabra;
    }

    public void run(){
        for(int i = 0; i < veces; i++){
            System.out.println(palabra);
        }
    }

    public static void main(String[] args){
        ThreadConHerencia hilo1 = new ThreadConHerencia("Hilo1");
        ThreadConHerencia hilo2 = new ThreadConHerencia("Hilo2");
        hilo1.start();
        hilo2.start();
    }

}