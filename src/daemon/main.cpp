/*
 * main.c
 *
 * Copyright 2017  <jasper.vv@gmail.com>
 *
 * License: GPL v3.0
 * See rasp-train project for license details: https://github.com/jvandervelden/rasp-train.
 *
 */

#include <signal.h>
#include <wiringPi.h>

#include <string>

#include <iostream>
#include <thread>

#include <zmq.hpp>

#include <unistd.h>

#include "PwmPinHandler.h"
#include "SwitchPinHandler.h"

using namespace std;

int GPIO_2 = 8;
int GPIO_3 = 9;

volatile sig_atomic_t run = 1;

void on_sig_int(int signal) {
    cout << "Killing process ... \n";
    run = 0;
}

int main(int argc, char **argv)
{
    signal(SIGKILL, on_sig_int);
    signal(SIGINT, on_sig_int);

    cout << "Initializing wiring Pi.\n";

    wiringPiSetup();

    SwitchPinHandler* switchHandler = new SwitchPinHandler(GPIO_3);
    switchHandler->run();
    switchHandler->setValue(0.0f);

    PwmPinHandler* pwmHandler = new PwmPinHandler(GPIO_2);
    pwmHandler->run();
    pwmHandler->setValue(0.0f);

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://127.0.0.1:5555");

    cout << "Socket oppened on port 5555." << endl;

    char buffer[2048] = {};

    while (run) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);

        memcpy(&buffer, request.data(), request.size());

        buffer[request.size() + 1] = '\0';

        cout << buffer << endl;

        //  Send reply back to client
        zmq::message_t reply (15);
        memcpy (reply.data (), "{\"status\":\"ok\"}", 15);
        socket.send (reply);

        /*
        cout << "Edit Value:\n";
        cout << "1: PWM (Motor)\n";
        cout << "2: Switch\n";
        cout << "3: Exit\n";

        int menuValue;

        cin >> menuValue;

        switch (menuValue) {
            case 1:
                float speed;

                cout << "Enter a value between 0.0 and 1.0: ";
                cin >> speed;

                pwmHandler->setValue(speed);
                break;
            case 2:
                float switchVal;

                cout << "Enter a 0.0 (off) or 1.0 (on): ";
                cin >> switchVal;

                switchHandler->setValue(switchVal);
                break;
            case 3:
                run = 0;
                break;
            default:
                cout << menuValue << " is not a valid item.\n";
                break;
        }
        */
    }

    socket.close();


    switchHandler->stop();
    pwmHandler->stop();

    delete switchHandler;
    delete pwmHandler;

    return 0;
}
