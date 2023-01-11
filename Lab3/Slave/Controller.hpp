#pragma once

#include <Arduino.h>

#define POWER_BUTTON_PIN 2
#define POTENTIOMETER_PIN A0

namespace Controller
{
    enum Mode
    {
        On = 0,
        Off = 1
    };

 

    void initialize(int *slave_addrs, int n_entries);
    void setState(Mode mode);
    void cycleMode();
    void loop();
}