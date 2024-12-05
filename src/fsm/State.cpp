/**
* Implements the functionality of the State class, including transition management,
 * timer handling, and lifecycle hooks.
 */

#include "fsm/State.h"
#include "fsm/Transition.h"
#include "events/Event.h"
#include "actions/AlarmTimer.h"

// Static member initialization.
/**
 * Static counter to assign unique IDs to each state.
 */
int8_t State::_ids = -1;

/**
 * Constructs a state with an optional timeout duration.
 *
 * @param timeout Timeout duration in milliseconds. Defaults to 0 (no timeout).
 */
State::State(const unsigned long timeout) {
    if (timeout > 0) {
        stateTimer = new AlarmTimer(timeout);
    }
}

/**
 * Adds a transition to the state.
 *
 * @param transition Pointer to the transition to add.
 * @return A pointer to this state for method chaining.
 */
State* State::addTransition(Transition* transition) {
    if (firstTransition == nullptr) {
        firstTransition = transition;
        lastTransition = transition;
    } else {
        lastTransition->setNext(transition);
        lastTransition = transition;
    }
    totalTransitions++;
    transition->setOwner(this);
    return this;
}

/**
 * Checks transitions for a triggered condition.
 *
 * @return Pointer to the triggered transition, or `nullptr` if none are triggered.
 */
Transition* State::checkTransitions() {
    if (firstTransition) {
        for (auto priority = PRIORITY_TRANSITION; priority <= IMMEDIATE_TRANSITION;
             priority = static_cast<TransitionPriority>(priority + 1)) {
            for (Transition* tr = firstTransition; tr != nullptr; tr = tr->getNext()) {
                if (tr->getPriority() == priority && tr->isTriggered()) {
                    triggeredTransition = tr;
                    return tr;
                }
            }
        }
    }
    triggeredTransition = nullptr;
    return nullptr;
}

/**
 * Checks whether the state's timer has elapsed.
 *
 * @return `true` if the timer has elapsed, `false` otherwise.
 */
bool State::isTimerElapsed() const {
    return stateTimer && stateTimer->elapsed();
}

/**
 * Starts the state's timer.
 */
void State::startStateTimer() const {
    if (stateTimer) {
        stateTimer->start();
    }
}

/**
 * Stops the state's timer.
 */
void State::stopStateTimer() const {
    if (stateTimer) {
        stateTimer->stop();
    }
}

/**
 * Hook invoked when entering the state.
 *
 * @param event Pointer to the event triggering the transition. Can be `nullptr`.
 */
void State::onEnter(Event* event) const {
    startStateTimer();
}

/**
 * Hook invoked when exiting the state.
 *
 * @param event Pointer to the event triggering the transition. Can be `nullptr`.
 */
void State::onExit(Event* event) const {
    stopStateTimer();
}

