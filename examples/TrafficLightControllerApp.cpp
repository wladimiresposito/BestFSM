//
// Created by wla on 23/12/24.
//

#include "TrafficLightController.h"

// Global controller instance
TrafficLightController* trafficLight;

void setup() {
    Serial.begin(9600);
    trafficLight = new TrafficLightController();
    trafficLight->begin();
}

void loop() {
    trafficLight->update();
}
