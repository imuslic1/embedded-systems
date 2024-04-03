#include "mbed.h"
#include "N5110.h"
#include "lpc1114etf.h"
#include <stdio.h>

AnalogIn potMeter(dp9);
DigitalIn taster(Taster_1);
N5110 lcd(dp4,dp24,dp23,dp25,dp2,dp6,dp18);

char* floatToString(float num) {
    //Alokacija memorije za string
    char* str = (char*)malloc(20 * sizeof(char));

    //Tretman negativnih brojeva
    if (num < 0) {
        *str++ = '-';
        num = -num;
    }

    //Cjelobrojni dio
    int intPart = (int)num;
    int index = 0;
    do {
        str[index++] = intPart % 10 + '0';
        intPart /= 10;
    } while (intPart != 0);

    //Obrtanje cjelobrojnog dijela zbog upisa
    for (int i = 0; i < index / 2; i++) {
        char temp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = temp;
    }

    //Decimalna tacka
    str[index++] = '.';

    //Necijeli dio
    float fracPart = num - (int)num;
    for (int i = 0; i < 6; i++) { //6 decimalnih mjesta, modifyable
        fracPart *= 10;
        int digit = (int)fracPart;
        str[index++] = digit + '0';
        fracPart -= digit;
    }

    //Null-terminacija stringa
    str[index] = '\0';

    return str;
}

void prikaziOtpor() {
    char otporString[10];
    float otpor = 100000 * potMeter.read();
    sprintf(otporString, "%d", (int)otpor);
    //Refresh displeja
    lcd.clear();
    lcd.printString("Otpor (Ohm): ", 0, 0);
    lcd.printString(otporString, 0, 2);
}

void prikaziNapon() {
    float refNapon = 3.3;
    float napon = refNapon * potMeter.read();
    char* naponString;
    naponString = floatToString(napon);
    //Refresh displeja
    lcd.clear();
    lcd.printString("Napon (V): ", 0, 0);
    lcd.printString(naponString, 0, 2);
    free(naponString);
}   

int main() {
    //false za prikaz otpora, true za prikaz napona
    lcd.init();
    bool viewMode = false;  
    
    while (true) {
        if(taster == 1) viewMode = !viewMode;

        if(viewMode == false) prikaziOtpor();
        else prikaziNapon();
        wait_us(100);       
    }
}
