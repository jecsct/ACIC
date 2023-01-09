#include "Server.hpp"
#include <Wire.h>

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Server
{

    const uint8_t cEntity = 0;
    const uint8_t cEntityCount = 5;
    const uint8_t cEntityList[cEntityCount] = {0, 1, 2};

    void initialize()
    {
        Wire.begin();
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
            message = receiveFromOwn() else message = receiveFromWire()

                return message;
    }

    uint8_t *receiveFromWire(uint8_t target, uint8_t size)
    {

        int message[size] = {0};

        Wire.requestFrom(target, size);
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