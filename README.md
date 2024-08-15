# Project System Design

This project is designed to create a modular robotic system with distinct components for input, output, control, and communication, utilizing an event-driven architecture. Below is an in-depth description of the system design.

## Overview

The system is composed of several packages, each responsible for a different aspect of the robot's functionality:

1. **Core**: Manages the communication protocols and event handling.
2. **Devices**: Includes input and output devices.
3. **Controllers**: Contains various controllers to manage different robot functions.
4. **System**: Integrates all components and runs the robot.

```plaintext
└───main
    ├───.pio
    │   └───build
    │       └───upesy_wrover
    ├───.vscode
    ├───include
    │   ├───controller
    │   ├───core
    │   │   └───event
    │   └───device
    │       ├───input
    │       │   ├───gamepad
    │       │   └───LimitSwitch
    │       └───output
    │           └───RCMotor
    ├───lib
    ├───src
    │   └───sl_core
    │       └───com
    └───test
```

## System Design

```mermaid
graph TD
    subgraph "Main Application"
        Main[Main Thread]
    end

    subgraph "Event Bus"
        EB[EventBus Singleton]
        EBM[EventBus Mutex]
    end

    subgraph "Input Mapper"
        IM[InputMapper Singleton]
        IPT[Input Processing Task]
        IMQ[Input Queue]
        IMM[InputMapper Mutex]
        ISR[GPIO ISR]
    end

    subgraph "Controllers"
        OC[Controllers]
        OCT[Controller Tasks]
    end

    Main --> EB
    Main --> IM
    Main --> OC

    EB <--> EBM
    EB -.-> OC

    IM <--> IMM
    IM --> IPT
    ISR --> IMQ
    IMQ --> IPT
    IPT --> EB

    OC --> OCT
    OCT --> EB

    classDef thread fill:#f9f,stroke:#333,stroke-width:2px;
    classDef mutex fill:#bbf,stroke:#333,stroke-width:2px;
    classDef queue fill:#bfb,stroke:#333,stroke-width:2px;
    classDef isr fill:#fbb,stroke:#333,stroke-width:2px;

    class Main,IPT,DCT,OCT thread;
    class EBM,IMM mutex;
    class IMQ queue;
    class ISR isr;
```

The diagram visualizes the parallelism and key components of the system:

- **Main Application**: The main thread that initializes and starts other components.
- **Event Bus**: 
    - A singleton instance with a mutex for thread-safe operations. 
    - Handles event publishing and subscription.
- **Input Mapper**: 
    - A singleton instance with a mutex for thread-safe operations. 
    - Has a GPIO Interrupt Service Routine (ISR) for immediate input detection.
    - Uses a queue to pass input events from the ISR to the Input Processing Task.
    - The Input Processing Task runs continuously, processing inputs and publishing events to the Event Bus.
- **Controllers**:
    - Represent additional controllers in the system.
    - Each has its own task and can subscribe to events from the Event Bus.

The diagram shows how these components interact:

Solid lines represent direct method calls or data flow.
Dotted lines represent event-based communication through the Event Bus.

This architecture allows for parallel processing of inputs, events, and control logic, while using mutexes and queues to ensure thread-safe operations and efficient inter-task communication.

## Class Design

```mermaid
classDiagram
    class EventBus {
        -subscribers: Map<EventType, List<EventHandler>>
        +subscribe(eventType: EventType, handler: EventHandler)
        +publish(event: Event)
    }

    class EventType {
        <<enumeration>>
        GAMEPAD_INPUT
        SENSOR_DATA
        MOTOR_COMMAND
    }

    class EventHandler {
        <<interface>>
        +handle(event: EventType)
    }

    class InputDevice {
        <<interface>>
        +read(): InputData
    }

    class Gamepad {
        +read(): GamepadData
    }

    class ColorSensor {
        -protocol: CommunicationProtocol
        +read(): ColorData
    }

    class LimitSwitch {
        -protocol: CommunicationProtocol
        +read(): boolean
    }

    class OutputDevice {
        <<interface>>
        +write(command: OutputCommand)
    }

    class HDMotor {
        -protocol: CommunicationProtocol
        +write(command: MotorCommand)
    }

    class StandardServo {
        -protocol: CommunicationProtocol
        +write(command: ServoCommand)
    }

    class ContinuousRotationServo {
        -protocol: CommunicationProtocol
        +write(command: ServoCommand)
    }

    class InputController {
        -eventBus: EventBus
        -inputDevices: List<InputDevice>
        +pollInputs()
    }

    class DrivetrainController {
        -eventBus: EventBus
        -motors: List<HDMotor>
        +handle(event: EventType)
    }

    class BallCollectorController {
        -eventBus: EventBus
        -intakeMotor: HDMotor
        +handle(event: EventType)
    }

    class BallSortingController {
        -eventBus: EventBus
        -colorSensor: ColorSensor
        -sortingServo: StandardServo
        +handle(event: EventType)
    }

    class ShootingController {
        -eventBus: EventBus
        -shootingMotor: HDMotor
        -angleServo: StandardServo
        +handle(event: EventType)
    }

    class WhiteBallDoorController {
        -eventBus: EventBus
        -doorServo: StandardServo
        +handle(event: EventType)
    }

    class RobotSystem {
        -eventBus: EventBus
        -inputController: InputController
        -controllers: List<EventHandler>
        +initialize()
        +run()
    }

    InputDevice <|-- Gamepad
    InputDevice <|-- ColorSensor
    InputDevice <|-- LimitSwitch
    OutputDevice <|-- HDMotor
    OutputDevice <|-- StandardServo
    OutputDevice <|-- ContinuousRotationServo
    EventHandler <|-- DrivetrainController
    EventHandler <|-- BallCollectorController
    EventHandler <|-- BallSortingController
    EventHandler <|-- ShootingController
    EventHandler <|-- WhiteBallDoorController

    RobotSystem --> EventBus
    RobotSystem --> InputController
    RobotSystem --> "1..*" EventHandler
    InputController --> EventBus
    InputController --> "1..*" InputDevice
    DrivetrainController --> "2..*" HDMotor
    BallCollectorController --> HDMotor
    BallSortingController --> ColorSensor
    BallSortingController --> StandardServo
    ShootingController --> HDMotor
    ShootingController --> StandardServo
    WhiteBallDoorController --> StandardServo
```

