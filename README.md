# BestFSM 🎯
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-Arduino-blue.svg)](https://www.arduino.cc/)
[![Version](https://img.shields.io/badge/version-1.0.0-green.svg)](https://semver.org/)
[![C++](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Documentation](https://img.shields.io/badge/docs-Doxygen-blue.svg)](https://www.doxygen.nl)

A high-precision, embedded-focused Finite State Machine library designed for real-time applications and resource-constrained environments.

A robust, modular finite state machine (FSM) framework for embedded systems, built to simplify complex event-driven designs. BestFSM offers high extensibility, precise timing controls, and integration-ready components, making it an ideal choice for advanced Arduino projects.

```ascii
 +---------+    Event     +---------+
 |  State  |------------>|  State  |
 |   A     |   Timer     |   B     |
 +---------+   Condition +---------+
      |          ...          |
      +-----------------------+
         Priority/Immediate
```

## 🌟 Key Features

- 🕒 **Zero-Drift Timer System**: Precise timing control with automatic drift compensation

  🎛️ **Rich Event Handling**: Built-in support for buttons, serial input, and custom events

  🔀 **Priority-Based Transitions**: Five transition types with deterministic evaluation order

  🧠 **Memory Efficient**: Optimized for embedded systems with minimal RAM footprint

  🐞 **Professional Debug Support**: Configurable debugging for states, events, and timing

  🧩 **Hardware Abstraction**: Clean separation between FSM logic and hardware interfaces

  ⚡ **Plug-and-Play**: Modular design for seamless integration

## 📋 Table of Contents

- [Installation](#installation)
- [Quick Start](#quick-start)
- [Core Concepts](#core-concepts)
- [Examples](#examples)
- [API Reference](#api-reference)
- [Contributing](#contributing)
- [License](#license)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/wladimiresposito/BestFSM.git
```

2. Copy to your Arduino libraries:
```bash
cp -r bestfsm ~/Arduino/libraries/
```

## Quick Start

Create a simple LED blink state machine:

```cpp
#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"

constexpr uint8_t LED_PIN = 13;
constexpr unsigned long ON_TIME = 3000;  // 3 seconds
constexpr unsigned long OFF_TIME = 1000; // 1 second

// Define states
class LedOnState : public State {
public:
    explicit LedOnState(unsigned long timeout) : State(timeout) {}
    void onEnter(Event* event) const override {
        digitalWrite(LED_PIN, HIGH);
        State::onEnter(event);
    }
};

class LedOffState : public State {
public:
    explicit LedOffState(unsigned long timeout) : State(timeout) {}
    void onEnter(Event* event) const override {
        digitalWrite(LED_PIN, LOW);
        State::onEnter(event);
    }
};

// Create state instances
auto stateOn = new LedOnState(ON_TIME);
auto stateOff = new LedOffState(OFF_TIME);

// Setup FSM
void setup() {
    pinMode(LED_PIN, OUTPUT);
    
    // Configure transitions
    stateOn->addTransition(new StateTimeoutTransition(stateOff));
    stateOff->addTransition(new StateTimeoutTransition(stateOn));
    
    // Initialize FSM with initial state
    auto fsm = new FSM(stateOn);
    fsm->start();
    
    or
        
    // Initialize FSM with no state    
    auto fsm = new FSM();
    // Then use setup() for initial state
    fsm->setup(stateOn);
    fsm->start();        
        
}

void loop() {
    fsm->run();
}
```
### 📚Button Input Example
```cpp
#include "fsm/FSM.h"
#include "events/DebouncedButtonEventSource.h"
#include "fsm/EventTransition.h"

constexpr uint8_t BUTTON_PIN = 2;

auto buttonSource = new DebouncedButtonEventSource(BUTTON_PIN);
auto buttonPressed = new EventTransition(nextState, Event::buttonPressed, buttonSource);
```

## 📚Configuration

The library provides several configuration options through preprocessor definitions:

```cpp
// Debug options
#define FSM_DEBUG          // Enable general FSM debugging
#define FSM_DEBUG_STATE    // Enable state transition debugging
#define FSM_DEBUG_EVENT    // Enable event debugging
#define FSM_DEBUG_TIMER    // Enable timer debugging
#define ACTION_DEBUG       // Enable action debugging
#define SCHEDULER_DEBUG    // Enable scheduler debugging
```

## Core Concepts

### States

**Flexible State Management**

States represent system configurations with lifecycle hooks:

- `State`: Base class for implementing FSM states

- Lifecycle hooks: `onEnter()`, `onExit()`, `onUpdate()`

- Built-in timer support

  - `onEnter`: Initialization and entry actions

  - `onExit`: Cleanup and exit actions

  - `onUpdate`: No transition state behavior


### Transitions

**Flexible Transitions Management**

- Support for multiple state types and transitions
- Built-in timer functionality for timed state transitions
- Priority-based transition system

Five transition types with priority ordering:
1. `PriorityTransition`: Highest priority, combines events and timeouts
2. `ConditionTransition`: Evaluates boolean conditions
3. `EventTransition`: Responds to system events
4. `TimeoutTransition`: Timer-based transitions
5. `ImmediateTransition`: Always triggers when checked

### Event Sources

- `BaseEventSource`: Base class for event sources
- `DebouncedButtonEventSource`: Debounced button input
- `SerialInterfaceEventSource`: Serial communication events
- `RawButtonEventSource`: Direct button input

### Event System

- Comprehensive event handling with support for button presses, serial input, and custom events
- Debounced button input support
- Event value types: integer, byte, and float
- Extensible event source system

Rich event handling with built-in support for:
- Button press/release
- Serial communication
- Timer events
- Custom event types

### Action Framework

- Support for periodic and timed actions
- Action scheduling with precise timing control
- Zero-drift timer implementation
- Chainable action execution

Reusable actions with precise timing:
- `Action`: Abstract base class for all actions
- `PeriodicAction`: Recurring behavior
- `TimedAction`: One-shot delayed execution
- `Scheduler`: Manages multiple actions

## Examples

**Example: Blinking LED using Actions**

```cpp
#include <Arduino.h>
#include "actions/PeriodicAction.h"
#include "actions/Scheduler.h"

constexpr uint8_t LED_PIN = 13;             // Pin number for the LED
constexpr unsigned long BLINK_PERIOD = 500; // Blink every 500 milliseconds

class BlinkAction : public PeriodicAction {
public:
    explicit BlinkAction() : PeriodicAction(BLINK_PERIOD) { }

    void action() override {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
};

auto blinkAction = new BlinkAction();
auto scheduler = new Scheduler();

void setup() {
    pinMode(LED_PIN, OUTPUT);
    scheduler->addAction(blinkAction);
}

void loop() {
    scheduler->run();
}
```

### Button Debouncing
```cpp
auto button = new DebouncedButtonEventSource(BUTTON_PIN);
auto ledState = new LedState();

// Transition when button is pressed
ledState->addTransition(new EventTransition(
    nextState,
    Event::buttonPressed,
    button
));
```

### Serial Interface
```cpp
auto serialEventSource = new SerialInterfaceEventSource();
auto processingState = new ProcessingState();

// React to serial input
processingState->addTransition(new EventTransition(
    processedState,
    Event::serialReceived,
    serialEventSource
));
```

## Examples and Use Cases  

Explore detailed examples in the `examples/` directory:  

- [ActionBlinkLed.cpp](examples/ActionBlinkLed.cpp) - Periodic LED blinking.  
- [blink.cpp](examples/blink.cpp) - FSM-driven LED control.  
- [TesteSerialButton.cpp](examples/TesteSerialButton.cpp) - Serial-controlled FSM.  

More examples in the [examples/](examples/) directory.

## Project Structure  

```
bestfsm
├── examples
├── src
├── include
└── tests
```

## 🔧 Technical Details
## Memory Management Philosophy in BestFSM

While BestFSM is designed for Arduino and embedded systems, it intentionally uses dynamic allocation and pointers through the `new` operator. This design choice offers several advantages for embedded systems:

### Pointer-Based Architecture

```cpp
auto stateOn = new LedOnState(1000);
auto transition = new StateTimeoutTransition(stateOff);
state->addTransition(transition);
```

The pointer-based approach:
- Simplifies parameter passing
- Avoids unnecessary object copying
- Reduces stack memory usage
- Enables flexible object relationships

### Memory Safety Without Overhead

The library is designed for Arduino's infinite loop paradigm:
```cpp
void loop() {
    fsm->run();  // Runs indefinitely
}
```

Key characteristics:
- Objects are allocated once during setup
- No explicit deallocation needed
- Memory pattern remains stable during execution
- No memory leaks in practice due to program lifecycle

### Smart Pointers Omission

Traditional smart pointer concerns don't apply:
- No need for RAII in infinite loop context
- No benefit from automatic destruction
- Extra overhead avoided
- Memory footprint kept minimal

### Memory Efficiency

This approach actually improves memory efficiency:
```cpp
auto ledOnState = new LedOnState(1000)
// Direct pointer usage
ledOnState->addTransition(new StateTimeoutTransition(ledOffState); 
auto fsm = new FSM(ledOnState);  // Single allocation
fsm->start(); // Direct usage
...
...
...
fsm->run(); // Direct usage
```

Benefits:
- No object copying
- No memory fragmentation
- Predictable memory layout
- Minimal overhead

In embedded systems, this controlled use of dynamic allocation provides a pragmatic balance between modern C++ features and resource constraints.

### Memory Footprint
- Base FSM: ~100 bytes
- Per State: ~20 bytes
- Per Transition: ~12 bytes
- Event System: ~40 bytes base

### Timing Precision
- Timer Resolution: according to the Arduino clock
- Drift Compensation: Automatic
- Minimum State Duration: according to the Arduino clock

## Contributing

We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

## 🙏 Acknowledgments

- Inspired by modern FSM design patterns
- Built with embedded systems best practices
- Developed with reliability and ease of use in mind
- Thanks to all contributors

## 📞 Contact

Project Link: [https://github.com/wladimiresposito/BestFSM](https://github.com/wladimiresposito/BestFSM)
