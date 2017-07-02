#ifndef BASEPINHANDLER_H
#define BASEPINHANDLER_H

#include "../MessageDefinitions.h"

class BasePinHandler {
    public:
        BasePinHandler(int pin);
        int getPin();

        virtual void run();
        virtual void stop();
        virtual void setValue(float value);
        virtual float getValue();
        virtual string getType();

        ~BasePinHandler();
    protected:
        int pin;
};

#endif // BASEPINHANDLER_H
