var net = require("net");

var buffer = '';

const server = net.createServer((socket) => {
    socket.name = socket.remoteAddress + ":" + socket.remotePort;
    socket.write("Connected to WoxelCraft Debug Server\n");
    console.log("[+] " + socket.name + " connected");
    socket.on("data", (data) => {
        buffer += data;
        if (buffer.indexOf('\n') != -1) {
            const lines = buffer.split('\n');			
            lines.forEach(line => {
                if (line.length > 0) {
                    console.log("[+] Received: " + line)           
                }								    
			});
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
