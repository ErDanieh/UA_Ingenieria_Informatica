#include "ros/ros.h"
#include "std_msgs/String.h"

void chisteCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Recibí un chiste: %s", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "chistes_nodo_receptor");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("chistes", 10, chisteCallback);
  ros::spin();

  return 0;
}
