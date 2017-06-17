#ifndef PWMPINHANDLER_H
#define PWMPINHANDLER_H

#include <iostream>
#include <zmq.hpp>
#include <thread>

#include <wiringPi.h>

using namespace std;

class QueueMessageHandler {

    private:
        int listenPort;
        thread queueThread;
        void threadFunction();
        bool running = false;
        zmq::context_t context = zmq::context_t(1);
        zmq::socket_t socket = zmq::socket_t(this->context, ZMQ_REP);

    public:
        QueueMessageHandler(int listenPort);
        ~QueueMessageHandler();

};

#endif
