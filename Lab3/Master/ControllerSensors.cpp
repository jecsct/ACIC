#include "ControllerSensors.hpp"


namespace ControllerSensors {

  // The previous button state
  bool lastState = false;

  // Initialize the button module
  void initialize(int buttonPin, Function fn) {
    pin = buttonPin;
    callbackFn = fn;
    pinMode(Pin, INPUT);
  }

  // Check if the button is pressed
  void check() {
      const bool buttonPressed = (digitalRead(pin) == HIGH);
      if (buttonPressed != lastState) {
        lastState = buttonPressed;
        if (buttonPressed) {
          callbackFn();
        }
      }
  }

  
}