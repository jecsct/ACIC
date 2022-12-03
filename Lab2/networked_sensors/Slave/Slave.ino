#define SLAVE_ADDR  8;
#define RED_LED_PIN  1;
#define GREEN_LED_PIN  1;
#define YELLOW_LED_PIN  1;

int temp;
int pot;
int light;

int potTime;
int potState;

void callbackFunction(int i) {
     while (1 < Wire.available()) {
           // make sure there is something to read
           char c = Wire.read(); // read the next byte as a char
           Serial.print(c);
     }
     int x = Wire.read();
     Serial.println(x);
}


void checkRed() {
    if (temp > 26) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
    } else {
        digitalWrite(YELLOW_LED_PIN, LOW);
    }
}

void checkGreen() {
    // int time = (int)(pot / 1023 * 1.8 + 0.2);
    int time = map(pot, 0, 1023, 0.2, 2);
    unsigned long currentTime = millis() 
    if (currentTime - potTime > time) {
        if (potState) {
            digitalWrite(GREEN_LED_PIN, LOW);
        } else {
            digitalWrite(GREEN_LED_PIN, HIGH);
            potState = 0;
            potTime = millis();
        }
    }
}

void checkYellow() {
    // int intensity = (int)(light / 1023 * 255);
    int intensity = map(light, 0, 1023, 0, 255);
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

    checkRed();
    checkGreen();
    checkYellow();

}
