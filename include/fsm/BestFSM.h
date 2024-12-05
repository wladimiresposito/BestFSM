/**
* Main include file for the FSM framework.
 *
 * Responsibilities:
 * - Includes essential FSM-related headers.
 * - Provides macros for debugging FSM operations.
 *
 * Design Considerations:
 * - Enables conditional debugging output based on the `FSM_DEBUG` macro.
 */

#ifndef BEST_FSM_H
#define BEST_FSM_H

#ifdef FSM_DEBUG
    #define FSM_DEBUG_PRINT(x) Serial.println(F(x)) ///< Debug print macro.
#else
    #define FSM_DEBUG_PRINT(x) ///< No-op if `FSM_DEBUG` is not defined.
#endif

#include "Transition.h"
#include "State.h"
#include "FSM.h"

#endif
