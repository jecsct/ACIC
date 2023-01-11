#include <Wire.h>

//Array with adresses of the slaves (roundabout entrys)
const int slave_addresses[] = { 0, 1 /*, 2, 3*/ };
//Number of roundabout entrys
#define NUMBER_OF_ENTRIES 2
//Controller entry number
#define CONTROLLER_ENTRY 0
//inner semaphore
const int inner_sem[] = { 5, 6, 7 };
//outter semaphore
const int outer_sem[] = { 8, 9, 10 };
//pedrestrian semaphore
const int ped_sem[] = { 11, 12 };
//Pin for the pedestrian button
#define PED_BUTTON 13

//Blink timer when turned off
const int off_blink_timer = 500;

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
// Time of the last communication
unsigned long lastCom = millis();
// Time to wait for response before assuming a fault
const unsigned long timeout_timer = 1000;

//Indicates the state to which the leds will go to
int state = 2;
//Indicates the last state the LEDS were in
int last_state = 2;

int received_message = 0;
int received_message_entry_number = 0;

//Indicates if the peddestrian button was pressed 
bool timer_activated;


// Blinks the communication led
void blinkComLed() {
  digitalWrite(COM_LED, HIGH);
  delay(5);
  digitalWrite(COM_LED, LOW);
}

// Sets up all the pins in the system
void semaphores_setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(inner_sem[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(outer_sem[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(ped_sem[i], OUTPUT);
  }

  pinMode(PED_BUTTON, INPUT);
}

// Sets the variable that tells the program what its behaviour should be (On/Off)
void turnOnOff() {
  power = !power;
}

// Shuts all lights in the system down
void powerOff() {
  power = false;

  for (int i = 0; i < 3; i++) {
    setLEDPower(inner_sem[i], false);
  }
  for (int i = 0; i < 3; i++) {
    setLEDPower(outer_sem[i], false);
  }
  for (int i = 0; i < 2; i++) {
    setLEDPower(ped_sem[i], false);
  }
}

// Updates the state of the semaphore to the one it should be reproducing right now
void updateSemaphore(int *array) {
  received_message_entry_number = array[1];
  received_message = array[2];

  switch (received_message) {
    case 0: // API_RED
      { 
        state = 0;
        break;
      }
    case 1: //API_GREEN
      {  
        state = 1;
        break;
      }
    case 2: //API_OFF
      {  
        state = 2;
        powerOff();
        break;
      }
  }
}

//Sets the output of a given pin based on a bool value
void setLEDPower(int pinEntry, bool output) {
  if (output) {
    digitalWrite(pinEntry, HIGH);
  } else {
    digitalWrite(pinEntry, LOW);
  }
}

//handles the event where the pedestrian button was clicked
void handleTimerActivated() {
  if (!timer_activated) {
    timer_activated = true;
    change_timer = change_timer - ((entry_timer - (millis() - change_timer)) / 2);
  }
}

void handleLedError() {
}

//processes the PING response(STATUS) from the slaves
void processResponse(int *array) {

  if (array[0] == getApiStatus()) {
    int *info = new int[8];
    intToBin(array[2], info);
    for (int i = 0; i < 5; i++) {
      if (info[i] == 1) {
        handleLedError();
      }
    }
    if (info[6] == 1) {
      handleTimerActivated();
    }
    delete[] info;
  }
}


// Converts a decimal integer to a binary array
void *intToBin(int num, int *info) {
  for (int i = 7; num >= 0 && i >= 0; i--) {
    info[i] = num % 2;
    num = num / 2;
  }
}

//Sends and receives a message to a given address number
void sendMessage(char message, int entry_number) {
  if (entry_number == 0 && message != getApiStatus()) {
    int *array = getApiMessage(message, CONTROLLER_ENTRY, entry_number);
    blinkComLed();
    updateSemaphore(array);
    delete[] array;
  } else {

    Wire.beginTransmission(entry_number);
    int *array = getApiMessage(message, CONTROLLER_ENTRY, entry_number);

    for (int i = 1; i < array[0]; i++) {
      blinkComLed();
      Wire.write(array[i]);
    }

    Wire.endTransmission();
    Wire.requestFrom(entry_number, getMessageResponseSize(message));
    int idx = -1;
    int *response_array;
    while (Wire.available()) {
        blinkComLed();
        lastCom = millis();
        int c = Wire.read();
        if (idx == -1) {
          response_array = new int[c];
        } else {
          response_array[idx] = c;
        }
        idx++;
    }

    processResponse(response_array);
    delete[] response_array;
    delete[] array;
  }
}

// Resest the variable *currentGreenEntrySemaphore* if it is equal or greater than the number of toundabout entrys in the current system
void resetGreenSemaphore() {
  if (currentGreenEntrySemaphore >= NUMBER_OF_ENTRIES) {
    currentGreenEntrySemaphore = 0;
  }
}

//Reads and converts the potenciomenter value to miliseconds
void readPotentiometer() {
  int pot_read = analogRead(POT_PIN);
  entry_timer = map(pot_read, 0, 1023, 2, 15) * 1000;  // convert to [2, 15] interval
}

// Checks if it is time to change the state of the roundabout
void control() 
{
  if (millis() - change_timer > entry_timer || first_time) {

    timer_activated = false;
    first_time = false;

    controlSemaphores();

    currentGreenEntrySemaphore++;
  }

}

//Sends pings to every slave address
void sendPings() { 
  for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++) {
    sendMessage(getApiPing(), slave_addresses[entry_number]);
  }
}

//changes the state of the roundabout
void controlSemaphores()  {
  for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++) 
  {
    if (entry_number != currentGreenEntrySemaphore) 
    {
      sendMessage(getApiRed(), slave_addresses[entry_number]);
    }
  }

  sendMessage(getApiGreen(), slave_addresses[currentGreenEntrySemaphore]);

  resetGreenSemaphore();

  change_timer = millis();
}

