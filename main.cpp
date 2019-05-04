#include <iostream>
#include <string>
#include "robot.h"
#include "missionControl.h"
#include "communcation.h"
#include "controller.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
	ofstream robot_locations;
	robot_locations.open("robot_locations.txt");
	uint8_t mission[64];
	uint8_t r1_message[64];
	uint8_t r2_message[64];
	uint8_t r3_message[64];
	for (int i = 0; i < 64; i++)
	{
		mission[i] = 255;
	}
	// This mission is sent at tick 0, and includes 2 tasks
	// task 0 is at [6,6] and takes 12 seconds to complete
	// task 1 is at [8,7] and takes 26 seconds to complete
	mission[0] = 64;
	mission[1] = 0;
	mission[2] = 0;
	mission[3] = 2;

	mission[4] = 0;
	mission[5] = 6;
	mission[6] = 6;
	mission[7] = 12;

	mission[8] = 1;
	mission[9] = 8;
	mission[10] = 7;
	mission[11] = 26;

	controller r1 = controller(1, 1, 0);
	controller r2 = controller(8, 8, 0);
	controller r3 = controller(1, 8, 0);
	r1.sim_recv(mission,12);
	r2.sim_recv(mission, 12);
	r3.sim_recv(mission, 12);
	for (int i = 0; i < 175; i++)
	{
		if (i == 32)
		{
			// This mission is sent at tick 32, and includes 2 tasks
			// task 0 is at [4,2] and takes 12 seconds to complete
			// task 1 is at [5,3] and takes 26 seconds to complete
			cout << "Send New Mission" << endl;
			mission[0] = 64;
			mission[1] = 0;
			mission[2] = 0;
			mission[3] = 2;

			mission[4] = 0;
			mission[5] = 4;
			mission[6] = 2;
			mission[7] = 12;

			mission[8] = 1;
			mission[9] = 5;
			mission[10] = 3;
			mission[11] = 26;

			r1.sim_recv(mission, 12);
			r2.sim_recv(mission, 12);
			r3.sim_recv(mission, 12);
		}
		else if (i == 96)
		{
			// This mission is sent at tick 96, and includes 3 tasks
			// task 0 is at [4,8] and takes 12 seconds to complete
			// task 1 is at [7,1] and takes 26 seconds to complete
			// task 1 is at [4,3] and takes 17 seconds to complete
			cout << "Send New Mission" << endl;
			mission[0] = 64;
			mission[1] = 0;
			mission[2] = 0;
			mission[3] = 3;

			mission[4] = 0;
			mission[5] = 2;
			mission[6] = 8;
			mission[7] = 12;

			mission[8] = 1;
			mission[9] = 7;
			mission[10] = 1;
			mission[11] = 26;

			mission[12] = 2;
			mission[13] = 4;
			mission[14] = 3;
			mission[15] = 17;

			r1.sim_recv(mission, 12);
			r2.sim_recv(mission, 12);
			r3.sim_recv(mission, 12);
		}

		string r1_data = r1.run_once();
		uint8_t r1_x = r1_data[0];
		uint8_t r1_y = r1_data[1];
		r1_data.erase(0, 2);
		if (r1_data.length() > 0)
		{
			uint8_t i;
			for (i = 0; i < r1_data.length(); i++)
			{
				r1_message[i] = r1_data[i];
			}
			uint8_t size = i;
			for (; i < 64; i++)
			{
				r1_message[i] = 255;
			}
			r2.sim_recv(r1_message, size);
			r3.sim_recv(r1_message, size);
		}
		robot_locations << r1_x << ',' << r1_y << "|";


		string r2_data = r2.run_once();
		uint8_t r2_x = r2_data[0];
		uint8_t r2_y = r2_data[1];
		r2_data.erase(0, 2);
		if (r2_data.length() > 0)
		{
			uint8_t i;
			for (i = 0; i < r2_data.length(); i++)
			{
				r2_message[i] = r2_data[i];
			}
			uint8_t size = i;
			for (; i < 64; i++)
			{
				r2_message[i] = 255;
			}
			r1.sim_recv(r2_message, size);
			r3.sim_recv(r2_message, size);
		}
		robot_locations << r2_x << ',' << r2_y << "|";

		string r3_data = r3.run_once();
		uint8_t r3_x = r3_data[0];
		uint8_t r3_y = r3_data[1];
		r3_data.erase(0, 2);
		if (r3_data.length() > 0)
		{
			uint8_t i;
			for (i = 0; i < r3_data.length(); i++)
			{
				r3_message[i] = r3_data[i];
			}
			uint8_t size = i;
			for (; i < 64; i++)
			{
				r3_message[i] = 255;
			}
			r1.sim_recv(r3_message, size);
			r2.sim_recv(r3_message, size);
		}
		
		
		robot_locations << r3_x << ',' << r3_y << endl;

	}
	robot_locations.close();

	cout << "Done" << endl;
	system("pause");
}

