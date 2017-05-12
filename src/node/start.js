var express = require('express');
var path = require('path');
var args = require('commander');
var _ = require('underscore');
var programVersion = '1.0.0';
var port;
var basePath;

console.log(JSON.stringify(process.argv));

args.version(programVersion)
    .option('-p, --port <port>', 'Port to listen on.', /^([0-9]+)$/, '3000')
    .option('-P, --base-path <path>', 'Base path of the application.', /^(.+)$/, './')
    .parse(process.argv);

port = args.port;
basePath = args.basePath;

var app = express();

console.log('Serving static content from: ' + path.join(basePath, 'static'));
app.use(express.static(path.join(basePath, 'static')));

app.listen(port, function () {
    console.log('Raspberry Train started on port: ' + port);
});
