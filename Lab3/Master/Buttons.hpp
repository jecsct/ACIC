#pragma once

#include <Arduino.h>


/// A module to handle button presses.
///
namespace Buttons
{

    /// The callback function.
    ///
    typedef void (*Function)();

    /// The button.
    ///
    enum Button : uint8_t
    {
        Power = 2,
        Ped = 13,
    };

    /// Initialize the buttons module.
    ///
    void initialize();

    /// Set a callback if the given button is pressed.
    ///
    void setCallback(Button button, Function fn);

    /// Poll the button states.
    ///
    void poll();

}