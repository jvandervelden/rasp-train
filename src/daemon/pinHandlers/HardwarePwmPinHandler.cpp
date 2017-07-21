#include "HardwarePwmPinHandler.h"

HardwarePwmPinHandler::HardwarePwmPinHandler(int pin) : BasePinHandler(pin) {
    pinMode(this->pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(10);
    pwmSetRange(100);
}

void HardwarePwmPinHandler::run() {
    pwmWrite(this->pin, this->onPercent);
}

void HardwarePwmPinHandler::stop() {
    pwmWrite(this->pin, 0);
}

void HardwarePwmPinHandler::setValue(float value) {
    this->onPercent =
        (value > 1.0 ?
        1.0 :
        value < 0.0 ?
            0.0 :
            value) * 100.0;

    pwmWrite(this->pin, this->onPercent);
}

float HardwarePwmPinHandler::getValue() {
    return this->onPercent / 100.0;
}

string HardwarePwmPinHandler::getType() {
    return PIN_TYPE_PWM;
}

HardwarePwmPinHandler::~HardwarePwmPinHandler() {
    this->stop();
}
