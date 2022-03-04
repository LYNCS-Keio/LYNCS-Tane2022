#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "PinAssign.h"
#include "Dps310.h"
#include "BMX055.h"
#include "MadgwickAHRS.h"
#include "Motor.h"
#include "GNSS.h"

TinyGPSPlus tinygps;
SoftwareSerial sSerial(GNSS_RX, GNSS_TX);
Madgwick madgwick;
Dps310 PressureSensor = Dps310();
BMX055 nineDoFSensor = BMX055();
Motor motor = Motor();
GNSS gps = GNSS();
int16_t ret;
double target_azimuth;

void setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200);
    Serial.println(F("LYNCS Tane 2022"));
    sSerial.begin(9600);
    pinMode(19, OUTPUT);
    digitalWrite(19, LOW);
    motor.Init();
    /**
    PressureSensor.begin(Wire);
    ret = PressureSensor.startMeasureBothCont(4,2,4,2);
    **/
    /**/
    madgwick.begin(10); //1Hz (1000msec周期)
    nineDoFSensor.BMX055_Init(Wire);
    delay(100);
    /**/
    gps.Init(sSerial, tinygps);
}

void loop() {
    Serial.println("--------------------------------------"); 
    if (gps.get_azimuth(target_azimuth)) {
        Serial.print("target azimuth = ");
        Serial.println(target_azimuth);
    }
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
    Serial.print("yaw= ");
    Serial.print(yaw);
    Serial.println(""); 
    **/
    /**
    motor.MotorA_Rotate(-1);
    motor.MotorB_Rotate(1);
    **/
    delay(100);
}
