#include "Controller.hpp"
#include "ControllerMode.hpp"
#include "ControllerSensors.hpp"

namespace Controller
{

    Mode gCurrentMode = Mode::Off;
    int *entries;

    int numEntries;

    ControllerMode *const gController[] = {
        new ControllerModeOn(),
        new ControllerModeOff()}
        ;

    void initialize(int *slave_addrs, int n_entries)
    {
        // gController[static_cast<int>(gCurrentMode)]->initialize();
        ControllerSensors::initialize(POWER_BUTTON_PIN, POTENTIOMETER_PIN, &cycleMode);
        entries = slave_addrs;
        numEntries = n_entries;
    }
    
    void setState(Mode mode)
    {
        if (gCurrentMode != mode)
        {
            gController[static_cast<int>(gCurrentMode)]->firstTime = true;
            gCurrentMode = mode;
        }
    }

    void cycleMode()
    {
        Serial.println("cycleMode");
        if (gCurrentMode == Mode::Off) {
            setState(Mode::On);
            Serial.println("ONNNNNNNNNNNNNNNNNNNNN");
        }
        else {
            setState(Mode::Off);
            Serial.println("OFFFFFFFFFFFFFFFFFFF");
        }
    }

    void loop()
    {
        gController[static_cast<int>(gCurrentMode)]->loop(entries, numEntries);
        ControllerSensors::checkPower();
        Serial.print(">>>>>>>>>>>>>>>>>>>>>>> ");
        if (gCurrentMode == Mode::Off) {
            Serial.println("OFF");
        }
        else {
            Serial.println("ON");
        }

    }
}