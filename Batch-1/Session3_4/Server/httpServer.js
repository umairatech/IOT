var http = require('http');   //include
const PORT = 8080;

function handleRequest(request, response){
    try{
        console.log(request.url);
        response.writeHead(200, {'Content-Type':'text/html'});
        response.end('<h1> Hello There!</h1>'); 
    }catch(err){
        console.log(err);
    }
}

var firstServer = http.createServer(handleRequest);

firstServer.listen(PORT, function(){
    console.log("Server Listining...")
});

