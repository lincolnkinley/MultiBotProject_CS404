#pragma once

// task.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <cstdint>
#include "definitions.h"

using namespace std;

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
	void initialize(uint8_t, uint8_t, uint8_t, uint8_t);
	task(uint8_t, uint8_t, uint8_t, uint8_t);
	void update(uint8_t);
	uint8_t get_x();
	uint8_t get_y();
	uint8_t get_TID();
	bool is_complete();
	uint8_t distance(bool [][MAP_SIZE], uint8_t, uint8_t);
	uint8_t get_status();
	uint8_t get_wait_time();
};