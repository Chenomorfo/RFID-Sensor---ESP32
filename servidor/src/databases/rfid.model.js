import { db } from '../dbpool.js';
import { DataTypes } from 'sequelize'

export const Acceso = db.define(
    'acceso',
    {
        // Model attributes are defined here
        UID: {
            type: DataTypes.STRING,
            allowNull: false,
            primaryKey: true
        },
        Usuario: {
            type: DataTypes.STRING,
            // allowNull defaults to true
        },
        Nivel: {
            type: DataTypes.TINYINT,
            defaultValue: 3
        }
    },
    {
        tableName: "Accesos"
        // Other model options go here
    },
);

export const Registro = db.define(
    'registro',
    {
        // Model attributes are defined here
        Id: {
            type: DataTypes.INTEGER,
            allowNull: false,
            primaryKey: true,
            autoIncrementIdentity: true
        },
        Fecha: {
            type: DataTypes.DATE,
            defaultValue: DataTypes.NOW
            // allowNull defaults to true
        },
    },
    {
        tableName: "Registros"
        // Other model options go here
    },
);

Acceso.hasMany(Registro, {
    foreignKey: "Usuario",

})
Registro.belongsTo(Acceso)