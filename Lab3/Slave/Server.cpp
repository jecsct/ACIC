#include "Server.hpp"
#include <Wire.h>
#include "Message.hpp"

namespace Server
{
    const bool cSlave = true;
    int cEntity = 0;

    MessageID previousMessage;

    int *queueMessage;

    Message *getMessage(MessageID messageID)
    {
        switch (static_cast<int>(messageID))
        {
        case static_cast<int>(MessageID::RED):
            return new MessageRED();
            break;
        case static_cast<int>(MessageID::GREEN):
            return new MessageGREEN();
            break;
        case static_cast<int>(MessageID::OFF):
            return new MessageOFF();
            break;
        case static_cast<int>(MessageID::STATUS):
            return new MessageSTATUS();
            break;
        case static_cast<int>(MessageID::ACK):
            return new MessageACK();
            break;
        }
        return nullptr;
    }

    void initialize(int entity)
    {
        if (cSlave)
        {
            Wire.begin(cEntity);
            Wire.onReceive(receiveEvent);
            Wire.onRequest(requestEvent);
        }
        else
        {
            Wire.begin();
        }
        cEntity = entity;
    }

    void receiveEvent()
    {
        int *msg = receiveMessage(0, 4);
        //   MessageID messageID = message[1];
        Message *message = getMessage(static_cast<MessageID>(msg[1]));
        message->onReceive();
        free(message);
    }

    void requestEvent()
    {
        Message *message = getMessage(previousMessage);
        sendMessage(message->respond(0, 0), 4); // wrong
        free(message);
    }

    void communicate(Message *message, int target)
    {
        int *msg = message->send(cEntity, target);

        sendMessage(msg, 4);
        int *response = receiveMessage(msg[2], 4);
        // Serial.println("messagen received!");
        // int x = 0;
        // bool status = message->receive(&x); // wrong
        // Serial.println("freed");
        free(msg);
    }

    void sendMessage(int *message, int size)
    {
        int target = message[2];

        if (target == cEntity)
            sendToOwn(message);
        else
            sendToWire(message, target, size);
    }

    int *receiveMessage(int target, int size)
    {
        int *message;
        if (target == cEntity)
        {
            Serial.println("From own");
            message = receiveFromOwn();
        }
        else
        {
            Serial.println("From wire");
            if (!cSlave)
            {
                Wire.requestFrom(target, size);
            }
            message = receiveFromWire(size);
        }
        Serial.println(message[1]);
        Message *msg = getMessage(static_cast<MessageID>(message[1]));
        msg->onReceive();
        free(msg);

        return message;
    }

    int *receiveFromWire(int size)
    {

        int message[size] = {0};

        for (int i = 0; i < size; i++)
        {
            if (Wire.available())
            {
                message[i] = Wire.read();
            }
        }
        return message;
    }

    int *receiveFromOwn()
    {
        return queueMessage;
    }

    void sendToWire(int *message, int target, int size)
    {
        Wire.beginTransmission(target);
        for (int i = 0; i < size; i++)
        {
            Wire.write(message[i]);
        }
    }

    void sendToOwn(int *message)
    {
        queueMessage = message;
    }
}