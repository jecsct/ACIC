#pragma once

#include <Arduino.h>

// A module to handle the power button and the potentiometer.
namespace ControllerSensors
{

    typedef void (*Function)();

    // TRAVASSOS1 ----------------------------------------------------------------------------------
    
    // TRAVASSOS2 ----------------------------------------------------------------------------------

    // The power button callback function

    // Initialize the module
    void initialize(int powerButtonPin, int potentiometerPin, Function powerFn);

    // Check if the power button is pressed
    void checkPower();

    // Read the potentiometer
    int getPotentiometerValue();

}