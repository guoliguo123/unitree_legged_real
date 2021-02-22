// currently, the robot should under walking mode.
// receive msg: walk_2s
// convert msgs to lcm?  OR convert it to udp through convert.h

#include <time.h>
#include <string>
#include "unitree_legged_sdk/unitree_legged_sdk.h"
//#include "convert.h"
#include <iostream>

using std::cout;
using std::endl;

using namespace UNITREE_LEGGED_SDK;

int main(int argc, char *argv[]){
    UNITREE_LEGGED_SDK::InitEnvironment();
	cout << "InitEnvironment finished" << endl;
	cout << HIGHLEVEL << endl;

    
	UDP udp(HIGHLEVEL);
	return 0;

    HighCmd cmd = {0};
	udp.InitCmdData(cmd);

    HighCmd standCmd = {0};
	standCmd.mode = 1;

	udp.SetSend(standCmd);
}
