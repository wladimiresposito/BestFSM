//
// Created by wla on 23/12/24.
//

#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include <Arduino.h>
#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/EventTransition.h"
#include "DebouncedButtonEventSource.h"

// Pin definitions
constexpr uint8_t BUTTON_PIN = 2;        // Button input pin
constexpr uint8_t MOTOR_OPEN_PIN = 3;    // Motor control pin for opening
constexpr uint8_t MOTOR_CLOSE_PIN = 4;   // Motor control pin for closing
constexpr uint8_t LIMIT_OPEN_PIN = 5;    // Limit switch for fully open position
constexpr uint8_t LIMIT_CLOSE_PIN = 6;   // Limit switch for fully closed position
constexpr uint8_t OBSTACLE_SENSOR_PIN = 7; // Obstacle detection sensor

// Timing constants (in milliseconds)
constexpr unsigned long OPENING_TIME = 5000;   // Time to open the door
constexpr unsigned long CLOSING_TIME = 5000;   // Time to close the door
constexpr unsigned long OPEN_TIME = 10000;     // Time door remains open

// Forward declarations
class ClosedState;
class OpeningState;
class OpenState;
class ClosingState;

// Base state for common door functionality
class DoorState : public State {
protected:
    AlarmTimer* stateTimer{nullptr};
    void stopMotor() const {
        digitalWrite(MOTOR_OPEN_PIN, LOW);
        digitalWrite(MOTOR_CLOSE_PIN, LOW);
    }
};

// State: Door is fully closed
class ClosedState final : public DoorState {
public:
    ClosedState() : DoorState() {}

    void onEnter(Event* event) const override {
        stopMotor();
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        State::onExit(event);
    }
};

// State: Door is opening
class OpeningState final : public DoorState {
public:
    explicit OpeningState(unsigned long timeout = OPENING_TIME) : DoorState() {
        stateTimer = new AlarmTimer(timeout);
    }

    void onEnter(Event* event) const override {
        digitalWrite(MOTOR_OPEN_PIN, HIGH);
        digitalWrite(MOTOR_CLOSE_PIN, LOW);
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        stopMotor();
        State::onExit(event);
    }
};

// State: Door is fully open
class OpenState final : public DoorState {
public:
    explicit OpenState(unsigned long timeout = OPEN_TIME) : DoorState() {
        stateTimer = new AlarmTimer(timeout);
    }

    void onEnter(Event* event) const override {
        stopMotor();
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        State::onExit(event);
    }
};

// State: Door is closing
class ClosingState final : public DoorState {
public:
    explicit ClosingState(unsigned long timeout = CLOSING_TIME) : DoorState() {
        stateTimer = new AlarmTimer(timeout);
    }

    void onEnter(Event* event) const override {
        digitalWrite(MOTOR_OPEN_PIN, LOW);
        digitalWrite(MOTOR_CLOSE_PIN, HIGH);
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
        stopMotor();
        State::onExit(event);
    }
};

// Door Controller class
class DoorController {
    FSM* fsm;
    DebouncedButtonEventSource* buttonSource;
    DebouncedButtonEventSource* obstacleSource;

    // States
    ClosedState* closedState;
    OpeningState* openingState;
    OpenState* openState;
    ClosingState* closingState;

    // Initialize limit switch reading
    bool isFullyOpen() const {
        return digitalRead(LIMIT_OPEN_PIN) == HIGH;
    }

    bool isFullyClosed() const {
        return digitalRead(LIMIT_CLOSE_PIN) == HIGH;
    }

    bool hasObstacle() const {
        return digitalRead(OBSTACLE_SENSOR_PIN) == HIGH;
    }

public:
    DoorController() {
        // Create states
        closedState = new ClosedState();
        openingState = new OpeningState();
        openState = new OpenState();
        closingState = new ClosingState();

        // Create event sources
        buttonSource = new DebouncedButtonEventSource(BUTTON_PIN);
        obstacleSource = new DebouncedButtonEventSource(OBSTACLE_SENSOR_PIN);

        // Configure transitions
        // From Closed state
        closedState->addTransition(new EventTransition(
            openingState,
            Event::buttonPressed,
            buttonSource
        ));

        // From Opening state
        openingState->addTransition(new StateTimeoutTransition(openState));
        openingState->addTransition(new EventTransition(
            openState,
            Event::buttonPressed,
            buttonSource
        ));

        // From Open state
        openState->addTransition(new StateTimeoutTransition(closingState));
        openState->addTransition(new EventTransition(
            closingState,
            Event::buttonPressed,
            buttonSource
        ));

        // From Closing state
        closingState->addTransition(new StateTimeoutTransition(closedState));
        closingState->addTransition(new EventTransition(
            openingState,
            Event::buttonPressed,
            buttonSource
        ));
        // Obstacle detection during closing
        closingState->addTransition(new EventTransition(
            openingState,
            Event::buttonPressed,
            obstacleSource
        ));

        // Initialize FSM with closed state
        fsm = new FSM(closedState);
    }

    void begin() {
        // Initialize pins
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinMode(MOTOR_OPEN_PIN, OUTPUT);
        pinMode(MOTOR_CLOSE_PIN, OUTPUT);
        pinMode(LIMIT_OPEN_PIN, INPUT_PULLUP);
        pinMode(LIMIT_CLOSE_PIN, INPUT_PULLUP);
        pinMode(OBSTACLE_SENSOR_PIN, INPUT);

        // Initial state
        stopMotor();

        // Start FSM
        fsm->start();
    }

    void stopMotor() const {
        digitalWrite(MOTOR_OPEN_PIN, LOW);
        digitalWrite(MOTOR_CLOSE_PIN, LOW);
    }

    void update() {
        fsm->run();
    }
};

#endif //DOOR_CONTROLLER_H
