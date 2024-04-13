#include <SPI.h>
#include <AMIS30543.h>
#include <SparkFun_TB6612.h>

volatile boolean flag2 = false;
volatile int initialMillis = 0;
volatile int startMillis = 0;
volatile int  endMillis = 0;
unsigned int  prevDuration = 0;
unsigned int  duration = 0;
volatile int  durationTemp = 0;
boolean currentState = true;
boolean prevState = true;


//Roll
const uint8_t rollDirPin = 46;
const uint8_t rollStepPin = 45;
const uint8_t rollSlaveSelect = 44;

//Pitch
const uint8_t pitchDirPin = 49;
const uint8_t pitchStepPin = 48;
const uint8_t pitchSlaveSelect = 47;

//Linear
const uint8_t linDirPin = 43;
const uint8_t linStepPin = 42;
const uint8_t linSlaveSelect = 41;

//Flow
const uint8_t sucBtn = 22;
const uint8_t irrBtn = 23;
const uint8_t sucSol = 24;
const uint8_t irrSol = 25;

//DC driver
const uint8_t AIN1 = 2;
const uint8_t BIN1 = 7;
const uint8_t AIN2 = 4;
const uint8_t BIN2 = 8;
const uint8_t PWMA = 5;
const uint8_t PWMB = 6;
const uint8_t STBY = 9;

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

//homing button
const uint8_t homeBtn = 26;

//Analog Pins
const int potPin = 0;
const int x_dir = 1;
const int y_dir = 2;

int val_x;
int val_y;
int potVal;
int prevPotVal;
int homingVal;

int counter = 0;

boolean rollSleepFlag = true;
boolean pitchSleepFlag = true;
boolean linSleepFlag = true;
boolean linToggleFlag = true;
boolean flag = false;
boolean homeFlag = false;

long prevTime = 0;

AMIS30543 rollStepper;
AMIS30543 pitchStepper;
AMIS30543 linStepper;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  rollStepper.init(rollSlaveSelect);
  pitchStepper.init(pitchSlaveSelect);
  linStepper.init(linSlaveSelect);

  digitalWrite(rollStepPin, LOW);
  pinMode(rollStepPin, OUTPUT);
  digitalWrite(rollDirPin, LOW);
  pinMode(rollDirPin, OUTPUT);
  delay(1);

  digitalWrite(pitchStepPin, LOW);
  pinMode(pitchStepPin, OUTPUT);
  digitalWrite(pitchDirPin, LOW);
  pinMode(pitchDirPin, OUTPUT);
  delay(1);

  digitalWrite(linStepPin, LOW);
  pinMode(linStepPin, OUTPUT);
  digitalWrite(linDirPin, LOW);
  pinMode(linDirPin, OUTPUT);
  delay(1);

  rollStepper.resetSettings();
  rollStepper.setCurrentMilliamps(2000);
  rollStepper.setStepMode(8);
  rollStepper.enableDriver();

  pitchStepper.resetSettings();
  pitchStepper.setCurrentMilliamps(1700);
  pitchStepper.setStepMode(16);
  pitchStepper.enableDriver();

  linStepper.resetSettings();
  linStepper.setCurrentMilliamps(1700);
  linStepper.setStepMode(202);
  linStepper.enableDriver();

  pinMode(sucBtn, INPUT_PULLUP);
  pinMode(irrBtn, INPUT_PULLUP);  
  pinMode(homeBtn, INPUT_PULLUP);  

  Serial.begin(9600);

  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);


  pitchStepper.sleep();
  rollStepper.sleep();
//  Homing();
  //rollStepper.sleepStop();

