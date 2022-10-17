#pragma once

#include "libs.h"

bool nombre_comercio_es_valido(char nombre_comercio[15])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(nombre_comercio));

	for (int i = 0; i < longitud_texto; i++)
		if (!isalnum(nombre_comercio[i]) && nombre_comercio[i] != 32)
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 5 && longitud_texto <= 15;
}

bool es_caracter_especiales(char caracter)
{
	return (caracter >= 33 && caracter <= 47) ||
		(caracter >= 58 && caracter <= 64) ||
		(caracter >= 123 && caracter <= 126);
}

bool nombre_usuario_es_valido(char nombre_usuario[50])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(nombre_usuario));

	// El espacio tiene el valor 32 en ASCII
	// isalpha evalua que el caractes este entre el rango de valores ASCII para letras
	// Para mayusculas son del 65 al 90 y para minusculas son del 97 al 122
	for (int i = 0; i < longitud_texto; i++)
		if (!isalpha(nombre_usuario[i]) && nombre_usuario[i] != 32)
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 5 && longitud_texto <= 50;
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
		if (!isalnum(alias_usuario[i]) && alias_usuario[i] != 32)
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 3 && longitud_texto <= 10;
}

bool password_usuario_es_valida(char password[30])
{
	const int longitud_texto = static_cast<int>(strlen(password));
	bool tiene_letras = false;
	bool tiene_nums = false;
	bool tiene_caracteres_especiales = false;

	for (int i = 0; i < longitud_texto; i++)
	{
		if (isalpha(password[i])) tiene_letras = true;
		else if (isdigit(password[i])) tiene_nums = true;
		else if (es_caracter_especiales(password[i])) tiene_caracteres_especiales = true;
	}

	return (tiene_letras && tiene_nums && tiene_caracteres_especiales) && longitud_texto >= 3 && longitud_texto <= 10;
}

bool nombre_cliente_es_valido(char nombre[50])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(nombre));

	for (int i = 0; i < longitud_texto; i++)
		if (!isalpha(nombre[i]) && nombre[i] != 32)
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 5 && longitud_texto <= 50;
}

bool alias_cliente_es_valido(char alias[15])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(alias));

	for (int i = 0; i < longitud_texto; i++)
		if (!isalpha(alias[i]) && alias[i] != 32)
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 5 && longitud_texto <= 15;
}

bool telefono_cliente_es_valido(char telefono[10])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(telefono));

	for (int i = 0; i < longitud_texto; i++)
		if (!isdigit(telefono[i]))
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto == 10;
}

bool email_cliente_es_valido(char email[25])
{
	const int longitud_texto = static_cast<int>(strlen(email));
	bool tiene_nombre_cuenta = false;
	bool tiene_arroba = false;
	bool tiene_nombre_dominio = false;
	bool tiene_punto = false;
	bool tiene_extencion = false;

	for (int i = 0; i < longitud_texto; i++)
	{
		if (isalpha(email[i])) tiene_nombre_cuenta = true;
		if (tiene_nombre_cuenta && email[i] == 64) tiene_arroba = true; // 64 es el @
		if (tiene_arroba && isalpha(email[i])) tiene_nombre_dominio = true;
		if (tiene_nombre_dominio && email[i] == 46) tiene_punto = true; // 46 es el .
		if (tiene_punto && isalpha(email[i])) tiene_extencion = true;
	}

	return tiene_nombre_cuenta
		&& tiene_arroba
		&& tiene_nombre_dominio
		&& tiene_punto
		&& tiene_extencion
		&& longitud_texto >= 5
		&& longitud_texto <= 25;
}

bool nombre_promocion_es_valido(char nombre[50])
{
	bool es_valido = true;
	const int longitud_texto = static_cast<int>(strlen(nombre));

	for (int i = 0; i < longitud_texto; i++)
		if (!isalpha(nombre[i]))
		{
			es_valido = false;
			break;
		}

	return es_valido && longitud_texto >= 5 && longitud_texto <= 50;
}

bool monto_promociones_es_valida(float monto_promociones)
{
	return monto_promociones >= 0 && monto_promociones <= 100;
}

bool porcentaje_descuento_promocion_es_valido(int porcentaje_descuneto)
{
	return porcentaje_descuneto >= 0 && porcentaje_descuneto <= 100;
}

bool monto_consumo_es_valido(float monto)
{
	return monto > 0;
}
