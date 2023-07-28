#Lamport algorithm 4 threads

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

def thread3():
    global turn
    global flag
    global counter
    while True:
        flag[2] = True
        turn = 0
        while flag[0] and turn == 0:
            pass
        #critical section
        counter += 1
        print("Thread 3: ", counter)
        flag[2] = False
        time.sleep(1)

def thread4():
    global turn
    global flag
    global counter
    while True:
        flag[3] = True
        turn = 0
        while flag[0] and turn == 0:
            pass
        #critical section
        counter += 1
        print("Thread 4: ", counter)
        flag[3] = False
        time.sleep(1)

if __name__ == "__main__":
    counter = 0
    flag = [False, False, False, False]
    turn = 0
    t1 = threading.Thread(target=thread1)
    t2 = threading.Thread(target=thread2)
    t3 = threading.Thread(target=thread3)
    t4 = threading.Thread(target=thread4)
    t1.start()
    t2.start()
    t3.start()
    t4.start()

##Output
##
##Thread 1:  1
##Thread 2:  2
##Thread 3:  3
##Thread 4:  4
##Thread 1:  5
##Thread 2:  6
##Thread 3:  7
##Thread 4:  8
##Thread 1:  9