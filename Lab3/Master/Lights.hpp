#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>
#include <Wire.h>

/// The display module to control the attached LEDs
///
namespace Lights
{

    enum Light : int
    {
        ControllerOn = 3,
        ControllerCom = 4,
        InnerRed = 5,
        InnerYellow = 6,
        InnerGreen = 7,
        OuterRed = 8,
        OuterYellow = 9,
        OuterGreen = 10,
        PedRed = 11,
        PedGreen = 12,
    };

    void initialize();
    void turnOnLight(Light light);
    void turnOffLight(Light light);
    void turnAllOff();

}