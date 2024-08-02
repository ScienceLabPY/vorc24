class ShootingController:
    def __init__(self, event_bus, shooting_motor, angle_servo):
        self.event_bus = event_bus
        self.shooting_motor = shooting_motor
        self.angle_servo = angle_servo
        event_bus.subscribe("GAMEPAD_DATA", self)
    
    def handle(self, event):
        if event.type == "GAMEPAD_DATA":
            # Process gamepad data and control shooting motor and angle servo
            pass