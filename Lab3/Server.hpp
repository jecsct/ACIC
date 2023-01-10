#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// Module to communicate
///
namespace Server {


/// The color of the LED
///


/// Initialize the display module.
///
void initialize();

/// Get the maximum level.
///
/// @return The maximum level value.
///
void loop();

void communicate(Message message);

}