#ifndef PINHANDLERMANAGER_H
#define PINHANDLERMANAGER_H

#include <stdio.h>
#include "pinHandlers/BasePinHandler.h"

struct PinHandlerNode {
    BasePinHandler* handler;

    PinHandlerNode* next;
    PinHandlerNode* prev;
};

typedef void (* NodeLoopHandler)(PinHandlerNode* node);

class PinHandlerManager {
    public:
        PinHandlerManager();

        void AddHandler(BasePinHandler* handler);
        BasePinHandler* GetHandler(int pin);
        void DeleteHandler(int pin);
        void DeleteAllHandlers();

        void loopHandlers(NodeLoopHandler callback);

        ~PinHandlerManager();
    protected:
        PinHandlerNode* FindNode(int pin);
    private:
        PinHandlerNode* handlerListHead = 0;
        PinHandlerNode* handlerListTail = 0;
};

#endif // PINHANDLERMANAGER_H
