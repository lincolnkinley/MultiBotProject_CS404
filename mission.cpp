// mission.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <list>
#include <cstdint>
#include "task.h"
#include "definitions.h"

#ifndef _MISSION
#define _MISSION

using namespace std;

// Mission controls a list of tasks for the robot to complete
// Missions are given to every robot in the system, so the robots must communicate with each other to acomplish the mission
// Each mission has a Mission ID, as well as a list of tasks.
class mission
{
private:
	uint8_t ID;
	list<task> tasks;
public:
	mission(uint8_t input_ID);
	void add_task(uint8_t TID, uint8_t x, uint8_t y, uint8_t time);
	void update();
	bool is_complete();
	uint8_t get_MID();
	void change_status(uint8_t TID, uint8_t status);
	task* find_nearest_task(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y);
};

mission::mission(uint8_t input_ID)
{
	ID = input_ID;
	tasks.clear();
}

// Adds a new task to the list of tasks for this mission
// TID is task ID, x is x coord of the task, y is y coord of the task, time is the amount of time the robot is suppsed to spend at the task.
void mission::add_task(uint8_t TID, uint8_t x, uint8_t y, uint8_t time)
{
	tasks.push_back(task(TID,x,y,time));
}

// This funciton will remove completed tasks from a mission
// This allows the mission controller to know when all of the tasks have been completed and the mission can be removed
void mission::update()
{
	list<task>::iterator it = tasks.begin();

	while (it != tasks.end())
	{
		if (it->task::is_complete())
		{
			tasks.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

bool mission::is_complete()
{
	if (tasks.empty())
	{
		return true;
	}
	return false;
}


// This function will find the task with the coresponding task ID as the input parameter, and change the status of that task.
void mission::change_status(uint8_t TID, uint8_t status)
{
	for (list<task>::iterator it = tasks.begin(); it != tasks.end(); it++)
	{
		if (it->get_TID() == TID)
		{
			it->update(status);
		}
	}
}

uint8_t mission::get_MID()
{
	return ID;
}

// This will return the address of the task that is closest to the provided x and y coordinates
task* mission::find_nearest_task(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y)
{
	uint8_t nearest_distance = 255;
	task* nearest_task = NULL;
	for (list<task>::iterator it = tasks.begin(); it != tasks.end(); it++)
	{
		if (it->get_status() == 0)
		{
			uint8_t my_distance = it->distance(map, robot_x, robot_y);
			if (my_distance < nearest_distance)
			{
				nearest_distance = my_distance;
				nearest_task = &(*it);
			}
		}
	}
	return nearest_task;
}

#endif