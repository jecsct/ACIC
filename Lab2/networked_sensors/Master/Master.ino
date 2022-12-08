#define TEMP_PIN  0;
#define POT_PIN  1;
#define LIGHT_PIN  2;

#define SLAVE_ADDR 8;

int intensity = 0;
int temperature = 0;
int potentiometer = 0;

void sendMessage(int value, int led) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(value);
    Wire.write(led);
    Wire.endTransmission();
}

void readTemperature() {
    temperature = analogRead(TEMP_PIN);
}

void readPotentiometer() {
    int pot analogRead(POT_PIN);
    potentiometer = map(pot, 0, 1023, 2, 20); //Should then be divided by 10
}

void readLight() {
    int light =  analogRead(LIGHT_PIN);
    intensity = map(light, 0, 1023, 0, 255);
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
