int GREEN = 5;
int RED = 4;
int BLUE = 3;
int YELLOW = 2;
int BUTTON = 7;

bool buttonPressed = false;
bool paused = false;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  pinMode(BUTTON, INPUT);
}



void wait () {
  int time = 1000; 

  while (time > 0) {
    
    // Button is being pressed
    while (digitalRead(BUTTON) == HIGH) {      
      buttonPressed = true;
    }

    // Button has been pressed
    if (buttonPressed) {
      paused = !paused;
      buttonPressed = false;
    }

    if (paused)
      time++;

    delay(1);
    time--;
  }
}



void loop() {
  // Red
  digitalWrite(RED, HIGH);

  wait();

  // Green
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);

  wait();

  // Blue
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);

  wait();

  // Yellow
  digitalWrite(BLUE, LOW);
  digitalWrite(YELLOW, HIGH);

  wait();

  digitalWrite(YELLOW, LOW);

  wait();

}
