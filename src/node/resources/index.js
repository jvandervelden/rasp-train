var GpioResource = require('./GpioResource');
var _ = require('underscore');

var resources = [
    new GpioResource()
];

exports.startResrouces = function(expressApp) {
    console.log('Initializing the resource routes.');
    _.each(resources, function (resource) {
        resource.init(expressApp);
    });
}