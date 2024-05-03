from machine import Pin, PWM, ADC
from time import sleep
import dht
sleep(0.1)

taster = Pin(3, Pin.IN)
led1 = Pin(0, Pin.OUT)
led2 = Pin(1, Pin.OUT)
led3 = PWM(Pin(2))
potMeter = ADC(Pin(26))
sensorPin = Pin(17, Pin.IN, Pin.PULL_UP)
sensor = dht.DHT11(sensorPin)

led3.freq(1000)

while True:
    print("Temperature: {}".format(sensor.temperature()))
    #print(sensorPin.value())
    led3.duty_u16(potMeter.read_u16())

    led1(1)
    led2(1)
    sleep(0.5)

    