#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "chistes_nodo_publicador");
  ros::NodeHandle nh;
  ros::Publisher chiste_pub = nh.advertise<std_msgs::String>("chistes", 10);
  ros::Rate loop_rate(1); // 1 mensaje por segundo

  std::vector<std::string> chistes = {
    "¿Por qué no se puede confiar en átomos? ¡Porque hacen cosas a tus espaldas!",
    "¿Cuál es el objeto más complejo del universo? La escoba, porque barre estrellas.",
    "¿Qué hace una abeja en el gimnasio? ¡Zum-ba!",
    "¿Qué hace un pez en el mar? Nada.",
    "¿Qué pasa cuando dos burros escuchan música? Una burrada de sonidos."
  };

  srand(time(NULL));

  while (ros::ok())
  {
    std_msgs::String msg;
    msg.data = chistes[rand() % chistes.size()];

    ROS_INFO("%s", msg.data.c_str());
    chiste_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
