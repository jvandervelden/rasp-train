#include "SoftwarePwmPinHandler.h"

SoftwarePwmPinHandler::SoftwarePwmPinHandler(int pin) : BasePinHandler(pin) {
}

void SoftwarePwmPinHandler::run() {
    this->running = true;

    this->pwmThread = thread(&SoftwarePwmPinHandler::threadFunction, this);
}

void SoftwarePwmPinHandler::threadFunction() {
    cout << "Starting pwm on pin: " << this->pin << "\n";

    pinMode(this->pin, OUTPUT);

    while(this->running) {
        digitalWrite(this->pin, HIGH);

        delayMicroseconds(this->onMicroseconds);

        digitalWrite(this->pin, LOW);

        delayMicroseconds(this->offMicroseconds);
    }

    digitalWrite(this->pin, LOW);

    cout << "Stopping pwm on pin: " << this->pin << "\n";
}

void SoftwarePwmPinHandler::stop() {
    if (this->running) {
        this->running = false;
        this->pwmThread.join();
    }
}

void SoftwarePwmPinHandler::setValue(float value) {
    this->onPercent =
        value > 1.0 ?
        1.0 :
        value < 0.0 ?
            0.0 :
            value;

    this->calculateCycle();
}

float SoftwarePwmPinHandler::getValue() {
    return this->onPercent;
}

string SoftwarePwmPinHandler::getType() {
    return PIN_TYPE_PWM;
}

void SoftwarePwmPinHandler::calculateCycle() {
    unsigned long cyclesPerScond = 44000;

    // 1000 Microseconds in milliecond * 1000 milliseconds in a second = 1000000.
    unsigned long microsecondsForCycle = 1000000 / cyclesPerScond;

    this->onMicroseconds = microsecondsForCycle * this->onPercent;
    this->offMicroseconds = microsecondsForCycle * (1.0 - this->onPercent);
}

SoftwarePwmPinHandler::~SoftwarePwmPinHandler() {
    this->stop();
}
