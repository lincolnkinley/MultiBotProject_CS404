// communication.cpp
// Lincoln Kinley

#include <list>
#include <string>

class communication
{
private:
    list<string> inbox;
    string instruction;
    void readMessage();
    void sendMessage();
    void broadcastMessage();
    void execute();
public:
    void readMessages();
    
}
