# rasp-train
Project to drive a model train via a raspberry pi.

Project file is Code::Blocks.

PwmPinHandler class sends a PWM (pulse width modultator) signal to a GPIO pin specified. I use https://www.cytron.com.my/p-mdd10a dc motor driver.

SwitchPinHandler class sets the GPIO signal to a constant high or low.

Main.cpp has simple setup to run a motor off GPIO 2 and a switch off GPIO3.
