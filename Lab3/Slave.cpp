#include "Slave.hpp"
#include "SlaveMode.hpp"

namespace Slave {
    
    Mode gCurrentMode = Mode::Off;
    
    SlaveMode const gSlave[] = {
        new SlaveModeOn();
        new SlaveModeOff();
        new SlaveModeOff();
    };

    void initialize() {
        gSlave[static_cast<uint8_t>(gCurrentMode)]->initialize();
    }

    void setState(Mode mode) {
        if (gCurrentMode != mode) {
            gCurrentMode = mode;
        }
    }

    void loop() {
        gSlave[static_cast<uint8_t>(gCurrentMode)]->loop();
    }
}