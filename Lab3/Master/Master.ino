#include <Wire.h>

//Adress of the slave arduino
#define SLAVE_ADDR 8

//Pin do LED vermelho que indica se o sistema esta ligado ou nao
#define POWER_LED 3
//Pin do LED azul da comunicacao
#define COM_LED 4

//Pin do potenciometer
#define POT_PIN A0 
//Reading from the potenciometer
int potentiometer = 0;


//Defines if system is on/off
bool power;

//Defines the wait timer in-between semaphore phases
int wait_timer;
//Minimum timer for semaphore phase
#define MIN_TIMER 2
//Maximum timer for semaphore phase
#define MAX_TIMER 15


void comLEDUpdate(bool output){
  if (output){
    digitalWrite(COM_LED,HIGH);
  }else{
    digitalWrite(COM_LED,LOW);
  }
} 

//Turns the power led on/and of depending on the power variable
void powerLEDUpdate(){
  if (power){
    digitalWrite(COM_LED,HIGH);
  }else{
    digitalWrite(COM_LED,LOW);
  }
}

void sendMessage(char[] value) {
    Wire.beginTransmission(SLAVE_ADDR);
    comLEDUpdate(true);
    Wire.write(value);
    comLEDUpdate(false);
    Wire.endTransmission();
}

void sendMessage() {
  Wire.beginTransmission(entryNumber);
  Wire.write(message);
  Wire.endTransmission();
  Wire.requestFrom(entryNumber, 1);
  while(Wire.avaliable()) {
    char c = Wire.read();
    Serial.print(c)
  }
}


//Reads and converts the potenciomenter value to miliseconds
void readPotentiometer() {
    int pot_read = analogRead(POT_PIN);
    wait_timer = map(pot_read, 0, 1023, 2, 15) * 1000; // convert to [2, 15] interval
}


void setup(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(POWER_LED, OUTPUT); 
  pinMode(COM_LED, OUTPUT); 
  power=false;
  wait_timer=2000;
}

void loop(){
  powerLEDUpdate();
  readPotentiometer();
}