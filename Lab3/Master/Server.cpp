#include "Server.hpp"
#include <Wire.h>
#include "Message.hpp"
#include "Lights.hpp"
namespace Server
{
    const bool cSlave = false;
    int cEntity = 0;

    MessageID previousMessage;

    int *queueMessage;

    Message *getMessage(MessageID messageID)
    {
        switch (static_cast<int>(messageID))
        {
        case static_cast<int>(MessageID::RED):
            Serial.println("RED MESSAGE;");
            return new MessageRED();
        case static_cast<int>(MessageID::GREEN):
            Serial.println("GREEN MESSAGE;");
            return new MessageGREEN();
        case static_cast<int>(MessageID::OFF):
            Serial.println("OFF MESSAGE;");
            return new MessageOFF();
        case static_cast<int>(MessageID::STATUS):
            Serial.println("STATUS MESSAGE;");
            return new MessageSTATUS();
        case static_cast<int>(MessageID::ACK):
            Serial.println("ACK MESSAGE;");
            return new MessageACK();
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
        int *msg = receiveMessage(0);
        //   MessageID messageID = message[1];
        Message *message = getMessage(static_cast<MessageID>(msg[1]));
        message->onReceive();
        free(message);
    }

    void requestEvent()
    {
        Message *message = getMessage(previousMessage);
        sendMessage(message->respond(0, 0), message->size); // wrong
        free(message);
    }

    void communicate(Message *message, int target)
    {
        Serial.println("communicate");
        int *msg = message->send(cEntity, target);
        Serial.println(message->size);
        sendMessage(msg, message->size);
        int *response = receiveMessage(msg[2]);
        // Serial.println("messagen received!");
        // int x = 0;
        // bool status = message->receive(&x); // wrong
        // Serial.println("freed");
        free(msg);
    }

    void sendMessage(int *message, int size)
    {
        int target = message[2];
        Serial.print("target: ");
        Serial.println(target);
        if (target == cEntity)
            sendToOwn(message);
        else
            sendToWire(message, target, size);
    }

    int *receiveMessage(int target)
    {
        int *message;
        Message *msg = getMessage(static_cast<MessageID>(message[1]));

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
                Wire.requestFrom(target, msg->reqSize);
            }
            message = receiveFromWire(msg->reqSize);
        }
        // Serial.println(msg);
        // msg->onReceive();
        // free(msg);

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
        Lights::turnOnLight(Lights::ControllerCom);
        Serial.println("Seding to wire");
        Wire.beginTransmission(target);
        for (int i = 0; i < size; i++)
        {
            Wire.write(message[i]);
        }
        Lights::turnOffLight(Lights::ControllerCom);
    }

    void sendToOwn(int *message)
    {
        queueMessage = message;
    }
}