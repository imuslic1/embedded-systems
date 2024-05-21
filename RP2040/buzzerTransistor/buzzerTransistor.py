from machine import Pin, ADC
from time import sleep

mq5Digital = Pin(2, Pin.IN)
led = Pin(1, Pin.OUT)
buzzer = Pin(0, Pin.OUT)

while True:
    
