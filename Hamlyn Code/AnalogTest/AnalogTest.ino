const int x_dir = 0;
const int y_dir = 1;
int val_x;
int val_y;

//Flow


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val_x = analogRead(x_dir);
  val_y = analogRead(y_dir);

  Serial.print("x= ");
  Serial.print(val_x);
  Serial.print(" y= ");
  Serial.println(val_y);
}
