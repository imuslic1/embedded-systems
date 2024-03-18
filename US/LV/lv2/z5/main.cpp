#include "mbed.h"
#include "lpc1114etf.h"

#define T 1

DigitalOut led(LED0);

int main() {
    float on = T;
    float off = T;
    const float deltaT = 0.9/(30*T);
        
    while(1) {
        on = off = T;
        
        while(on <= 1.9*T) {
            led = 1; 
            wait_us(on*(1e6));
            led = 0;
            wait_us(off*(1e6));
            
            on += deltaT;
            off -= deltaT;
        }
        
        while(off <= 1.9*T) {
            led = 1;
            wait_us(on*(1e6));
            led = 0;
            wait_us(off*(1e6));
            
            on -= deltaT;
            off += deltaT;
        }
    }
}