### Core Package

#### Event

1. **EventBus**

    - **Description**: Central hub for event management, handling subscription and publication of events.
    - **Attributes**:
        - `subscribers`: A map of `EventType` to a list of `EventHandler` instances.
    - **Methods**:
        - `subscribe(eventType: EventType, handler: EventHandler)`: Registers an event handler for a specific event type.
        - `publish(event: Event)`: Publishes an event to all subscribed handlers.

2. **EventType**

    - **Description**: Enum defining different types of events.
    - **Values**: `GAMEPAD_INPUT`, `SENSOR_DATA`, `MOTOR_COMMAND`, etc.

3. **EventHandler**
    - **Description**: Interface for handling events.
    - **Methods**:
        - `handle(event: Event)`: Handles the event.

#### Communication

1. **CommunicationProtocol**

    - **Description**: Interface for different communication protocols.
    - **Methods**:
        - `initialize()`: Initializes the protocol.
        - `read(address: int, register: int): byte[]`: Reads data from a device.
        - `write(address: int, register: int, data: byte[])`: Writes data to a device.

2. **I2CProtocol, SPIProtocol, GPIOProtocol**
    - **Description**: Implementations of the `CommunicationProtocol` interface for I2C, SPI, and GPIO.

### Devices Package

#### Input

1. **InputDevice**

    - **Description**: Interface for input devices.
    - **Methods**:
        - `read(): InputData`: Reads data from the input device.

2. **Gamepad, ColorSensor, LimitSwitch**
    - **Description**: Implementations of the `InputDevice` interface.
    - **Attributes**:
        - `protocol`: The communication protocol used by the device.
    - **Methods**:
        - `read()`: Reads specific data from the device (e.g., `GamepadData`, `ColorData`, `boolean`).

#### Output

1. **OutputDevice**

    - **Description**: Interface for output devices.
    - **Methods**:
        - `write(command: OutputCommand)`: Writes a command to the output device.

2. **Motor, Servo**
    - **Description**: Implementations of the `OutputDevice` interface.
    - **Attributes**:
        - `protocol`: The communication protocol used by the device.
    - **Methods**:
        - `write(command: MotorCommand/ServoCommand)`: Writes specific commands to the device.

### Controllers Package

1. **InputController**

    - **Description**: Manages input devices and polls them for data.
    - **Attributes**:
        - `eventBus`: The event bus for publishing events.
        - `inputDevices`: A list of input devices.
    - **Methods**:
        - `pollInputs()`: Polls all input devices and publishes events.

2. **MotionController, BallCollectionController, BallSortingController, ShootingController**
    - **Description**: Handle specific events and control corresponding devices.
    - **Attributes**:
        - `eventBus`: The event bus for subscribing to events.
        - `motors`: A list of motors (specific to `MotionController`).
        - `intakeMotor`: The motor for intake (specific to `BallCollectionController`).
        - `colorSensor`, `sortingServo`: Devices for sorting (specific to `BallSortingController`).
        - `shootingMotor`, `angleServo`: Devices for shooting (specific to `ShootingController`).
    - **Methods**:
        - `handle(event: EventType)`: Handles the event and controls the devices accordingly.

### System Package

1. **RobotSystem**
    - **Description**: The main class that integrates all components and runs the robot.
    - **Attributes**:
        - `eventBus`: The central event bus.
        - `inputController`: The input controller.
        - `controllers`: A list of event handlers (controllers).
    - **Methods**:
        - `initialize()`: Initializes the system.
        - `run()`: Runs the system, typically in a loop, polling inputs and handling events.

## UML Diagram

The UML diagram included in `UMLDiagram.txt` provides a visual representation of the classes and their relationships. It is structured into packages: Core, Devices, Controllers, and System, detailing the interaction between various components.

## Conclusion

This project design ensures a modular and scalable robotic system, allowing for easy addition and modification of components. The use of an event-driven architecture enhances the system's flexibility and responsiveness, making it suitable for complex robotic applications.
