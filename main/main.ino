#include <Wire.h>
#include "PinAssign.h"
#include "Dps310.h"
#include "BMX055.h"
#include "MadgwickAHRS.h"
#include "Motor.h"

Madgwick madgwick;
Dps310 PressureSensor = Dps310();
BMX055 nineDoFSensor = BMX055();
Motor motor = Motor();
int16_t ret;

void setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200);
    pinMode(19, OUTPUT);
    digitalWrite(19, LOW);
    /**
    PressureSensor.begin(Wire);
    ret = PressureSensor.startMeasureBothCont(4,2,4,2);
    **/
    /** 
    madgwick.begin(10); //1Hz (1000msec周期)
    nineDoFSensor.BMX055_Init(Wire);
    delay(100);
    **/
    motor.Init();
}

void loop() {
    /**
     float heightMetre;
    ret = PressureSensor.calcHeighMetre(heightMetre, 100820);
    if (ret == 0) {
        Serial.println(heightMetre);
    }
    **/
    /**
    madgwick.update(nineDoFSensor.xGyro, nineDoFSensor.yGyro, nineDoFSensor.zGyro,
    nineDoFSensor.xAccl, nineDoFSensor.yAccl, nineDoFSensor.zAccl, 
    nineDoFSensor.xMag, nineDoFSensor.yMag, nineDoFSensor.zMag);
    float roll  = madgwick.getRoll();
    float pitch = madgwick.getPitch();
    float yaw   = madgwick.getYaw();
    nineDoFSensor.BMX055_Accl();
    nineDoFSensor.BMX055_Gyro();
    nineDoFSensor.BMX055_Mag();
    Serial.println("--------------------------------------"); 
    Serial.print("roll= ");
    Serial.print(roll);
    Serial.println("");
    Serial.print("pitch= ");
    Serial.print(pitch);
    Serial.println(""); 
    Serial.print("yaw= ");
    Serial.print(yaw);
    Serial.println(""); 
    **/
    motor.MotorA_Rotate(-1);
    motor.MotorB_Rotate(1);
    delay(2000);
    motor.MotorA_Rotate(1);
    motor.MotorB_Rotate(-1);
    delay(2000);
}
