#include "ros/ros.h"

#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>

class tf_odometry{
    public:
    tf_odometry(ros::NodeHandle &co){
        sub = co.subscribe("/t265/odom", 1000, &tf_odometry::callback, this);
    }

    void callback(nav_msgs::Odometry odom){
        tf::TransformBroadcaster br;
        tf::Transform transform;
        transform.setOrigin(tf::Vector3(odom.pose.pose.position.x, odom.pose.pose.position.y, 0));
        tf::Quaternion q(odom.pose.pose.orientation.x, odom.pose.pose.orientation.y, odom.pose.pose.orientation.z, odom.pose.pose.orientation.w);
        // ROS_INFO("odom: %f,%f,%f",odom.pose.pose.position.x, odom.pose.pose.position.y, odom.pose.pose.position.z);
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "tf_odom", "vehicle_centre"));
    }

    private:
    
    tf::TransformBroadcaster br;
    ros::Subscriber sub;
};

int main(int argc, char **argv){
  

    ros::init(argc, argv, "tf_publisher");
    ros::NodeHandle tfp;
    
   
    tf_odometry tfpub(tfp);

    ros::spin();
    return 0;
}