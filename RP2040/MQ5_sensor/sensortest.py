from machine import Pin, ADC, PWM
from time import sleep
sleep(0.5)

mq5 = ADC(Pin(26))
mq5Digital = Pin(2, Pin.IN)
warningLED = Pin(1, Pin.OUT)
buzzer = Pin(0, Pin.OUT)

while(True):
    warningLED(0)
    buzzer(0)
    if(mq5Digital.value()==0):
        warningLED(1)
        buzzer(1)

    readVal = mq5.read_u16()
    actualVal = int(((readVal - 20500) / (45000-20500)) * 65535)
    print(readVal)

    sleep(0.5)