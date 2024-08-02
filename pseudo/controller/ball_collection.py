class BallCollectionController:
    def __init__(self, event_bus, intake_motor):
        self.event_bus = event_bus
        self.intake_motor = intake_motor
        event_bus.subscribe("GAMEPAD_DATA", self)
    
    def handle(self, event):
        if event.type == "GAMEPAD_DATA":
            # Process gamepad data and control intake motor
            pass