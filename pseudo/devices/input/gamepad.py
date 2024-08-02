from core.com.spi import SPIProtocol
from input_device import InputDevice

class GamepadData:
    pass

class Gamepad(InputDevice):
    def __init__(self, protocol: SPIProtocol) -> None:
        self.protocol = SPIProtocol()

    def read(self):
        # Read gamepad input
        raw_data = self.protocol.read()
        # Parse the raw data and return the gamepad data
        # ...
        return GamepadData()


