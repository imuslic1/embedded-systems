from machine import Pin, ADC, PWM, Timer
import network
import time
import simple
import dht

# Konfiguracija WiFi veze
wifi_ssid = "Asterix"
wifi_password = "123a456d78"

# Konfiguracija MQTT protokola
mqtt_server = "broker.hivemq.com"
mqtt_topic_led1 = b"i&v/led1"
mqtt_topic_led2 = b"i&v/led2"
mqtt_topic_led3 = b"i&v/led3"
mqtt_topic_pot =  b"i&v/potenciometar"
mqtt_topic_taster = b"i&v/taster"
mqtt_topic_rgbRed = b"i&v/rgbRed"
mqtt_topic_rgbGreen = b"i&v/rgbGreen"
mqtt_topic_rgbBlue = b"i&v/rgbBlue"
mqtt_topic_sensor = b"i&v/dht11"
mqtt_client_name = "mbedSim"

# Inicijalizacija mreže
print("Connecting to WiFi: ", wifi_ssid)
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(wifi_ssid, wifi_password)

# Čekanje na vezu
while not wifi.isconnected():
    pass

# Uspješno povezan na WiFi
print("Connected to WiFi")
print("IP address:", wifi.ifconfig()[0])

# Podešavanje pinova
taster = Pin(3, Pin.IN)
led1 = Pin(0, Pin.OUT)
led2 = Pin(1, Pin.OUT)
pot = ADC(Pin(26))
led3 = PWM(Pin(2))
led3.freq(1000)

rgbRed = PWM(Pin(5))
rgbGreen = PWM(Pin(6))
rgbBlue = PWM(Pin(7))
rgbRed.freq(1000)
rgbGreen.freq(1000)
rgbBlue.freq(1000)

sensor = dht.DHT11(Pin(28))

# Callback funkcije za primljene poruke (kontrola LED dioda)
def message_arrived_led1(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    led1.value(int(float(msg)))

def message_arrived_led2(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    led2.value(int(float(msg)))

def message_arrived_led3(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    led3.duty_u16(int(float(msg)*65535))

def message_arrived_rgbRed(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    rgbRed.duty_u16(int(float(msg)*65535))

def message_arrived_rgbGreen(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    rgbGreen.duty_u16(int(float(msg)*65535))

def message_arrived_rgbBlue(topic, msg):
    print("Message arrived on topic:", topic)
    print("Payload:", msg)
    rgbBlue.duty_u16(int(float(msg)*65535))

# Custom callback dispatcher procedura za prosljeđivanje poruke na tačan topic
def custom_dispatcher(topic, msg):
    if topic == mqtt_topic_led1:
        message_arrived_led1(topic, msg)
    elif topic == mqtt_topic_led2:
        message_arrived_led2(topic, msg)
    elif topic == mqtt_topic_led3:
        message_arrived_led3(topic, msg)
    elif topic == mqtt_topic_rgbRed:
        message_arrived_rgbRed(topic, msg)
    elif topic == mqtt_topic_rgbGreen:
        message_arrived_rgbGreen(topic, msg)
    elif topic == mqtt_topic_rgbBlue:
        message_arrived_rgbBlue(topic, msg)

# Interrupt rutina za senzor
def sensorReport(pin):
    sensor.measure()
    temperature = sensor.temperature()
    humidity = sensor.humidity()
    publish = str("Sensor\nTemp: " + str(temperature) + "\nHumidity: " + str(humidity))
    buf = "{{\"Senzor\": \n{}}}".format(publish)
    client.publish(mqtt_topic_sensor, publish)

# Inicijalizacija varijabli za status potenciometra i tastera
taster_state = taster.value()
last_pot_value = pot.read_u16()

# Povezivanje na MQTT broker
client = simple.MQTTClient(client_id=mqtt_client_name, server=mqtt_server, port=1883)
client.connect()

# Subscribe na teme
client.set_callback(custom_dispatcher)
client.subscribe(mqtt_topic_led1)
client.subscribe(mqtt_topic_led2)
client.subscribe(mqtt_topic_led3)
client.subscribe(mqtt_topic_rgbRed)
client.subscribe(mqtt_topic_rgbGreen)
client.subscribe(mqtt_topic_rgbBlue)
client.subscribe(mqtt_topic_sensor)

# Inicijalizacija Timera za interrupte senzora
t = Timer(period=10000, callback=sensorReport, mode=Timer.PERIODIC)

# Main loop
while True:
    # Slanje stanja tastera
    if taster.value() != taster_state:
        taster_state = taster.value()
        buf = "{{\"Taster\": {}}}".format(taster_state)
        client.publish(mqtt_topic_taster, buf)
    
    # Slanje vrijednosti potenciometra
    pot_value = pot.read_u16()
    if pot_value != last_pot_value:
        last_pot_value = pot_value
        buf = "{{\"Potenciometar\": {}}}".format(pot_value)
        client.publish(mqtt_topic_pot, buf)
    
    # Provjera dolazećih poruka, na dolazeću poruku se poziva Dispatcher za callback
    client.check_msg()

    time.sleep(0.1)