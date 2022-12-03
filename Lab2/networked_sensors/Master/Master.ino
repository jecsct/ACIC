#define TEMP_PIN  0;
#define POT_PIN  1;
#define LIGHT_PIN  2;

#define SLAVE_ADDR 8;


void sendMessage(int value, int led) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(value);
    Wire.write(led);
    Wire.endTransmission();
}

int readTemperature() {
    return analogRead(TEMP_PIN);
}

int readPotentiometer() {
    return analogRead(POT_PIN);
}

int readLight() {
    return analogRead(LIGHT_PIN);
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
