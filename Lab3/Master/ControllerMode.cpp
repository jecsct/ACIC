#include "ControllerMode.hpp"
#include "C:\Users\Joao\Desktop\Tecnico\1Ano\P2\ACIC\Git\Lab3\Server.hpp"
#include "C:\Users\Joao\Desktop\Tecnico\1Ano\P2\ACIC\Git\Lab3\Message.hpp"
#include "Lights.hpp"
#include "Message.hpp"
// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include "Display.hpp"

void ControllerModeOn::loop()
{
    Lights::turnOnLight(Light::ControllerOn);
    readPotentiometer();

    if (millis() - change_timer > entry_timer || first_time)
    {
        for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++)
        {
            if (entry_number != currentGreenEntrySemaphore)
            {
                Server::communicate(MessageRED); //missing entry number
            }
        }

        Server::communicate(MessageRED); //missing entry number to green

        currentGreenEntrySemaphore++;

        resetGreenSemaphore();

        change_timer = millis();
        first_time = false;
    }
}

void ControllerModeOff::loop()
{
    if (_firstTime)
    {
        MessageOFF message = new MessageOFF();
        Server::communicate(message);
        _firstTime = false;
    }
    Light::
}
