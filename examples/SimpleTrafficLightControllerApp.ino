//
// Created by wla on 24/12/24.
//

#include "SimpleTrafficLightController.h"

// Create global state objects
GreenState* greenState   = new GreenState(GREEN_TIME);
YellowState* yellowState = new YellowState(YELLOW_TIME);
RedState* redState       = new RedState(RED_TIME);

// Create a pointer to the FSM
FSM* trafficFsm = nullptr;

void setup() {
    Serial.begin(9600);

    // Set pin modes
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    // Add transitions
    greenState->addTransition(new StateTimeoutTransition(yellowState));
    yellowState->addTransition(new StateTimeoutTransition(redState));
    redState->addTransition(new StateTimeoutTransition(greenState));

    // Instantiate the FSM with the initial state
    trafficFsm = new FSM(greenState);
    // Start the FSM
    trafficFsm->start();
}

void loop() {
    // Continuously run the FSM
    trafficFsm->run();
}
