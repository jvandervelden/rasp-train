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

#include <unistd.h>

#include <thread>

#include "QueueMessageHandler.h"

using namespace std;

volatile sig_atomic_t run = 1;

void on_sig_int(int signal) {
    cout << "Killing process ... \n";
    run = 0;
}

int main(int argc, char **argv)
{
    signal(SIGKILL, on_sig_int);
    signal(SIGINT, on_sig_int);

    cout << "Initializing wiring Pi." << endl;

    wiringPiSetup();

    PinHandlerManager* pinHandlerManager = new PinHandlerManager();
    QueueMessageHandler messageHandler(5555, pinHandlerManager);

    while (run && messageHandler.isRunning()) {
        delayMicroseconds(100000);
    }

    delete pinHandlerManager;

    return 0;
}
