#include "Controller.hpp"

namespace Controller {
    
    Mode gCurrentMode = Mode::Off;
    
    ControllerMode const gController[] = {
        new ControllerModeOn();
        new ControllerModeOff();
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

}