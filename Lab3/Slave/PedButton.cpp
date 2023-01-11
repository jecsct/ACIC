#include "PedButton.hpp"

namespace PedButton
{

  // The previous button state
  bool lastState = false;

  // The button pin
  int pin;

  // The callback function
  Function callbackFn;
  // Initialize the button module
  void initialize(int buttonPin, Function fn)
  {
    pin = buttonPin;
    callbackFn = fn;
    pinMode(pin, INPUT);
  }

  // Check if the button is pressed
  void check()
  {
    const bool buttonPressed = (digitalRead(pin) == HIGH);
    if (buttonPressed != lastState)
    {
      lastState = buttonPressed;
      if (buttonPressed)
      {
        callbackFn();
      }
    }
  }

}