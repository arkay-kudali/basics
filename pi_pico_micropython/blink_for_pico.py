from machine import Pin
import time

# Setup onboard LED (GPIO 25)
led = Pin(25, Pin.OUT)

while True:
    led.toggle()      # Toggle LED state
    time.sleep(1)     # Wait 1 second
