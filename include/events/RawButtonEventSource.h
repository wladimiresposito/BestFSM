
#ifndef RAW_BUTTON_EVENT_SOURCE_H
#define RAW_BUTTON_EVENT_SOURCE_H

#include "BaseEventSource.h"

/**
 * Event source for detecting raw button state changes.
 *
 * Responsibilities:
 * - Monitors a button pin for state changes.
 * - Generates button press and release events.
 *
 * Design Considerations:
 * - Does not debounce the button; use `DebouncedButtonEventSource` for debouncing.
 *
 * Usage:
 * - Instantiate with a specific button pin.
 * - Call `getEvent` to retrieve the current button event.
 */
class RawButtonEventSource final : public BaseEventSource {
    uint8_t pin;           ///< The pin connected to the button.
    bool lastState{HIGH};  ///< Last recorded button state.

public:
    /**
     * Constructs a raw button event source.
     *
     * @param buttonPin The pin connected to the button.
     */
    explicit RawButtonEventSource(const uint16_t buttonPin) : pin{buttonPin} { }

    /**
     * Retrieves the button pin.
     *
     * @return The pin number associated with the button.
     */
    uint8_t getPin() const { return pin; }

    /**
     * Retrieves the current button event.
     *
     * Behavior:
     * - Generates a `buttonPressed` event when the button state transitions to LOW.
     * - Generates a `buttonReleased` event when the button state transitions to HIGH.
     * - Returns `Event::none` if the state has not changed.
     *
     * @return Pointer to the generated event.
     */
    Event* getEvent() override {
        const bool currentState = digitalRead(pin);

        if (currentState != lastState) {
            lastState = currentState;
            if (currentState == HIGH) {
                return Event::buttonReleased->setByteValue(pin);
            }
            return Event::buttonPressed->setByteValue(pin);
        }
        return Event::none;
    }
};

#endif //RAW_BUTTON_EVENT_SOURCE_H
