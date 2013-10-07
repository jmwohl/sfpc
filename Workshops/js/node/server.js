var express = require('express');
var app = express();
var server = require('http').createServer(app).listen(8000);
var io = require('socket.io').listen(server);
io.sockets.on('connection', function(client){
    client.on('message', function(err, msg){
        client.broadcast.emit('message', msg);
    });
 });
