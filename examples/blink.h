/**
 * Example states for controlling an LED using an FSM.
 *
 * Responsibilities:
 * - Defines `LedOnState` and `LedOffState` for toggling LED states.
 * - Includes lifecycle hooks (`onEnter` and `onExit`) for state behavior.
 */

#ifndef BLINK_H
#define BLINK_H

#undef FSM_DEBUG_STATE
#include "fsm/FSMDebug.h"
#include "fsm/State.h"

constexpr uint8_t LED_PIN = 13; ///< Pin number for the LED.

/**
 * State for turning the LED ON.
 */
class LedOnState final : public State {
public:
    /**
     * Constructs a state for turning the LED ON with a timeout.
     *
     * @param timeout Duration for the state in milliseconds.
     */
    explicit LedOnState(const unsigned long timeout) : State(timeout) { }

    /**
     * Turns the LED ON and starts the timer.
     *
     * @param event Pointer to the event triggering the state.
     */
    void onEnter(Event* event) const override {
        digitalWrite(LED_PIN, HIGH);
        FSM_DEBUG_STATE_PRINTLN("LED ON");
        State::onEnter(event);
    }

    /**
     * Stops the timer when exiting the state.
     *
     * @param event Pointer to the event triggering the exit.
     */
    void onExit(Event* event) const override {
        State::onExit(event);
    }
};

/**
 * State for turning the LED OFF.
 */
class LedOffState final : public State {
public:
    /**
     * Constructs a state for turning the LED OFF with a timeout.
     *
     * @param timeout Duration for the state in milliseconds.
     */
    explicit LedOffState(const unsigned long timeout) : State(timeout) { }

    /**
     * Turns the LED OFF and starts the timer.
     *
     * @param event Pointer to the event triggering the state.
     */
    void onEnter(Event* event) const override {
        digitalWrite(LED_PIN, LOW);
        FSM_DEBUG_STATE_PRINTLN("LED OFF");
        State::onEnter(event);
    }

    /**
     * Stops the timer when exiting the state.
     *
     * @param event Pointer to the event triggering the exit.
     */
    void onExit(Event* event) const override {
        State::onExit(event);
    }
};

#endif
