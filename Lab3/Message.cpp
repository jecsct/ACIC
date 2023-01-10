#include "Message.hpp"

#include "Server.hpp"
#include "Slave.hpp"
//used to Send this message

// Concrete Creator or Client
Message getMessage(MessageID* messageID) {                           // (1)
    switch(messageID){                                   // (4)
    case MessageID::RED:
        return MessageRED;
        break;
    case MessageID::GREEN:
        return MessageGREEN;
        break;
    }
    return nullptr;
}

static void MessageRED::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, MessageID::RED, target, sender + MessageID::RED + target};
    // Server::sendMessage(message, size);
}
//used to control what happens when this message is received
static void MessageRED::onReceive()
{
    Slave::setMode(Mode::Red);
}
// used to repond to this message
static void MessageRED::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}

// used to control what the asnwer to this message was
static void MessageRED::receive(uint *message)
{
    return 

}





static void MessageGREEN::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, Message::GREEN, target, sender + Message::GREEN + target};
    Server::sendMessage(message, size);
}

static void MessageGREEN::onReceive()
{
}

static void MessageGREEN::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}






static void MessageOFF::send(uint8_t sender, uint8_t target)
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, Message::OFF, target, sender + Message::OFF + target};
    Server::sendMessage(messag, size);
}

static void MessageOFF::receive()
{
}

static void MessageOFF::respond(uint8_t sender, uint8_t target)
{
    return MessageACK::send();
}






static void MessagePING::send()
{
}
static void MessagePING::receive()
{
}





static void MessageACK::send()
{
    uint8_t size = 4;
    uint8_t message[size] = {sender, MessageID::ACK, target, sender + MessageID::ACK + target};
}

static void MessageACK::receive()
{
}






static void MessageSTATUS::send()
{
}

static void MessageSTATUS::receive()
{
}
