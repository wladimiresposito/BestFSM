/**
 * Represents a debounced button input.
 *
 * Responsibilities:
 * - Handles button press/release events with debounce logic.
 * - Provides methods to check button state and event occurrence.
 */

#ifndef DEBOUNCED_BUTTON_H
#define DEBOUNCED_BUTTON_H

#include <Arduino.h>
#include "actions/AlarmTimer.h"

class DebouncedButton {
private:
    uint8_t pin; ///< Pin number connected to the button.
    AlarmTimer* debounceTimer; ///< Timer for handling debounce.
    bool lastStableState = HIGH; ///< Last stable state of the button.
    bool lastRawState = HIGH; ///< Last raw (non-debounced) state of the button.
    bool buttonPressed = false; ///< Indicates if the button was pressed.
    bool buttonReleased = false; ///< Indicates if the button was released.

public:
    /**
     * Constructs a debounced button.
     *
     * @param buttonPin The pin number connected to the button.
     * @param debounceTime The debounce duration in milliseconds.
     */
    explicit DebouncedButton(const uint8_t buttonPin, const unsigned long debounceTime = 100)
        : pin{buttonPin}, debounceTimer{new AlarmTimer(debounceTime)} {
        pinMode(pin, INPUT_PULLUP);
    }

    /**
     * Updates the button state and checks for debounced events.
     */
    void update() {
        buttonPressed = false;
        buttonReleased = false;

        const bool currentState = digitalRead(pin);

        if (currentState != lastRawState) {
            lastRawState = currentState;
            debounceTimer->start();
        } else if (debounceTimer->elapsed()) {
            if (currentState != lastStableState) {
                if (currentState == LOW) {
                    buttonPressed = true;
                } else {
                    buttonReleased = true;
                }
                lastStableState = currentState;
            }
        }
    }

    /**
     * Checks if the button was pressed.
     *
     * @return `true` if the button was pressed since the last update, `false` otherwise.
     */
    bool isPressed() const { return buttonPressed; }

    /**
     * Checks if the button was released.
     *
     * @return `true` if the button was released since the last update, `false` otherwise.
     */
    bool isReleased() const { return buttonReleased; }

    /**
     * Retrieves the current debounced state of the button.
     *
     * @return `true` if the button is pressed, `false` otherwise.
     */
    bool getState() const { return lastStableState == LOW; }

    /**
     * Retrieves the pin number connected to the button.
     *
     * @return The pin number.
     */
    uint8_t getPin() const { return pin; }
};

#endif
