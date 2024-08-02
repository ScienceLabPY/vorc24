from core.event import *
from core.com import *
from devices import *
from controller import *

class RobotSystem:
    def __init__(self):
        self.event_bus = EventBus()
        self.setup_communication_protocols()
        self.setup_input_devices()
        self.setup_output_devices()
        self.setup_controllers()
    
    def setup_communication_protocols(self):
        self.i2c = I2CProtocol()
        self.spi = SPIProtocol()
        self.gpio = GPIOControl()
    
    def setup_input_devices(self):
        self.gamepad = Gamepad()
        self.color_sensor = ColorSensor(self.i2c)
        self.limit_switch = LimitSwitch(self.gpio)
        self.input_devices = [self.gamepad, self.color_sensor, self.limit_switch]
    
    def setup_output_devices(self):
        self.left_motor = Motor(self.spi)
        self.right_motor = Motor(self.spi)
        self.intake_motor = Motor(self.spi)
        self.shooting_motor = Motor(self.spi)
        self.sorting_servo = Servo(self.spi)
        self.angle_servo = Servo(self.spi)
    
    def setup_controllers(self):
        self.input_controller = InputController(self.event_bus, self.input_devices)
        self.motion_controller = MotionController(self.event_bus, [self.left_motor, self.right_motor])
        self.ball_collection_controller = BallCollectionController(self.event_bus, self.intake_motor)
        self.ball_sorting_controller = BallSortingController(self.event_bus, self.color_sensor, self.sorting_servo)
        self.shooting_controller = ShootingController(self.event_bus, self.shooting_motor, self.angle_servo)
    
    def run(self):
        while True:
            self.input_controller.poll_inputs()
            # Add any other necessary periodic tasks
            # You might want to add a small delay here to control the loop rate

# Main program
if __name__ == "__main__":
    robot = RobotSystem()
    robot.run()