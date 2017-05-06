#!/bin/bash

SRC_ROOT=src
LIB_ROOT=bin/obj

mkdir -p $LIB_ROOT

g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/BasePinHandler.cpp -o $LIB_ROOT/BasePinHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/main.cpp -o $LIB_ROOT/main.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/PwmPinHandler.cpp -o $LIB_ROOT/PwmPinHandler.o
g++ -Wall -g -std=c++11 -Isrc -c $SRC_ROOT/SwitchPinHandler.cpp -o $LIB_ROOT/SwitchPinHandler.o
g++ -o bin/raspTrain $LIB_ROOT/BasePinHandler.o $LIB_ROOT/main.o $LIB_ROOT/PwmPinHandler.o $LIB_ROOT/SwitchPinHandler.o -lwiringPi -lpthread
