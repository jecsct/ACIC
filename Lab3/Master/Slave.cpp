#include "Slave.hpp"
#include "SlaveMode.hpp"
#include "PedButton.hpp"
#include "Lights.hpp"

namespace Slave {
    
    Mode gCurrentMode = Mode::Off;
    Mode gPreviousMode = Mode::Off;
    bool timerActivated = false;

    SlaveMode* const gSlave[] = {
        new SlaveModeRed(),
        new SlaveModeGreen(),
        new SlaveModeOff()
    };

    int getStatus() {
        return 1;
    }

    void setTimerActivated() {
        timerActivated = true;
    }

    void initialize() {
        Serial.println("init slave");
        // gSlave[static_cast<int>(gCurrentMode)]->initialize();
        Lights::initialize();
        PedButton::initialize(PED_PIN, &setTimerActivated);

    }

    void setState(Mode mode) {
        if (gCurrentMode != mode) {
            gPreviousMode = gCurrentMode;
            gCurrentMode = mode;
        }
    }

    void loop() {
        gSlave[static_cast<int>(gCurrentMode)]->loop();
        PedButton::check();
    }
}