#include <Wire.h>

#define SLAVE_ADDR 8

#define RED_LED_PIN 3
#define TEMP_THRESHOLD 26


#define TEMP_PIN A0
#define LIGHT_PIN A1
#define POT_PIN A3

#define LIGHT_MAX 200 // intensity equivalent to sensor under a ceiling light

int light = 0;
int temperature = 0;
int potentiometer = 0;


void sendMessage(char sensor[], int value) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(sensor);
    Wire.write(value);
    Wire.endTransmission();
}

// void readTemperature() {
//     int temp_read = analogRead(TEMP_PIN);
//     temperature = (((temp_read/1024.0) * 5.0) - 0.5) * 100; // convert to celsius
//     sendMessage("T", temperature);
// }
void controlRed() {
    Wire.requestFrom(SLAVE_ADDR, 1);
    
  while (Wire.available() < 1) {
    delay(1);
  }

  // read the data and print it to the serial monitor
  int temperature = Wire.read();
  Serial.println(temperature);
    if (temperature >= TEMP_THRESHOLD) {
        digitalWrite(RED_LED_PIN, HIGH);
    } else {
        digitalWrite(RED_LED_PIN, LOW);
    }
}

void readPotentiometer() {
    int pot_read = analogRead(POT_PIN);
    potentiometer = map(pot_read, 0, 1023, 0, 180); // convert to [0, 180] interval
    sendMessage("P", potentiometer);
}


void readLight() {
    int light_read =  analogRead(LIGHT_PIN);
    light_read = constrain(light_read, 0, LIGHT_MAX);
    light = map(light_read, 0, LIGHT_MAX, 0, 255); // convert to [0, 255] interval
    sendMessage("L", light);
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
       pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
    // readTemperature();
    controlRed();
    readPotentiometer();
    readLight();
}
