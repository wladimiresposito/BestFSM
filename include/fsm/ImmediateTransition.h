//
// Created by wla on 16/11/2024.
//

#ifndef IMMEDIATE_TRANSITION_H
#define IMMEDIATE_TRANSITION_H

#include "Transition.h"

/**
 * Represents a transition that is always triggered immediately.
 *
 * Responsibilities:
 * - Always returns true when checked for triggering.
 *
 * Design Considerations:
 * - Useful for default or fallback transitions.
 */
class ImmediateTransition final : public Transition {  // ou UnconditionalTransition
public:
    /**
     * Constructs an immediate transition.
     *
     * @param next Pointer to the next state.
     */
    explicit ImmediateTransition(State* next): Transition(next) {  }

    TransitionPriority getPriority() const override { return IMMEDIATE_TRANSITION; }

    bool isTriggered() override {
        return true;  // Always transitions
    }
};

#endif //IMMEDIATE_TRANSITION_H
