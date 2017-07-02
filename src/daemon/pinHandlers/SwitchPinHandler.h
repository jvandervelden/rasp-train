#ifndef SWITCHPINHANDLER_H
#define SWITCHPINHANDLER_H

#include <iostream>
#include <wiringPi.h>

#include "BasePinHandler.h"

class SwitchPinHandler : public BasePinHandler
{
    public:
        SwitchPinHandler(int pin);

        void run();
        void stop();
        void setValue(float value);
        float getValue();
        string getType();

        ~SwitchPinHandler();
    private:
        bool on = false;

        void setGpioValue();
};

#endif // SWITCHPINHANDLER_H
