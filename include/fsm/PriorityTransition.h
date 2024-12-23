//
// Created by wla on 08/11/2024.
//

#ifndef PRIORITY_TRANSITION_H
#define PRIORITY_TRANSITION_H

#include "EventTransition.h"
#include "Transition.h"
#include "State.h"

/**
 * @brief Priority transition class
 *
 * Special transition that checks both events and timeouts.
 * Always checked first regardless of other transitions.
 *
 * Key features:
 * - Highest checking priority
 * - Multiple trigger conditions
 * - Event and timer support
 *
 * Usage:
 * @code
 * state->addTransition(new PriorityTransition(
 *     nextState,
 *     Event::buttonPressed(),
 *     true  // Use timeout
 * ));
 * @endcode
 */
class PriorityTransition final : public EventTransition {
    bool checkTimeout{true}; ///< Whether to check the state's timer for timeout.


public:
    /**
     * Constructs a priority transition with only timeout check.
     *
     * @param next Pointer to the next state.
     */
     explicit PriorityTransition(State* next): EventTransition(next, nullptr, nullptr) { }

    /**
     * Constructs a priority transition with event and timeout check.
     *
     * @param next Pointer to the next state.
     * @param event Pointer to the expected event.
     * @param source Pointer to the event source.
     * @param hasTimeout Whether to include timeout checks.
     */
    explicit PriorityTransition(State* next, const Event* event, BaseEventSource* source, const bool hasTimeout = false):
         EventTransition(next, event, source), checkTimeout(hasTimeout) { }

    TransitionPriority getPriority() const override { return PRIORITY_TRANSITION; }

    bool isTriggered() override {
        // Checks event if specified
        if (EventTransition::isTriggered()) { return true; }

        // Check timeout if enabled
        if (checkTimeout) {
            return  getOwner()->isTimerElapsed();
        }

         return false;
    }
};

#endif //PRIORITY_TRANSITION_H
