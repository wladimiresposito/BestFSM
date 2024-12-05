/**
 * Defines the implementation of the FSM class, including methods to start,
 * stop, and run the finite state machine (FSM) and manage state transitions.
 */

#include "fsm/FSM.h"
#include "fsm/Transition.h"
#include "events/Event.h"

/**
 * Starts the FSM, transitioning to the initial state and invoking its `onEnter` method.
 *
 * Preconditions:
 * - The FSM must have an initial state configured via the constructor or `setup`.
 *
 * Postconditions:
 * - The FSM's `running` state is set to true.
 * - The current state is set to the initial state.
 * - The `onEnter` method of the initial state is invoked.
 */

void FSM::start() {
    if (!initialState) return;
    currentState = initialState;
    currentState->onEnter(nullptr);
    running = true;
}

/**
 * Stops the FSM, staying in the current state.
 *
 * Postconditions:
 * - The FSM's `running` state is set to false.
 * - If the FSM was running
 */
void FSM::stop() {
    running = false;
}

void FSM::restart() {
    running = true;
}

/**
 * Executes a single FSM update cycle.
 *
 * Behavior:
 * - If a triggered transition is detected, the FSM transitions to the corresponding state.
 * - If no transitions are triggered, invokes the `onUpdate` method of the current state.
 *
 * Preconditions:
 * - The FSM must have a currentState state and be running state.
 */
void FSM::run() {
    if (!running || !currentState) { return; }

    const Transition* triggeredTransition = currentState->checkTransitions();

    if (triggeredTransition) {
        State* nextState = triggeredTransition->getNextState();
        Event* event = triggeredTransition->getLastEvent();
        if (nextState) {
            currentState->onExit(event);
#ifdef FSM_DEBUG
            logStateTransition(currentState, nextState);
#endif
            currentState = nextState;
            currentState->onEnter(event);
        }
    } else {
        currentState->onUpdate();
    }
}
