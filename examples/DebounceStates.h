/**
* States used for button debounce handling in an FSM.
 *
 * Responsibilities:
 * - Provides states for waiting, debouncing, and pressed button scenarios.
 */

#ifndef DEBOUNCE_STATES_H
#define DEBOUNCE_STATES_H

#include "fsm/State.h"

constexpr unsigned long DEBOUNCE_TIME = 60; ///< Default debounce duration in milliseconds.

/**
 * State for waiting for a button press.
 */
class WaitPressState final : public State {
public:
    /**
     * Constructs a `WaitPressState`.
     */
    WaitPressState() : State() { }

    /**
     * Invoked when entering the state.
     *
     * @param event Pointer to the triggering event.
     */
    void onEnter(Event* event) const override {
        State::onEnter(event);
    }
};

/**
 * State for handling button debouncing.
 */
class DebouncingState final : public State {
public:
    /**
     * Constructs a `DebouncingState` with a debounce duration.
     *
     * @param debounceTime Duration in milliseconds.
     */
    explicit DebouncingState(const unsigned long debounceTime = DEBOUNCE_TIME) : State(debounceTime) { }

    /**
     * Invoked when entering the state.
     *
     * @param event Pointer to the triggering event.
     */
    void onEnter(Event* event) const override {
        State::onEnter(event);
    }
};

/**
 * State representing a pressed button.
 */
class PressedState final : public State {
public:
    /**
     * Constructs a `PressedState`.
     */
    PressedState() : State() { }

    /**
     * Invoked when entering the state.
     *
     * @param event Pointer to the triggering event.
     */
    void onEnter(Event* event) const override {
        State::onEnter(event);
    }
};

#endif
