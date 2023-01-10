#include "Buttons.hpp"


namespace Buttons {

const uint8_t buttonCount      = 2;
const Button buttonPins[]      = {Power, Ped};

bool lastState[buttonCount];
Function callbackFn[buttonCount];


void initialize() {
  // Set all button pins to input
  for (int i; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT); 
  }
  // Set the last state to true.
  memset(lastState, static_cast<uint8_t>(true), sizeof lastState);
  // Set all callbacks to nullptr
  memset(callbackFn, 0, sizeof callbackFn);
}


void setCallback(Button button, Function fn) {
  callbackFn[static_cast<uint8_t>(button)] = fn;
}


void poll() {
  for (int i = 0; i < buttonCount; i++) {
    const bool buttonPressed = (digitalRead(buttonPins[i]) != 0);
    if (buttonPressed != lastState[i]) {
      lastState[i] = buttonPressed;
      if (buttonPressed) {
        pressedButtonIndex = i;
      }
    }
  }
  if (pressedButtonIndex < buttonCount && callbackFn[pressedButtonIndex] != nullptr) {
    callbackFn[pressedButtonIndex]();
  }
}

  
}