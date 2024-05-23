#include "mbed.h"
#include "aenc.h"
aenc::aenc(SPI &spi,PinName cs,int target):SPi(spi),_cs(cs){
    SPi.format(12,1);
    aenc::set_target(target);
}

aenc::aenc(SPI &spi,PinName cs):SPi(spi),_cs(cs){
    SPi.format(12,1);
}

void aenc::set_target(int target){
    angle_point=(float)(target % 360);
}

float aenc::get_data(){
    _cs=0;
    val=SPi.write(0x00);
    _cs=1;
    res=val/4096.0f*360.0f;
    return res;
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
        state=Brake;
    }else if(duty > 0.0f){
        state=CCW;
    }else{
        duty*=-1;
        state=CW;
    }
    return state;
}

int aenc::pid_con(float kp,float ki,float kd){
    KP=kp;
    KI=ki;
    KD=kd;
    pid_con();
    //
    return state;
}

