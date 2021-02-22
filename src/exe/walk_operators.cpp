// currently, the robot should under walking mode.
// receive msg: walk_2s
// convert msgs to lcm?  OR convert it to udp through convert.h

//#include <ros/ros.h>
#include "std_msgs/msg/string.hpp"
#include <pthread.h>
#include <time.h>
#include <string>
//#include <boost/thread.hpp>
//#include <boost/thread/mutex.hpp>
//#include <unitree_legged_msgs/HighCmd.h>
//#include <unitree_legged_msgs/HighState.h>
//unitree_legged_msgs/msg/walk2s.h
#include "unitree_legged_msgs/msg/walk2s.hpp"
#include "unitree_legged_sdk/unitree_legged_sdk.h"
//#include "convert.h" //TODO Solve the unitree_legged_msgs:: namespace issue

#include <iostream>
#include <rclcpp/rclcpp.hpp>

bool finished = false;
using namespace UNITREE_LEGGED_SDK;
using unitree_legged_msgs::msg::Walk2s;


void walk_callback(const Walk2s::SharedPtr msg)
{
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "I heard: [%d]", msg->time);
}


//template<typename TCmd, typename TState, typename TLCM>
int mainhelper(int argc, char *argv[]){
    std::cout << "WARNING: Control level is set to HIGH-level." << std::endl
              << "Make sure the robot is standing on the ground." << std::endl
              << "Press Enter to continue..." << std::endl;
    std::cin.ignore();

    //ros::NodeHandle n;
    //ros::Subscriber sub = n.subscribe("walk", 1000, walkCallback);
    //ros::spin();
    //
    // Create a new node
    // Create new sub from the node
    //   rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription_;       // CHANGE

    auto node = std::make_shared<rclcpp::Node>("my_node_name");
    rclcpp::Subscription<Walk2s>::SharedPtr subscription_ = node->create_subscription<Walk2s>("topic", 10, walk_callback);
		    

    rclcpp::spin(node);
    rclcpp::shutdown();
}


int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);

    UNITREE_LEGGED_SDK::LeggedType rname = UNITREE_LEGGED_SDK::LeggedType::A1;

    UNITREE_LEGGED_SDK::InitEnvironment();
    mainhelper(argc, argv);
    //mainhelper<UNITREE_LEGGED_SDK::HighCmd, UNITREE_LEGGED_SDK::HighState, UNITREE_LEGGED_SDK::LCM>(argc, argv);

}
