#include "mbed.h"
#include "N5110.h"
#include "lpc1114etf.h"
#include <stdio.h>

AnalogIn potMeter(dp9);
DigitalIn taster(Taster_1);
N5110 lcd(dp4,dp24,dp23,dp25,dp2,dp6,dp18);

void prikaziOtpor() {
    char otporString[10];
    float otpor = 10000 * potMeter.read();
    snprintf(otporString, sizeof(otporString), "%.3f", otpor);

    lcd.clear();
    lcd.printString("Otpor (kOhm): ", 0, 0);
    lcd.printString(otporString, 1, 0);
}

void prikaziNapon() {
    float refNapon = potMeter.get_reference_voltage();
    float napon = refNapon * potMeter.read();
    char naponString[20];
    snprintf(naponString, sizeof(naponString), "%.3f", napon);

    lcd.clear();
    lcd.printString("Napon (V): ", 0, 0);
    lcd.printString(naponString, 1, 0);
}   

int main() {
    //false za prikaz otpora, true za prikaz napona
    lcd.init();
    bool viewMode = false;  
    
    while (true) {
        if(taster == 1) viewMode = !viewMode;

        if(viewMode == false) prikaziOtpor();
        else prikaziNapon();
        wait_us(1000);       
    }
}
