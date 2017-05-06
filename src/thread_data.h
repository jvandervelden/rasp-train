#ifndef THREAD_DATA_H_INCLUDED
#define THREAD_DATA_H_INCLUDED

#include "BasePinHandler.h"

struct thread_data {
    int pin;
    PwmPinHandler* pinHandler;
}

#endif // THREAD_DATA_H_INCLUDED
