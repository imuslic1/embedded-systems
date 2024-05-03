from machine import Pin, ADC, PWM
import network
import time
import simple

#Define network
wlan=network.WLAN(network.STA_IF)
wlan.active(True)
# wlan.connect('Lab220', 'lab220lozinka')

wlan.connect('Asterix_WLAN', '123A456d78')

# Define topics
TEMASUBLED1 = "i&v/led1"
TEMASUBLED2 = "i&v/led2"
TEMASUBLED3 = "i&v/led3"
TEMAPUBPOT  = "i&v/potenciometar"
TEMAPUBTAST = "i&v/taster"

# Initialize pins
taster = Pin(3, Pin.IN)
led1 = Pin(0, Pin.OUT)  # Sending messages with -X
led2 = Pin(1, Pin.OUT)  # Sending messages with MQTT Dash
pot = ADC(Pin(28))
led3 = PWM(Pin(2))
led3.freq(1000)

# Initialize MQTT client
client = simple.MQTTClient(client_id='mbedSim', server='broker.hivemq.com', user='', password='', port=1883)
client.connect()

def messageArrived_led1(topic, msg):
    led1.value(int(msg))

def messageArrived_led2(topic, msg):
    led2.value(int(msg))

def messageArrived_led3(topic, msg):
    led3.duty_u16(float(msg))

client.set_callback(messageArrived_led1)
client.subscribe(TEMASUBLED1)
client.set_callback(messageArrived_led2)
client.subscribe(TEMASUBLED2)
client.set_callback(messageArrived_led3)
client.subscribe(TEMASUBLED3)

notConnected=True

taster_state = taster.value()
pot_value = pot.read_u16()

# Main loop
while True:
    
    #Make connection
    if notConnected :
        while not wlan.isconnected() and wlan.status()>=0:
            print("Konektuje se: ")
            time.sleep(0.1)
        notConnected=False

    # Check if button state has changed
    if taster.value() != taster_state:
        taster_state = taster.value()
        buf = "{{\"Taster\": {}}}".format(taster_state)
        client.publish(TEMAPUBTAST, buf)

    # Check if potentiometer value has changed
    if pot_value != pot.read_u16():
        pot_value = pot.read_u16()
        buf = "{{\"Potenciometar\": {}}}".format(pot_value)
        client.publish(TEMAPUBPOT, buf)

    # Process incoming MQTT messages
    client.check_msg()

    # Wait for a short duration
    time.sleep(1)
