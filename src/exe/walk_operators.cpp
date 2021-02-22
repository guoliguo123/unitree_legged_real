// currently, the robot should under walking mode.
// receive msg: walk_2s
// convert msgs to lcm?  OR convert it to udp through convert.h

//#include <ros/ros.h>
#include "std_msgs/msg/string.hpp"
#include <pthread.h>
#include <time.h>
#include <string>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
//#include <unitree_legged_msgs/HighCmd.h>
//#include <unitree_legged_msgs/HighState.h>
//unitree_legged_msgs/msg/walk2s.h
#include "unitree_legged_msgs/msg/walk2s.h"
#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include "convert.h"

bool finished = false;
using namespace UNITREE_LEGGED_SDK;

void walkCallback(const unitree_legged_msgs::walk_2s& walk_msg)
{
	
	ROS_INFO("callback");
	if (finished) {
		//ROS_INFO("finished skip");
		return;
	}

	finished = true;

	ROS_INFO("I heard: [%d]", walk_msg.time);

    HighCmd standCmd = {0};
    //unitree_legged_msgs::HighCmd walkCmd = {0};
	standCmd.mode = 1;

	UDP udp(HIGHLEVEL);

	udp.SetSend(standCmd);
	udp.Send();

	sleep(2);
/*
    HighCmd walkCmd = {0};
    //unitree_legged_msgs::HighCmd walkCmd = {0};
	walkCmd.forwardSpeed = 0.2f;

	UDP udp(2);

	udp.SetSend(walkCmd);
	udp.Send();
*/
	
	

	

/*
     unitree_legged_msgs::HighCmd walk;
     int time;
     walk = walk_msg.highcmd;
     time = walk_msg.time;
     UNITREE_LEGGED_SDK::HighCmd walk_sdk;
     walk_sdk = ToLcm(walk, walk_sdk);
     UNITREE_LEGGED_SDK::LCM roslcm(UNITREE_LEGGED_SDK::HIGHLEVEL);
     //roslcm.Send(walk_sdk);
     ROS_INFO("speed: [%f]", walk.forwardSpeed);
*/
}

//template<typename TCmd, typename TState, typename TLCM>
int mainhelper(int argc, char *argv[]){
    std::cout << "WARNING: Control level is set to HIGH-level." << std::endl
              << "Make sure the robot is standing on the ground." << std::endl
              << "Press Enter to continue..." << std::endl;
    std::cin.ignore();

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("walk", 1000, walkCallback);
    ros::spin();
}


int main(int argc, char *argv[]){
    ros::init(argc, argv, "walk_ros");

    UNITREE_LEGGED_SDK::LeggedType rname = UNITREE_LEGGED_SDK::LeggedType::A1;

    UNITREE_LEGGED_SDK::InitEnvironment();
    mainhelper(argc, argv);
    //mainhelper<UNITREE_LEGGED_SDK::HighCmd, UNITREE_LEGGED_SDK::HighState, UNITREE_LEGGED_SDK::LCM>(argc, argv);

}
