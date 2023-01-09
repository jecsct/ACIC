#include "Display.hpp"

namespace Display
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


    void loop()
    {

    }

}