#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// Module to communicate
///
namespace Server {


/// The color of the LED
///
enum class Message : uint8_t {
  RED = 0,
  GREEN = 1,
  OFF = 2,
  PING = 3,
  ACK = 4,
  STATUS = 5,
};

/// Initialize the display module.
///
void initialize();

/// Get the maximum level.
///
/// @return The maximum level value.
///
uint8_t getMaximumLevel();

/// Get the level of the givem LED.
///
/// @param color The color of the LED to retrieve.
///
uint8_t getLevel(Color color);

/// Get the level of the givem LED.
///
/// @param index The index of the LED to retrieve (0-2).
///
uint8_t getLevel(uint8_t index);

/// Set the level of the given LED.
///
/// @param color The color of the LED to change.
/// @param level The level for the LED.
///
void setLevel(Color color, uint8_t level);

/// Set the level of the given LED.
///
/// @param index The index of the LED to change (0-2).
/// @param level The level for the LED.
///
void setLevel(uint8_t index, uint8_t level);


}