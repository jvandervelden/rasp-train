#ifndef HARDWAREPWMPINHANDLER_H
#define HARDWAREPWMPINHANDLER_H

#include <iostream>
#include <wiringPi.h>

#include "BasePinHandler.h"

using namespace std;

const int HARDWARE_PWM_PIN = 18;

class HardwarePwmPinHandler : public BasePinHandler {
    public:
        HardwarePwmPinHandler(int pin);

        void run();
        void stop();
        void setValue(float value);
        float getValue();
        string getType();

        ~HardwarePwmPinHandler();
    protected:
    private:
        float onPercent = 0.0;
};

#endif // HARDWAREPWMPINHANDLER_H
