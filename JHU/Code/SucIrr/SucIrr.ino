#include <SparkFun_TB6612.h>


int motorSpeed = 50;


/******** Serial parameters ********/
char inByte = 0;
int prevByte = 0;
boolean newData = false;
int currentTime;
int prevTime;
bool firstTime = true;
#define NOP __asm__ __volatile__ ("nop\n\t")




// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 10
#define BIN1 8
#define AIN2 11
#define BIN2 7
#define PWMA 5 
#define PWMB 6
#define STBY 9


// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motorA = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor motorB = Motor(BIN1, BIN2, PWMB, 1, STBY);

void setup()
{
  Serial.begin(115200);

  pinMode(buttonIrrPin, INPUT_PULLUP);
  pinMode(buttonSucPin, INPUT_PULLUP);
  pinMode(buttonAnalog, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
   
  pinMode(encoderAPinA, INPUT);
  pinMode(encoderAPinB, INPUT);
  pinMode(encoderBPinA, INPUT);
  pinMode(encoderBPinB, INPUT);

  attachInterrupt(0, doEncoderA, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(1, doEncoderB, CHANGE);
}

void doEncoderA() {
  if (bitRead(PIND, encoderAPinA)^bitRead(PIND, encoderAPinB)) {
    encoderAPos--; //CW
  }
  else {
    encoderAPos++; //CCW
  }
  if (encoderAPos < 107)
    maxTL = 1;
  else
    maxTL = 0;
  if (encoderAPos > 1893)
    maxBR = 1;
  else
    maxBR = 0;
  //Serial.println(encoderAPos);
}

void doEncoderB() {
  if (bitRead(PIND, encoderBPinA)^bitRead(PIND, encoderBPinB)) {
    encoderBPos--; //CCW
  }
  else {
    encoderBPos++; //CW
  }
  if (encoderBPos < 107)
    maxTR = 1;
  else
    maxTR = 0;
  if (encoderBPos > 1893)
    maxBL = 1;
  else
    maxBL = 0;
  //Serial.println(encoderBPos);
}

void loop()
{
  val_x = analogRead(x_dir);
  val_y = analogRead(y_dir);
//  Serial.print(val_x);
//  Serial.print(" ");
//  Serial.println(val_y);

  //////////////BL: (0,0)///////////////////// 
  if (val_x < 200 && val_y < 200) {
    if (!maxBL)
      //motorB.drive((-1)*motorSpeed); //counterclockwise
      motorA.drive((-1)*motorSpeed); //counterclockwise
    else
      motorA.brake();
  }

  //////////////BR: (1021,0)////////////////// 
  if (val_x > 800 && val_y < 200) {
    if (!maxBR)
      //motorA.drive((-1)*motorSpeed); //counterclockwise
      motorB.drive((-1)*motorSpeed); //counterclockwise
    else
      motorB.brake();
  }

  //////////////TR: (1021,1021)////////////////// 
  if (val_x > 800 && val_y > 800) {
    if (!(maxTR))
      //motorB.drive(motorSpeed); 
      motorA.drive(motorSpeed); 
    else
      motorA.brake();
  }

  /////////////TL: (0,1021)///////////////////
  if (val_x < 200 && val_y > 800) {
    if (!(maxTL))
      //motorA.drive(motorSpeed); //clockwise (looking at magnet)
      motorB.drive(motorSpeed);
    else
      motorB.brake();
  }

  if (val_x < 500 && val_x > 490 && val_y > 510 && val_y < 540) {
    motorA.brake();
    motorB.brake();
  }
  
  //////////////////////////////////////////
    btnAna = digitalRead(buttonAnalog); //PINB won't work for some reason
  
    if(btnAna == 0){
      encoderAPos = 1000;
      encoderBPos = 1000;
    }

  //////////////For Bluetooth///////////////////////
    buttonIrr = digitalRead(buttonIrrPin);
    buttonSuc = digitalRead(buttonSucPin);
    
    if (buttonIrrPrev ^ buttonIrr) {
      Serial.print('I');
      Serial.print(buttonIrr);
      buttonIrrPrev = buttonIrr;
    }

    if (buttonSucPrev ^ buttonSuc) {
      Serial.print('S');
      Serial.print(buttonSuc);
      buttonSucPrev = buttonSuc;
    }
    delayMicroseconds(10);

  // same thing for S
}

