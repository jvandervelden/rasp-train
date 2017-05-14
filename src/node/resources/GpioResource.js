var BaseResource = require('./BaseResource');
var gpioService = require('../services/GpioService')

var GpioResource = function () { }

GpioResource.BASE_URL = '/v1.0/gpios';

GpioResource.prototype.init = function (expressApp) {
    if (!expressApp) {
        throw 'Must specify expressApp so I can bind.';
    }

    this.expressApp = expressApp;

    this.expressApp.get(BaseResource.API_BASE_URL + GpioResource.BASE_URL, this.handleGetAllRequest);
    this.expressApp.get(BaseResource.API_BASE_URL + GpioResource.BASE_URL + '/:gpioId', this.handleGetRequest);
}

GpioResource.prototype.handleGetAllRequest = function (request, response) {
    response.status(200).send(gpioService.getAllGpios());
}

GpioResource.prototype.handleGetRequest = function (request, response) {
    var gpioId = request.params.gpioId;
    var gpioModel = gpioService.getGpioById(gpioId);

    if (gpioModel != null) {
        response.status(200).send(gpioModel);
    } else {
        response.status(404).send('Gpio: ' + gpioId + ' does not exist. May not be a GPIO pin.');
    }
}

module.exports = GpioResource;