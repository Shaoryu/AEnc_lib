#include "mbed.h"
#include "aenc.h"
aenc::aenc(PinName mosi,PinName miso,PinName clk,PinName cs):SPI(mosi,miso,clk),_cs(cs){
    format(12,1);
}

aenc::aenc(PinName mosi,PinName miso,PinName clk,PinName cs,int target):SPI(mosi,miso,clk),_cs(cs){
    format(12,1);
    aenc::set_target(target);
}

void aenc::set_target(int target){
    angle_point=(float)target;
}

void aenc::get_data(){
    _cs=0;
    val=write(0x00);
    _cs=1;
    res=val/4096.0f*360.0f;
}

int aenc::pid_con(){
    get_data();
        diff = duty = angle_point-res;
    if(diff<-180.0f){
        diff+=360.0f;
    }else if(diff>180.0f){
        diff-=360.0f;
    }

    d = diff - last_diff;
    i+=diff+last_diff;

    duty=diff*KP+i*KI+d*KD;
    if(duty*duty<0.000001f){
        flag=Brake;
    }else if(duty > 0.0f){
        flag=CCW;
    }else{
        duty*=-1;
        flag=CW;
    }
    return flag;
    //
}

int aenc::pid_con(float kp,float ki,float kd){
    KP=kp;
    KI=ki;
    KD=kd;
    pid_con();
    //
    return flag;
}

