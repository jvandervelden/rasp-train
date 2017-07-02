#include "SwitchPinHandler.h"

SwitchPinHandler::SwitchPinHandler(int pin) : BasePinHandler(pin) {
}

void SwitchPinHandler::run() {
    pinMode(this->pin, OUTPUT);
    this->setGpioValue();
}

void SwitchPinHandler::stop() {
    this->on = false;

    this->setGpioValue();
}

void SwitchPinHandler::setValue(float value) {
    this->on = value > 0.0;

    this->setGpioValue();
}

void SwitchPinHandler::setGpioValue() {
    if (this->on) {
        digitalWrite(this->pin, LOW);
    } else {
        digitalWrite(this->pin, HIGH);
    }
}

float SwitchPinHandler::getValue() {
    return this->on ? 1.0f : 0.0f;
}

string SwitchPinHandler::getType() {
    return PIN_TYPE_SWITCH;
}

SwitchPinHandler::~SwitchPinHandler() {
    this->stop();
}
