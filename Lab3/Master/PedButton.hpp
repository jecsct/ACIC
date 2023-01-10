#pragma once

#include <Arduino.h>


/// A module to handle button presses.
///
namespace PedButton {

    /// The callback function.
    ///
    typedef void (*Function)();

    const int pin;

    Function callback;


    /// Initialize the buttons module.
    ///
    void initialize(int buttonPin, Function fn);

    /// Set a callback if the given button is pressed.
    ///
    void setCallback(Button button, Function fn);

    /// Poll the button states.
    ///
    void poll();

}