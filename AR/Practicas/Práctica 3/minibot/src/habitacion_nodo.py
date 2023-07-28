#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

class Habitacion:
    def __init__(self):
        self.largo = 0
        self.ancho = 0
        self.pos_x = 0
        self.pos_y = 0
        self.distancias = []
        self.giros = 0

    def distancia_callback(self, data):
        if data.data == -1:
            self.giros += 1
            if self.giros == 4:
                self.calcular_habitacion()
        else:
            self.distancias.append(data.data)

    def calcular_habitacion(self):
        self.largo = sum(self.distancias[:-1])
        self.ancho = self.distancias[-1]
        self.pos_x = self.largo / 2
        self.pos_y = self.ancho / 2
        self.distancias = []
        self.giros = 0
        print("Largo:", self.largo)
        print("Ancho:", self.ancho)
        print("Superficie:", self.largo * self.ancho)
        print("Posición X:", self.pos_x)
        print("Posición Y:", self.pos_y)

def habitacion_nodo():
    hab = Habitacion()
    rospy.init_node('habitacion_nodo', anonymous=True)
    rospy.Subscriber('distancia', Int32, hab.distancia_callback)
    rospy.spin()

if __name__ == '__main__':
    habitacion_nodo()
