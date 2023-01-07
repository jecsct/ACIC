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

//Blink timer when turned off
const int off_blink_timer=500;


//Pin do LED vermelho que indica se o sistema esta ligado ou nao
#define POWER_LED 3
//Pin do LED azul da comunicacao
#define COM_LED 4

//Pin do potenciometer
#define POT_PIN A0 
//Reading from the potenciometer
int potentiometer = 0;
//Defines the wait timer in-between roundabout entrys
int entry_timer;


//Defines if system is on/off
bool power;

//Minimum timer for semaphore phase
#define MIN_TIMER 2
//Maximum timer for semaphore phase
#define MAX_TIMER 15
//Number of outside semaphores
#define NUMBER_OF_ENTRIES 2


int timer = millis();
int currentGreenSemaphore = 0;

void blinkComLed(){
    digitalWrite(COM_LED,HIGH);
    delay(10);
    digitalWrite(COM_LED,LOW);
}


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



void sendMessage(char message, int entry_number) {
  blinkComLed();
  Wire.beginTransmission(entry_number);
  int *array = getApiMessage(message, 0, entry_number);
  for (int i = 1; i < array[0]; i++){
    Wire.write(message);
  }
  Wire.endTransmission();
  Wire.requestFrom(entry_number, getMessageResponseSize(message));
  while(Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
}
// resets the state of the controller so that is ready to start from scratch
void reset() {

}

//Reads and converts the potenciomenter value to miliseconds
void readPotentiometer() {
    int pot_read = analogRead(POT_PIN);
    entry_timer = map(pot_read, 0, 1023, 2, 15) * 1000; // convert to [2, 15] interval
}

void control() {
    if (millis() - timer > entry_timer) {
      controlSemaphores();
    }
}

void controlSemaphores() {
  int entry_number = 0;
  for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++){
    if (entry_number != currentGreenSemaphore) {
      sendMessage(API_RED, entry_number);
    }
  }
  sendMessage(getApiGreen(), currentGreenSemaphore);
}


void setup(){
  Serial.begin(9600);
  Wire.begin();
  // pinMode(POWER_LED, OUTPUT); 
  // pinMode(COM_LED, OUTPUT);
  semaphores_setup(); 
  power=false;
  entry_timer=2000;
}


void loop(){
  if(power){
    setLEDPower(POWER_LED, true);
    readPotentiometer();
    control();
  }else{
    
    setLEDPower(POWER_LED, false);


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