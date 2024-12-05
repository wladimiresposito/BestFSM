#ifndef MULTITASK_H
#define MULTITASK_H

#include <Arduino.h>
#include "fsm/State.h"

#undef FSM_DEBUG_STATE
#include "fsm/FSMDebug.h"

constexpr uint8_t LED1 = LED_BUILTIN    ; ///< 13: Pin number for the LED BUILTIN.
constexpr uint8_t LED2 = LED_BUILTIN_RX ; ///< 17: Pin number for the LED RX.
constexpr uint8_t LED3 = LED_BUILTIN_TX ; ///< 30: Pin number for the LED TX.

/**
 * @class Led1OnState
 * @brief Represents a state in which LED1 is turned on.
 * @extends State
 *
 * This class is part of a Finite State Machine (FSM) and handles the state
 * where LED1 is active (on).
 */
class Led1OnState final : public State {
public:
    /**
     * @brief Construct a new Led1OnState object
     * @param timeout The duration this state should last
     */
    explicit Led1OnState(const long timeout) : State(timeout) { }

    /**
     * @brief Actions to perform when entering this state
     * @param event Pointer to the event that triggered this state
     *
     * This method turns on LED1, prints a debug message, and calls the parent's onEnter method.
     */
    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("on(LED1)");
        digitalWrite(LED1, HIGH);
        State::onEnter(event);
    }

};

/**
 * @class Led1OffState
 * @brief Represents a state in which LED1 is turned off.
 * @extends State
 *
 * This class is part of a Finite State Machine (FSM) and handles the state
 * where LED1 is inactive (off).
 */
class Led1OffState final : public State {
public:
    /**
     * @brief Construct a new Led1OffState object
     * @param timeout The duration this state should last
     */
    explicit Led1OffState(const long timeout) : State(timeout) { }

    /**
     * @brief Actions to perform when entering this state
     * @param event Pointer to the event that triggered this state
     *
     * This method turns off LED1, prints a debug message, and calls the parent's onEnter method.
     */
    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("Off(LED1)");
        digitalWrite(LED1, LOW);
        State::onEnter(event);
    }
};

class Led2OnState final : public State {
public:
    explicit Led2OnState(const long timeout) : State(timeout) { }

    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("on(LED2)");
        digitalWrite(LED2, HIGH);
        State::onEnter(event);
    }
};

class Led2OffState final : public State {
public:
    explicit Led2OffState(const long timeout) : State(timeout) { }

    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("Off(LED2)");
        digitalWrite(LED2, LOW);
        State::onEnter(event);
    }
};

class Led3OnState final : public State {
public:
    explicit Led3OnState(const long timeout) : State(timeout) { }

    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("on(LED3)");
        digitalWrite(LED3, HIGH);
        State::onEnter(event);
    }
};

class Led3OffState final : public State {
public:
    explicit Led3OffState(const long timeout) : State(timeout) { }

    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINTLN("Off(LED3)");
        digitalWrite(LED3, LOW);
        State::onEnter(event);
    }
};

#endif


