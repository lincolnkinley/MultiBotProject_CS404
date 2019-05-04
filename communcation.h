#pragma once

// communication.h
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>

using namespace std;

class communication
{
private:
	uint8_t inbox [64];
	short int tx_pin;
	short int rx_pin;
	string readMessage(int offset);
	void execute();
	void sendMessage();
	uint8_t buffer_point;
public:
	communication();
	void pin_init(uint8_t, uint8_t);
	void rcv(uint8_t *args, uint8_t size);
	string readMessages();
	void broadcastMessage();
};