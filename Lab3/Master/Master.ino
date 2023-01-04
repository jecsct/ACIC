#include <Wire.h>

//Adress of the slave arduino
#define SLAVE_ADDR 8


//inner semaphore
const int inner_sem[]= {5,6,7};
//outter semaphore
const int outer_sem[]= {8,9,10};
//pedrestrian semaphore
const int ped_sem[]= {11,12};
//Pin for the pedestrian button
#define PED_BUTTON 13

const int off_blink_timer=500;


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
//Number of outside semaphores
#define NUMBER_OF_ENTRIES 4 


int timer = millis();
int currentGreenSemaphore = 0;


void semaphores_setup(){
  for ( int i = 0 ; i < 3 ; i++){
    pinMode(inner_sem[i], OUTPUT); 
  }
  for ( int i = 0 ; i < 3 ; i++){
    pinMode(outer_sem[i], OUTPUT); 
  }
  for ( int i = 0 ; i < 3 ; i++){
    pinMode(ped_sem[i], OUTPUT); 
  }
  pinMode(PED_BUTTON, INPUT); 


  pinMode(POWER_LED, OUTPUT); 
  pinMode(COM_LED, OUTPUT); 

}

void setLEDPower(int pinEntry, bool output){
  if (output){
    digitalWrite(pinEntry,HIGH);
  }else{
    digitalWrite(pinEntry,LOW);
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

void sendMessage(char value) {
    Wire.beginTransmission(SLAVE_ADDR);
    setLEDPower(COM_LED, true);
    Wire.write(value);
    setLEDPower(COM_LED,false);
    Wire.endTransmission();
}

void sendMessage() {
  // Wire.beginTransmission(entryNumber);
  // Wire.write(message);
  // Wire.endTransmission();
  // Wire.requestFrom(entryNumber, 1);
  // while(Wire.avaliable()) {
  //   char c = Wire.read();
  //   Serial.print(c);
  // }
}

// resets the state of the controller so that is ready to start from scratch
void reset() {

}

//Reads and converts the potenciomenter value to miliseconds
void readPotentiometer() {
    int pot_read = analogRead(POT_PIN);
    wait_timer = map(pot_read, 0, 1023, 2, 15) * 1000; // convert to [2, 15] interval
}

void control() {
  if (power) {
    if (millis() - timer > wait_timer) {
      controlSemaphores();

    }
  }
}

void controlSemaphores() {
  // int i = 0;
  // while (i < NUMBER_OF_ENTRIES) {
  //   if (i != currentGreenSemaphore) {
  //     sendMessage(API_RED, i);
  //   }
  //   i++;
  // }
  // sendMessage(API_GREEN, currentGreenSemaphore);
}


void setup(){
  Serial.begin(9600);
  Wire.begin();
  // pinMode(POWER_LED, OUTPUT); 
  // pinMode(COM_LED, OUTPUT);
  semaphores_setup(); 
  power=false;
  wait_timer=2000;
}

void loop(){
  if(power){
    powerLEDUpdate();
    readPotentiometer();
    control();
  }else{
    unsigned long start_time = millis();
    unsigned long current_time = millis();

    while ( current_time - start_time < off_blink_timer && !power ){
      setLEDPower(inner_sem[1], true);
      setLEDPower(outer_sem[1], true);
      current_time = millis();
    }

    start_time = millis();
    current_time = millis();

    while ( current_time - start_time < off_blink_timer && !power ){
      setLEDPower(inner_sem[1], false);
      setLEDPower(outer_sem[1], false);
      current_time = millis();
    }

  }
}