#include "mbed.h"
#include "lpc1114etf.h"

BusOut leds(LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7);
DigitalOut E(LED_ACT);

int main() {
    E = 0;
    leds = 0;


    while (true) {
        for(int i=0; i<=8; ++i) {
            leds = static_cast<int>(std::pow(2, i));
            wait_us(100000);
        }
        leds = 255;
        wait_us(100000);
        for(int i=8; i>=0; --i) {
            leds = leds - static_cast<int>(std::pow(2, i));
            wait_us(100000);
        }
    }
}
