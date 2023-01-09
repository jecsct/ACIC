//car semaphore array structure
#define CAR_RED 0
#define CAR_YELLOW 1
#define CAR_GREEN 2

//pedestrian semaphore array struture
#define PED_RED 0
#define PED_GREEN 1


void setOutputSemaphores(int* pins, int length){
  for (int i = 0 ; i < length ; i++ )
  {
    pinMode(pins[i], OUTPUT);
  }
}

void setInputSemaphores ( int pins[], int length) 
{
  for (int i = 0 ; i < length ; i++ )
  {
    pinMode(pins[i], INPUT);
  }
}

void powerOn( int pins[], int length)
{
  for (int i = 0 ; i < length ; i++ )
  {
    digitalWrite(pins[i], HIGH);
  }
}

void powerOff ( int pins[], int length ) 
{
  for (int i = 0 ; i < length ; i++ )
  {
    digitalWrite(pins[i], LOW);
  }
}

setLEDPower(int pin, bool power)
{
  if (power){
    digitalWrite(pin,HIGH);
  }else{
    digitalWrite(pin,LOW);
  }
}

void blinkLED(int pin, int delay)
{
  digitalWrite(pin, HIGH);
  delay(delay);
  digitalWrite(pin, LOW);
}

void turnRED( int outer[], int inner[], int ped[] )
{
  digitalWrite(outer_sem[CAR_GREEN], LOW); // outer green off
  digitalWrite(inner_sem[CAR_RED], LOW); // inner red off

  digitalWrite(outer_sem[CAR_YELLOW], HIGH);  // outer yellow on
  digitalWrite(inner_sem[CAR_YELLOW], HIGH);  // inner yellow on

  delay(500);
  
  digitalWrite(inner_sem[CAR_YELLOW], LOW); // inner yellow off
  digitalWrite(outer_sem[CAR_YELLOW], LOW); // outer yellow off

  digitalWrite(outer_sem[CAR_RED], HIGH);  // outer red on
  digitalWrite(inner_sem[CAR_GREEN], HIGH); // inner green on

  digitalWrite(ped_sem[PED_RED], LOW);  //ped red off
  digitalWrite(ped_sem[PED_GREEN], HIGH);   // ped green on
}

void turnGREEN( int outer[], int inner[], int ped[] )
{
  digitalWrite(outer_sem[CAR_RED], LOW); // outer red off
  digitalWrite(inner_sem[CAR_RED], LOW); // inner gree off

  digitalWrite(outer_sem[CAR_YELLOW], HIGH);  // outer yellow on
  digitalWrite(inner_sem[CAR_YELLOW], HIGH);  // inner yellow on
  
  delay(500);

  digitalWrite(inner_sem[CAR_YELLOW], LOW); // inner yellow off
  digitalWrite(outer_sem[CAR_YELLOW], LOW); // outer yellow off

  digitalWrite(outer_sem[CAR_GREEN], HIGH);  // outer green on
  digitalWrite(inner_sem[CAR_RED], HIGH); // inner red on

  digitalWrite(ped_sem[1], LOW);  //ped green off
  digitalWrite(ped_sem[0], HIGH);   // ped red on
}

