import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import spidev
import time


class NRF:
    def __init__(self):
        GPIO.setmode(GPIO.BCM)
        self.address = [0x44, 0x97, 0x4D, 0xE8, 0x5D]
        self.radio = NRF24(GPIO, spidev.SpiDev())
        self.radio.begin(0, 17, 4000000)
        self.radio.setPayloadSize(32)
        self.radio.setChannel(0x43)
        self.radio.setDataRate(NRF24.BR_250KBPS)
        self.radio.setPALevel(NRF24.PA_MIN)
        self.radio.openWritingPipe(self.address)
        self.radio.stopListening()

    def send(self, data: str, p_repeats: int = 1):
        for i in range(p_repeats):
            self.radio.write(data)
            if p_repeats > 1 and i+1 != p_repeats:
                time.sleep(1/50)
