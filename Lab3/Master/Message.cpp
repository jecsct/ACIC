#include "AnimationMode.hpp"

#include "Server.hpp"

//used to Send this message
void MessageRED::send(uint8_t sender, MessageID message, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, message, target, sender + message + target};
    Server::sendMessage(message, size);
}
//used to control what happens when this message is received
void MessageRED::onReceive()
{
}
// used to repond to this message
void MessageRED::respond()
{
}

// used to control what the asnwer to this message was
void MessageRED::receive()
{
}

void MessageGREEN::send(uint8_t sender, MessageID message, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, message, target, sender + message + target};
    Server::sendMessage(message, size);
}

void MessageGREEN::receive()
{
}

void MessageOFF::send(uint8_t sender, MessageID message, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, message, target, sender + message + target};
    Server::sendMessage(messag, size);
}

void MessageOFF::receive()
{
}

void MessagePING::send()
{
}
void MessagePING::receive()
{
}

void MessageACK::send()
{
}

void MessageACK::receive()
{
}

void MessageSTATUS::send()
{
}

void MessageSTATUS::receive()
{
}
