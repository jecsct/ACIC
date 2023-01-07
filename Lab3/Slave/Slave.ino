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

//Defines if system is on or off 
bool power = false;

const int off_blink_timer=500;

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
}

void setLEDPower(int pinEntry, bool output){
  if (output){
    digitalWrite(pinEntry,HIGH);
  }else{
    digitalWrite(pinEntry,LOW);
  }
}

void receiveEvent(){

}

void requestEvent(){
  // Wire.write(/*resposta*/);
}

void setup(){
  semaphores_setup();
  Wire.begin();
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop(){
  if (power){
    // fazer algo ligado
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