#ifndef BASEPINHANDLER_H
#define BASEPINHANDLER_H


class BasePinHandler {
    public:
        BasePinHandler(int pin);
        int getPin();
        virtual void run() = 0;
        virtual void stop() = 0;
        virtual void setValue(float value) = 0;

        virtual ~BasePinHandler();
    protected:
        int pin;
    private:
};

#endif // BASEPINHANDLER_H
