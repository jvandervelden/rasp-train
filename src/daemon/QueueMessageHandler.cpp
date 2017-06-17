#include <zmq.hpp>
#include "QueueMessageHandler.h"

QueueMessageHandler::QueueMessageHandler(int listenPort) {
    this->listenPort = listenPort;

    cout << "Starting zero mq on port: " << this->listenPort << "\n";

    char socketAddress[25] = {};
    sprintf(socketAddress, "tcp://127.0.0.1:%d", this->listenPort);

    this->socket.bind (socketAddress);

    cout << "Starting to process queue." << endl;

    this->running = true;

    this->queueThread = thread(&QueueMessageHandler::threadFunction, this);
}

void QueueMessageHandler::threadFunction() {
    char buffer[2048] = {};
    zmq::message_t request;

    while(this->running) {
        if (this->socket.recv (&request, ZMQ_DONTWAIT)) {

            memcpy(&buffer, request.data(), request.size());

            buffer[request.size() + 1] = '\0';

            cout << buffer << endl;

            zmq::message_t reply (15);
            memcpy (reply.data(), "{\"status\":\"ok\"}", 15);

            this->socket.send (reply);
        } else {
            delayMicroseconds(100000);
        }
    }
}

QueueMessageHandler::~QueueMessageHandler() {

    cout << "Closing zero mq.\n";

    this->socket.close();

    this->running = false;

    this->queueThread.join();
}