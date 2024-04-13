
void rollSetDir(bool dir) {
  delayMicroseconds(1);
  digitalWrite(rollDirPin, dir);
  delayMicroseconds(1);
}

void pitchSetDir(bool dir) {
  delayMicroseconds(1);
  digitalWrite(pitchDirPin, dir);
  delayMicroseconds(1);
}

void linSetDir(bool dir) {
  delayMicroseconds(1);
  digitalWrite(linDirPin, dir);
  delayMicroseconds(1);
}
