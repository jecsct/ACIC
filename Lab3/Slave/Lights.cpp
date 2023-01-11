#include <Wire.h>
#include "Lights.hpp"

namespace Lights
{

    const int cInnerSemCount = 3;
    const int cInnerSem[cInnerSemCount] = {1, 2, 3};

    void initialize()
    {
        for (int i = 0; i < cInnerSemCount; i++)
        {
            pinMode(cInnerSem[i], OUTPUT);
        }
    }
    
    void turnOnLight(Light light) {
        digitalWrite(light, HIGH);
    }
    void turnOffLight(Light light) {
        digitalWrite(light, LOW);
    }

}