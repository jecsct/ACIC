#pragma once


#include <Arduino.h>
#include "Message.hpp"

/// Module to communicate
///
namespace Server
{
    Message *getMessage(MessageID message);
    /// The color of the LED
    ///

    /// Initialize the display module.
    ///
    void initialize();

    /// Get the maximum level.
    ///
    /// @return The maximum level value.
    ///
    void receiveEvent();
    void requestEvent();
    void communicate(Message *message, int target);
    void sendMessage(int *message, int size);
    int *receiveMessage(int target, int size);
    int *receiveFromWire(int size);
    int *receiveFromOwn();
    void sendToWire(int *message, int target, int size);
    void sendToOwn(int *message);

     
    } 