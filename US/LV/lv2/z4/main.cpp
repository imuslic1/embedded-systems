#include "mbed.h"
#include "lpc1114etf.h"

BusOut leds(LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7);
DigitalIn taster1(Taster_1);
DigitalIn taster2(Taster_2);

int main() {
    while(true) {
        while(taster1 == 0 && taster2 == 0) {
            leds = 1;
            wait_us(500000);
            leds = 0x0;
            wait_us(500000);
        }
        
        if(taster1) {
            for(int i=0; i<=8; ++i) {
                leds = static_cast<int>(pow(2, i));
                wait_us(100000);
            }
            
            for(int i=8; i>=0; --i) {
                leds = 255 - static_cast<int>(pow(2, i));
                wait_us(100000);
            }
        }
        
        else if(taster2) {
            for(int i=0; i<=8; ++i) {
                leds = static_cast<int>(pow(2, i));
                wait_us(500000);
            }
            
            for(int i=8; i>=0; --i) {
                leds = 255 - static_cast<int>(pow(2, i));
                wait_us(500000);
            }
        }
    }
}