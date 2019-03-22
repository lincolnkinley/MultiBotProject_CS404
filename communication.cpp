// communication.cpp
// Lincoln Kinley

#include <list>
#include <queue>

#ifndef _COMMUNICATION
#define _COMMUNICATION

class communication
{
private:
    queue<string> inbox;
    string instruction;
    string objective;
    short int tx_pin;
    short int rx_pin;
    void readMessage();
    void execute();
    void sendMessage();
    void broadcastMessage();
public:
    communication(int, int);
    string readMessages();
};

communication::communication(int a, int b)
{
    tx_pin = a;
    rx_pin = b;
    instruction = "";
    objective = "";
}

// This functions will completely cover how the robot communicates with others. This is the only callable funciton
// This function will return the Robots current objective
void communication::readMessages()
{
    while(not inbox.empty())
    {
        readMessage();
        execute();
    }
    if(objective == "")
    return objective;
}

// This function will read the first message in the inbox, add it to the instruction, and remove the message
void communication::readMessage()
{

}

// This function will read the instruction and determine what action needs to be taken
void communication::execute()
{

}

// This function will send a message to a single entity
void communication::sendMessage()
{

}

// This funciton will send a mesage to all entiries in the system
void communication::broadcastMessage()
{

}

#endif
