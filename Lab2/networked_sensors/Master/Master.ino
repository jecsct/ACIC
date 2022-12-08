#include <Wire.h>

#define SLAVE_ADDR 8

#define TEMP_PIN A0
#define LIGHT_PIN A1
#define POT_PIN A3


int intensity = 0;
int temperature = 0;
int potentiometer = 0;

void sendMessage(int value) {
    Wire.beginTransmission(SLAVE_ADDR);
    Serial.println(value);
    Wire.write(value);
    Wire.endTransmission();
}

void readTemperature() {
    temperature = analogRead(TEMP_PIN);
    Serial.println(temperature);
    sendMessage(temperature);
}

void readPotentiometer() {
    int pot = analogRead(POT_PIN);
    potentiometer = map(pot, 0, 1023, 2, 20); //Should then be divided by 10
    Serial.println(potentiometer);
    sendMessage(potentiometer);
}

void readLight() {
    int light =  analogRead(LIGHT_PIN);
    intensity = map(light, 0, 1023, 0, 255);
    Serial.println(intensity);
    sendMessage(intensity);
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
    readTemperature();
    readPotentiometer();
    readLight();
}
