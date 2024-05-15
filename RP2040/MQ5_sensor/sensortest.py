from machine import Pin, ADC, PWM
from time import sleep

mq5 = ADC(Pin(26))
mq5Digital = Pin(1, Pin.IN)
warningLED = Pin(0, Pin.OUT)
buzzer = PWM(Pin(2))
buzzer.freq(900)

while(True):
    warningLED(0)
    buzzer.duty_u16(0)

    if(mq5Digital.value()==0):
        warningLED(1)
        buzzer.duty_u16(12000)

    readVal = mq5.read_u16()
    actualVal = int(((readVal - 20500) / (45000-20500)) * 65535)
    #print(actualVal)
    print(actualVal)

    sleep(0.5)