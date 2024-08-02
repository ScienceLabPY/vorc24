from core.event import Event

class InputController:
    def __init__(self, event_bus, input_devices):
        self.event_bus = event_bus
        self.input_devices = input_devices
    
    def poll_inputs(self):
        for device in self.input_devices:
            data = device.read()
            event = Event(f"{type(device).__name__}_DATA", data)
            self.event_bus.publish(event)