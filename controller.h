#pragma once

// controller.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>
#include "communcation.h"
#include "robot.h"
#include "missionControl.h"
#include "navigation.h"
#include "definitions.h"

using namespace std;

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
	controller(uint8_t, uint8_t, short int );
	void run_continuous();
	string run_once();
	void sim_recv(uint8_t *in, uint8_t);
};