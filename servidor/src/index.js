import app from './libs/express.js'
import networks from './libs/networks.js'
import { db } from './dbpool.js'
const PORT = process.env.PORT || 3000
import { Acceso, Registro } from './databases/rfid.model.js'
import './databases/rfid.model.js'

app.get("/", (req, res) => {
    res.send("Hola mundo")
})

app.get("/setup", async (req, res) => {
    await db.sync({ force: true })
    res.send("DB preparada")
})

app.post("/rfid", async (req, res) => {
    const data = req.body

    const result = await Acceso.findByPk(data)
    if (result) {
        if (result.dataValues.Usuario)
            return res.json(result)
        else
            return res.send("Favor de registrarlo a un nombre")
    }

    const rfid = await Acceso.build({ UID: data })
    await rfid.save();
    return res.send("rfid creado:" + data)
})

app.post("/test",async (req,res)=>{
    const data = req.body
    console.log(data)
    res.send("OK")
})

async function main() {
    try {
        await db.sync()
        app.listen(PORT, () => {
            console.table(networks)
            console.log("App listening on:", PORT);
        })
    } catch (error) {

    }
}

main();