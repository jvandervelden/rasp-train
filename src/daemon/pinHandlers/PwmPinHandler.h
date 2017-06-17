#ifndef PWMPINHANDLER_H
#define PWMPINHANDLER_H

#include <iostream>
#include <wiringPi.h>
#include <thread>
#include "BasePinHandler.h"

using namespace std;

class PwmPinHandler : public BasePinHandler {
    public:
        PwmPinHandler(int pin);
        void run();
        void stop();
        void setValue(float value);
        virtual ~PwmPinHandler();
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

#endif // PWMPINHANDLER_H
