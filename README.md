# //AEnc_lib
//・CANMotorを用いたアブソリュートエンコーダの角度制御。
//・一応555想定。
//・ゲイン調整は甘いので、突如変わるかも
//・以下サンプルプログラム。きもい。






/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "CANMotor.h"
#include "aenc.h"

CAN can(p30,p29);
CANMotorManager mng(can);
CANMotor motor(can,mng,0x01,0);


SPI spi(p11,p12,p13);
aenc aenc(spi,p14);

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    aenc.set_target(150);

    while (true) {
        aenc.pid_con();
        motor.state(aenc::state);
        motor.duty_cycle(aenc::duty);
        mng.write_all();
        led = !led;
        ThisThread::sleep_for(5ms);
    }
}
