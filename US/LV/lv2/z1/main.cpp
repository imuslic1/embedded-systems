/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lpc1114etf.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

int main() {
    while(1) {
        myled1 = 1;
        wait_us(10e6);
        myled1 = 0;
        wait_us(10e6);

        myled2 = 1;
        wait_us(10e6);
        myled2 = 0;
        wait_us(10e6);

        myled3 = 1;
        wait_us(10e6);
        myled3 = 0;
        wait_us(10e6);

        myled4 = 1;
        wait_us(10e6);
        myled4 = 0;
        wait_us(10e6);

    }
}