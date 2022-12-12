#include <Wire.h>

#define SLAVE_ADDR 8

#define TEMP_PIN A0
#define LIGHT_PIN A1
#define POT_PIN A3

//git sinc

int intensity = 0;
int temperature = 0;
int potentiometer = 0;

void sendMessage(char sensor[], int value) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(sensor);
    Wire.write(value);
    Wire.endTransmission();
}

void readTemperature() {
    temperature = analogRead(TEMP_PIN);
    Serial.print("T ");
    Serial.println(temperature);
    sendMessage("T", temperature);
}

void readPotentiometer() {
    int pot = analogRead(POT_PIN);
    potentiometer = map(pot, 0, 1023, 200, 2000); //Should then be divided by 10
    Serial.print("P ");
    Serial.println(potentiometer);
    sendMessage("P", potentiometer);
}

void readLight() {
    int light =  analogRead(LIGHT_PIN);
    intensity = map(light, 0, 1023, 0, 255);
    Serial.print("L ");
    Serial.println(intensity);
    sendMessage("L", intensity);
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
    Serial.println("=====");
}
