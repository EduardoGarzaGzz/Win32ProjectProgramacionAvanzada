#pragma once

struct Usuario {
    bool EsAdmin;
    char NombreDeUsuario[100];
    char Contasena[30];

    struct Usuario* SiguentePuntero;
    struct Usuario* UltimoPuntero;
} *NodoActualDeUsuario;

struct Cliente {
    bool EsPremium;
    char Nombre[200];
    char Dirección[255];

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

struct Promocion {
    bool EstaActivo;
    char Nombre[100];
    char Descripcion[255];
    float bono;

    struct Promocion* SiguentePuntero;
    struct Promocion* UltimoPuntero;
} *NodoActualDePromocion;

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