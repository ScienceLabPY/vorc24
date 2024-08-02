class BallSortingController:
    def __init__(self, event_bus, color_sensor, sorting_servo):
        self.event_bus = event_bus
        self.color_sensor = color_sensor
        self.sorting_servo = sorting_servo
        event_bus.subscribe("ColorSensor_DATA", self)
    
    def handle(self, event):
        if event.type == "ColorSensor_DATA":
            # Process color data and control sorting servo
            pass