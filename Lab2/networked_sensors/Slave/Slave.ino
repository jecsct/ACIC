#include <Wire.h>

#define SLAVE_ADDR  8
#define RED_LED_PIN  11
#define GREEN_LED_PIN  12
#define YELLOW_LED_PIN  13

int potentiometerTime = 200;
int temperature = 20;
int intensity = 240;

int prevTime = 0;

void callbackFunction(int i) {
     while (1 < Wire.available()) {
           // make sure there is something to read
           char c = Wire.read(); // read the next byte as a char
           Serial.print(c);
     }
     int x = Wire.read();
     Serial.println(x);
}


void controlRed() {
    if (temperature > 26) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
    } else {
        digitalWrite(YELLOW_LED_PIN, LOW);
    }
}

void controlGreen() {
    unsigned long currentTime = millis();
    if (currentTime - prevTime > potentiometerTime) {
        if (digitalRead(GREEN_LED_PIN) == HIGH) {
            digitalWrite(GREEN_LED_PIN, LOW);
        } else {    
            digitalWrite(GREEN_LED_PIN, HIGH);
        }
        prevTime = currentTime;
    }
}

void controlYellow() {
    analogWrite(YELLOW_LED_PIN, intensity);
}

void setup() {
    // put your setup code here, to run once:
    Wire.begin(SLAVE_ADDR);
    Wire.onReceive(callbackFunction);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

    controlRed();
    controlGreen();
    controlYellow();

}
