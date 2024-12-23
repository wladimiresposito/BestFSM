/**
* Debug utilities for the FSM framework.
 *
 * Responsibilities:
 * - Provides macros for conditional debug logging of FSM operations.
 *
 * Design Considerations:
 * - Separate macros are provided for state, event, and timer debugging.
 */

#ifndef FSM_DEBUG_H
#define FSM_DEBUG_H

#ifdef FSM_DEBUG_STATE
    #define FSM_DEBUG_STATE_PRINT(msg) Serial.print(msg) ///< Debug print for state transitions.
    #define FSM_DEBUG_STATE_PRINTLN(msg) Serial.println(msg) ///< Debug print with newline for state transitions.
#else
    #define FSM_DEBUG_STATE_PRINT(msg) ///< No-op if `FSM_DEBUG_STATE` is not defined.
    #define FSM_DEBUG_STATE_PRINTLN(msg) ///< No-op if `FSM_DEBUG_STATE` is not defined.
#endif

#ifdef FSM_DEBUG_EVENT
    #define FSM_DEBUG_EVENT_PRINT(msg) Serial.print(F(msg)) ///< Debug print for events.
    #define FSM_DEBUG_EVENT_PRINTLN(msg) Serial.println(F(msg)) ///< Debug print with newline for events.
#else
    #define FSM_DEBUG_EVENT_PRINT(msg) ///< No-op if `FSM_DEBUG_EVENT` is not defined.
    #define FSM_DEBUG_EVENT_PRINTLN(msg) ///< No-op if `FSM_DEBUG_EVENT` is not defined.
#endif

#ifdef FSM_DEBUG_TIMER
    #define FSM_DEBUG_TIMER_PRINT(msg) Serial.print(F(msg)) ///< Debug print for timers.
    #define FSM_DEBUG_TIMER_PRINTLN(msg) Serial.println(F(msg)) ///< Debug print with newline for timers.
#else
    #define FSM_DEBUG_TIMER_PRINT(msg) ///< No-op if `FSM_DEBUG_TIMER` is not defined.
    #define FSM_DEBUG_TIMER_PRINTLN(msg) ///< No-op if `FSM_DEBUG_TIMER` is not defined.
#endif

#endif
