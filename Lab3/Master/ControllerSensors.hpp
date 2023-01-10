#pragma once

#include <Arduino.h>


// A module to handle thepedestrian button.
namespace ControllerSensors {

    typedef void (*Function)();

    // The button pin
    const int pin;

    // The callback function
    Function callbackFn;


    // Initialize the buttons module.
    void initialize(int buttonPin, Function fn);

    // Check if the button is pressed
    void check();

}