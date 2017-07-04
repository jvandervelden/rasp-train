import wiringpi

wiringpi.wiringPiSetup()

wiringpi.pinMode(1, wiringpi.PWM_OUTPUT);
wiringpi.pwmSetMode(wiringpi.PWM_MODE_MS); 
wiringpi.pwmSetClock(384);
wiringpi.pwmSetRange(1000);
wiringpi.pwmWrite(1, 0);
