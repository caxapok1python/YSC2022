// pin
#define RST 12 // pin to push reset

// restart arduino
void setupRescure(){
  digitalWrite(RST, HIGH);
  pinMode(RST, OUTPUT);
}
void resetArduino(){
  digitalWrite(RST, LOW);
}