#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

def distancia_nodo():
    pub = rospy.Publisher('distancia', Int32, queue_size=10)
    rospy.init_node('distancia_nodo', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    distancia = 0
    girando = False
    while not rospy.is_shutdown():
        if not girando:
            # Leer distancia del sensor aquí
            distancia += 1
            if distancia >= 10:
                girando = True
                distancia = 0
        else:
            # Simular giro aquí
            distancia = -1
            girando = False
        
        if distancia == -1:
            msg = "El robot está girando"
        else:
            msg = f"Distancia a la pared: {distancia}"
        pub.publish(distancia)
        rate.sleep()

if __name__ == '__main__':
    try:
        distancia_nodo()
    except rospy.ROSInterruptException:
        pass
