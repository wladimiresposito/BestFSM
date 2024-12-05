//
// Created by wla on 15/11/2024.
//

#ifndef SERIAL_INTERFACE_EVENT_SOURCE_H
#define SERIAL_INTERFACE_EVENT_SOURCE_H

#include "BaseEventSource.h"

/**
 * Event source for handling serial input as events.
 *
 * Responsibilities:
 * - Monitors the serial interface for incoming data.
 * - Generates a `serialReceived` event when data is received.
 *
 * Design Considerations:
 * - Supports one-byte serial input only.
 * - Returns `Event::none` if no data is available.
 *
 * Usage:
 * - Instantiate and call `getEvent` to retrieve serial events.
 */
class SerialInterfaceEventSource: public BaseEventSource {
    int expectedChar;
public:
    /**
     * Constructs a serial interface event source.
     */

    explicit SerialInterfaceEventSource(const int expectedChar = 0): expectedChar{expectedChar} { }

    /**
     * @brief Checks for and processes serial input events
     * @return Event* Pointer to an Event object or Event::none
     *
     * This function performs the following:
     * 1. Checks if data is available on the Serial port
     * 2. If data is available, it reads one byte
     * 3. If no specific character is expected (expectedChar == 0),
     *    it returns a serialReceived event with the read byte
     * 4. If a specific character is expected and matches the read byte,
     *    it returns a serialReceived event with the read byte
     * 5. If no event is triggered, it returns Event::none
     *
     * @note This function overrides a base class method
     */
    Event* getEvent() override {
        if (Serial.available() > 0) {
            const int received = Serial.read();
            if (expectedChar == 0) {
                return Event::serialReceived->setIntValue(received);
            }
            if (received == expectedChar) {
                return Event::serialReceived->setIntValue(received);
            }
        }
        return Event::none;
    }
};


#endif // SERIAL_INTERFACE_EVENT_SOURCE_H
