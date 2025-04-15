#include <LiquidCrystal_I2C.h>

void setup() {
  Serial.begin(115200);
  Serial.println();

}

void loop() {
  static unsigned long loopCnt = 0;
  static unsigned long nextMil = millis() + 1000;
  loopCnt++; //loopCnt = loopCnt + 1;

  if (millis() > nextMil) {
    nextMil = millis() + 1000;
    Serial.println(loopCnt);
    loopCnt = 0;
  }
}
