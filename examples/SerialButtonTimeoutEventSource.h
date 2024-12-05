/**
* Event source for handling serial input with a timeout.
 *
 * Responsibilities:
 * - Generates events for specific serial characters within a timeout window.
 */

#ifndef SERIAL_BUTTON_TIMEOUT_EVENT_SOURCE_H
#define SERIAL_BUTTON_TIMEOUT_EVENT_SOURCE_H

#include "events/BaseEventSource.h"
#include "actions/AlarmTimer.h"

class SerialButtonTimeoutEventSource final : public BaseEventSource {
    AlarmTimer* serialTimer; ///< Timer for managing serial input timeout.
    bool waitingTimeout{false}; ///< Indicates if a timeout is active.
    const int expectedChar; ///< Character expected to trigger an event.

public:
    /**
     * Constructs a serial button timeout event source.
     *
     * @param charReceived Character to monitor for input.
     * @param timeout Timeout duration in milliseconds.
     */
    SerialButtonTimeoutEventSource(const int charReceived, const unsigned long timeout)
        : serialTimer{new AlarmTimer(timeout)}, expectedChar{charReceived} { }

    /**
     * Retrieves the current serial event or timeout event.
     *
     * Behavior:
     * - Generates a `serialReceived` event if the expected character is received.
     * - Resets the timeout if no input occurs.
     *
     * @return Pointer to the generated event or `Event::none` if no event occurred.
     */
    Event* getEvent() override {
        if (waitingTimeout) {
            if (serialTimer->elapsed()) {
                waitingTimeout = false;
            }
            return Event::none;
        }

        if (Serial.available() > 0) {
            const int received = Serial.read();
            if (received == expectedChar) {
                waitingTimeout = true;
                serialTimer->start();
                return Event::serialReceived->setIntValue(received);
            }
        }

        return Event::none;
    }
};

#endif
