//
// Created by wla on 14/11/2024.
//

#ifndef ACTION_H
#define ACTION_H

/**
 * Abstract base class for defining actions within the FSM framework.
 *
 * Responsibilities:
 * - Provides an interface for defining custom actions.
 * - Supports chaining of actions via linked structure.
 *
 * Design Considerations:
 * - Derived classes must implement the `action` method.
 * - The `execute` method invokes the `action` method and may include additional behavior.
 */
class Action {
    Action* next{nullptr}; ///< Pointer to the next action in the chain.

public:
    /**
     * Default constructor.
     */
    Action() = default;

    /**
     * Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Action() = default;

    /**
     * Sets the next action in the chain.
     *
     * @param action Pointer to the next action.
     */
    void setNext(Action* action) { next = action; }

    /**
     * Retrieves the next action in the chain.
     *
     * @return Pointer to the next action.
     */
    Action* getNext() const { return next; }

    /**
     * Executes the action.
     *
     * Behavior:
     * - Calls the `action` method, which must be implemented by derived classes.
     */
    virtual void execute() { action(); }

    /**
     * Defines the specific behavior of the action.
     *
     * This method must be implemented by derived classes.
     */
    virtual void action() = 0;
};


#endif // ACTION_H