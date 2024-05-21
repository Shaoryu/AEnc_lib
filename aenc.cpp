#include "mbed.h"
#include "aenc.h"
aenc::aenc(PinName miso,PinName clk,PinName cs):SPI(p11,miso,clk),_cs(cs){
    format(12,1);
}

aenc::aenc(PinName miso,PinName clk,PinName cs,int target):SPI(p11,miso,clk),_cs(cs){
    format(12,1);
    aenc::set_target(target);
}

aenc::set_target(int target){
    angle_point=(float)target;
}

aenc::get_data(){
    cs=0;
    val=spi.write(0x00);
    cs=1;
    res=val/4096.0f*360.0f;
}

aenc::pid_con(){
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
        motor.state(Motor::Brake);
        flag=0;
    }else if(duty > 0.0f){
        motor.state(Motor::CCW);
        flag=1;
    }else{
        motor.state(Motor::CW);
        duty*=-1;
        flag=-1;
    }
    return flag;
    //
}

aenc::pid_con(float kp,float ki,float kd){
    KP=kp;
    KI=ki;
    KD=kd;
    pid_con();
    //
}

