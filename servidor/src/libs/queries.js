import { Acceso } from "../databases/rfid.model.js"

export const VerificarRegistroExistente = async (data) => {
    try {
        const result = await Acceso.findByPk(data)

        if (result) {
            if (result.dataValues.Usuario)
                return { Pass: true, UID: result.dataValues.UID, Usuario: result.dataValues.Usuario, Nivel: result.dataValues.Nivel }

            else
                return { Pass: true, UID: null, Usuario: null, Nivel: 0 }

        }

        const rfid = await Acceso.build({ UID: data })
        await rfid.save();
    } catch (error) {
        return { Pass: true, UID: null, Usuario: null, Nivel: 0 }

    }

    return { Pass: true, UID: null, Usuario: null, Nivel: 0 }

}