var net = require("net");

var server = net.createServer((socket) => {
    socket.name = socket.remoteAddress + ":" + socket.remotePort;
    socket.write("Connected to Woxelcraft Debug Server\n");
    console.log("[+] " + socket.name + " connected\n");
    socket.on("data", (data) => {
        console.log("[+] Received: " + data);        
    });
    socket.on("end", () => { 
        console.log("[-] Client " + socket.name + " disconnected\n");        
    });
    socket.on('error', (err) => {
        console.log("[+] Error: " + socket.name + " " + err.message);
    });        
}).listen(5000);

console.log("************ Woxelcraft Debug Server running at port 5000 ************");
