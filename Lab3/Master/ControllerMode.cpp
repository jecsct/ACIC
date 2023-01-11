#include "ControllerMode.hpp"
#include "ControllerSensors.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "Lights.hpp"


void ControllerModeOn::loop(int *entries, int numEntries)
{
    Serial.println("ON");
    Lights::turnOnLight(Lights::ControllerOn);
    entry_timer = ControllerSensors::getPotentiometerValue();

    if (millis() - change_timer > entry_timer || firstTime)
    {
        Message *message = new MessageRED();
        for (int i = 0; i < numEntries; i++) {
            if (entries[i] != currentGreenEntrySemaphore) {
                Serial.print("message to: ");
                Serial.println(entries[i]);
                // Serial.println(entries[i]);
                // Serial.println(message->send(0, 0)[1]);
                Server::communicate(message, entries[i]); //missing entry number
            }
        }
        // Serial.println("After for");
        free(message);
        // Serial.print("Green sem : ");
        // Serial.println(currentGreenEntrySemaphore);

        message = new MessageGREEN();
        Server::communicate(message, currentGreenEntrySemaphore); //missing entry number to green
        free(message);
        
        // currentGreenEntrySemaphore++;

        change_timer = millis();
        firstTime = false;
    }
}

void ControllerModeOff::loop(int *entries, int numEntries) {
    Serial.println("OFF");
    Lights::turnOffLight(Lights::ControllerOn);
    if (firstTime) {
        Message *message = new MessageOFF();
        Server::communicate(message, 0);
        free(message);
        firstTime = false;
    }
}
