#include "mbed.h"
#include "lpc1114etf.h"

BusOut leds(LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7);
DigitalIn taster(Taster_1);

int main() {
    
    int brojac = 0;
    bool increment = true;
    
    while(1) {
        leds = brojac;
        
        if(taster == 1) {
            increment = !increment;            
            wait_us(200000);
        }
            
        if(increment)
            ++brojac;
        else --brojac;
        
        if(brojac > 255) brojac = 0;
        if(brojac < 0) brojac = 255;

        
        wait_us(1000000);
    }
}