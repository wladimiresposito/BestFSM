//
// Created by wla on 23/12/24.
//

#include "DoorController.h"

// Global controller instance
DoorController* doorController;

void setup() {
    Serial.begin(9600);
    doorController = new DoorController();
    doorController->begin();
}

void loop() {
    doorController->update();
}
