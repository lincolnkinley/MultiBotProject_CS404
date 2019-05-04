// navigation.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>
#include <algorithm>
#include "definitions.h"

#ifndef _NAVIGATION
#define _NAVIGATION

using namespace std;

// Navigation is responsible for finding the best path from one point to another
// Navigation uses a D* algorithm to find the best path.
class navigation
{
private:
	bool map[MAP_SIZE][MAP_SIZE];
	string path;
public:
	navigation();
	void set_map(bool[][MAP_SIZE]);
	void find_path(uint8_t robot_x, uint8_t robot_y, uint8_t goal_x, uint8_t goal_y);
	string get_path();
};

navigation::navigation()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = false;
		}
	}
}

void navigation::set_map(bool input_map[][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = input_map[i][j];
		}
	}
}

// This function returns a string representing the steps the robot should make to get to the target location.
// The string is a format where u is up, l is left, r is right, d is down, and e is end
// for example a path could be "urruurrre" for up, right, right, up, up, right, right, right, end
void navigation::find_path(uint8_t robot_x, uint8_t robot_y, uint8_t goal_x, uint8_t goal_y)
{
	int dirMap[MAP_SIZE][MAP_SIZE] = { 0 };

	int step = 1;
	dirMap[goal_x][goal_y] = step;

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
	int xStep = robot_x;
	int yStep = robot_y;
	step = 0;

	path.clear();

	int pathVal = dirMap[robot_x][robot_y];

	while (xStep != goal_x || yStep != goal_y)
	{
		if (dirMap[xStep][yStep + 1] == pathVal - 1)
		{
			yStep = yStep + 1;
			path += 'd';
		}
		else if (dirMap[xStep][yStep - 1] == pathVal - 1)
		{
			yStep = yStep - 1;
			path += 'u';
		}
		else if (dirMap[xStep + 1][yStep] == pathVal - 1)
		{
			xStep = xStep + 1;
			path += 'r';
		}
		else if (dirMap[xStep - 1][yStep] == pathVal - 1)
		{
			xStep = xStep - 1;
			path += 'l';
		}
		else
		{
			throw; // I am lost!
		}
		step++;
		pathVal = pathVal - 1;
	}
	path += 'e';
}

string navigation::get_path()
{
	return path;
}

#endif