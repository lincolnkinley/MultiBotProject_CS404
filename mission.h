#pragma once

// mission.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <list>
#include <cstdint>
#include "task.h"
#include "definitions.h"

using namespace std;

class mission
{
private:
	uint8_t ID;
	list<task> tasks;
public:
	mission(uint8_t);
	void add_task(uint8_t, uint8_t, uint8_t, uint8_t);
	void update();
	bool is_complete();
	uint8_t get_MID();
	void change_status(uint8_t, uint8_t);
	task* find_nearest_task(bool[][MAP_SIZE], uint8_t, uint8_t);
};