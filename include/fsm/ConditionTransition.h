//
// Created by wla on 08/11/2024.
//

#ifndef CONDITION_TRANSITION_H
#define CONDITION_TRANSITION_H

#include "Transition.h"
/**
 * @brief Condition-based transition
 *
 * Transition that triggers based on a boolean condition function.
 * Has highest priority in transition checking.
 *
 * Key features:
 * - Boolean condition evaluation
 * - Highest transition priority
 * - Custom condition functions
 *
 * Usage:
 * @code
 * state->addTransition(new ConditionTransition(
 *     nextState,
 *     []() { return digitalRead(PIN) == HIGH; }
 * ));
 * @endcode
 */
class ConditionTransition final : public Transition {
    bool (*condition)();  ///< Pointer to a condition function.

public:
    /**
     * Constructs a condition transition.
     *
     * @param next Pointer to the next state.
     * @param cond Pointer to the condition function.
     */
    ConditionTransition(State* next, bool (*cond)())
        : Transition(next), condition{cond} { }

    TransitionPriority getPriority() const override { return CONDITION_TRANSITION; }

    bool isTriggered() override {
        if (condition && condition()) {
            return true;
        }
        return false;
    }
};

#endif //CONDITION_TRANSITION_H
