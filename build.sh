#!/bin/bash

SRC_ROOT=src/daemon
LIB_ROOT=bin/obj

mkdir -p $LIB_ROOT

g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/pinHandlers/BasePinHandler.cpp -o $LIB_ROOT/BasePinHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/main.cpp -o $LIB_ROOT/main.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/pinHandlers/PwmPinHandler.cpp -o $LIB_ROOT/PwmPinHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/pinHandlers/SwitchPinHandler.cpp -o $LIB_ROOT/SwitchPinHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/QueueMessageHandler.cpp -o $LIB_ROOT/QueueMessageHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/PinHandlerManager.cpp -o $LIB_ROOT/PinHandlerManager.o
g++ -o bin/raspTrain $LIB_ROOT/BasePinHandler.o $LIB_ROOT/main.o $LIB_ROOT/PwmPinHandler.o $LIB_ROOT/SwitchPinHandler.o $LIB_ROOT/QueueMessageHandler.o $LIB_ROOT/PinHandlerManager.o -lwiringPi -lpthread -lzmq -std=c++11
