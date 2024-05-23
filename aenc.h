#ifndef _AENC_H_
#define _AENC_H_

#include "mbed.h"
#include "CANMotor.h"


class aenc : public SPI
{
public:
    
    
    aenc(PinName mosi,PinName miso,PinName clk,PinName cs);//miso(DO),clk(CLK),cs(CSn)※mosiは使っていないよ;
    aenc(PinName mosi,PinName miso,PinName clk,PinName cs,int target);//miso(DO),clk(CLK),cs(CSn)※mosiは使っていないよ;
    void set_target(int target);
    float KP,KI,KD;//pidのゲイン。
    float duty;//デューティ比。マックス0.3,最小0.01よりちっちゃい
    float angle_point;//目標(deg)。

    
    void get_data();
    int pid_con();
    int pid_con(float kp,float ki,float kd);

    int flag;

private:
    
    DigitalOut _cs;

    float res;
    int val;
    float diff;

    float i;
    float last_diff;
    float d;
    enum{
        Free,
        CW,
        CCW,
        Brake,
    };
    
};

#endif

