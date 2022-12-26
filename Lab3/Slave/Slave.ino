#include <Wire.h>

//Adress of the slave arduino
#define SLAVE_ADDR 8

//inner semaphore
int inner_sem[]= {5,6,7}
//outter semaphore
int outer_sem[]= {8,9,10}
//pedrestrian semaphore
int ped_sem[]= {11,12}
//Pin for the pedestrian button
#define PED_BUTTON 13

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

void callbackFunction() {

}


void setup(){
  semaphores_setup();
  Wire.onReceive(callbackFunction);

}

void loop(){

}