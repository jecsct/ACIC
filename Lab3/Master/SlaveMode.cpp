#include "SlaveMode.hpp"


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
        Serial.println("[[[[[[[[[[[[[[[[[[[[[[[[[[[ FIRST TIME GREEN ]]]]]]]]]]]]]]]]]]]]]]]]]]");
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
    Lights::turnAllOff();
    Serial.println("Slave off");
    delay(500);
    Lights::turnOnLight(Lights::InnerYellow);
    Lights::turnOnLight(Lights::OuterYellow);
    delay(500);
}
