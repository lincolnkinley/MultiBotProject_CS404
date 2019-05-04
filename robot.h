#pragma once

// robot.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <list>
#include <cstdint>
#include "task.h"

using namespace std;

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
	robot(uint8_t, uint8_t, short int);
	void init(uint8_t, uint8_t, short int);
	void move_up();
	void move_left();
	void move_right();
	void move_down();
	uint8_t get_x();
	uint8_t get_y();
};