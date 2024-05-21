#ifndef _AENC_H_
#define _AENC_H_

#include "mbed.h"


class aenc : public SPI
{
public:
    
    
    aenc(PinName miso,PinName clk,PinName cs);//miso(DO),clk(CLK),cs(CSn)※mosiは使っていないよ;
    void set_target(int target);
    float Kp,Ki,Kd;//pidのゲイン。
    float duty;//デューティ比。マックス0.3,最小0.01よりちっちゃい
    float angle_point;//目標(deg)。

    
    int get_data();
    float pid_con();
    float pid_con(float kp,float ki,float kd);
    
private:
    
    DigitalIn _cs;

    float res;
    int val;
    float diff;

    float i;
    int flag;
    float last_diff;
    float d;
    
};

#endif
