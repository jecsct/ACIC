#include <Wire.h>

#define SLAVE_ADDR  8

#define GREEN_LED_PIN 2
#define RED_LED_PIN 3
#define YELLOW_LED_PIN 5

#define BLINK_MIN_PERIOD 200
#define BLINK_MAX_PERIOD 2000
#define TEMP_THRESHOLD 26


#define TEMP_PIN A0

int potentiometer;
int temperature;
int light;

unsigned long prevTime = 0;


void callbackFunction(int i) {
    char c;
    while (1 < Wire.available()) {
          // make sure there is something to read
          c = Wire.read(); // read the next byte as a char
    }
    int x = Wire.read(); // read the next byte as an  int

    if (c == 'T') {
      temperature = x;
    } else if (c == 'L') {
      light = x;
    } else if (c == 'P') {
      potentiometer = x;
    }
}


// void controlRed() {
//     if (temperature >= TEMP_THRESHOLD) {
//         digitalWrite(RED_LED_PIN, HIGH);
//     } else {
//         digitalWrite(RED_LED_PIN, LOW);
//     }
// }

void controlGreen() {
    int blink_period = map(potentiometer, 0, 180, BLINK_MIN_PERIOD/2, BLINK_MAX_PERIOD/2);
    unsigned long currentTime = millis();
    
    if (currentTime > prevTime + blink_period) {
        if (digitalRead(GREEN_LED_PIN) == HIGH) {
            digitalWrite(GREEN_LED_PIN, LOW);
        } else {    
            digitalWrite(GREEN_LED_PIN, HIGH);
        }
        prevTime = currentTime;
    }
}

void controlYellow() {
    analogWrite(YELLOW_LED_PIN, 255-light);
}

void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDR);
    Wire.onReceive(callbackFunction);

    Wire.onRequest(sendData);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
}


void sendData() {
  Wire.write(temperature);  // send a message to the master
}

void readTemperature() {
    int temp_read = analogRead(TEMP_PIN);
    temperature = (((temp_read/1024.0) * 5.0) - 0.5) * 100; // convert to celsius
    // sendMessage("T", temperature);
}

void loop() {
    // controlRed();
    controlGreen();
    controlYellow();
    readTemperature();
}
