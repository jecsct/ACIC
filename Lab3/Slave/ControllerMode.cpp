#include "ControllerMode.hpp"
#include "ControllerSensors.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "Lights.hpp"


void ControllerModeOn::loop(int *entries, int numEntries)
{
    Lights::turnOnLight(Lights::ControllerOn);
    entry_timer = ControllerSensors::getPotentiometerValue();

    if (millis() - change_timer > entry_timer || first_time)
    {
        Message *message = new MessageRED();
        for (int i = 0; i < numEntries; i++) {
            if (entries[i] != currentGreenEntrySemaphore) {
                Server::communicate(message, entries[i]); //missing entry number
            }
        }

        Server::communicate(message, currentGreenEntrySemaphore); //missing entry number to green
        free(message);
        
        currentGreenEntrySemaphore++;

        change_timer = millis();
        first_time = false;
    }
}

void ControllerModeOff::loop(int *entries, int numEntries) {
    if (_firstTime) {
        Message *message = new MessageOFF();
        Server::communicate(message, 0);
        _firstTime = false;
        free(message);
    }
}
