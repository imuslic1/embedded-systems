from machine import Pin
from time import sleep

ledCrvena = Pin(16, Pin.OUT)
ledZuta = Pin(17, Pin.OUT)
ledZelena = Pin(18, Pin.OUT)

def ledsOff():
    ledCrvena(0)
    ledZuta(0)
    ledZelena(0)
    
ledsOff()
sleep(1)

while True:
    ledCrvena(1)
    sleep(5)
    ledZuta(1)
    sleep(2)
    ledCrvena(0)
    ledZuta(0)
    ledZelena(1)
    sleep(5)
    
    brojac = 0
    
    while brojac <= 5:
        sleep(0.5)
        ledZelena(0)
        sleep(0.5)
        ledZelena(1)
        brojac += 1
        
    ledZelena(1)
    sleep(0.5)
    ledZelena(0)
    ledZuta(1)
    sleep(3)
    ledZuta(0)
    ledCrvena(1)
    
        
