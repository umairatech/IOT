var http = require('http');
var HttpDispatcher = require('httpdispatcher');  //npm install httpdispatcher
var dispatcher     = new HttpDispatcher();

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
})
dispatcher.onGet("/ONOFF", function(req, res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end('<h1> Hello There, This is ONOFF page');
});;

firstServer.listen(PORT, function(){
    console.log("Server Listining...")
});

