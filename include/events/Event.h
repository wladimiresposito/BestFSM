//
// Created by wla on 08/11/2024.
//

#ifndef EVENT_H
#define EVENT_H

#include "GenericValue.h"

// Definitions of event types
enum class EventType: uint8_t {
    EVENT_NONE,
    EVENT_GLOBAL_TIMEOUT,
    EVENT_LOCAL_TIMEOUT,
    EVENT_CONDITION,
    EVENT_BUTTON_PRESSED,
    EVENT_BUTTON_RELEASED,
    EVENT_SERIAL_RECEIVED,
    EVENT_SERIAL_SENT,
    EVENT_CUSTOM
};

/**
 * Represents an event in the FSM, containing a type and optional associated value.
 *
 * Responsibilities:
 * - Encapsulates event type and value for use in state transitions.
 * - Provides methods to retrieve or set event values of various types.
 *
 * Static Members:
 * - Predefined events like `none`, `globalTimeout`, `buttonPressed`, etc., for convenience.
 *
 * Usage:
 * - Instantiate with a specific `EventType` and an optional value (int, float, or byte).
 * - Use type-specific getter methods (`getIntValue`, `getFloatValue`) to retrieve values.
 * - Compare events using equality and inequality operators.
 */
class Event {
    EventType type{EventType::EVENT_NONE}; ///< Type of the event.
    ValueType valueType{VALUE_NONE};      ///< Type of the associated value.
    GenericValue genValue;                ///< Union storing the event's value.

public:
    // Static members representing commonly used events.
    static Event* none;              ///< Represents no event.
    static Event* globalTimeout;     ///< Represents a global timeout event.
    static Event* localTimeout;      ///< Represents a local timeout event.
    static Event* buttonPressed;     ///< Represents a button press event.
    static Event* buttonReleased;    ///< Represents a button release event.
    static Event* serialReceived;    ///< Represents a serial data received event.
    static Event* serialSent;        ///< Represents a serial data sent event.

    /**
     * Constructs an event with a specified type.
     *
     * @param type The type of the event.
     */
    explicit Event(EventType type);

    /**
     * Constructs an event with a type and an integer value.
     *
     * @param type The type of the event.
     * @param value The integer value associated with the event.
     */
    explicit Event(EventType type, int value);

    /**
     * Constructs an event with a type and a byte value.
     *
     * @param type The type of the event.
     * @param value The byte value associated with the event.
     */
    explicit Event(EventType type, uint8_t value);

    /**
     * Constructs an event with a type and a float value.
     *
     * @param type The type of the event.
     * @param value The float value associated with the event.
     */
    explicit Event(EventType type, float value);

    /**
     * Sets the event's integer value.
     *
     * @param v The integer value to set.
     * @return A pointer to the updated event.
     */
    Event* setIntValue(int v);

    /**
     * Sets the event's float value.
     *
     * @param v The float value to set.
     * @return A pointer to the updated event.
     */
    Event* setFloatValue(float v);

    /**
     * Sets the event's byte value.
     *
     * @param v The byte value to set.
     * @return A pointer to the updated event.
     */
    Event* setByteValue(uint8_t v);

    /**
     * Retrieves the event's integer value.
     *
     * @return The integer value if set, otherwise 0.
     */
    int getIntValue() const;

    /**
     * Retrieves the event's float value.
     *
     * @return The float value if set, otherwise 0.0f.
     */
    float getFloatValue() const;

    /**
     * Retrieves the event's byte value.
     *
     * @return The byte value if set, otherwise 0.
     */
    uint8_t getByteValue() const;

    /**
     * Retrieves the event's type.
     *
     * @return The event's type as an `EventType`.
     */
    EventType getEventType() const;

    /**
     * Equality operator to compare two events.
     *
     * @param other The event to compare against.
     * @return `true` if the events are of the same type, `false` otherwise.
     */
    bool operator==(const Event& other) const;

    /**
     * Inequality operator to compare two events.
     *
     * @param other The event to compare against.
     * @return `true` if the events are of different types, `false` otherwise.
     */
    bool operator!=(const Event& other) const;

    /**
     * Equality operator to compare two events.
     *
     * @param other The event pointer to compare against.
     * @return `true` if the events are of the same type, `false` otherwise.
     */
    bool operator==(const Event* other) const;

    /**
     * Inequality operator to compare two events.
     *
     * @param other The event pointer to compare against.
     * @return `true` if the events are of different types, `false` otherwise.
     */
    bool operator!=(const Event* other) const;
};


#endif // EVENT_H