//Checks if the pedestrian was pressed
void checkPedestrianButton(){
  int value = digitalRead(PED_BUTTON);
  if (value == HIGH) {
    handleTimerActivated();
  }
}

//Sets the system up. Is run one time when the system is first runs
void setup() {
  Serial.begin(9600);
  Wire.begin();
  semaphores_setup();
  pinMode(POWER_BUTTON, INPUT);
  pinMode(POWER_LED, OUTPUT);
  pinMode(COM_LED, OUTPUT);
  power = false;
  entry_timer = 2000;
}

//Checks if the power button was/is pressed
void checkPowerButton() {

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

void loop() {
  if (millis() > lastCom + 1000) {
    powerOff();
  }

  checkPowerButton();

  if (power) {
    checkPedestrianButton();

    setLEDPower(POWER_LED, true);
    readPotentiometer();

    control();
    sendPings();

    switch (state) {
      case 0:
        {  // API_RED
          if (last_state != getApiRed()) {
            setLEDPower(outer_sem[2], false);  // outer green off
            setLEDPower(inner_sem[0], false);  // inner red off

            if (millis() < change_timer + 500) {
              setLEDPower(outer_sem[1], true);  // outer yellow on
              setLEDPower(inner_sem[1], true);  // inner yellow on
              break;
            }

            setLEDPower(inner_sem[1], false);  // inner yellow off
            setLEDPower(outer_sem[1], false);  // outer yellow off

            setLEDPower(outer_sem[0], true);  // outer red on
            setLEDPower(inner_sem[2], true);  // inner green on

            setLEDPower(ped_sem[0], false);  //ped red off
            setLEDPower(ped_sem[1], true);   // ped green on

            last_state = getApiRed();
          }

          state = 10;
          break;
        }

      case 1:
        {  //API_GREEN
          if (last_state != getApiGreen()) {
            setLEDPower(outer_sem[0], false);  // outer green off
            setLEDPower(inner_sem[2], false);  // inner red off

            if (millis() < change_timer + 500) {
              setLEDPower(outer_sem[1], true);  // outer yellow on
              setLEDPower(inner_sem[1], true);  // inner yellow on
              break;
            }

            setLEDPower(inner_sem[1], false);  // inner yellow off
            setLEDPower(outer_sem[1], false);  // outer yellow off

            setLEDPower(outer_sem[2], true);  // outer red on
            setLEDPower(inner_sem[0], true);  // inner green on

            setLEDPower(ped_sem[1], false);  //ped red off
            setLEDPower(ped_sem[0], true);   // ped green on

            last_state = getApiGreen();
          }

          state = 10;
          break;
        }
    }

  } else {

    first_time = true;

    setLEDPower(POWER_LED, false);
    for (int entry_number = 0; entry_number < NUMBER_OF_ENTRIES; entry_number++) {
      sendMessage(getApiOff(), slave_addresses[entry_number]);
    }


    unsigned long start_time = millis();
    unsigned long current_time = millis();

    while (current_time - start_time < off_blink_timer && !power) {
      setLEDPower(inner_sem[1], true);
      setLEDPower(outer_sem[1], true);
      current_time = millis();

      checkPowerButton();
    }

    start_time = millis();
    current_time = millis();

    while (current_time - start_time < off_blink_timer && !power) {
      setLEDPower(inner_sem[1], false);
      setLEDPower(outer_sem[1], false);
      current_time = millis();

      checkPowerButton();
    }
  }
}