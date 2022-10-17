#pragma once

#include "libs.h"
#include "structs.h"

bool archivo_promociones_tiene_error = true;
Promocion* promocion_seleccionada = nullptr;

void ir_primer_nodo_promociones_lista()
{
	if (ptr_promociones == nullptr) return;
	while (ptr_promociones->AnteriorPuntero != nullptr)
	{
		ptr_promociones = ptr_promociones->AnteriorPuntero;
	}
}

void ir_ultimo_nodo_promociones_lista()
{
	if (ptr_promociones == nullptr) return;
	while (ptr_promociones->SiguentePuntero != nullptr)
	{
		ptr_promociones = ptr_promociones->SiguentePuntero;
	}
}

void agregar_promocion_lista(Promocion* p)
{
	p->SiguentePuntero = nullptr;
	p->AnteriorPuntero = nullptr;

	if (ptr_promociones == nullptr)
	{
		ptr_promociones = p;
		return;
	}

	ir_ultimo_nodo_promociones_lista();

	ptr_promociones->SiguentePuntero = p;
	p->AnteriorPuntero = ptr_promociones;
}

void leer_promociones()
{
	Promocion* promocion = nullptr;
	ifstream file;

	file.open("promociones.bin", ios::in | ios::binary);

	if (!file.is_open() || file.fail())
	{
		archivo_promociones_tiene_error = true;
		return;
	}

	do
	{
		promocion = new Promocion;
		if (!file.read(reinterpret_cast<char*>(promocion), sizeof(Promocion)))
		{
			break;
		}

		promocion->SiguentePuntero = nullptr;
		promocion->AnteriorPuntero = nullptr;

		agregar_promocion_lista(promocion);
	}
	while (true);

	file.close();
}

void guardar_en_archivo_promociones()
{
	ir_primer_nodo_promociones_lista();
	Promocion* tmpNode = ptr_promociones;
	ofstream file;

	file.open("promociones.bin", ios::out | ios::binary | ios::trunc);

	if (!file.is_open() || file.fail())
	{
		archivo_promociones_tiene_error = true;
	}

	while (tmpNode != nullptr)
	{
		file.write(reinterpret_cast<char*>(tmpNode), sizeof(Promocion));
		tmpNode = tmpNode->SiguentePuntero;
	}

	file.close();
}

Promocion* buscar_promocion_por_nombre(char nombre[50])
{
	ir_primer_nodo_promociones_lista();
	Promocion* p = nullptr;

	p = ptr_promociones;
	while (p != nullptr)
	{
		if (strcmp(nombre, p->Nombre) == 0)
			return p;

		p = p->SiguentePuntero;
	}

	return nullptr;
}

void eliminar_promocion_por_nombre(char nombre[50])
{
	Promocion* p = buscar_promocion_por_nombre(nombre);

	if (p->AnteriorPuntero == nullptr)
	{
		ir_primer_nodo_promociones_lista();
		if (p->SiguentePuntero != nullptr)
		{
			ptr_promociones = p->SiguentePuntero;
			p->SiguentePuntero->AnteriorPuntero = nullptr;
			p->SiguentePuntero = nullptr;
		}
		else
		{
			ptr_promociones = nullptr;
		}
	}
	else if (p->SiguentePuntero == nullptr)
	{
		ir_ultimo_nodo_promociones_lista();
		if (p->AnteriorPuntero != nullptr)
		{
			ptr_promociones = p->AnteriorPuntero;
			p->AnteriorPuntero->SiguentePuntero = nullptr;
			p->AnteriorPuntero = nullptr;
		}
		else
		{
			ptr_promociones = nullptr;
		}
	}
	else
	{
		p->SiguentePuntero->AnteriorPuntero = p->AnteriorPuntero;
		p->AnteriorPuntero->SiguentePuntero = p->SiguentePuntero;
	}

	delete p;
}
