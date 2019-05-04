// missionControl.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <list>
#include <cstdint>
#include <string>
#include "mission.h"
#include "definitions.h"

#ifndef _MISSIONCONTROL
#define _MISSIONCONTROL

using namespace std;

// mission control handles wchich current mission and task of all available missions and tasks are selected.
// mission control has a lsit of missions, as well as pointers to the current mission and task.
// mission control also has two flags which are used to tell the main controller when to accept a missions, and abandon a mission.
class missionControl
{
private:
	list<mission> missions;
	mission* current_mission;
	task* current_task;
	uint8_t acceptance_delay;
	bool broadcast_flag;
	void abandon_task();
	bool abandon_flag;
public:
	missionControl();
	void add_mission(uint8_t* args, uint8_t length);
	void update(string mission_args);
	void find_task(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y);
	bool update_task(bool map[][MAP_SIZE], uint8_t robotx, uint8_t robot_y);
	uint8_t get_current_mission_ID();
	uint8_t missionControl::get_current_task_ID();
	uint8_t get_current_goal_x();
	uint8_t get_current_goal_y();
	uint8_t get_wait_time();
	void completed_task();
	bool get_broadcast_flag();
	bool get_abandon_flag();
};

missionControl::missionControl()
{
	current_mission = NULL;
	current_task = NULL;
	acceptance_delay = 0;
	broadcast_flag = false;
	abandon_flag = false;
}

// Adds a new mission to the list of missions
// Every time this is called a single mission is created
// args in an array of uint8_t which represents the tasks
// args should have four values for every task, where 0 is task ID, 1 is x coordinate, 2 is y cooridnate, and 3 is time.
void missionControl::add_mission(uint8_t* args, uint8_t length)
{
	mission new_mission = mission(args[1]);
	for (int i = 4; i < length; i += 4)
	{
		new_mission.add_task(args[i], args[i + 1], args[i + 2], args[i + 3]);
	}
	missions.push_back(new_mission);
}

// Will find the nearest available task on the oldest mission
// checks the oldest mission first to ensure missions are completeed in FIFO order
// If no tasks are available then the current missions and current task will be NULL
void missionControl::find_task(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y)
{

	for (list<mission>::iterator it = missions.begin(); it != missions.end(); it++)
	{
		current_task = it->find_nearest_task(map, robot_x, robot_y);
		if (current_task != NULL)
		{
			current_mission = &(*it);
			acceptance_delay = current_task->distance(map, robot_x, robot_y);
			return;
		}
	}
	current_task = NULL;
	current_mission = NULL;
}

// This funciton updates the mission control
// First, if there are any arguments, they are processed
// arguments will either create a new mission or modify an existing mission (like a different robot completes a task)
// Next the robot will decrement its acceptance delay if its considering but hasn't accepted a mission
// If anohter robot has accepted the mission already that means the other robot was closer to the objective andthis robot will abandon the task
// Finally, the robot will check all missions in the mission list to see if any are complete and can be deleted
void missionControl::update(string mission_args)
{

	for (int i = 0; i < mission_args.size(); i+=4)
	{
		uint8_t a = mission_args[i];
		uint8_t b = mission_args[i + 1];
		uint8_t c = mission_args[i + 2];
		uint8_t d = mission_args[i + 3];
		if (a == 64)
		{
			int size;
			for (size = 4; (i+size < mission_args.size()) && (mission_args[i+size]) < 64; size += 4);
			uint8_t* instructions = new uint8_t[size];
			for (int c = 0; c < size; c++)
			{
				instructions[c] = mission_args[i + c];
			}
			add_mission(instructions, size);
			delete(instructions);
			instructions = NULL;
			i += (size-4);
		}
		else if (a == 65)
		{
			for (list<mission>::iterator it = missions.begin(); it != missions.end(); it++)
			{
				if (it->get_MID() == b)
				{
					it->change_status(c, d);
					if (current_task != NULL)
					{
						if ((current_mission->get_MID() == b) && (current_task->get_TID() == c))
						{
							abandon_task();
							acceptance_delay = 0;
						}
					}
				}
			}
		}
	}

	if (acceptance_delay > 0)
	{
		acceptance_delay--;
		if (acceptance_delay == 0)
		{
			broadcast_flag = true;
		}
	}
	
	list<mission>::iterator it = missions.begin();
	while (it != missions.end())
	{
		if (it->mission::is_complete())
		{
			missions.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

// This function will change the status of a task
// This is used for when other robots accepts or completes a task
// every robot must be notified that another robot has accepted or completed a task to ensure two robots do not attempt the same task
// Will return true if the task is updated. will return false otherwise, which indicates the robot does not have a task.
bool missionControl::update_task(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y)
{
	if (current_task == NULL)
	{
		find_task(map, robot_x, robot_y);
		if (current_task == NULL)
		{
			return false;
		}
		current_task->update(2);
		return true;
	}
	return false;
}

uint8_t missionControl::get_current_mission_ID()
{
	return current_mission->get_MID();
}

uint8_t missionControl::get_current_task_ID()
{
	return current_task->get_TID();
}

uint8_t missionControl::get_current_goal_x()
{
	return current_task->get_x();
}

uint8_t missionControl::get_current_goal_y()
{
	return current_task->get_y();
}

uint8_t missionControl::get_wait_time()
{
	return current_task->get_wait_time();
}

void missionControl::completed_task()
{
	current_task->update(3);
	current_task = NULL;
	current_mission = NULL;
}

bool missionControl::get_broadcast_flag()
{
	if (broadcast_flag)
	{
		broadcast_flag = false;
		return true;
	}
	return false;

}

void missionControl::abandon_task()
{
	current_task = NULL;
	current_mission = NULL;
	abandon_flag = true;
}

bool missionControl::get_abandon_flag()
{
	if (abandon_flag)
	{
		abandon_flag = false;
		return true;
	}
	return false;
}

#endif