var zmq = require("zeromq");
var _ = require("underscore");

var daemonSocket = zmq.socket("req");

var messageTypes = {
    CONFIG: "00",
    GPIO_MSG: "01",
    QUERY: "02"
};

var configMessages = {
    QUIT: "00",
    CLEAR_ALL: "01",
    CREATE_GPIO: "02",
    DELETE_GPIO: "03",
    DELETE_ALL: "04"
};

var gpioPinTypes = {
    PWM: "00",
    SWITCH: "01"
};

var gpioMessages = {
    SET_PIN_VALUE: "00"
};

var queryMessages = {
    GET_GPIO_STATUS: "00",
    GET_ALL_GPIO_STATUSES: "01",
    GET_DAEMON_STATUS: "02"
};

var buildMessage = function (messageType, message, value) {
    return messageType + ":" + message + ":" + value;
};

var formatValue = function (value) {
    var valueStr;

    if (_.isNumber(value)) {
        valueStr = value.toFixed(3) + "";
    } else {
        parseFloat(value).toFixed(3) + "";
    }

    if (valueStr.length === 5) {
        valueStr = "00" + valueStr;
    } else if (valueStr.length === 6) {
        valueStr = "0" + valueStr;
    } else if (valueStr.length > 7) {
        valueStr = valueStr.substr(0, 7);
    }

    return valueStr;
};

var formatPin = function (pin) {
    var pinStr = pin + "";

    if (pinStr.length === 1) {
        pinStr = "00" + pinStr;
    } else if (pinStr.length === 2) {
        pinStr = "0" + pinStr;
    } else if (pinStr.length > 3) {
        pinStr = pinStr.substr(0, 3);
    }

    return pinStr;
}

var buildPinValue = function (pin, value) {
    return formatPin(pin) + ":" + formatValue(value);
};

daemonSocket.connect("tcp://127.0.0.1:5555");

console.log("connected to daemon on port 5555");

daemonSocket.on("message", function (reply) {
    console.log("got reply: " + reply);
});

process.on("SIGINT", function () {
    console.log("Closing socket");
    daemonSocket.close();
});

exports.setPinStatus = function (gpio, value) {
    daemonSocket.send(buildMessage(messageTypes.GPIO_MSG, gpioMessages.SET_PIN_VALUE, buildPinValue(gpio.wiringPiPin, value)));
}