//
// Created by wla on 08/11/2024.
//

#ifndef STATE_TIMER_TRANSITION_H
#define STATE_TIMER_TRANSITION_H

#include "Transition.h"

/**
 * @brief Timer-based Transition
 *
 * That triggers based on state timer.
 * Has lowest priority in transition checking.
 *
 * Key features:
 * - Timer-based triggering
 * - Uses state's timer
 * - Lowest transition priority
 *
 * Usage:
 * @code
 * state->addTransition(new StateTimerTransition(nextState));
 * @endcode
 */
class StateTimeoutTransition final : public Transition {
public:
    /**
     * Constructs a state timeout transition.
     *
     * @param next Pointer to the next state.
     */
    explicit StateTimeoutTransition(State* next)
        : Transition(next) {  }

    TransitionPriority getPriority() const override { return TIMEOUT_TRANSITION; }

    bool isTriggered() override {
        // The owner always exists
        return  getOwner()->isTimerElapsed();
    }
};

#endif //STATE_TIMER_TRANSITION_H
