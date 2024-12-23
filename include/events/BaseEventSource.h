#ifndef BASE_EVENT_SOURCE_H
#define BASE_EVENT_SOURCE_H

#include "Event.h"
#include "actions/AlarmTimer.h"

/**
 * Base class for all event sources in the FSM.
 *
 * Responsibilities:
 * - Defines a common interface for retrieving events.
 * - Provides utility methods for handling timer-based timeout events.
 *
 * Design Considerations:
 * - Derived classes must implement the `getEvent` method to return specific event types.
 */
class BaseEventSource {
public:
    /**
     * Default constructor.
     */
    BaseEventSource() = default;

    /**
     * Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~BaseEventSource() = default;

    /**
     * Retrieves the current event generated by this source.
     *
     * @return Pointer to the event. Defaults to `Event::none` if no event is available.
     */
    virtual Event* getEvent() {
        return Event::none;
    }

    /**
     * Retrieves a timeout event if the specified timer has elapsed.
     *
     * @param timer Pointer to the timer to check.
     * @return Pointer to the timeout event if the timer has elapsed, otherwise `Event::none`.
     */
    virtual Event* getTimeoutEvent(AlarmTimer* timer) {
        if (timer && timer->elapsed()) {
            return Event::localTimeout;
        }
        return Event::none;
    }
};


#endif //BASE_EVENT_SOURCE_H
