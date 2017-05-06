#include "PwmPinHandler.h"

PwmPinHandler::PwmPinHandler(int pin) : BasePinHandler(pin) {
}

void PwmPinHandler::run() {
    this->running = true;

    this->pwmThread = thread(&PwmPinHandler::threadFunction, this);
}

void PwmPinHandler::threadFunction() {
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

void PwmPinHandler::stop() {
    if (this->running) {
        this->running = false;
        this->pwmThread.join();
    }
}

void PwmPinHandler::setValue(float value) {
    this->onPercent =
        value > 1.0 ?
        1.0 :
        value < 0.0 ?
            0.0 :
            value;

    this->calculateCycle();
}

void PwmPinHandler::calculateCycle() {
    unsigned long cyclesPerScond = 44000;

    // 1000 Microseconds in milliecond * 1000 milliseconds in a second = 1000000.
    unsigned long microsecondsForCycle = 1000000 / cyclesPerScond;

    this->onMicroseconds = microsecondsForCycle * this->onPercent;
    this->offMicroseconds = microsecondsForCycle * (1.0 - this->onPercent);
}

PwmPinHandler::~PwmPinHandler() {
    this->stop();
}
