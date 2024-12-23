//
// Created by wla on 23/12/24.
//

#ifndef TRAFFIC_LIGHT_CONTROLLER_H
#define TRAFFIC_LIGHT_CONTROLLER_H

#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/EventTransition.h"
#include "fsm/ConditionTransition.h"
#include "DebouncedButtonEventSource.h"

// Pin definitions
constexpr uint8_t RED_PIN = 2;
constexpr uint8_t YELLOW_PIN = 3;
constexpr uint8_t GREEN_PIN = 4;
constexpr uint8_t PEDESTRIAN_BUTTON_PIN = 5;
constexpr uint8_t EMERGENCY_BUTTON_PIN = 6;

// Timing constants (in milliseconds)
constexpr unsigned long RED_DURATION = 30000;    // 30 seconds
constexpr unsigned long GREEN_DURATION = 25000;  // 25 seconds
constexpr unsigned long YELLOW_DURATION = 5000;  // 5 seconds
constexpr unsigned long PEDESTRIAN_WAIT = 3000;  // 3 seconds wait after button press
constexpr unsigned long BLINK_INTERVAL = 500;    // 0.5 second blink interval

// Event sources
auto pedestrianButton = new DebouncedButtonEventSource(PEDESTRIAN_BUTTON_PIN);
auto emergencyButton = new DebouncedButtonEventSource(EMERGENCY_BUTTON_PIN);

// Forward declarations of states
class RedState;
class YellowState;
class GreenState;
class EmergencyState;

// Base state with common functionality
class TrafficLightState: public State {
protected:
    AlarmTimer* stateTimer{nullptr};

    void turnOffAllLights() const {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(YELLOW_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
    }
};

// Red light state
class RedState final: public TrafficLightState {
public:
    explicit RedState(unsigned long duration = RED_DURATION): TrafficLightState() {
        // Initialize the state with the specified duration
        stateTimer = new AlarmTimer(duration);
    }

    void onEnter(Event* event) const override {
        turnOffAllLights();
        digitalWrite(RED_PIN, HIGH);
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        digitalWrite(RED_PIN, LOW);
        State::onExit(event);
    }
};

// Yellow light state with blinking capability
class YellowState final: public TrafficLightState {
    bool isBlinking;
    AlarmTimer* blinkTimer;

public:
    explicit YellowState(unsigned long duration = YELLOW_DURATION, bool blink = false):
        TrafficLightState(), isBlinking(blink) {
        stateTimer = new AlarmTimer(duration);
        blinkTimer = new AlarmTimer(BLINK_INTERVAL);
    }

    void onEnter(Event* event) const override {
        turnOffAllLights();
        digitalWrite(YELLOW_PIN, HIGH);
        if (isBlinking) {
            blinkTimer->start();
        }
        State::onEnter(event);
    }

    void onUpdate() const override {
        if (isBlinking && blinkTimer->elapsed()) {
            digitalWrite(YELLOW_PIN, !digitalRead(YELLOW_PIN));
        }
    }

    void onExit(Event* event) const override {
        digitalWrite(YELLOW_PIN, LOW);
        State::onExit(event);
    }
};

// Green light state
class GreenState final: public TrafficLightState {
    bool pedestrianWaiting;

public:
    explicit GreenState(unsigned long duration = GREEN_DURATION):
        TrafficLightState(), pedestrianWaiting(false) {
        stateTimer = new AlarmTimer(duration);
    }

    void onEnter(Event* event) const override {
        turnOffAllLights();
        digitalWrite(GREEN_PIN, HIGH);
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        digitalWrite(GREEN_PIN, LOW);
        State::onExit(event);
    }
};

// Emergency state (flashing red)
class EmergencyState final: public TrafficLightState {
    AlarmTimer* blinkTimer;

public:
    explicit EmergencyState(): TrafficLightState() {
        blinkTimer = new AlarmTimer(BLINK_INTERVAL);
    }

    void onEnter(Event* event) const override {
        turnOffAllLights();
        blinkTimer->start();
        State::onEnter(event);
    }

    void onUpdate() const override {
        if (blinkTimer->elapsed()) {
            digitalWrite(RED_PIN, !digitalRead(RED_PIN));
        }
    }

    void onExit(Event* event) const override {
        digitalWrite(RED_PIN, LOW);
        State::onExit(event);
    }
};

// Traffic Light Controller class
class TrafficLightController {
    FSM* fsm;

    // States
    RedState* redState;
    YellowState* yellowState;
    GreenState* greenState;
    EmergencyState* emergencyState;

public:
    TrafficLightController() {
        // Create states
        redState = new RedState();
        yellowState = new YellowState();
        greenState = new GreenState();
        emergencyState = new EmergencyState();

        // Configure normal operation transitions
        redState->addTransition(new StateTimeoutTransition(greenState));
        greenState->addTransition(new StateTimeoutTransition(yellowState));
        yellowState->addTransition(new StateTimeoutTransition(redState));

        // Add emergency transitions
        redState->addTransition(new EventTransition(
            emergencyState,
            Event::buttonPressed,
            emergencyButton
        ));
        yellowState->addTransition(new EventTransition(
            emergencyState,
            Event::buttonPressed,
            emergencyButton
        ));
        greenState->addTransition(new EventTransition(
            emergencyState,
            Event::buttonPressed,
            emergencyButton
        ));

        // Add pedestrian button transition (shortens green duration)
        greenState->addTransition(new EventTransition(
            yellowState,
            Event::buttonPressed,
            pedestrianButton
        ));

        // Return from emergency transition
        emergencyState->addTransition(new EventTransition(
            redState,
            Event::buttonPressed,
            emergencyButton
        ));

        // Initialize FSM with red state
        fsm = new FSM(redState);
    }

    void begin() {
        // Initialize pins
        pinMode(RED_PIN, OUTPUT);
        pinMode(YELLOW_PIN, OUTPUT);
        pinMode(GREEN_PIN, OUTPUT);
        pinMode(PEDESTRIAN_BUTTON_PIN, INPUT_PULLUP);
        pinMode(EMERGENCY_BUTTON_PIN, INPUT_PULLUP);

        // Start the FSM
        fsm->start();
    }

    void update() {
        fsm->run();
    }
};


#endif //TRAFFIC_LIGHT_CONTROLLER_H
