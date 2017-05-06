/*
 * main.c
 *
 * Copyright 2017  <pi@raspberrypi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>

int GPIO_2 = 8;

volatile sig_atomic_t run = 1;

void on_sig_int(int signal) {
    printf("Killing process ... ");
    run = 0;
}

int main(int argc, char **argv)
{
    signal(SIGKILL, on_sig_int);
    signal(SIGINT, on_sig_int);

    printf("Initializing wiring Pi.\n");

    wiringPiSetup();

    char keypressed;

    pinMode(GPIO_2, OUTPUT);

    float onLength = 0.5;
    float offLength = 0.5;
    int dir = 1;
    int i = 0;

    long cyclesPerScond = 44000;
    long microsecondsForCycle = 1000000 / cyclesPerScond;

    printf("Microsecond per cycle %d\n", microsecondsForCycle);

    while(run) {
        digitalWrite(GPIO_2, HIGH);

        delayMicroseconds(microsecondsForCycle * onLength);

        digitalWrite(GPIO_2, LOW);

        delayMicroseconds(microsecondsForCycle * offLength);
    }

    digitalWrite(GPIO_2, LOW);

    return 0;
}

