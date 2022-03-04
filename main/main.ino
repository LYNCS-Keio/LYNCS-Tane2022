#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <BluetoothSerial.h>
#include "PinAssign.h"
#include "Dps310.h"
#include "BMX055.h"
#include "MadgwickAHRS.h"
#include "Motor.h"
#include "GNSS.h"

BluetoothSerial SerialBT;
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
    SerialBT.begin("LYNCS Tane 2022");
    sSerial.begin(9600);
    // ニクロム線の初期化
    pinMode(19, OUTPUT);
    digitalWrite(19, LOW);
    // モーターの初期化
    // モーターは必ず初期化してください
    // さもなくば燃えます
    motor.Init();
    // DPS310の初期化
    /**/
    PressureSensor.begin(Wire);
    ret = PressureSensor.startMeasureBothCont(4,2,4,2);
    /**/
    // BMX055及びMadgwick Filterの初期化
    // Madgwick Filterの周波数が実際のループの周波数と合うようにすること
    /**/
    madgwick.begin(10); //10Hz (1000msec周期)
    nineDoFSensor.BMX055_Init(Wire);
    delay(100);
    /**/
    // GNSSの初期化
    gps.Init(sSerial, tinygps);
}

// Madgwick Filterとの兼ね合いを考えるとループは10Hz程度が最適
void loop() {
    // 目的地の方位取得
    SerialBT.println("--------------------------------------"); 
    if (gps.get_azimuth(target_azimuth)) {
        SerialBT.print("target azimuth = ");
        SerialBT.println(target_azimuth);
    }
    // 高度(m)の取得
    /**/
    float heightMetre;
    ret = PressureSensor.calcHeighMetre(heightMetre, 100820);
    if (ret == 0) {
        SerialBT.print("height = ");
        SerialBT.println(heightMetre);
    }
    /**/
    // 自身の方位の取得
    /**/
    madgwick.update(nineDoFSensor.xGyro, nineDoFSensor.yGyro, nineDoFSensor.zGyro,
    nineDoFSensor.xAccl, nineDoFSensor.yAccl, nineDoFSensor.zAccl, 
    nineDoFSensor.xMag, nineDoFSensor.yMag, nineDoFSensor.zMag);
    float roll  = madgwick.getRoll();
    float pitch = madgwick.getPitch();
    float yaw   = madgwick.getYaw();
    nineDoFSensor.BMX055_Accl();
    nineDoFSensor.BMX055_Gyro();
    nineDoFSensor.BMX055_Mag();
    SerialBT.print("yaw= ");
    SerialBT.print(yaw);
    SerialBT.println(""); 
    /**/
    // モーターの回転
    // MotorX_Rotate(1 or 0 or -1);
    // モーターXを正転 or 停止 or 逆転　する
    /**
    motor.MotorA_Rotate(-1);
    motor.MotorB_Rotate(1);
    **/
    delay(100);
}
