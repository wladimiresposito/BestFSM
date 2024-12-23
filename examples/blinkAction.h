/**
* Actions for controlling an LED using periodic intervals.
 *
 * Responsibilities:
 * - Defines `ActionLedOn` and `ActionLedOff` for toggling LED states.
 */

#ifndef BLINK_ACTION_H
#define BLINK_ACTION_H

#include <Arduino.h>
#include "actions/PeriodicAction.h"

#undef ACTION_DEBUG
#include "actions/ActionDebug.h"

constexpr uint8_t LED_PIN = 13; ///< Pin number for the LED.
constexpr unsigned long ON_TIME = 4000; ///< Duration for LED ON state in milliseconds.
constexpr unsigned long DELAY = 3000; ///< Delay before turning LED ON in milliseconds.
constexpr unsigned long OFF_TIME = 4000; ///< Duration for LED OFF state in milliseconds.

/**
 * Action for turning the LED ON.
 */
class ActionLedOn final : public PeriodicAction {
public:
    /**
     * Constructs an action for turning the LED ON.
     */
    explicit ActionLedOn() : PeriodicAction(ON_TIME) { }

    /**
     * Turns the LED ON.
     */
    void action() override {
        ACTION_DEBUG_PRINTLN("LED ON");
        digitalWrite(LED_PIN, HIGH);
    }
};

/**
 * Action for turning the LED OFF.
 */
class ActionLedOff final : public PeriodicAction {
public:
    /**
     * Constructs an action for turning the LED OFF with a delay.
     */
    explicit ActionLedOff() : PeriodicAction(OFF_TIME, DELAY) { }

    /**
     * Turns the LED OFF.
     */
    void action() override {
        ACTION_DEBUG_PRINTLN("LED OFF");
        digitalWrite(LED_PIN, LOW);
    }
};

#endif
