#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <fstream>
#include <sstream>
#include <cmath>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "simple_navigation_goals");

  // Tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait for the action server to come up
  while (!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // Read waypoints from waypoints.csv
  std::string waypointsFile = "../robotics/src/second_project/waypoints.csv";          //wothout absolute path does not work
  std::ifstream file(waypointsFile);

  if (!file.is_open()) {
    ROS_ERROR_STREAM("Failed to open " << waypointsFile);
    return 1;
  }

  // // Count the number of waypoints in the file
  // int totalWaypoints = 0;
  std::string line;
  // while (std::getline(file, line)) {
  //   totalWaypoints++;
  // }

  // file.clear();  // Reset file flags
  // file.seekg(0); // Reset file pointer to the beginning

  // int waypointsReached = 0;
  // int arrivato = 0;
  ros::Duration(7).sleep(); // Wait rviz to adjust robot orientation

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string x, y, theta;
    if (std::getline(ss, x, ',') && std::getline(ss, y, ',') && std::getline(ss, theta)) {
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = std::stod(x);
      goal.target_pose.pose.position.y = std::stod(y);

      double theta_rad = std::stod(theta);  // Convert theta to a numeric type (double)
      goal.target_pose.pose.orientation.w = std::cos(theta_rad/2);
      goal.target_pose.pose.orientation.z = std::sin(theta_rad/2);

      ROS_INFO("Sending goal: x=%s, y=%s, theta=%s", x.c_str(), y.c_str(), theta.c_str());
      ac.sendGoal(goal);
      ROS_INFO("%s",ac.getState().toString().c_str());
      // ac.waitForResult(ros::Duration(300.0));
      while (ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)  {

        ROS_INFO("%d",ac.waitForResult());
        ros::Duration(1).sleep();

        // if (ac.waitForResult() == 1) {
        // arrivato = 1;
        // }

      }
      // arrivato = 0;
      // if (!ac.waitForResult(ros::Duration(300.0))) {
      //   ROS_ERROR("Failed to reach the goal or the goal is unreachable");
      //   return 1;
      // }

      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved forward");
      else
        ROS_INFO("The base failed to move forward for some reason");

      ac.getState() = actionlib::SimpleClientGoalState::PENDING;
      // if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
      //   waypointsReached++;
      //   int waypointsLeft = totalWaypoints - waypointsReached;
      //   ROS_INFO("%d of %d waypoints reached. %d waypoints left.", waypointsReached, totalWaypoints, waypointsLeft);

      //   if (waypointsLeft == 0) {
      //     ROS_INFO("All waypoints have been reached");
      //   }
    
      // } else {
      //   ROS_INFO("Failed to reach the goal");
      // }
    } 
  }

  file.close();

  return 0;
}
