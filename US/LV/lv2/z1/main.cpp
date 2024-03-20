/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lpc1114etf.h"

DigitalOut E(LED_ACT);

DigitalOut myled1(LED0);
DigitalOut myled2(LED1);
DigitalOut myled3(LED2);
DigitalOut myled4(LED3);
DigitalOut myled5(LED4);
DigitalOut myled6(LED5);
DigitalOut myled7(LED6);
DigitalOut myled8(LED7);

int main() {
    E = 0;
    myled1 = myled2 = myled3 = myled4 = myled5 = myled6 = myled7 = myled8 = 0;
    
    while(1) {
        myled1 = 1;
        wait_us(1e6);
        myled1 = 0;
        wait_us(1e6);

        myled2 = 1;
        wait_us(1e6);
        myled2 = 0;
        wait_us(1e6);

        myled3 = 1;
        wait_us(1e6);
        myled3 = 0;
        wait_us(1e6);

        myled4 = 1;
        wait_us(1e6);
        myled4 = 0;
        wait_us(1e6);

    }
}
