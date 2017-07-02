#include "BasePinHandler.h"

BasePinHandler::BasePinHandler(int pin) {
    this->pin = pin;
}

int BasePinHandler::getPin() {
    return this->pin;
}

void BasePinHandler::run() {}
void BasePinHandler::stop() {}
void BasePinHandler::setValue(float value) {}
float BasePinHandler::getValue() { return 0.0f; }
string BasePinHandler::getType() { return ""; }

BasePinHandler::~BasePinHandler() {
}
