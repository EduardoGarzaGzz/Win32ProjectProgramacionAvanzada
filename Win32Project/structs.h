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

bool nombre_usuario_es_valido(char nombre_usuario[50])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(nombre_usuario));

	// El espacio tiene el valor 32 en ASCII
	// isalpha evalua que el caractes este entre el rango de valores ASCII para letras
	// Para mayusculas son del 65 al 90 y para minusculas son del 97 al 122
	for (int i = 0; i < longitud_texto; i++) 
		if (nombre_usuario[i] != 32 || !isalpha(nombre_usuario[i]))
		{
			es_valido = false;
			break;
		}

	return es_valido && (longitud_texto >= 5 && longitud_texto <= 50);
}

bool alias_usuario_es_valido(char alias_usuario[10])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(alias_usuario));

	// El espacio tiene el valor 32 en ASCII
	// isalnum evalua que el caractes este entre el rango de valores ASCII para letras
	// Para mayusculas son del 65 al 90 y para minusculas son del 97 al 122
	// y para digitos que son del 48 y 57
	for (int i = 0; i < longitud_texto; i++)
		if (alias_usuario[i] != 32 || !isalnum(alias_usuario[i]))
		{
			es_valido = false;
			break;
		}

	return es_valido && (longitud_texto >= 3 && longitud_texto <= 10);
}

// Contraseña
// TODO Debe contener una letra, un numero y un caracter especial obligatoriamente
bool contrasena_usuario_es_valida(char password[30])
{
	//bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(password));
	bool tiene_letras = false;
	bool tiene_nums = false;
	bool tiene_caracteres_especiales = false;
	char chr;

	for (int i = 0; i < longitud_texto; i++)
	{
		chr = password[i];
		if (isalpha(chr)) tiene_letras = true;
		else if (isdigit(chr)) tiene_nums = true;
		else if (true) tiene_caracteres_especiales = true;
	}

	return (tiene_letras && tiene_nums && tiene_caracteres_especiales) && (longitud_texto >= 3 && longitud_texto <= 10);
}

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

struct Cliente
{
	bool EsPremium;
	char Nombre[200];
	char Direccion[255];

	struct Cliente* SiguentePuntero;
	struct Cliente* UltimoPuntero;
} * NodoActualDeCliente;

struct Cajero
{
	bool EstaActivo;
	char identidad[100];
	char direccion[255];
	float DineroDisponible;
	float DineroTotal;

	struct Cajero* SiguentePuntero;
	struct Cajero* UltimoPuntero;
} * NodoActualDeCajero;

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

struct Promocion
{
	bool EstaActivo;
	char Nombre[100];
	char Descripcion[255];
	float bono;

	struct Promocion* SiguentePuntero;
	struct Promocion* UltimoPuntero;
} * NodoActualDePromocion;

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


struct Consumo
{
	char NombreDelCliente[100];
	float Monto;
	float SubTotal;
	float Descuento;
	float Total;
	char Dato[20];

	struct Consumo* SiguentePuntero;
	struct Consumo* UltimoPuntero;
} * NodoActualDeConsumo;
