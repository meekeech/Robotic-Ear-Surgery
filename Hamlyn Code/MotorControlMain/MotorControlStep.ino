
void rollStep()
{
  digitalWrite(rollStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(rollStepPin, LOW);
  delayMicroseconds(3);
  delayMicroseconds(2000);
}

void pitchStep()
{
  digitalWrite(pitchStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(pitchStepPin, LOW);
  delayMicroseconds(3);
  delayMicroseconds(2000);
}

void linStep()
{
  digitalWrite(linStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(linStepPin, LOW);
  delayMicroseconds(3);
  delayMicroseconds(900); //900 to like 16000
}
