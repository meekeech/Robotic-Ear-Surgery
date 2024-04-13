short initialMillis = 0;
volatile unsigned short startMillis = 0;
volatile unsigned short endMillis = 0;
unsigned short duration = 0;
volatile unsigned short durationTemp = 0;

boolean flag = true;


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3,INPUT);
  attachInterrupt(0, contactMade, FALLING);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(1, contactLost, RISING);  // encoder pin on interrupt 0 - pin 2

  initialMillis = millis();
}

void loop() {

  durationTemp = endMillis - startMillis;

  if (flag == true) {
    duration = duration + durationTemp;
    flag = false;
  }
  
}

void contactMade() {
 startMillis = millis()-initialMillis;
}

void contactLost() {
  endMillis - millis()-initialMillis;
  flag = true;
}
