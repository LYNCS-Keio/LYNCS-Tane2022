#include <Wire.h>
#include "PinAssign.h"
#include "Dps310.h"

Dps310 PressureSensor = Dps310();
int16_t ret;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  PressureSensor.begin(Wire);
  ret = PressureSensor.startMeasureBothCont(4,2,4,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  float heightMetre;
  ret = PressureSensor.calcHeighMetre(heightMetre, 100820);
  if (ret == 0) {
      Serial.println(heightMetre);
  }

  delay(100);
}
