
volatile boolean flag2 = false;
volatile double initialMillis = 0;
volatile int startMillis = 0;
volatile int  endMillis = 0;
double  prevDuration = 0;
double  duration = 0;
double totalTime = 0;
volatile int  durationTemp = 0;
boolean currentState = true;
boolean prevState = true;


byte inByte = 0;
int prevByte = 0;
boolean newData = false;
int currentTime;
int prevTime;
bool firstTime = true;
#define NOP __asm__ __volatile__ ("nop\n\t")


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(19, INPUT_PULLUP);
  initialMillis = millis();
}



void loop() {


  currentState = digitalRead(19);

  if (currentState == LOW && prevState == HIGH) {
    prevState = LOW;
    startMillis = millis();

    //    Serial.print(startMillis);
    //    Serial.print(" ");

  }


  if (currentState == HIGH && prevState == LOW) {
    prevState = HIGH;
    endMillis = millis();
    flag2 = true;
  }

  if (flag2 == true && endMillis - startMillis > 10 ) {
    durationTemp = endMillis - startMillis;
    duration = prevDuration + durationTemp;
    prevDuration = duration;
    flag2 = false;


  }


  recvOneChar();
  showNewData();
}





void recvOneChar() {
  if (Serial.available() > 0) {
    totalTime = (millis()-initialMillis)/1000;
    inByte = Serial.read();
    NOP;
    newData = true;
  }
}

void showNewData() {
  if (newData == true) {
    //if (inByte > 0) {
    Serial.print("Contact Time: ");
    Serial.println(duration / 1000);
    Serial.print("Total Time: ");
    Serial.println(totalTime);
    
    //}
    newData = false;
  }
}
