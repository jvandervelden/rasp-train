#ifndef QUEUEMESSAGEHANDLER_H
#define QUEUEMESSAGEHANDLER_H

#include <string>
#include <iostream>
#include <zmq.hpp>
#include <thread>

#include <wiringPi.h>

#include "MessageDefinitions.h"
#include "PinHandlerManager.h"
#include "pinHandlers/SwitchPinHandler.h"
#include "pinHandlers/PwmPinHandler.h"

using namespace std;

class QueueMessageHandler {

    private:
        PinHandlerManager* pinHandlerManager;
        int listenPort;
        thread queueThread;
        void threadFunction();
        volatile bool running = false;
        zmq::context_t context = zmq::context_t(1);
        zmq::socket_t socket = zmq::socket_t(this->context, ZMQ_REP);

        string handleMessage(string message);

        string handleConfigMessage(string messageData);
        string handleGpioMessage(string messageData);
        string handleQueryMessage(string messageData);

        string buildErrorMessage(string errorMessage);
        string buildSuccessMessage(string successValue);

        string buildGpioMessage(BasePinHandler* handler);

    public:
        bool isRunning();
        QueueMessageHandler(int listenPort, PinHandlerManager* pinHandlerManager);
        ~QueueMessageHandler();

};

#endif
