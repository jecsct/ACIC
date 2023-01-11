#include "ControllerSensors.hpp"

namespace ControllerSensors
{

  // The previous power button state 
  bool lastButtonState = false;
  //  The power button pin
  int powerPin;

  // The potentiometer pin
  int potPin;
  Function powerCallbackFn;

  // Initialize the module
  void initialize(int powerButtonPin, int potentiometerPin, Function powerFn)
  {
    powerPin = powerButtonPin;
    potPin = potentiometerPin;
    pinMode(powerPin, INPUT);
    pinMode(potPin, INPUT);
    powerCallbackFn = powerFn;
  }

  // Check if the button is pressed
  void checkPower()
  {
    const bool buttonPressed = (digitalRead(powerPin) == HIGH);
    if (buttonPressed != lastButtonState)
    {
      lastButtonState = buttonPressed;

      if (buttonPressed)
      {
        powerCallbackFn();
      }
    }
  }

  // Read the potentiometer
  int getPotentiometerValue()
  {
    int potRead = analogRead(potPin);
    int value = map(potRead, 0, 1023, 2000, 15000); // convert value to [2000, 15000] interval
    return value;
  }

}