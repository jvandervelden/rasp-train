var GpioModel = require('../models/gpio');
var gpios = require('../gpio/gpio').gpios;
var _ = require('underscore');

exports.getAllGpios = function () {
    var gpioModels = [];

    _.each(gpios, function (value) {
        gpioModels.push(GpioModel.fromGpioDefinition(value));
    });

    return gpioModels;
}

exports.getGpioById = function (id) {
    if (gpios.hasOwnProperty(id + '')) {
        return GpioModel.fromGpioDefinition(gpios[id + '']);
    }

    return null;
}