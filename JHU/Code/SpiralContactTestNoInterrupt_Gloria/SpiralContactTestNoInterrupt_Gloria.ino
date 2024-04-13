
boolean flagL = false;
boolean flagR = false;

double initialMillis = 0;
double totalTime = 0;

int startMillisL = 0;
int  endMillisL = 0;
int startMillisR = 0;
int  endMillisR = 0;

double  prevDurationL = 0;
double  durationL = 0;
int  durationTempL = 0;
boolean currentStateL = true;
boolean prevStateL = true;

double  prevDurationR = 0;
double  durationR = 0;
volatile int  durationTempR = 0;
boolean currentStateR = true;
boolean prevStateR = true;


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
  pinMode(18, INPUT_PULLUP);
  initialMillis = millis();
}



void loop() {


  currentStateL = digitalRead(19);
  currentStateR = digitalRead(18);


  if (currentStateL == LOW && prevStateL == HIGH) {
    prevStateL = LOW;
    startMillisL = millis();
  }

  if (currentStateR == LOW && prevStateR == HIGH) {
    prevStateR = LOW;
    startMillisR = millis();
  


  if (currentStateL == HIGH && prevStateL == LOW) {
    prevStateL = HIGH;
    endMillisL = millis();
    flagL = true;
  }
  if (currentStateR == HIGH && prevStateR == LOW) {
    prevStateR = HIGH;
    endMillisR = millis();
    flagR = true;
  }

  if (flagL == true && endMillisL - startMillisL > 10 ) {
    durationTempL = endMillisL - startMillisL;
    durationL = prevDurationL + durationTempL;
    prevDurationL = durationL;
    flagL = false;
  }

  if (flagR == true && endMillisR - startMillisR > 10 ) {
    durationTempR = endMillisR - startMillisR;
    durationR = prevDurationR + durationTempR;
    prevDurationR = durationR;
    flagR = false;
  }


  recvOneChar();
  showNewData();
}





void recvOneChar() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
    NOP;
    newData = true;
  }
}

void showNewData() {
  if (newData == true) {

    if (inByte == 'r'){
      initialMillis = millis();
      durationL = 0;
      durationR = 0;
      prevDurationL = 0;
      prevDurationR = 0;
    }
     
    else if (inByte == 's') {
      totalTime = (millis() - initialMillis) / 1000;
      Serial.print("Contact Time Left: ");
      Serial.println(durationL / 1000);
      Serial.print("Contact Time Right: ");
      Serial.println(durationR / 1000);
      Serial.print("Total Time: ");
      Serial.println(totalTime);    
    }


    newData = false;
  }
}
