import { Sequelize } from "sequelize";

export const db = new Sequelize("rfid", "cheno", "cheno", {
    host: "localhost",
    port: 49171,
    dialect: "mssql",
    pool: {
        max: 5,
        min: 0,
        idle: 10000
    },
    logging: false
})