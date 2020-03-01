var http            = require('http');
var HttpDispatcher  = require('httpdispatcher');
var fs              = require('fs');
var path            = require('path');

var dispatcher      = new HttpDispatcher();

const PORT = 8080;

function handleRequest(request, response){
    try{
        console.log(request.url);
        dispatcher.dispatch(request, response);
    }catch(err){
        console.log(err);
    }
}

var firstServer = http.createServer(handleRequest);

dispatcher.onGet("/", function(req, res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end('<h1> Hello There, This is HOME page</h1>');
});

dispatcher.onGet("/Welcome", function(req, res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end('<h1> Hello There, This is WELCOME page');
});
dispatcher.onGet("/ONOFF", function(req, res){
    fs.readFile('./ONOFF.txt', 'utf8', function(err, data){
        if (!err) {
            console.log('received data: ' + data);
            res.writeHead(200, {'Content-Type': 'text/html'});
            res.write(data);
            res.end();
        } else {
            console.log(err);
        }
    });
 });
firstServer.listen(PORT, function(){
    console.log("Server Listining...")
});
