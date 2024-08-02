from enum import Enum

# enum EventType {
#     GAMEPAD_INPUT
#     SENSOR_DATA
#     MOTOR_COMMAND
#     ...
# }

class EventType(Enum):
    GAMEPAD_INPUT = 1
    SENSOR_DATA = 2
    MOTOR_COMMAND = 3