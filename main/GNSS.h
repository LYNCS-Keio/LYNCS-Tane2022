#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class GNSS
{
    public:
        void Init(SoftwareSerial &bus, TinyGPSPlus &gps)
        {
            _bus = &bus;
            _gps = &gps;
        }
        int get_azimuth(double &azimuth)
        {
            int ret = 0;
            while (_bus->available() > 0){
                char c = _bus->read();
                //Serial.print(c);
                _gps->encode(c);
                if (_gps->location.isUpdated()){
                    now_longitude = _gps->location.lng();
                    now_latitude = _gps->location.lat();
                    now_altitude = _gps->altitude.meters();
                    azimuth = azimuth_cal(now_longitude,now_latitude);
                    ret = 1;
                }
            }
            return ret;
        }
        
    private:
        SoftwareSerial *_bus;
        TinyGPSPlus *_gps;
        double const pi = 3.14159265358;
        double const radius = 6378.137;
        double goal_longitude = 139.65670;
        double goal_latitude = 35.56784;
        double now_latitude;
        double now_longitude;
        double now_altitude;

        double azimuth_cal(double now_longitude,double now_latitude){
            double nlng_rad = now_longitude*pi/180;
            double nlat_rad = now_latitude*pi/180; 
            double glng_rad = goal_longitude*pi/180;
            double glat_rad = goal_latitude*pi/180;

            double azimuth = pi + atan2(sin(glng_rad - nlng_rad),cos(nlat_rad)*tan(glat_rad) - sin(nlat_rad)*cos(glng_rad - nlng_rad));
            return azimuth * 180 / pi;
        }
        double distance_cal(double now_longitude,double now_latitude){
            double nlng_rad = now_longitude*pi/180;
            double nlat_rad = now_latitude*pi/180; 
            double glng_rad = goal_longitude*pi/180;
            double glat_rad = goal_latitude*pi/180;

            double distance = radius*acos(sin(nlat_rad)*sin(glat_rad) + cos(nlat_rad)*cos(glat_rad)*cos(glng_rad - nlng_rad));
            return distance;
};