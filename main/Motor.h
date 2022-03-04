#include <Arduino.h>
#include "PinAssign.h"

class Motor
{
    public:
    /**
     * @brief モーター初期化
     * @param None
     */
    void Init() {
        pinMode(MotorA_LineA, OUTPUT);
        pinMode(MotorA_LineB, OUTPUT);
        pinMode(MotorB_LineA, OUTPUT);
        pinMode(MotorB_LineB, OUTPUT);
        //初期状態は停止
        MotorA_Rotate(0);
        MotorB_Rotate(0);
    }

    /**
     * @brief モーターAの回転制御
     * @param int dir 
     * dir = 1      : 正転
     * dir = -1     : 逆転
     * otherwise    : 停止
     */
    void MotorA_Rotate(int dir=0) {
        if (dir == 1) {
            digitalWrite(MotorA_LineA, LOW);
            digitalWrite(MotorA_LineB, HIGH);
        } else if (dir == -1) {
            digitalWrite(MotorA_LineA, HIGH);
            digitalWrite(MotorA_LineB, LOW);
        } else {
            digitalWrite(MotorA_LineA, LOW);
            digitalWrite(MotorA_LineB, LOW);
        }
    }

    /**
     * @brief モーターBの回転制御
     * @param int dir 
     * dir = 1      : 正転
     * dir = -1     : 逆転
     * otherwise    : 停止
     */
    void MotorB_Rotate(int dir=0) {
        if (dir == 1) {
            digitalWrite(MotorB_LineA, LOW);
            digitalWrite(MotorB_LineB, HIGH);
        } else if (dir == -1) {
            digitalWrite(MotorB_LineA, HIGH);
            digitalWrite(MotorB_LineB, LOW);
        } else {
            digitalWrite(MotorB_LineA, LOW);
            digitalWrite(MotorB_LineB, LOW);
        }
    }

};