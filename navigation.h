#pragma once

// navigation.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>
#include <algorithm>
#include "definitions.h"

using namespace std;

class navigation
{
private:
	bool map[MAP_SIZE][MAP_SIZE];
	string path;
public:
	navigation();
	void set_map(bool[][MAP_SIZE]);
	void find_path(uint8_t, uint8_t, uint8_t, uint8_t);
	string get_path();
};