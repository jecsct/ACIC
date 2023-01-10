#include "Display.hpp"

namespace Lights
{

    const uint8_t cInnerSemCount = 3;
    const uint8_t cInnerSem[cInnerSemCount] = {1, 2, 3}

    void initialize()
    {
        for (int i = 0; i < cInnerSemCount; i++)
        {
            pinMode(cInnerSemCount[i], OUTPUT);
        }
    }
    
    void turnOnLight(Light light) {
        digitalWrite(light, HIGH);
    }
    void turnOffLight(Light light) {
        digitalWrite(light, LOW);
    }

}