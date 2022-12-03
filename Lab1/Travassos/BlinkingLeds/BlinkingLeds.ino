const int myPins[] = {3, 4, 5, 6};
const int numberLEDs = 4;

unsigned long previousMillis = 2;
const long interval = 1000;

int buttonPin =7;
int buttonRead;

void setup() {
  for(int i = 0; i < numberLEDs; i++){
    pinMode(myPins[i], OUTPUT); 
  }
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonRead=digitalRead(buttonPin);
  while ( buttonRead == 1 ) { 
    buttonRead=digitalRead(buttonPin); 
    Serial.println(buttonRead);  
  }
  Serial.println(buttonRead);
  previousMillis = millis();
  for(int i = 0; i< numberLEDs; i++){
    digitalWrite(myPins[i], HIGH);  // sets the LED on
    
    unsigned long currentMillis = millis();
    
    while (currentMillis - previousMillis < interval) { 
      currentMillis = millis();
    }

    buttonRead = digitalRead( buttonPin );
    while (buttonRead == 1) { 
      buttonRead=digitalRead(buttonPin); 
    }

    digitalWrite( myPins[i], LOW );   // sets the LED off
    currentMillis = millis();
    previousMillis = currentMillis;

  }
    

  buttonRead=digitalRead(buttonPin);
  while ( buttonRead == 1 ){ buttonRead=digitalRead(buttonPin); }

  unsigned long currentMillis = millis();

  while ( currentMillis - previousMillis < interval ) {
    currentMillis = millis();
  }

  previousMillis = currentMillis;
  
}

