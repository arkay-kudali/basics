from machine import Pin
import time

# Onboard LED (Pico W)
led = Pin("LED", Pin.OUT)

while True:
    led.toggle()
    time.sleep(1)
