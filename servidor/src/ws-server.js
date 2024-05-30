import app from './libs/express.js'
import networks from './libs/networks.js'
import { db } from './dbpool.js'

const PORT = process.env.PORT || 3000

const server = createServer(app);
const io = new Server(server, {
    cors: "*"
});

const __dirname = dirname(fileURLToPath(import.meta.url));

import { createServer } from 'node:http';
import { fileURLToPath } from 'node:url';
import { dirname, join } from 'node:path';
import { Server } from 'socket.io';
import { VerificarRegistroExistente } from './libs/queries.js';


app.get('/', (req, res) => {
    res.sendFile(join(__dirname, 'pages/index.html'));
});

app.get('/wasa', (req, res) => {
    res.sendFile(join(__dirname, 'pages/wasa.html'));
});

app.get('/rfid', (req, res) => {
    res.sendFile(join(__dirname, 'pages/wasabi.html'));
});

io.on('connection', (socket) => {
    console.log('a user connected');
    socket.on('disconnect', () => {
        console.log('user disconnected');
    });

    socket.on('chat message', (msg) => {
        io.emit('chat message', msg);
    });

    socket.on("rfid", async rfid => {
        console.log("rfid catched:", rfid)
        const trusted = await VerificarRegistroExistente(rfid)
        console.log(trusted)
        io.emit("trusted", trusted)
    })

});

async function main() {
    try {
        await db.sync({ force: false })
        server.listen(PORT, () => {
            console.table(networks)
            console.log("App listening on:", PORT);
        })
    } catch (error) {

    }
}

main();