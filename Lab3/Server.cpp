#include "Server.hpp"
#include <Wire.h>
#include "Message.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Server
{
    const bool slave = false;
    const uint8_t cEntity = 0;
    const uint8_t cEntityCount = 5;
    const uint8_t cEntityList[cEntityCount] = {0, 1, 2};

    MessageID previousMessage;

    void initialize()
    {
        if (slave)
        {
            Wire.begin(cEntity);
            Wire.onReceive(receiveEvent);
            Wire.onRequest(requestEvent);
        }
        else
        {
            Wire.begin();
        }
    }

    void receiveEvent()
    {
        uint8_t *message = receiveMessage(0, 4);
        MessageID messageID = message[1];
        Message message = getMessage(messageID);
        message.onReceive();

    }

    void requestEvent()
    {
        Message message = getMessage(previousMessage);
        sendMessage(message.respond());
    }

    void communicate(Message message)
    {
        int *msg = message.send();

        sendMessage(msg, message.size);

        int *response = receiveMessage(msg[2], message.resp_size);

        bool status = message.receive(response);
    }

    void sendMessage(uint8_t *message, uint8_t size)
    {
        uint8_t target = message[2];
        if (target == cEntity)
            sendToOwn(message, target, size);
        else
            sendToWire(message, target, size);
    }

    uint8_t *receiveMessage(uint8_t target, uint8_t size)
    {
        uint8_t *message;
        if (target == cEntity)
            message = receiveFromOwn() else
            {
                if (!slave)
                {
                    Wire.requestFrom(target, size);
                }

                message = receiveFromWire(size);
            }

        return message;
    }

    uint8_t *receiveFromWire(uint8_t size)
    {

        int message[size] = {0};

        for (int i = 0; i < size; i++)
        {
            if (Wire.avaliable())
            {
                message[i] = Wire.read();
            }
        }
        return message;
    }

    uint8_t *receiveFromOwn(uint8_t target, uint8_t size)
    {
    }

    void sendToWire(uint8_t *message, uint8_t target, uint8_t size)
    {
        Wire.beginTransmission(target);
        for (int i = 0; i < size; i++)
        {
            Wire.write(message);
        }
        Wire.endTransmission();
    }

    void sendToOwn(uint8_t *message, uint8_t target, uint8_t size)
    {
    }