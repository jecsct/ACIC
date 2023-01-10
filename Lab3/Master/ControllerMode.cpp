#include "ControllerMode.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "Light.hpp"
// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!


#include "Display.hpp"


void ControllerModeOn::loop()
{


}


void ControllerModeOff::loop()
{
    if (_firstTime) {
        MessageOFF message = new MessageOFF();
        Server::communicate(message);
        _firstTime = false;
    }
    Light::
    
}

