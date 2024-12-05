/**
* Debug utilities for actions and schedulers.
 *
 * Responsibilities:
 * - Provides macros for conditional debug logging.
 *
 * Design Considerations:
 * - Logging is enabled or disabled based on preprocessor definitions (`ACTION_DEBUG` and `SCHEDULER_DEBUG`).
 */
#ifndef ACTION_DEBUG_H
#define ACTION_DEBUG_H

#ifdef ACTION_DEBUG
    #define ACTION_DEBUG_PRINT(msg) Serial.print(F(msg)) ///< Prints a debug message.
    #define ACTION_DEBUG_PRINTLN(msg) Serial.println(F(msg)) ///< Prints a debug message with a newline.
#else
    #define ACTION_DEBUG_PRINT(msg) ///< No-op if `ACTION_DEBUG` is not defined.
    #define ACTION_DEBUG_PRINTLN(msg) ///< No-op if `ACTION_DEBUG` is not defined.
#endif

#ifdef SCHEDULER_DEBUG
    #define SCHEDULER_DEBUG_PRINT(msg) Serial.print(F(msg)) ///< Prints a scheduler debug message.
    #define SCHEDULER_DEBUG_PRINTLN(msg) Serial.println(F(msg)) ///< Prints a scheduler debug message with a newline.
#else
    #define SCHEDULER_DEBUG_PRINT(msg) ///< No-op if `SCHEDULER_DEBUG` is not defined.
    #define SCHEDULER_DEBUG_PRINTLN(msg) ///< No-op if `SCHEDULER_DEBUG` is not defined.
#endif

#endif
