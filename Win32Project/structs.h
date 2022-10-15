#pragma once

#include "libs.h"

struct Comercio
{
	int Id;
	char Nombre[50];
};

struct TipoUsuario
{
	int Id;
	char Nombre[50];
};

struct Usuario
{
	int Id;
	int ComercioId;
	int TipoUsuarioId;

	bool EsSuperAdmin;
	bool EsAdmin;

	char NombreDeUsuario[50];
	char AliasDeUsuario[10];
	char Contasena[30];
	char RutaFoto[255];

	struct Usuario* SiguentePuntero;
	struct Usuario* UltimoPuntero;
} * ptr_usuarios;

struct Cliente
{
	bool EsPremium;
	int ComercioId;
	char Nombre[50];
	char Alias[15];
	char Telefono[10];
	char Email[25];
	char Fecha[10];

	struct Cliente* SiguentePuntero;
	struct Cliente* UltimoPuntero;
} * ptr_clientes;


struct Promocion
{
	bool Estatus;
	char Nombre[50];
	float MontoPromocion;
	int PorcentajeDescuento;
	char Fecha[10];

	struct Promocion* SiguentePuntero;
	struct Promocion* UltimoPuntero;
} * ptr_promociones;

struct Consumo
{
	int ClienteId;
	float Monto;
	char Fecha[10];
	float SubTotal;
	float Descuento;
	float Total;

	struct Consumo* SiguentePuntero;
	struct Consumo* UltimoPuntero;
} * ptr_consumos;