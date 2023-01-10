#include "SlaveMode.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!


#include "Lights.hpp"


void SlaveModeRed::loop()
{
    Lights::turnOnLight(Light::InnerRed);
    delay(500);
    Lights::turnOnLight(Light::InnerRed);
}


void SlaveModeGreen::loop()
{
    Lights::turnOnLight(Light::GREEN);
    delay(500);
    Lights::turnOnLight(Light::GREEN);

    
}

void SlaveModeOff::loop()
{
    Lights::turnOnLight(Light::InnerYellow);
    delay(500);
    Lights::turnOnLight(Light::OuterYellow);

}    
