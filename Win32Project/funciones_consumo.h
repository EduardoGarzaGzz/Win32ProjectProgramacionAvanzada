#pragma once

#include "libs.h"
#include "structs.h"

bool archivo_consumos_tiene_error = true;
Consumo* consumo_seleccionado = nullptr;

void ir_primer_nodo_consumos_lista()
{
	if (ptr_consumos == nullptr) return;
	while (ptr_consumos->AnteriorPuntero != nullptr)
	{
		ptr_consumos = ptr_consumos->AnteriorPuntero;
	}
}

void ir_ultimo_nodo_consumos_lista()
{
	if (ptr_consumos == nullptr) return;
	while (ptr_consumos->SiguentePuntero != nullptr)
	{
		ptr_consumos = ptr_consumos->SiguentePuntero;
	}
}

void agregar_consumo_lista(Consumo* c)
{
	c->SiguentePuntero = nullptr;
	c->AnteriorPuntero = nullptr;

	if (ptr_consumos == nullptr)
	{
		ptr_consumos = c;
		return;
	}

	ir_ultimo_nodo_consumos_lista();

	ptr_consumos->SiguentePuntero = c;
	c->AnteriorPuntero = ptr_consumos;
}

void leer_consumos()
{
	Consumo* consumo = nullptr;
	ifstream file;

	file.open("consumos.bin", ios::in | ios::binary);

	if (!file.is_open() || file.fail())
	{
		archivo_consumos_tiene_error = true;
		return;
	}

	do
	{
		consumo = new Consumo;
		if (!file.read(reinterpret_cast<char*>(consumo), sizeof(Consumo)))
		{
			break;
		}

		consumo->SiguentePuntero = nullptr;
		consumo->AnteriorPuntero = nullptr;

		agregar_consumo_lista(consumo);
	} while (true);

	file.close();
}

void guardar_en_archivo_consumos()
{
	ir_primer_nodo_consumos_lista();
	Consumo* tmpNode = ptr_consumos;
	ofstream file;

	file.open("consumos.bin", ios::out | ios::binary | ios::trunc);

	if (!file.is_open() || file.fail())
	{
		archivo_consumos_tiene_error = true;
	}

	while (tmpNode != nullptr)
	{
		file.write(reinterpret_cast<char*>(tmpNode), sizeof(Consumo));
		tmpNode = tmpNode->SiguentePuntero;
	}

	file.close();
}
