#include <Wire.h>

//Adress of the slave arduino
#define SLAVE_ADDR 1

//Time period for yellow light
#define YELLOW_TIMER 500

//inner semaphore
const int outer_sem[]= {5,6,7};
//outter semaphore
const int inner_sem[]= {8,9,10};
//pedrestrian semaphore
const int ped_sem[]= {11,12};
//Pin for the pedestrian button
#define PED_BUTTON 13
//Indicates if pedestrian clicked the pedestrian button this cycle
bool pedestrian_clicked = false;

//Defines if system is on or off 
bool power = false;

const int off_blink_timer=500;

int received_message = 0;
int received_message_entry_number = 0;

int *status = new int[7];


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
      power=true;
      state = 0;
      break;
    }
    case 1:{ //API_GREEN
      power=true;
      state = 1;
      break;
    }
    case 2:{ //API_OFF
      state = 2;
      power=false;
      Serial.println("OFF");
      break;
    }
  }
}

void receiveEvent(){

  Serial.println("RECEBI MENSAEGM");

  int *array = new int[4];
  int i = 0;
  while(1 < Wire.available()) { 
    array[i++] = Wire.read();
  }
  array[i] = Wire.read();
  processMessage(array);
  // free(array);
  delete[] array;
}

void requestEvent(){
  int *array = getApiMessageResponse(received_message, 0, received_message_entry_number,255);
  // Serial.println("Comecei a enviar");
  // Serial.print("received_message ");
  // Serial.println(received_message);
  // Serial.print("receive message entry number ");
  // Serial.println(received_message_entry_number);
  // Serial.print("response size ");
  // Serial.println(array[0]);

  for(int i = 1; i < array[0]; i++){
    Serial.println(array[i]);
    Wire.write(array[i]);
  }
  Serial.println("Acabei de enviar");
  delete[] array;
}

// Converts a binary array to a decimal integer
int binToInt(int *array) {
  int res = 0;
  for (int i = 0; i < 8; i++) {
    res += array[i] * pow(2, 7-i);
  }
  return res;
}


// pedestRedFailing, pedestYellowFailing, pedestGreenFailing, redFailing, yellowFailing, greenFailing, timerActivated, 0]
void checkStatus() {
  for(int i = 1; i < 2; i++){
    int s = digitalRead(ped_sem[i]);
    //int s = 0;
    status[i] = s;
  }

   for(int i = 1; i < 3; i++){
    // int s = digitalRead(inner_sem[i]);
    int s = 0;
    status[i+2] = s;
  }
}

void checkPedestrianButton(){
  int value = digitalRead(PED_BUTTON);
  if ( value == HIGH) {
  Serial.print("BBBBBBBBBBBBBBB: ");
  Serial.println(value);
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

  if (power){
    checkPedestrianButton();
    switch(state){
    case 0:{ // API_RED

      setLEDPower(outer_sem[2], false); // outer green off
      setLEDPower(inner_sem[0], false); // inner red off

      setLEDPower(outer_sem[1], true);  // outer yellow on
      setLEDPower(inner_sem[1], true);  // inner yellow on

      delay(500);
      
      setLEDPower(inner_sem[1], false); // inner yellow off
      setLEDPower(outer_sem[1], false); // outer yellow off
      
      setLEDPower(outer_sem[0], true);  // outer red on
      setLEDPower(inner_sem[2], true); // inner green on

      setLEDPower(ped_sem[1], false);  //ped red off
      setLEDPower(ped_sem[0], true);   // ped green on

      status[6] = 0;

      state = 10;
      break;
    }
    case 1:{ //API_GREEN
      setLEDPower(outer_sem[0], false); // outer green off
      setLEDPower(inner_sem[2], false); // inner red off

      setLEDPower(outer_sem[1], true);  // outer yellow on
      setLEDPower(inner_sem[1], true);  // inner yellow on
      
      delay(500);

      setLEDPower(inner_sem[1], false); // inner yellow off
      setLEDPower(outer_sem[1], false); // outer yellow off
      
      setLEDPower(outer_sem[2], true);  // outer red on
      setLEDPower(inner_sem[0], true); // inner green on

      setLEDPower(ped_sem[0], false);  //ped red off
      setLEDPower(ped_sem[1], true);   // ped green on

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