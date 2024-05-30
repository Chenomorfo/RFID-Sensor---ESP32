export class Acceso {
    UID: string = ""
    Usuario?: string
    Nivel: number = 0
    Registros: Registro[] = []
}

class Registro {

    Id: number = 0
    Fecha: Date = new Date()
}