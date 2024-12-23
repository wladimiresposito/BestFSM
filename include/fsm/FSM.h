//
// Created by wla on 08/11/2024.
//
#ifndef FSM_H
#define FSM_H

#include "FSMDebug.h"


#include "State.h"

#ifdef FSM_DEBUG
inline void logStateTransition(State* from, State* to) {
        Serial.print(F("State transition: "));
        Serial.print(from->getId());
        Serial.print(F(" -> "));
        Serial.println(to->getId());
    }
#endif
/**
 * Manages the execution and state transitions of a finite state machine (FSM).
 *
 * Responsibilities:
 * - Tracks the current state and facilitates state transitions.
 * - Executes `onEnter`, `onExit`, and `onUpdate` hooks as necessary during FSM operation.
 * - Provides methods to start, stop, and run the FSM.
 *
 * Usage:
 * - Initialize with an optional initial state or configure later using `setup`.
 * - Use `start` to initialize the FSM and begin operation.
 * - Call `run` periodically to process transitions and update the current state.
 *
 * Design Considerations:
 * - The FSM must be explicitly started using the `start` method.
 * - Handles transitions based on the priority defined in `TransitionPriority`.
 */
class FSM {

    State* initialState;         ///< Pointer to the initial state of the FSM.
    State* currentState{nullptr};///< Pointer to the current state of the FSM.
    bool running{false};         ///< Indicates whether the FSM is currently running.

public:
    /**
     * Constructs an FSM instance with an optional initial state.
     *
     * @param initState Optional pointer to the initial state. Defaults to `nullptr`.
     */
    explicit FSM(State* initState): initialState{initState} { }

    ~FSM() = default;

    /**
     * Starts the FSM, transitioning to the initial state and invoking its `onEnter` method.
     *
     * Preconditions:
     * - The FSM must have an initial state configured via the constructor or `setup`.
     *
     * Postconditions:
     * - The FSM's `running` state is set to true.
     * - The current state is set to the initial state.
     */
    void start();

    /**
     * Stops the FSM, invoking the current state's `onExit` method if applicable.
     *
     * Postconditions:
     * - The FSM's `running` state is set to false.
     */
    void stop();
    void restart();

    /**
     * Executes a single FSM update cycle.
     *
     * Behavior:
     * - If a triggered transition is detected, the FSM transitions to the corresponding state.
     * - If no transitions are triggered, invokes the `onUpdate` method of the current state.
     *
     * Preconditions:
     * - The FSM must be in a running state (started).
     */
    void run();

    /**
     * Checks whether the FSM is currently running.
     *
     * @return `true` if the FSM is running, `false` otherwise.
     */
    bool isRunning() const { return running; }

    /**
     * Retrieves the current state of the FSM.
     *
     * @return Pointer to the current state, or `nullptr` if not running.
     */
    const State* getCurrentState() const { return currentState; }
};

#endif //FSM_H
