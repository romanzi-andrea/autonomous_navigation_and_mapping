# autonomous_navigation_and_mapping
Design of a ROS1 network for the mapping and autonomous navigation of a mobile robot

To run the mapping process, run the mapping.launch file and the bag first.bag (put the bag in your bags folder in the ROS workspace) with the --clock parameter (rosbag play --clock first.bag), it will start rviz for the mapping visualization 
To run the autonomous navigation, simply run the navigation.launch file, it will start stage as robot simulator and rviz for the visualization of the simulated robot 

IMPORTANT: notice that the bag file is missing, it's 2.8GB and i can't upload it on github, please if you want to run the mapping process send me an email and i will send you the bag, while the autonomous navigation will work anyway, the map used (the results of the mapping process with different parameters and algorithms) is already in the maps folder
