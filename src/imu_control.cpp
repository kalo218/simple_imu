#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

float front=0;
float side=0;
float rotate=0;

void msgCallback(const sensor_msgs::Imu& msg2)
{

    ROS_INFO("-------------------------");
    ROS_INFO("linear.x=%f",msg2.linear_acceleration.x);
    ROS_INFO("linear.y=%f",msg2.linear_acceleration.y);
    ROS_INFO("linear.z=%f",msg2.linear_acceleration.z);
    ROS_INFO("---------------------");
    ROS_INFO("angular.x=%f",msg2.angular_velocity.x);
    ROS_INFO("angular.y=%f",msg2.angular_velocity.y);
    ROS_INFO("angular.z=%f",msg2.angular_velocity.z);
    ROS_INFO("-------------------------");

    front = -msg2.linear_acceleration.y;
    
    side = msg2.linear_acceleration.x;
    
    rotate= msg2.angular_velocity.z;
    
        
}

int main(int argc, char**argv)
{
    ros::init(argc, argv, "imu_control"); // name of node
    ros::NodeHandle nh;

    ros::Publisher imu_control_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",100); //queue size 100;]
    ros::Subscriber imu_control_sub = nh.subscribe("android/imu", 100, msgCallback);

    ros::Rate loop_rate(10); //10Hz

    while(ros::ok())
    {
        geometry_msgs::Twist msg;
        msg.linear.x=front; 
        msg.linear.y=side;
        msg.linear.z=0.0;   //no use
        msg.angular.x=0.0;  //no use
        msg.angular.y=0.0;  //no use
        msg.angular.z=rotate;
        
        // ROS_INFO("-------------------------");
        // ROS_INFO("linear.x=%f",msg.linear.x);
        // ROS_INFO("linear.y=%f",msg.linear.y);
        // ROS_INFO("linear.z=%f",msg.linear.z);
        // ROS_INFO("---------------------");
        // ROS_INFO("angular.x=%f",msg.angular.x);
        // ROS_INFO("angular.y=%f",msg.angular.y);
        // ROS_INFO("angular.z=%f",msg.angular.z);
        // ROS_INFO("-------------------------");
        
        imu_control_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

    }
    
    return 0;
}
