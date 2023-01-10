#include "Controller.hpp"

namespace Controller {
    
    Mode gCurrentMode = Mode::Off;
    
    ControllerMode const gController[] = {
        new ControllerModeOn();
        new ControllerModeOff();
    }
    void initialize() {
        gController[static_cast<uint8_t>(gCurrentMode)]->initialize();
    }
    void setState(Mode mode) {
        if (gCurrentMode != mode) {
            gCurrentMode = mode;
        }
    }

    void cycleMode() {
        if (gCurrentMode == Mode::Off) 
            setState(Mode::On);
        else
            setState(Mode::Off);
    }

    void loop() {
        gController[static_cast<uint8_t>(gCurrentMode)]->loop();
    }

}