//  /******** Set up timer 2 to call ISR ********/
//  TCCR2A = 0;               // We need no options in control register A
//  //TCCR2B = (1 << CS20);     // Set prescaller to 1
//  TCCR2B = (1 << CS21);       // Set prescaller to 8
//  TIMSK2 = (1 << OCIE2A);   // Set timer to call ISR when TCNT2 = OCRA2
//  OCR2A = 255;               // sets the frequency of the generated wave
//  // Enable interrupts to generate waveform!
  //
  /******** Set up timer 1 to call ISR ********/
  TCCR1A = 0;               // We need no options in control register A
  TCCR1B = (1 << CS10);     // Set prescaller to 1
  //TCCR2B = (1 << CS21);       // Set prescaller to 8
  TIMSK1 = (1 << OCIE1A);   // Set timer to call ISR when TCNT1 = OCRA1
  OCR1AL = 1;               // sets the frequency of the generated wave
  sei();                    // Enable interrupts to generate waveform!

}
void loop() {

 
    

  
  
//if (digitalRead(homeBtn) == 0){
//  prevTime = millis();
//  while (digitalRead(homeBtn) == 0){
//    if (millis() - prevTime > 500){
//      Homing();
//      //prevTime = millis();
//    }
//  }
//  
//}
  
  ///////////////////////////////// ROLL ////////////////////////////////////////////////

  if (val_x == 0) {
    rollStepper.sleepStop();
    rollSleepFlag = true;
    rollSetDir(0);
    rollStep();
  }
  else if (val_x >= 1000) {
    rollStepper.sleepStop();
    rollSleepFlag = true;
    rollSetDir(1);
    rollStep();
  }
  else if (val_x >= 450 && val_x <= 550) {
    if (rollSleepFlag == true) {
      rollStepper.sleep();
      rollSleepFlag = false;
    }
  }

  /////////////////////////////////// PITCH ////////////////////////////////////////////////

  if (val_y == 0) {
    pitchStepper.sleepStop();
    pitchSleepFlag = true;
    pitchSetDir(0);
    pitchStep();
  }
  else if (val_y >= 800) {
    pitchStepper.sleepStop();
    pitchSleepFlag = true;
    pitchSetDir(1);
    pitchStep();
  }
  else if (val_y >= 450 && val_y <= 550) {
    if (pitchSleepFlag == true) {
      pitchStepper.sleep();
      pitchSleepFlag = false;
    }
  }

  /////////////////////////////////// LINEAR ///////////////////////////////////////////////
//  if (linSleepFlag == true) {
//    linStepper.sleep();
//    linSleepFlag = false;
//  }

  /////////////////////////////////// FLOW ///////////////////////////////////////////////


//  if (digitalRead(sucBtn) == LOW)
//    motor1.drive(255);
//  else
//    motor1.brake();
//
//  if (digitalRead(irrBtn) == LOW)
//    motor2.drive(255);
//  else
//    motor2.brake();

}

//void Homing() {
//  //homeFlag = true;
//  linSetDir(1); //0 is away
//  for (int i = 0; i < 50; i++)
//    potVal = analogRead(potPin);
//  homingVal = map(potVal, 1023, 0, 0, 5000);
//
//  while (digitalRead(homeBtn) == 1)
//    linStep();
//
//  linSetDir(0);
//
//  for (int i = 0; i < homingVal; i++) {
//    linStep();
//  }
//
//  prevPotVal = potVal;
//  //homeFlag = false;
//
//}


//ISR(TIMER2_COMPA_vect) {  // Called each time TCNT2 == OCR2A
//    if (flag == 1) {
//      homingVal = map(abs(potVal - prevPotVal), 0, 1023, 0, 5000);
//      for (int i = 0; i < homingVal; i++) {
//        linStep();
//      }
//      prevPotVal = potVal;
//      flag = 0;
//    }
//}


ISR(TIMER1_COMPA_vect) {
//  potVal = analogRead(potPin);
  val_x = analogRead(x_dir);
  val_y = analogRead(y_dir);
//      if (abs(potVal - prevPotVal) < 50) { //add a buffer in case the number drifts
//      //do nothing
//        linSleepFlag = true;
//        flag = 0;
//      }
//      else {
//        linStepper.sleepStop();
//        if (potVal < prevPotVal)
//          linSetDir(0);
//        else
//          linSetDir(1);
//        flag = 1;
//      }
}
