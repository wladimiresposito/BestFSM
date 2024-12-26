//
// Created by wla on 24/12/24.
//

#ifndef SIMPLE_TRAFFIC_LIGHT_CONTROLLER_H
#define SIMPLE_TRAFFIC_LIGHT_CONTROLLER_H

/****************************************************
 * TrafficLightController.ino
 *
 * Demonstrates a simple traffic light FSM.
 * States: GreenState, YellowState, RedState
 * Each state has a timer. When the timer elapses,
 * we transition to the next state.
 ****************************************************/

#include <Arduino.h>

// Include the BestFSM framework
#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"

// Pin definitions (adjust as needed)
constexpr uint8_t GREEN_LED_PIN  = 8;
constexpr uint8_t YELLOW_LED_PIN = 9;
constexpr uint8_t RED_LED_PIN    = 10;

// State durations in milliseconds
constexpr unsigned long GREEN_TIME  = 5000; // 5 seconds
constexpr unsigned long YELLOW_TIME = 2000; // 2 seconds
constexpr unsigned long RED_TIME    = 5000; // 5 seconds

// Define GreenState
class GreenState : public State {
public:
    explicit GreenState(unsigned long timeout) : State(timeout) {}

    void onEnter(Event* event) const override {
        Serial.println("Entering Green State");
        // Turn on green LED, turn off others
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        State::onEnter(event);
    }
};

// Define YellowState
class YellowState : public State {
public:
    explicit YellowState(unsigned long timeout) : State(timeout) {}

    void onEnter(Event* event) const override {
        Serial.println("Entering Yellow State");
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        State::onEnter(event);
    }
};

// Define RedState
class RedState : public State {
public:
    explicit RedState(unsigned long timeout) : State(timeout) {}

    void onEnter(Event* event) const override {
        Serial.println("Entering Red State");
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);
        State::onEnter(event);
    }
};

#endif //SIMPLE_TRAFFIC_LIGHT_CONTROLLER_H
