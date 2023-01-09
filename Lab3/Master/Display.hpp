#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// The display module to control the attached LEDs
///
namespace Display {


void initialize();


void loop();


}