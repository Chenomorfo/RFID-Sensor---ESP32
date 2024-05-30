import { io } from 'socket.io-client'
import express from 'express'

const app = express()
const PORT = 3001
const socket = io("ws://localhost:3000")

app.use(express.text())


app.post("/", async (req, res) => {
    const data = req.body
    socket.emit("rfid", data)
    const value = ['04 E3 9C 01 ', '21 1B 81 47 ', 'A0 41 33 25 '].includes(data) ? "Pass" : "Error"
    res.send(value)
})

app.listen(PORT, e => console.log("Listen on", PORT))