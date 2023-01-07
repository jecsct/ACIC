#include <Wire.h>

//Array with adresses of the slaves (roundabout entrys) 
const int slave_addresses[] = {/*0, */1/*, 2, 3*/};
//Number of roundabout entrys
#define NUMBER_OF_ENTRIES 1

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


#define POWER_BUTTON 2
//Defines if system is on/off
bool power;
//Indicates if button has pressed or not
bool buttonPressed = false;

//Minimum timer for semaphore phase
#define MIN_TIMER 2
//Maximum timer for semaphore phase
#define MAX_TIMER 15

//Indicates whether or not it is the first time that the semaphores are being controlled after the system was turned on
bool first_time = true;
//Indicates when the entry to the roundbout changed
unsigned long change_timer = millis();
//Indicates the semaphore that shoukd be turned to green
int currentGreenEntrySemaphore = 0;


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
  for ( int i = 0 ; i < 2 ; i++){
    pinMode(ped_sem[i], OUTPUT); 
  }
  pinMode(PED_BUTTON, INPUT); 
  pinMode(POWER_BUTTON,INPUT);

  pinMode(POWER_LED, OUTPUT); 
  pinMode(COM_LED, OUTPUT); 

}

void turnOnOff(){
  power = !power;
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
  Serial.println("ENVIEI");
  Wire.beginTransmission(entry_number);
  int *array = getApiMessage(message, 0, entry_number);
  for (int i = 1; i < array[0]; i++){
    Wire.write(message);
  }
  Wire.endTransmission();
  Wire.requestFrom(entry_number, getMessageResponseSize(message));
  while(Wire.available()) {
    char c = Wire.read();
  }
}

// 
void resetGreenSemaphore() {
  if ( currentGreenEntrySemaphore >= NUMBER_OF_ENTRIES){
    currentGreenEntrySemaphore = 0;
  }
}

//Reads and converts the potenciomenter value to miliseconds
void readPotentiometer() {
    int pot_read = analogRead(POT_PIN);
    entry_timer = map(pot_read, 0, 1023, 2, 15) * 1000; // convert to [2, 15] interval
}

void control() {

    // current_timer = millis();

    if (millis() - change_timer > entry_timer || first_time ) {
      controlSemaphores();
       first_time = false;
      // current_timer = millis();
    }
}

void controlSemaphores() {
  
  for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++){
    if (entry_number != currentGreenEntrySemaphore) {
      sendMessage(getApiRed(), slave_addresses[entry_number]);
    }
  }
  
  sendMessage(getApiGreen(), slave_addresses[currentGreenEntrySemaphore]);
  
  resetGreenSemaphore();

  change_timer = millis();
}

//Sets the system up. Is run one time when the system is first runs
void setup(){
  Serial.begin(9600);
  Wire.begin();
  // pinMode(POWER_LED, OUTPUT); 
  // pinMode(COM_LED, OUTPUT);
  semaphores_setup(); 
  power=false;
  entry_timer=2000;
}

//Checks if the power button was/is pressed
void checkPowerButton () {
    
    // Button is being pressed
    while (digitalRead(POWER_BUTTON) == HIGH) {      
      buttonPressed = true;
    }

    // Button has been pressed
    if (buttonPressed) {
      turnOnOff();
      buttonPressed = false;
    }

}

void loop(){


  while ( true ){

    sendMessage(0, 1);


    delay(5000);

    sendMessage(1,1);
  
    delay(5000);
  }

  // checkPowerButton();

  // if(power){
    
  //   setLEDPower(POWER_LED, true);
  //   readPotentiometer();
    
  //   control();

  // }else{
    
  //   first_time = true;
    
  //   setLEDPower(POWER_LED, false);

  // for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++){
  //     sendMessage(getApiOff(), slave_addresses[entry_number]);
  // }

  //   unsigned long start_time = millis();
  //   unsigned long current_time = millis();

  //   while ( current_time - start_time < off_blink_timer && !power ){
  //     setLEDPower(inner_sem[1], true);
  //     setLEDPower(outer_sem[1], true);
  //     current_time = millis();

  //     checkPowerButton();

  //   }

  //   start_time = millis();
  //   current_time = millis();

  //   while ( current_time - start_time < off_blink_timer && !power ){
  //     setLEDPower(inner_sem[1], false);
  //     setLEDPower(outer_sem[1], false);
  //     current_time = millis();

  //     checkPowerButton();

  //   }

  // }


}