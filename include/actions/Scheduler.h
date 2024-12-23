//
// Created by wla on 14/11/2024.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Action.h"

#define SCHEDULER_DEBUG
#include "ActionDebug.h"

/**
* @brief Scheduler for managing multiple periodic actions with precise timing
*
* The Scheduler class provides a framework for managing and executing multiple
* PeriodicAction instances, each with its own precise timing requirements.
* It ensures that each action maintains its timing accuracy regardless of
* system load or execution delays.
*
* Key features:
* - Manages multiple independent periodic actions
* - Maintains timing accuracy for each action
* - Chainable action addition
* - Automatic cleanup of finished actions
* - Dynamic action management
*
* Usage example:
* @code
* // Define periodic actions
* class Blink : public PeriodicAction {
*     void action() override { digitalWrite(LED_PIN, !digitalRead(LED_PIN)); }
* };
*
* class SendData : public PeriodicAction {
*     void action() override { Serial.println("Sending data..."); }
* };
*
* // Create and setup scheduler
* auto scheduler = new Scheduler();  // Supports unlimited actions
* auto blink     = new Blink(1000);   // Every 1s
* auto send      = new Send(2000);    // Every 2s
*
* scheduler->addAction(blink)->addAction(send);
*
* // In loop
* void loop() {
*     scheduler->run();  // Maintains precise timing for all actions
* }
* @endcode
*
* @note The Scheduler does not own the PeriodicAction objects and will not
* delete them. The user is responsible for proper memory management of the
* action objects.
*
* @warning The actual execution time of each action should be significantly
* shorter than its period to prevent timing conflicts.
*
* @param n Maximum number of actions this scheduler can manage
*
* Performance considerations:
* - Actions are executed sequentially
* - Each action maintains its own precise timing
* - System load affects execution order but not timing accuracy
* - Memory usage is proportional to maximum number of actions
*/
class Scheduler {
    Action* first{nullptr}; ///< Pointer to the first action in the sequence.
    Action* last{nullptr}; ///< Pointer to the last action in the sequence.
    int currentActions{0}; ///< Number of actions in the scheduler.

public:
    explicit Scheduler() = default;
    ~Scheduler() = default;

    /**
     * Adds an action to the scheduler.
     *
     * @param action Pointer to the action to add.
     * @return A pointer to this scheduler for method chaining.
     */
    Scheduler* addAction(Action* action) {
        if (!first) {
            first = action;
            last = action;
        } else {
            last->setNext(action);
            last = action;
        }
        return this;
    }


    /**
     * Executes all registered actions sequentially.
     */
    void run() const {
        for (Action* action = first; action != nullptr; action = action->getNext()) {
            action->execute();
        }
    }
};

#endif //SCHEDULER_H
