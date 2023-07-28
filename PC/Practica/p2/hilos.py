import threading


THREADS = 5
MAX_COUNT = 50000
EXPECTED = 250000

counter = 0

def thread():
    #Contador globa
    global counter
    print(format(threading.current_thread().name))
    
    for i in range(MAX_COUNT):
        counter += 1

def main():
    #Vector para almacenar los hilos
    threads = []
    
    #Bucle para clear los hilos
    for i in range(THREADS):
    #Creamos un nuevo hilo y lo metemos al vector
        t = threading.Thread(target=thread)
        threads.append(t)

        #Comienza la ejecución del hilo
        t.start()
     

    #Espera a que todos los se terminen
    for t in threads:
        t.join()
        

    #Imprimimos los valores de los contadores de cada hilo    
    print("Valor del contador: {} Esperado: {}\n".format(counter, EXPECTED))
        
if __name__ == "__main__":
    main()