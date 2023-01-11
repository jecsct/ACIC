#include "Message.hpp"

#include "Server.hpp"
#include "Slave.hpp"
// used to Send this message

// Concrete Creator or Client
//-------------------------------- Message RED --------------------------------

int *MessageRED::send(int sender, int target)
{

    int size = 4;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::RED);
    message[2] = target;
    message[3] = sender + static_cast<int>(MessageID::RED) + target;
    return message;
}
// used to control what happens when this message is received
void MessageRED::onReceive()
{
    Serial.println("message red!");
    Slave::setState(Slave::Red);
}
// used to repond to this message
int *MessageRED::respond(int sender, int target)
{
    Message *messageACK = new MessageACK();
    int *message = messageACK->send(sender, target);
    return message;
}

// used to control what the asnwer to this message was
bool MessageRED::receive(int *message)
{
    return true;
}

//-------------------------------- Message GREEN --------------------------------

int *MessageGREEN::send(int sender, int target)
{
    int size = 4;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::GREEN);
    message[2] = target;
    message[3] = sender + static_cast<int>(MessageID::GREEN) + target;
    return message;
}

void MessageGREEN::onReceive()
{
    Slave::setState(Slave::Green);
}

int *MessageGREEN::respond(int sender, int target)
{
    Message *messageACK = new MessageACK();
    int *message = messageACK->send(sender, target);
    return message;
}

bool MessageGREEN::receive(int *message)
{
    return true;
}

//-------------------------------- Message OFF --------------------------------

int *MessageOFF::send(int sender, int target)
{
    int size = 4;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::OFF);
    message[2] = target;
    message[3] = sender + static_cast<int>(MessageID::OFF) + target;
    return message;
}
void MessageOFF::onReceive()
{
    Slave::setState(Slave::Off);
}

int *MessageOFF::respond(int sender, int target)
{
    Message *messageACK = new MessageACK();
    int *message = messageACK->send(sender, target);
    return message;
}

bool MessageOFF::receive(int *message)
{
    return true;
}

//-------------------------------- Message PING --------------------------------

int *MessagePING::send(int sender, int target)
{
    int size = 4;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::PING);
    message[2] = target;
    message[3] = sender + static_cast<int>(MessageID::PING) + target;
    return message;
}
void MessagePING::onReceive()
{
}

int *MessagePING::respond(int sender, int target)
{
    Message *messageSTATUS = new MessageSTATUS();
    int *message = messageSTATUS->send(sender, target);
    return message;
}

bool MessagePING::receive(int *message)
{
    return true;
}

//-------------------------------- Message ACK --------------------------------

int *MessageACK::send(int sender, int target)
{
    int size = 4;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::ACK);
    message[2] = target;
    message[3] = sender + static_cast<int>(MessageID::ACK) + target;
    return message;
}
void MessageACK::onReceive()
{
}
int *MessageACK::respond(int sender, int target)
{
}
bool MessageACK::receive(int *message)
{
    return true;
}

//-------------------------------- Message STATUS --------------------------------

int *MessageSTATUS::send(int sender, int target)
{
    int size = 5;
    int *message = new int[size];
    message[0] = sender;
    message[1] = static_cast<int>(MessageID::STATUS);
    message[2] = target;
    message[3] = Slave::getStatus();
    message[4] = sender + static_cast<int>(MessageID::STATUS) + target + Slave::getStatus();
    return message;
}

void MessageSTATUS::onReceive()
{
}
int *MessageSTATUS::respond(int sender, int target)
{
}
bool MessageSTATUS::receive(int *message)
{
    return true;
}
