#pragma once

#include <Arduino.h>


// A module to handle the pedestrian button.
namespace PedButton {

    typedef void (*Function)();

 


    // Initialize the module
    void initialize(int buttonPin, Function fn);

    // Check if the button is pressed
    void check();

}