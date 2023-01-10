#include "PedButton.hpp"


namespace PedButton {

const uint8_t buttonCount      = 2;
const Button buttonPins[]      = {Power, Ped};

bool lastState;


void initialize(int buttonPin, Function fn) {
    pin = buttonPin;
    callback = fn;

  // Set all button pins to input
  pinMode(Pin, INPUT);
  // Set the last state to true.
  lastState = true;
  // Set all callbacks to nullptr
  memset(callback, 0, sizeof callback);
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