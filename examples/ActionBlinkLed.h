/**
* Action for blinking an LED periodically.
 *
 * Responsibilities:
 * - Toggles an LED on/off at a defined interval.
 */

#ifndef ACTION_BLINK_LED_H
#define ACTION_BLINK_LED_H

#include <Arduino.h>
#include "actions/PeriodicAction.h"

class ActionBlinkLed final : public PeriodicAction {
    int pin; ///< Pin number for the LED.

public:
    /**
     * Constructs an LED blinking action.
     *
     * @param pin The pin number for the LED.
     * @param period The interval in milliseconds.
     */
    explicit ActionBlinkLed(const int pin, const long period)
        : PeriodicAction(period), pin(pin) { }

    /**
     * Toggles the LED state.
     */
    void action() override {
        digitalWrite(pin, !digitalRead(pin));
    }
};

#endif
