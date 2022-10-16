#pragma once

#include "libs.h"

struct Usuario
{
	int Id;

	bool EsSuperAdmin;
	bool EsAdmin;

	char NombreComercio[15];
	char NombreDeUsuario[50];
	char AliasDeUsuario[10];
	char Password[30];
	char RutaFoto[255];
	char TipoUsuario[30];

	struct Usuario* SiguentePuntero;
	struct Usuario* AnteriorPuntero;
} * ptr_usuarios = nullptr;

struct Cliente
{
	bool EsPremium;
	char NombreComercio[15];
	char Nombre[50];
	char Alias[15];
	char Telefono[10];
	char Email[25];
	char Fecha[10];

	struct Cliente* SiguentePuntero;
	struct Cliente* AnteriorPuntero;
} * ptr_clientes = nullptr;


struct Promocion
{
	bool Estatus;
	char Nombre[50];
	float MontoPromocion;
	int PorcentajeDescuento;
	char Fecha[10];

	struct Promocion* SiguentePuntero;
	struct Promocion* AnteriorPuntero;
} * ptr_promociones = nullptr;

struct Consumo
{
	int ClienteId;
	float Monto;
	char Fecha[10];
	float SubTotal;
	float Descuento;
	float Total;

	struct Consumo* SiguentePuntero;
	struct Consumo* AnteriorPuntero;
} * ptr_consumos = nullptr;