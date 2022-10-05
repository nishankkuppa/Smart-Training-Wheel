#include <Stepper.h>

#define hallEffectSensor 2

// 1.8 degree per step
// 200 steps in one revolution
const int stepsPerHalfRevolution = 100;  // the motor should toggle between two states, active and stowed
int wheelRevolutions = 0;   // number of times the wheel spins
int velocity = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;  // 10 seconds

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerHalfRevolution, 8, 9, 10, 11);

void setup()
{
  // set the speed at 30 rpm:
  //myStepper.setSpeed(30);

  pinMode(hallEffectSensor, INPUT_PULLUP);
  startMillis = millis();  //initial start time

  // initialize the serial port:
  Serial.begin(9600);
}

void loop()
{
  wheelRevolutions = digitalRead(hallEffectSensor);
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

  // update velocity every 10 seconds
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    velocity = wheelRevolutions;
    startMillis = currentMillis;    // reset the timer
  }

  if (velocity > 15)
  {
    Serial.println("active");
    myStepper.step(stepsPerHalfRevolution);
    delay(500);
  }
  else
  {
    // step one revolution in the stowed position:
    Serial.println("stowed");
    myStepper.step(-stepsPerHalfRevolution);
    delay(500);
  }

  // reset the velocity
  velocity = 0;
}

