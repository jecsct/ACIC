#include <Wire.h>
#include "Lights.hpp"

namespace Lights
{

    const int cInnerSemCount = 10;
    const int cInnerSem[cInnerSemCount] = {
        static_cast<int>(ControllerOn),
        static_cast<int>(ControllerCom),
        static_cast<int>(InnerRed),
        static_cast<int>(InnerYellow),
        static_cast<int>(InnerGreen),
        static_cast<int>(OuterRed),
        static_cast<int>(OuterYellow),
        static_cast<int>(OuterGreen),
        static_cast<int>(PedRed),
        static_cast<int>(PedGreen),
    };

    void initialize()
    {
        Serial.println("initi lights");
        for (int i = 0; i < cInnerSemCount; i++)
        {   
            Serial.println(cInnerSem[i]);
            pinMode(cInnerSem[i], OUTPUT);
        }
    }

    void turnOnLight(Light light)
    {
        digitalWrite(static_cast<int>(light), HIGH);
    }
    void turnOffLight(Light light)
    {
        digitalWrite(static_cast<int>(light), LOW);
    }

}