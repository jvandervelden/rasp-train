var Gpio = function (physicalPin, wiringPiPin, name) {
    this.id = physicalPin;
    this.physicalPin = physicalPin;
    this.wiringPiPin = wiringPiPin;
    this.name = name;
}

Gpio.fromGpioDefinition = function (definition) {
    return new Gpio(definition.physicalPin, definition.wiringPiPin, definition.name);
}

module.exports = Gpio;