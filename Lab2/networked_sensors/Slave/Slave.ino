#include <Wire.h>

#define SLAVE_ADDR  8
#define GREEN_LED_PIN 2
#define RED_LED_PIN 3
#define YELLOW_LED_PIN 4

int potentiometerTime = 200;
int temperature = 20;
int intensity = 240;

int prevTime = 0;

void callbackFunction(int i) {
    char c;
    while (1 < Wire.available()) {
          // make sure there is something to read
          c = Wire.read(); // read the next byte as a char
    }
    int x = Wire.read();

    if (c == 'T') {
      temperature = x;
    } else if (c == 'L') {
      intensity = x;
    } else if (c == 'P') {
      potentiometerTime = x;
      Serial.println(x);

    }
    
}


void controlRed() {
    float temp = (temperature * 0.48828125) - 32;
    float cel = (( temperature * 4.8828125  ) - 97.65625 ) * 0.1  - 40 ;
    if (cel > 26) {
        digitalWrite(RED_LED_PIN, HIGH);
    } else {
        digitalWrite(RED_LED_PIN, LOW);
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
    analogWrite(YELLOW_LED_PIN, 255-intensity);
}

void setup() {
    // put your setup code here, to run once:
    Wire.begin(SLAVE_ADDR);
    Wire.onReceive(callbackFunction);
    Serial.begin(9600);
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
