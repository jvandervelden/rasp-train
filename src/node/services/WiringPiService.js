var zmq = require("zeromq");

var daemonSocket = zmq.socket("req");

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
    daemonSocket.send(gpio.wiringPiPin + ":" + value);
}