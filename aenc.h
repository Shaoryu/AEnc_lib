#ifndef _AENC_H_
#define _AENC_H_

#include "mbed.h"
#include "CANMotor.h"


class aenc 
{
public:
    aenc(SPI &spi,PinName cs,int target);//miso(DO),clk(CLK),cs(CSn)※mosiは使っていないよ;
    aenc(SPI &spi,PinName cs);//miso(DO),clk(CLK),cs(CSn)※mosiは使っていないよ;
    void set_target(int target);
    static float duty;//デューティ比。マックス0.3,最小0.01よりちっちゃい
    static float angle_point;//目標(deg)。

    
    float get_data();
    int pid_con();
    int pid_con(float kp,float ki,float kd);

    static int state;

private:
    SPI &SPi;
    DigitalOut _cs;

    float res;
    int val;
    float diff;

    float i;
    float last_diff;
    float d;
    float KP,KI,KD;//pidのゲイン。
    enum{
        Free,
        CW,
        CCW,
        Brake,
    };
    
};

#endif
