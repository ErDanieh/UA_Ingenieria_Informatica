#Petersonm algorithm

import threading
import time

def thread1():
    global turn
    global flag
    global counter
    while True:
        flag[0] = True
        turn = 1
        while flag[1] and turn == 1:
            pass
        #critical section
        counter += 1
        print("Thread 1: ", counter)
        flag[0] = False
        time.sleep(1)

def thread2():
    global turn
    global flag
    global counter
    while True:
        flag[1] = True
        turn = 0
        while flag[0] and turn == 0:
            pass
        #critical section
        counter += 1
        print("Thread 2: ", counter)
        flag[1] = False
        time.sleep(1)

if __name__ == "__main__":
    counter = 0
    flag = [False, False]
    turn = 0
    t1 = threading.Thread(target=thread1)
    t2 = threading.Thread(target=thread2)
    t1.start()
    t2.start()

##Output
##
##Thread 1:  1
##Thread 2:  2
##Thread 1:  3
##Thread 2:  4
##Thread 1:  5
##Thread 2:  6
##Thread 1:  7
##Thread 2:  8

