#include "BMX055.h"

void BMX055::BMX055_Init(TwoWire &bus)
{
    m_i2cbus = &bus;
    init();
}

void BMX055::init()
{
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Accl);
    m_i2cbus->write(0x0F); // Select PMU_Range register
    m_i2cbus->write(0x03);   // Range = +/- 2g
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Accl);
    m_i2cbus->write(0x10);  // Select PMU_BW register
    m_i2cbus->write(0x08);  // Bandwidth = 7.81 Hz
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Accl);
    m_i2cbus->write(0x11);  // Select PMU_LPW register
    m_i2cbus->write(0x00);  // Normal mode, Sleep duration = 0.5ms
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Gyro);
    m_i2cbus->write(0x0F);  // Select Range register
    m_i2cbus->write(0x04);  // Full scale = +/- 125 degree/s
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Gyro);
    m_i2cbus->write(0x10);  // Select Bandwidth register
    m_i2cbus->write(0x07);  // ODR = 100 Hz
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Gyro);
    m_i2cbus->write(0x11);  // Select LPM1 register
    m_i2cbus->write(0x00);  // Normal mode, Sleep duration = 2ms
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x4B);  // Select Mag register
    m_i2cbus->write(0x83);  // Soft reset
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x4B);  // Select Mag register
    m_i2cbus->write(0x01);  // Soft reset
    m_i2cbus->endTransmission();
    delay(100);
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x4C);  // Select Mag register
    m_i2cbus->write(0x00);  // Normal Mode, ODR = 10 Hz
    m_i2cbus->endTransmission();
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x4E);  // Select Mag register
    m_i2cbus->write(0x84);  // X, Y, Z-Axis enabled
    m_i2cbus->endTransmission();
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x51);  // Select Mag register
    m_i2cbus->write(0x04);  // No. of Repetitions for X-Y Axis = 9
    m_i2cbus->endTransmission();
    //------------------------------------------------------------//
    m_i2cbus->beginTransmission(Addr_Mag);
    m_i2cbus->write(0x52);  // Select Mag register
    m_i2cbus->write(0x16);  // No. of Repetitions for Z-Axis = 15
    m_i2cbus->endTransmission();
}

void BMX055::BMX055_Accl()
{
    int data[6];
    for (int i = 0; i < 6; i++)
    {
        m_i2cbus->beginTransmission(Addr_Accl);
        m_i2cbus->write((2 + i));// Select data register
        m_i2cbus->endTransmission();
        m_i2cbus->requestFrom(Addr_Accl, 1);// Request 1 byte of data
        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if (m_i2cbus->available() == 1)
        data[i] = m_i2cbus->read();
    }
    // Convert the data to 12-bits
    xAccl = ((data[1] * 16)) + (data[0]) / 16;
    if (xAccl > 2047)  xAccl -= 4096;
    yAccl = ((data[3] * 16)) + (data[2]) / 16;
    if (yAccl > 2047)  yAccl -= 4096;
    zAccl = ((data[5] * 16)) + (data[4]) / 16;
    if (zAccl > 2047)  zAccl -= 4096;
    xAccl = xAccl * 0.00098; // renge +-2g
    yAccl = yAccl * 0.00098; // renge +-2g
    zAccl = zAccl * 0.00098; // renge +-2g
}

void BMX055::BMX055_Gyro()
{
    int data[6];
    for (int i = 0; i < 6; i++)
    {
        m_i2cbus->beginTransmission(Addr_Gyro);
        m_i2cbus->write((2 + i));    // Select data register
        m_i2cbus->endTransmission();
        m_i2cbus->requestFrom(Addr_Gyro, 1);    // Request 1 byte of data
        // Read 6 bytes of data
        // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
        if (m_i2cbus->available() == 1)
        data[i] = m_i2cbus->read();
    }
    // Convert the data
    xGyro = (data[1] * 256) + data[0];
    if (xGyro > 32767)  xGyro -= 65536;
    yGyro = (data[3] * 256) + data[2];
    if (yGyro > 32767)  yGyro -= 65536;
    zGyro = (data[5] * 256) + data[4];
    if (zGyro > 32767)  zGyro -= 65536;

    xGyro = xGyro * 0.0038; //  Full scale = +/- 125 degree/s
    yGyro = yGyro * 0.0038; //  Full scale = +/- 125 degree/s
    zGyro = zGyro * 0.0038; //  Full scale = +/- 125 degree/s
}

void BMX055::BMX055_Mag()
{
    long int data[8];
    for (int i = 0; i < 8; i++)
    {
        m_i2cbus->beginTransmission(Addr_Mag);
        m_i2cbus->write((0x42 + i));    // Select data register
        m_i2cbus->endTransmission();
        m_i2cbus->requestFrom(Addr_Mag, 1);    // Request 1 byte of data
        // Read 6 bytes of data
        // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
        if (m_i2cbus->available() == 1)
        data[i] = m_i2cbus->read();
    }
    // Convert the data
    xMag = ((data[1] <<5) + (data[0]>>3));
    if (xMag > 4095)  xMag -= 8192;
    yMag = ((data[3] <<5) + (data[2]>>3));
    if (yMag > 4095)  yMag -= 8192;
    zMag = ((data[5] <<7) + (data[4]>>1));
    if (zMag > 16383)  zMag -= 32768;
    xMag=xMag*0.31;
    yMag=yMag*0.31;
    zMag=zMag*0.15;
}