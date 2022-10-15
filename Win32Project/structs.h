#pragma once

// Usuario
// Nombre completo del usuario
// TODO Validar que solo sean caracteres y espacios
// TODO minimo 5 caracteres maximo 50
// Alias del usuario
// TODO Solo caracteres alfanumericos
// TODO Minimo 3 maximo 10
// Foto del usuario
// TODO Agregar campo para la imagen del usuario
// TODO Agregar el comercio solo es uno para todos este se registrar con el admin
// Contraseña
// TODO minimo 3 maximo 10
// TODO Debe contener una letra, un numero y un caracter especial obligatoriamente
// TODO Agregar tipo de usuario

struct Usuario {
    bool EsAdmin;
    char NombreDeUsuario[100];
    char Contasena[30];

    struct Usuario* SiguentePuntero;
    struct Usuario* UltimoPuntero;
} *NodoActualDeUsuario;

// Cientes
// Nombre
// TODO Solo caracteres alfanumericos y espacios
// TODO Minimo 5 maximo 50
// Alias
// TODO Solo caracteres alfanumericos y espacios
// TODO Minimo 5 maximo 15
// Telefono
// TODO Solo caracteres numericos
// TODO Exactamente 10
// Email
// TODO Validar el formato de email
// TODO Minimo 5 maximo 25
// TODO Agregar comercio
// TODO Agregar fecha

struct Cliente {
    bool EsPremium;
    char Nombre[200];
    char Direccion[255];

    struct Cliente* SiguentePuntero;
    struct Cliente* UltimoPuntero;
} *NodoActualDeCliente;

struct Cajero {
    bool EstaActivo;
    char identidad[100];
    char direccion[255];
    float DineroDisponible;
    float DineroTotal;

    struct Cajero* SiguentePuntero;
    struct Cajero* UltimoPuntero;
} *NodoActualDeCajero;

// Promocion
// Nombre
// TODO Solo caracteres alfanumericos y espacios
// TODO Minimo 5 maximo 50
// Monto para promociones
// TODO Agregar Monto para promociones
// TODO Solo valores numericos no negativos y mayores a 100
// Porcentaje de descuento
// TODO Agregar procentaje de descuento es decimal
// TODO Valor numerico, mayor a 0 y menor a 100
// Estatus
// TODO Agregar estatus si esta activa o inactiva
// TODO Agregar fecha

struct Promocion {
    bool EstaActivo;
    char Nombre[100];
    char Descripcion[255];
    float bono;

    struct Promocion* SiguentePuntero;
    struct Promocion* UltimoPuntero;
} *NodoActualDePromocion;

// Consumos
// Cliente
// TODO Agregar campo para seleccionar al cliente
// Monto
// TODO Solo numeros mayor a 0
// TODO Agregar fecha
// Subtotal
// TODO Calcular automaticamente
// Descuento
// TODO Se asigna automaticamente si aplica
// Total
// TODO Automatico


struct Consumo {
    char NombreDelCliente[100];
    float Monto;
    float SubTotal;
    float Descuento;
    float Total;
    char Dato[20];

    struct Consumo* SiguentePuntero;
    struct Consumo* UltimoPuntero;
} *NodoActualDeConsumo;