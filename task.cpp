// task.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <cstdint>
#include "definitions.h"

#ifndef _TASK
#define _TASK

using namespace std;

// Task is the atomic operation of work in this system
// it includes a task ID, a location, a time, and a status
// Status is 0 if no robot has taken the task, 1 if a different robot is workin on this task, 2 if this robot is workin on this task, and 3 if the task is completed by this or another robot.
class task
{
private:
	uint8_t TID;
	uint8_t x;
	uint8_t y;
	uint8_t time;
	uint8_t status;
	
public:
	task();
	void initialize(uint8_t TID_input, uint8_t x, uint8_t y, uint8_t input_time);
	task(uint8_t TID_input, uint8_t x, uint8_t y, uint8_t input_time);
	void update(uint8_t status);
	uint8_t get_x();
	uint8_t get_y();
	uint8_t get_TID();
	bool is_complete();
	uint8_t distance(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y);
	uint8_t get_status();
	uint8_t get_wait_time();
};

task::task()
{
	TID = 255;
	x = 255;
	y = 255;
	time = 255;
	status = 0;
}

void task::initialize(uint8_t input_TID, uint8_t input_x, uint8_t input_y, uint8_t input_time)
{
	TID = input_TID;
	x = input_x;
	y = input_y;
	time = input_time;
	status = 0;
}

task::task(uint8_t input_TID, uint8_t input_x, uint8_t input_y, uint8_t input_time)
{
	TID = input_TID;
	x = input_x;
	y =input_y;
	time = input_time;
	status = 0;
}

void task::update(uint8_t new_status)
{
	status = new_status;

}

uint8_t task::get_x()
{
	return x;
}

uint8_t task::get_y()
{
	return y;
}

uint8_t task::get_TID()
{
	return TID;
}

bool task::is_complete()
{
	if (status == 3)
	{
		return true;
	}
	return false;
}

// This will find the distance to the x and y coordinate of this task using a D* algorithm
// This function is used to find the nearest task
uint8_t task::distance(bool map[][MAP_SIZE], uint8_t robot_x, uint8_t robot_y)
{
	int dirMap[MAP_SIZE][MAP_SIZE] = { 0 };

	int step = 1;
	dirMap[x][y] = step;

	while (dirMap[robot_x][robot_y] == 0)
	{

		for (int i = 0; i < MAP_SIZE; i++)
		{

			for (int j = 0; j < MAP_SIZE; j++)
			{
				if (dirMap[i][j] == step)
				{

					if (dirMap[i + 1][j] == 0 && map[i + 1][j] == 0)
					{
						dirMap[i + 1][j] = step + 1;
					}
					if (dirMap[i - 1][j] == 0 && map[i - 1][j] == 0)
					{
						dirMap[i - 1][j] = step + 1;
					}
					if (dirMap[i][j + 1] == 0 && map[i][j + 1] == 0)
					{
						dirMap[i][j + 1] = step + 1;
					}
					if (dirMap[i][j - 1] == 0 && map[i][j - 1] == 0)
					{
						dirMap[i][j - 1] = step + 1;
					}
				}

			}


		}
		step++;
	}
	return step - 1;
}

uint8_t task::get_status()
{
	return status;
}

uint8_t task::get_wait_time()
{
	return time;
}

#endif