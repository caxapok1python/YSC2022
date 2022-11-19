#define PODEZD_K_BANKE 50

// Automotive banka
void autoCatch(){
  man2Pos(workPos);
  readCap();
  while (!capState){
    manualPower(LEFT, PODEZD_K_BANKE);
    manualPower(RIGHT, PODEZD_K_BANKE);
    readCap();
  }
  manualPower(LEFT, 0);
  manualPower(RIGHT, 0);
  manCatch(true);
  delay(500);
  man2Pos(defaultPos);
  delay(1000);
}

void checkAutomotive(){
  if (modeTumbler > tumblerRange[1]){
    autoCatch();
    delay(100);
  }
  if (buttonLeft){
    delay(50);
    rpiLoop(); 
  }
}
