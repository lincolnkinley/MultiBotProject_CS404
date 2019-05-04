// robot.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <math.h>
#include <cstdint>
#include "task.h"

#ifndef _ROBOT
#define _ROBOT

using namespace std;

// The robot class controls the hardware of the robot
// current direction, current position are held in memory
// Funcitons provide the ability to have the robot move
class robot
{
private:
	uint8_t current_location[2];
	short int current_angle; // degrees
	void move_forward();
	void move_backward();
	void turn_left();
	void turn_right();
public:
	robot();
	robot(uint8_t x, uint8_t y, short int angle);
	void init(uint8_t x, uint8_t y, short int angle);
	void move_up();
	void move_left();
	void move_right();
	void move_down();
	uint8_t get_x();
	uint8_t get_y();
};

robot::robot()
{
	current_location[0] = 1;
	current_location[1] = 1;
	current_angle = 0;
}

void robot::init(uint8_t x, uint8_t y, short int angle)
{
	current_location[0] = x;
	current_location[1] = y;
	current_angle = angle;
}

robot::robot(uint8_t x, uint8_t y, short int angle)
{
	current_location[0] = x;
	current_location[1] = y;
	current_angle = angle;
}

// This function appears to be incorrect, but it's because the way C++ does 2D arrays
// in C++, the first value of a 2D array is the Y axis and the second ([y][x])
// to ensure consistancy, we treat the first as the x axis and the second as the y axis everywhere but here
// Same  but opposite for move_backward
void robot::move_forward()
{
	switch (current_angle)
	{
	case 0:
		current_location[0]--;
		break;
	case 90:
		current_location[1]--;
		break;
	case 180:
		current_location[0]++;
		break;
	case 270:
		current_location[1]++;
		break;
	}

}

// This function appears to be incorrect, but it's because the way C++ does 2D arrays
// in C++, the first value of a 2D array is the Y axis and the second ([y][x])
// to ensure consistancy, we treat the first as the x axis and the second as the y axis everywhere but here
void robot::move_backward()
{	
	switch (current_angle)
	{
	case 0:
		current_location[0]++;
		break;
	case 90:
		current_location[1]++;
		break;
	case 180:
		current_location[0]--;
		break;
	case 270:
		current_location[1]--;
		break;
	}
}

void robot::turn_left()
{
	current_angle = current_angle + 90;
	if (current_angle >= 360)
	{
		current_angle = 0;
	}
}

void robot::turn_right()
{
	current_angle = current_angle - 90;
	if (current_angle <= -90)
	{
		current_angle = 270;
	}
}

// This function checks if the robot is facing the correct direction and will move forward.
// if it is 90 degrees from the correct direction it will turn 90 degrees and drive forward
// if the robot is 180 degrees from the correct direction it will drive backward
// same for all move direction functions
void robot::move_up()
{
	// angle must be 90 to move up
	if (current_angle == 90)
	{
		move_forward();
		return;
	}
	else if (current_angle == 0)
	{
		turn_left();
		move_forward();
		return;
	}
	else if (current_angle == 180)
	{
		turn_right();
		move_forward();
		return;
	}
	move_backward();
}

// This function checks if the robot is facing the correct direction and will move forward.
// if it is 90 degrees from the correct direction it will turn 90 degrees and drive forward
// if the robot is 180 degrees from the correct direction it will drive backward
// same for all move direction functions
void robot::move_left()
{
	// angle must be 0 to move left
	if (current_angle == 0)
	{
		move_forward();
		return;
	}
	else if (current_angle == 270)
	{
		turn_left();
		move_forward();
		return;
	}
	else if (current_angle == 90)
	{
		turn_right();
		move_forward();
		return;
	}
	move_backward();
}

// This function checks if the robot is facing the correct direction and will move forward.
// if it is 90 degrees from the correct direction it will turn 90 degrees and drive forward
// if the robot is 180 degrees from the correct direction it will drive backward
// same for all move direction functions
void robot::move_right()
{
	// angle must be 180 to move right
	if (current_angle == 180)
	{
		move_forward();
		return;
	}
	else if (current_angle == 90)
	{
		turn_left();
		move_forward();
		return;
	}
	else if (current_angle == 270)
	{
		turn_right();
		move_forward();
		return;
	}
	move_backward();
}

// This function checks if the robot is facing the correct direction and will move forward.
// if it is 90 degrees from the correct direction it will turn 90 degrees and drive forward
// if the robot is 180 degrees from the correct direction it will drive backward
// same for all move direction functions
void robot::move_down()
{
	// angle must be 270 to move down
	if (current_angle == 270)
	{
		move_forward();
		return;
	}
	else if (current_angle == 180)
	{
		turn_left();
		move_forward();
		return;
	}
	else if (current_angle == 0)
	{
		turn_right();
		move_forward();
		return;
	}
	move_backward();
}

uint8_t robot::get_x()
{
	return current_location[0];
}

uint8_t robot::get_y()
{
	return current_location[1];
}

#endif