/**
* Event source for simulating button presses and releases via serial input.
 *
 * Responsibilities:
 * - Monitors serial input and generates button events based on predefined characters.
 */

#ifndef FAKE_SERIAL_BUTTON_EVENT_SOURCE_H
#define FAKE_SERIAL_BUTTON_EVENT_SOURCE_H

#include "events/SerialInterfaceEventSource.h"

class FakeSerialButtonEventSource final : public SerialInterfaceEventSource {
    const char expectedCharPressed; ///< Character indicating a button press.
    const char expectedCharReleased; ///< Character indicating a button release.

public:
    /**
     * Constructs a fake serial button event source.
     *
     * @param charPressed Character representing a button press.
     * @param charReleased Character representing a button release.
     */
    explicit FakeSerialButtonEventSource(const char charPressed, const char charReleased)
        : expectedCharPressed{charPressed}, expectedCharReleased{charReleased} { }

    /**
     * Retrieves the current button event based on serial input.
     *
     * Behavior:
     * - Matches serial input to `expectedCharPressed` or `expectedCharReleased`.
     *
     * @return Pointer to the generated event or `Event::none` if no event occurred.
     */
    Event* getEvent() override {
        const Event* serialEvent = SerialInterfaceEventSource::getEvent();
        if (serialEvent == Event::none) {
            return Event::none;
        }
        const char received = static_cast<char>(serialEvent->getIntValue());
        if (received == expectedCharPressed) {
            return Event::buttonPressed->setByteValue(received);
        }
        if (received == expectedCharReleased) {
            return Event::buttonReleased->setByteValue(received);
        }
        return Event::none;
    }
};

#endif
