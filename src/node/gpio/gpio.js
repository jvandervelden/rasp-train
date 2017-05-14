var cp = require('child_process');
var _ = require('underscore');
var gpioMap = {};

var readGpios = function () {
    var gpioBlob = cp.execSync('gpio readall');
    var gpioParse = /^\s*\|\s*[0-9]*\s*\|\s*([0-9]*)\s*\|(.*?)\|(?:.*?\|){2}\s*([0-9]+)\s*\|\|\s*([0-9]+)\s*\|(?:.*?\|){2}(.*?)\|\s*([0-9]*)\s*\|.*$/gm;
    var parts;

    while (parts = gpioParse.exec(gpioBlob.toString())) {
        if (parts.length != 7) {
            console.log('Error on gpio line: ' + parts[0]);
            continue;
        }

        if (parts[3].trim() != '' && parts[1].trim() != '') {
            gpioMap[parts[3] + ''] = {
                name: parts[2].trim(),
                wiringPiPin: parts[1],
                physicalPin: parts[3]
            };
        }

        if (parts[4].trim() != '' && parts[6].trim() != '') {
            gpioMap[parts[4] + ''] = {
                name: parts[5].trim(),
                wiringPiPin: parts[6],
                physicalPin: parts[4]
            };
        }
    }

    console.log('Found GPIOs', gpioMap);
}

exports.init = function () {
    readGpios();
}

exports.gpios = gpioMap;