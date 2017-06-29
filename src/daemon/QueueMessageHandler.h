#ifndef PWMPINHANDLER_H
#define PWMPINHANDLER_H

#include <string>
#include <iostream>
#include <zmq.hpp>
#include <thread>

#include <wiringPi.h>

#include "PinHandlerManager.h"

using namespace std;

const string CONFIG_MESSAGE_ID              = "00";
const string GPIO_MESSAGE_ID                = "01";
const string QUERY_MESSAGE_ID               = "02";

const string CONFIG_MESSAGE_QUIT            = "00";
const string CONFIG_MESSAGE_SET_ALL_VALUE_0 = "01";
const string CONFIG_MESSAGE_CREATE_GPIO     = "02";
const string CONFIG_MESSAGE_DELETE_GPIO     = "03";
const string CONFIG_MESSAGE_DELETE_ALL      = "04";

const string PIN_TYPE_PWM                   = "01";
const string PIN_TYPE_SWITCH                = "02";

const string GPIO_MESSAGE_SET_VALUE         = "00";

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

    public:
        bool isRunning();
        QueueMessageHandler(int listenPort, PinHandlerManager* pinHandlerManager);
        ~QueueMessageHandler();

};

#endif
