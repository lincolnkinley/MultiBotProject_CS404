// controller.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>
#include "communcation.h"
#include "robot.h"
#include "navigation.h"
#include "missionControl.h"
#include "definitions.h"

#ifndef _CONTROLLER
#define _CONTROLLER

using namespace std;

// Controller is the top level module of the robot
// each robot is represented by a single controller
// Once initialized, on an actual robot you should call run_continuous from main. This function never returns
// When simulating the robot call run_once from a loop in main. This allows simulation of more than one robot
// Also, the communications are simulated using sim_rcv
class controller
{
private:
	navigation nav;
	robot rob;
	communication com;
	missionControl missions;
	string path;
	bool map[MAP_SIZE][MAP_SIZE];
	uint32_t attempt_timer;
	int wait_time;
public:
	controller(uint8_t x, uint8_t y, short int angle);
	void run_continuous();
	string run_once();
	void sim_recv(uint8_t *in, uint8_t);
};

controller::controller(uint8_t x, uint8_t y, short int angle)
{
	bool default_map [MAP_SIZE][MAP_SIZE] = { 
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 }
		};
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = default_map[i][j];
		}
	}

	nav = navigation();
	nav.set_map(map);
	rob = robot();
	rob.init(x, y, angle);
	com = communication();
	missions = missionControl();
	attempt_timer = 0;
	wait_time = 0;
}

// Use this function when this is running on an acutal robot
void controller::run_continuous()
{
	// TODO 
}

// Use this function when simulating robots
string controller::run_once()
{
	string ret;
	ret += (char)(rob.get_x() + 48);
	ret += (char)(rob.get_y() + 48);
	string mission_args = com.readMessages();
	missions.update(mission_args);

	if (missions.get_broadcast_flag())
	{
		uint8_t message[4] = { 65,0,0,1 };
		message[1] = missions.get_current_mission_ID();
		message[2] = missions.get_current_task_ID();
		for (int i = 0; i < 4; i++)
		{
			ret += message[i];
		}
	}

	if (missions.get_abandon_flag())
	{
		path.clear();
	}

	if (missions.update_task(map, rob.get_x(), rob.get_y()))
	{
		// Enter this if statement if the robot has 
		nav.find_path(rob.get_x(), rob.get_y(), missions.get_current_goal_x(), missions.get_current_goal_y());
		path = nav.get_path();
	}
	if (wait_time > 0)
	{
		wait_time--;
		if (wait_time == 0)
		{
			uint8_t message[4] = { 65,0,0,3 };
			message[1] = missions.get_current_mission_ID();
			message[2] = missions.get_current_task_ID();
			for (int i = 0; i < 4; i++)
			{
				ret += message[i];
			}
			missions.completed_task();
		}
		return ret;
	}
	if (attempt_timer < 1)
	{
		attempt_timer++;
		return ret;
	}
	attempt_timer = 0;
	char movement = path[0];
	switch (movement) 
	{
	case 'u':
		rob.move_up();
		break;
	case 'l':
		rob.move_left();
		break;
	case 'r':
		rob.move_right();
		break;
	case 'd':
		rob.move_down();
		break;
	case 'e':
		wait_time = missions.get_wait_time();
		break;
	}
	path.erase(0, 1);
	return ret;
}

// Use this function to simulate bluetooth sending when simulating robots
void controller::sim_recv(uint8_t *in, uint8_t size)
{
	com.rcv(in, size);
}

#endif