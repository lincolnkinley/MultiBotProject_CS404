// communication.cpp
// Lincoln Kinley
// CS 404 - Project
// May 3, 2019

#include <string>
#include <cstdint>

#ifndef _COMMUNICATION
#define _COMMUNICATION

using namespace std;

// The communication is responsible for handling the bluetooth in and out of the robot
// When simulating the robot, communication is hardly used
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
	void pin_init(uint8_t a, uint8_t b);
	void rcv(uint8_t *args, uint8_t size);
	string readMessages();
	void broadcastMessage();
};

communication::communication()
{
	tx_pin = 0;
	rx_pin = 0;
	buffer_point = 0;
	for (int i = 0; i < 64; i++)
	{
		inbox[i] = 255;
	}
}

void communication::pin_init(uint8_t a, uint8_t b)
{
	tx_pin = a;
	rx_pin = b;
}

// This functions will completely cover how the robot communicates with others. This is the only callable funciton
// This function will return the Robots current objective
string communication::readMessages()
{
	string mission_args;
	for (int i = 0; (inbox[i] != 255) || (i >= 64); i += 4)
	{
		mission_args.append(readMessage(i));
	}
	buffer_point = 0;
	return mission_args;
}

// This function will read the first message in the inbox, add it to the instruction, and remove the message
string communication::readMessage(int offset)
{
	string arg;
	arg.append(string(1,inbox[offset]));
	arg.append(string(1, inbox[offset + 1]));
	arg.append(string(1, inbox[offset + 2]));
	arg.append(string(1, inbox[offset + 3]));
	inbox[offset] = 255;
	inbox[offset+1] = 255;
	inbox[offset+2] = 255;
	inbox[offset+3] = 255;
	return arg;
}

void communication::rcv(uint8_t *args, uint8_t size)
{
	uint8_t i;
	for (i = 0; i < size; i++)
	{
		if ((buffer_point+i) >= 64)
		{
			throw; // buffer overflow
		}
		inbox[buffer_point + i] = args[i];
	}
	buffer_point = buffer_point + i;
}


// This function will read the instruction and determine what action needs to be taken
void communication::execute()
{
	// This function was moved to be done by the controller as communication does not have access to other modules
}

// This function will send a message to a single entity
void communication::sendMessage()
{
	// TODO
}

// This funciton will send a mesage to all entiries in the system
void communication::broadcastMessage()
{
	// TODO
}

#endif