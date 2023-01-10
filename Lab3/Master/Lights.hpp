#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// The display module to control the attached LEDs
///
namespace Lights {

    enum Light : uint8_t
    {
        ControllerOn = 0,
        ControllerCom = 1,
        InnerRed = 2,
        InnerYellow = 3,
        InnerGreen = 4,
        OuterRed = 5,
        OuterYellow = 6,
        OuterGreen = 7,
    };


void initialize();


}