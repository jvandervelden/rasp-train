#ifndef SOFTWAREPWMPINHANDLER_H
#define SOFTWAREPWMPINHANDLER_H

#include <iostream>
#include <wiringPi.h>
#include <thread>

#include "BasePinHandler.h"

using namespace std;

class SoftwarePwmPinHandler : public BasePinHandler {
    public:
        SoftwarePwmPinHandler(int pin);

        void run();
        void stop();
        void setValue(float value);
        float getValue();
        string getType();

        ~SoftwarePwmPinHandler();
    protected:
    private:
        float onPercent = 0.0;
        float onMicroseconds = 0.0;
        float offMicroseconds = 1.0;
        bool running = false;
        thread pwmThread;

        void calculateCycle();
        void threadFunction();
};

#endif // SOFTWAREPWMPINHANDLER_H
