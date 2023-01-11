#include <Wire.h>

//Adress of the slave arduino
#define SLAVE_ADDR 1

//Time period for yellow light
#define YELLOW_TIMER 500

//inner semaphore
const int inner_sem[]= {5,6,7};
//outter semaphore
const int outer_sem[]= {8,9,10};
//pedrestrian semaphore
const int ped_sem[]= {11,12};
//Pin for the pedestrian button
#define PED_BUTTON 13
//Indicates if pedestrian clicked the pedestrian button this cycle
bool pedestrian_clicked = false;
// When the state last changed
unsigned long change_timer = millis();

unsigned long lastCom = millis();


//Defines if system is on or off 
bool power = false;

const int off_blink_timer=500;

int received_message = 0;
int received_message_entry_number = 0;

int status[] = {0,0,0,0,0,0,0,0};


//Indicates the mode in which the system is working on
int state = 2; //API OFF


void semaphores_setup(){
  for ( int i = 0 ; i < 3 ; i++){
    pinMode(inner_sem[i], OUTPUT); 
  }
  for ( int i = 0 ; i < 3 ; i++){
    pinMode(outer_sem[i], OUTPUT); 
  }
  for ( int i = 0 ; i < 2 ; i++){
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

void powerOff(){
  for ( int i = 0 ; i < 3 ; i++){
    setLEDPower(inner_sem[i], false); 
  }
  for ( int i = 0 ; i < 3 ; i++){
    setLEDPower(outer_sem[i], false); 
  }
  for ( int i = 0 ; i < 2 ; i++){
    setLEDPower(ped_sem[i], false); 
  }
}

void processMessage(int *array){
  received_message_entry_number = array[0];
  received_message = array[1];

  switch(received_message){
    case 0:{ // API_RED
      // Serial.println("RED");
      power=true;
      state = 0;
      break;
    }
    case 1:{ //API_GREEN
      // Serial.println("GREEN");
      power=true;
      state = 1;
      break;
    }
    case 2:{ //API_OFF
      state = 2;
      power=false;
      // Serial.println("OFF");
      break;
    }
  }
}

void receiveEvent(){

  // Serial.println("RECEBI MENSAEGM");

  int *array = new int[4];
  int i = 0;
  while(1 < Wire.available()) { 
    lastCom = millis();
    array[i++] = Wire.read();
  }
  array[i] = Wire.read();
  processMessage(array);
  // free(array);
  delete[] array;
}

void requestEvent(){

  int *array = getApiMessageResponse(received_message, 0, received_message_entry_number,binToInt(status));

  for(int i = 1; i < array[0]; i++){
    Serial.println(array[i]);
    Wire.write(array[i]);
  }
  Serial.print("Acabei de enviar");
  Serial.println(array[6]);
  resetButtonStatus();
  delete[] array;
}


void resetButtonStatus()
{
  status[6]=0;
}


// Converts a binary array to a decimal integer
int binToInt(int *array) {
  int res = 0;
  for (int i = 0; i < 8; i++) {
    res += array[i] * pow(2, 7-i);
  }
  // Serial.print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA  ");
  // Serial.println(res);
  return res;
}


// pedestRedFailing, pedestYellowFailing, pedestGreenFailing, redFailing, yellowFailing, greenFailing, timerActivated, 0]
void checkStatus() {
  for(int i = 0; i < 3; i++){
    //int s = digitalRead(ped_sem[i]);
    int s = 0;
    status[i] = s;
  }

   for(int i = 0; i < 3; i++){
    //int s = digitalRead(inner_sem[i]);
    int s = 0;
    status[i+3] = s;
  }

  status[7] = 0;
}

void checkPedestrianButton(){
  int value = digitalRead(PED_BUTTON);
  if ( value == HIGH) {
  // Serial.print("BBBBBBBBBBBBBBB: ");
  // Serial.println(value);
    status[6] = 1;
  }

}

void setup(){
  Serial.begin(9600);
  semaphores_setup();
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop(){
  if (millis() > lastCom + 1000) {
    state = getApiOff();
  }

  if (power){
    checkPedestrianButton();
    checkStatus();
    if (state == 10) {
      change_timer = millis();
    }
    switch(state){
    case 0:{ // API_RED

      setLEDPower(outer_sem[2], false); // outer green off
      setLEDPower(inner_sem[0], false); // inner red off

      if (millis() < change_timer + 500) {
        setLEDPower(outer_sem[1], true);  // outer yellow on
        setLEDPower(inner_sem[1], true);  // inner yellow on
        break;
      }
      
      setLEDPower(inner_sem[1], false); // inner yellow off
      setLEDPower(outer_sem[1], false); // outer yellow off
      
      setLEDPower(outer_sem[0], true);  // outer red on
      setLEDPower(inner_sem[2], true); // inner green on

      setLEDPower(ped_sem[0], false);  //ped red off
      setLEDPower(ped_sem[1], true);   // ped green on

      status[6] = 0;

      state = 10;
      break;
    }
    case 1:{ //API_GREEN
      setLEDPower(outer_sem[0], false); // outer green off
      setLEDPower(inner_sem[2], false); // inner red off

      if (millis() < change_timer + 500) {
        setLEDPower(outer_sem[1], true);  // outer yellow on
        setLEDPower(inner_sem[1], true);  // inner yellow on
        break;
      }

      setLEDPower(inner_sem[1], false); // inner yellow off
      setLEDPower(outer_sem[1], false); // outer yellow off
      
      setLEDPower(outer_sem[2], true);  // outer red on
      setLEDPower(inner_sem[0], true); // inner green on

      setLEDPower(ped_sem[1], false);  //ped red off
      setLEDPower(ped_sem[0], true);   // ped green on

      state = 10;
      break;
    }
    case 2:{ //API_OFF

      powerOff();

      power=false;
      Serial.println("OFF");
      break;
    }
  }

  }else{
    
    powerOff();


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