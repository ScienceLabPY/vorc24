class MotionController:
    def __init__(self, event_bus, motors):
        self.event_bus = event_bus
        self.motors = motors
        event_bus.subscribe("GAMEPAD_DATA", self)
    
    def handle(self, event):
        if event.type == "GAMEPAD_DATA":
            # Process gamepad data and control motors
            pass