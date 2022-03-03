#include<Wire.h>
#include <Arduino.h>

#define Addr_Accl 0x19  // (JP1,JP2,JP3 = Openの時)
#define Addr_Gyro 0x69  // (JP1,JP2,JP3 = Openの時)
#define Addr_Mag 0x13   // (JP1,JP2,JP3 = Openの時)


class BMX055
{
    public:
    void BMX055_Init(TwoWire &bus);
    void BMX055_Accl();
    void BMX055_Gyro();
    void BMX055_Mag();

    float   xAccl = 0.00;
    float   yAccl = 0.00;
    float   zAccl = 0.00;
    float   xGyro = 0.00;
    float   yGyro = 0.00;
    float   zGyro = 0.00;
    float   xMag  = 0.0000;
    float   yMag  = 0.0000;
    float   zMag  = 0.0000;

    private:
    void init();
    TwoWire *m_i2cbus;
};
