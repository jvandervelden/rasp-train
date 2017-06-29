#include "BasePinHandler.h"

BasePinHandler::BasePinHandler(int pin) {
    this->pin = pin;
}

int BasePinHandler::getPin() {
    return this->pin;
}

BasePinHandler::~BasePinHandler() {
}
