//
// Created by wla on 08/11/2024.
//
#ifndef GENERIC_VALUE_H
#define GENERIC_VALUE_H

#include <Arduino.h>


/**
 * Represents a union for storing different types of event values.
 *
 * Responsibilities:
 * - Supports multiple value types: integer, byte, and float.
 * - Provides a compact storage mechanism for associated event data.
 *
 * Design Considerations:
 * - Value type is determined externally by the `ValueType` enum.
 */
enum ValueType {
    VALUE_NONE,  ///< No value.
    VALUE_INT,   ///< Integer value.
    VALUE_BYTE,  ///< Byte value.
    VALUE_FLOAT  ///< Floating-point value.
};

/**
 * Union for storing event values in a generic format.
 *
 * Supported Types:
 * - Byte (`uint8_t`)
 * - Integer (`int`)
 * - Float (`float`)
 */
union GenericValue {
    uint8_t byteValue;  ///< Byte value.
    int intValue;       ///< Integer value.
    float floatValue;   ///< Floating-point value.

    /**
     * Constructor for initializing with a byte value.
     *
     * @param value The byte value to initialize.
     */
    explicit GenericValue(const uint8_t value) : byteValue{value} { }

    /**
     * Constructor for initializing with an integer value.
     *
     * @param value The integer value to initialize.
     */
    explicit GenericValue(const int value) : intValue{value} { }

    /**
     * Constructor for initializing with a float value.
     *
     * @param value The float value to initialize.
     */
    explicit GenericValue(const float value) : floatValue{value} { }
};

#endif //GENERIC_VALUE_H
