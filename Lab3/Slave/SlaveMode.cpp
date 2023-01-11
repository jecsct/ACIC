#include "SlaveMode.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include "Lights.hpp"

void SlaveModeRed::loop()
{
    Serial.println("Slave red");
    if (firstTime)
    {
        Lights::turnOffLight(Lights::OuterGreen);
        Lights::turnOffLight(Lights::InnerRed);

        Lights::turnOnLight(Lights::OuterYellow);
        Lights::turnOnLight(Lights::InnerYellow);
        delay(500);
        Lights::turnOffLight(Lights::OuterYellow);
        Lights::turnOffLight(Lights::InnerYellow);

        Lights::turnOnLight(Lights::OuterRed);
        Lights::turnOnLight(Lights::InnerGreen);

        Lights::turnOffLight(Lights::PedRed);
        Lights::turnOnLight(Lights::PedGreen);

        firstTime = false;
    }
}

void SlaveModeGreen::loop()
{
    Serial.println("Slave green");
    if (firstTime)
    {
        Lights::turnOffLight(Lights::OuterRed);
        Lights::turnOffLight(Lights::InnerGreen);

        Lights::turnOnLight(Lights::OuterYellow);
        Lights::turnOnLight(Lights::InnerYellow);
        delay(500);
        Lights::turnOffLight(Lights::OuterYellow);
        Lights::turnOffLight(Lights::InnerYellow);

        Lights::turnOnLight(Lights::OuterGreen);
        Lights::turnOnLight(Lights::InnerRed);

        Lights::turnOnLight(Lights::PedRed);
        Lights::turnOffLight(Lights::PedGreen);

        firstTime = false;
    }
}

void SlaveModeOff::loop()
{
    Serial.println("Slave off");
    Lights::turnOnLight(Lights::InnerYellow);
    Lights::turnOnLight(Lights::OuterYellow);
    delay(500);
    Lights::turnOffLight(Lights::InnerYellow);
    Lights::turnOffLight(Lights::OuterYellow);
    delay(500);
}
