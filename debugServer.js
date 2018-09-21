var net = require("net");

var buffer = '';

const server = net.createServer((socket) => {
    socket.name = socket.remoteAddress + ":" + socket.remotePort;
    socket.write("Connected to WoxelCraft Debug Server\n");
    console.log("[+] " + socket.name + " connected");
    socket.on("data", (data) => {
        buffer += data;
        if (buffer.indexOf('\0') < 0) {
            const lines = buffer.split('\0');
            lines.forEach(line => console.log("[+] Received: " + line))            
            buffer = '';
        } 
    });
    socket.on("end", () => { 
        console.log("[-] Client " + socket.name + " disconnected");        
    });
    socket.on('error', (err) => {
        console.log("[+] Error: " + socket.name + " " + err.message);
    });        
}).listen(5000);

console.log("************ WoxelCraft Debug Server running at port 5000 ************");
