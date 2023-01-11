#include "Server.hpp"
#include <Wire.h>
#include "Message.hpp"

namespace Server
{
    const bool cSlave = false;
    const int cEntity = 0;
    const int cEntityCount = 5;
    const int cEntityList[cEntityCount] = {0, 1, 2};

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
        }
        return nullptr;
    }

    void initialize()
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
    }

    void receiveEvent()
    {
        int *msg = receiveMessage(0, 4);
        //   MessageID messageID = message[1];
        Message *message = getMessage(static_cast<MessageID>(msg[1]));
        message->onReceive();
    }

    void requestEvent()
    {
        Message *message = getMessage(previousMessage);
        sendMessage(message->respond(0, 0), 4); // wrong
    }

    void communicate(Message *message, int target)
    {
        Serial.println("getting message");
        int *msg = message->send(cEntity, target);
        Serial.println("MESSAGE: ");
        Serial.println(msg[0]);
        Serial.println(msg[1]);
        Serial.println(msg[2]);
        Serial.println(msg[3]);
        Serial.println("sending message");
        sendMessage(msg, 4);
        Serial.println("messagen sent!");
        int *response = receiveMessage(msg[2], 4);
        // Serial.println("messagen received!");
        // int x = 0;
        // bool status = message->receive(&x); // wrong
        free(msg);
    }

    void sendMessage(int *message, int size)
    {
        int target = message[2];
        Serial.println("target");
        Serial.println(target);
        Serial.println("entity");
        Serial.println(cEntity);

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

        //   MessageID messageID = message[1];
        Serial.print("message[1]  :  ");
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
        Serial.println("Saved on own: ");
        Serial.println(message[0]);
        Serial.println(message[1]);
        Serial.println(message[2]);
        Serial.println(message[3]);
        queueMessage = message;
    }
}