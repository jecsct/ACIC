#include "Message.hpp"

#include "Server.hpp"

//used to Send this message
void MessageRED::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, MessageID::RED, target, sender + MessageID::RED + target};
    Server::sendMessage(message, size);
}
//used to control what happens when this message is received
void MessageRED::onReceive()
{
    State::
}
// used to repond to this message
void MessageRED::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}

// used to control what the asnwer to this message was
void MessageRED::receive(uint *message)
{
    return 

}





void MessageGREEN::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, Message::GREEN, target, sender + Message::GREEN + target};
    Server::sendMessage(message, size);
}

void MessageGREEN::onReceive()
{
}

void MessageGREEN::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}






void MessageOFF::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, Message::OFF, target, sender + Message::OFF + target};
    Server::sendMessage(messag, size);
}

void MessageOFF::receive()
{
}

void MessageOFF::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}






void MessagePING::send()
{
}
void MessagePING::receive()
{
}





void MessageACK::send()
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, MessageID::ACK, target, sender + MessageID::ACK + target};
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
