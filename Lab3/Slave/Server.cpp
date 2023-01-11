#include "Server.hpp"
#include <Wire.h>
#include "Message.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Server
{
    const bool cSlave = false;
    const int cEntity = 0;
    const int cEntityCount = 5;
    const int cEntityList[cEntityCount] = {0, 1, 2};

    MessageID previousMessage;

    int *queueMessage;

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
        sendMessage(message->respond(0, 0), 4); //wrong
    }

    void communicate(Message *message, int target)
    {
        int *msg = message->send(cEntity, target);

        // sendMessage(msg, 4);

        // int *response = receiveMessage(msg[2], 4);
        // int x = 0;
        // bool status = message->receive(&x); //wrong
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
            message = receiveFromOwn(); 
        else
            {
                if (!cSlave)
                {
                    Wire.requestFrom(target, size);
                }

                message = receiveFromWire(size);
            }

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

    //TRAVASSOS1 *message-------------------------------------------------------------------
    void sendToWire(int *message, int target, int size)
    //TRAVASSOS2 -----------------------------------------------------------------
    {
        Wire.beginTransmission(target);
        for (int i = 0; i < size; i++){
            Wire.write(message[i]);
        }
    }

    void sendToOwn(int *message)
    {
        queueMessage = message;
    }
}