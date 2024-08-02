from output_device import OutputDevice

class Servo(OutputDevice):
    def __init__(self, protocol):
        self.protocol = protocol
    
    def write(self, command):
        # Write servo command using the communication protocol
        pass