//
// Created by wla on 08/11/2024.
//
#include "events/Event.h"


/**
 * Defines the implementation of the Event class, including its constructors,
 * methods for value handling, and static event initializations.
 */

#include "events/Event.h"

// Static member initializations.
/**
 * Represents no event. Used as a default placeholder.
 */
Event* Event::none = new Event(EventType::EVENT_NONE);

/**
 * Represents a global timeout event.
 */
Event* Event::globalTimeout = new Event(EventType::EVENT_GLOBAL_TIMEOUT);

/**
 * Represents a local timeout event.
 */
Event* Event::localTimeout = new Event(EventType::EVENT_LOCAL_TIMEOUT);

/**
 * Represents a button press event.
 */
Event* Event::buttonPressed = new Event(EventType::EVENT_BUTTON_PRESSED);

/**
 * Represents a button release event.
 */
Event* Event::buttonReleased = new Event(EventType::EVENT_BUTTON_RELEASED);

/**
 * Represents a serial data received event.
 */
Event* Event::serialReceived = new Event(EventType::EVENT_SERIAL_RECEIVED);

/**
 * Represents a serial data sent event.
 */
Event* Event::serialSent = new Event(EventType::EVENT_SERIAL_SENT);

/**
 * Constructs an event with a specified type.
 *
 * @param type The type of the event.
 */
Event::Event(const EventType type) : type{type}, genValue{0} { }

/**
 * Constructs an event with a type and a byte value.
 *
 * @param type The type of the event.
 * @param value The byte value associated with the event.
 */
Event::Event(const EventType type, const uint8_t value)
    : type{type}, valueType{VALUE_BYTE}, genValue{value} { }

/**
 * Constructs an event with a type and an integer value.
 *
 * @param type The type of the event.
 * @param value The integer value associated with the event.
 */
Event::Event(const EventType type, const int value)
    : type{type}, valueType{VALUE_INT}, genValue{value} { }

/**
 * Constructs an event with a type and a float value.
 *
 * @param type The type of the event.
 * @param value The float value associated with the event.
 */
Event::Event(const EventType type, const float value)
    : type{type}, valueType{VALUE_FLOAT}, genValue{value} { }

/**
 * Sets the event's integer value.
 *
 * @param v The integer value to set.
 * @return A pointer to the updated event.
 */
Event* Event::setIntValue(const int v) {
    genValue.intValue = v;
    valueType = VALUE_INT;
    return this;
}

/**
 * Sets the event's byte value.
 *
 * @param v The byte value to set.
 * @return A pointer to the updated event.
 */
Event* Event::setByteValue(const uint8_t v) {
    genValue.byteValue = v;
    valueType = VALUE_BYTE;
    return this;
}

/**
 * Sets the event's float value.
 *
 * @param v The float value to set.
 * @return A pointer to the updated event.
 */
Event* Event::setFloatValue(const float v) {
    genValue.floatValue = v;
    valueType = VALUE_FLOAT;
    return this;
}

/**
 * Retrieves the event's integer value.
 *
 * @return The integer value if set, otherwise 0.
 */
int Event::getIntValue() const {
    if (valueType == VALUE_INT) {
        return genValue.intValue;
    }
    return 0;
}

/**
 * Retrieves the event's float value.
 *
 * @return The float value if set, otherwise 0.0f.
 */
float Event::getFloatValue() const {
    if (valueType == VALUE_FLOAT) {
        return genValue.floatValue;
    }
    return 0.0f;
}

/**
 * Retrieves the event's byte value.
 *
 * @return The byte value if set, otherwise 0.
 */
uint8_t Event::getByteValue() const {
    if (valueType == VALUE_BYTE) {
        return genValue.byteValue;
    }
    return 0;
}

/**
 * Retrieves the event's type.
 *
 * @return The event's type as an `EventType`.
 */
EventType Event::getEventType() const {
    return type;
}

/**
 * Compares the current event with another event for equality.
 *
 * @param other The event to compare against.
 * @return `true` if the events are of the same type, `false` otherwise.
 */
bool Event::operator==(const Event& other) const {
    return type == other.type;
}

/**
 * Compares the current event pointer with another event pointer for equality.
 *
 * @param other The event pointer to compare against.
 * @return `true` if the events are of the same type, `false` otherwise.
 */
bool Event::operator==(const Event* other) const {
    return type == other->type;
}

/**
 * Compares the current event with another event for inequality.
 *
 * @param other The event to compare against.
 * @return `true` if the events are of different types, `false` otherwise.
 */
bool Event::operator!=(const Event& other) const {
    return type != other.type;
}

/**
 * Compares the current event pointer with another event pointer for inequality.
 *
 * @param other The event pointer to compare against.
 * @return `true` if the events are of different types, `false` otherwise.
 */
bool Event::operator!=(const Event* other) const {
    return type != other->type;
}
