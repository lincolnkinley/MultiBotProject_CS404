#pragma once

// missionControl.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <list>
#include <cstdint>
#include <string>
#include "mission.h"
#include "definitions.h"

using namespace std;

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
	void add_mission(uint8_t*, uint8_t);
	void update(string);
	void find_task(bool [][MAP_SIZE], uint8_t, uint8_t);
	bool update_task(bool [][MAP_SIZE], uint8_t, uint8_t);
	uint8_t get_current_mission_ID();
	uint8_t missionControl::get_current_task_ID();
	uint8_t get_current_goal_x();
	uint8_t get_current_goal_y();
	uint8_t get_wait_time();
	void completed_task();
	bool get_broadcast_flag();
	bool get_abandon_flag();
};