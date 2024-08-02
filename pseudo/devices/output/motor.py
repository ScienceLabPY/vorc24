from output_device import OutputDevice

class Motor(OutputDevice):
    def __init__(self, protocol):
        self.protocol = protocol
    
    def write(self, command):
        # Write motor command using the communication protocol
        pass