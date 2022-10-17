#pragma once

#include "libs.h"
#include "structs.h"

bool archivo_clientes_tiene_error = true;
Cliente* cliente_seleccionado = nullptr;

void ir_primer_nodo_clientes_lista()
{
	if (ptr_clientes == nullptr) return;
	while (ptr_clientes->AnteriorPuntero != nullptr)
	{
		ptr_clientes = ptr_clientes->AnteriorPuntero;
	}
}

void ir_ultimo_nodo_clientes_lista()
{
	if (ptr_clientes == nullptr) return;
	while (ptr_clientes->SiguentePuntero != nullptr)
	{
		ptr_clientes = ptr_clientes->SiguentePuntero;
	}
}

void agregar_cliente_lista(Cliente* c)
{
	c->SiguentePuntero = nullptr;
	c->AnteriorPuntero = nullptr;

	if (ptr_clientes == nullptr)
	{
		ptr_clientes = c;
		return;
	}

	ir_ultimo_nodo_clientes_lista();

	ptr_clientes->SiguentePuntero = c;
	c->AnteriorPuntero = ptr_clientes;
}

void leer_clientes()
{
	Cliente* cliente = nullptr;
	ifstream file;

	file.open("clientes.bin", ios::in | ios::binary);

	if (!file.is_open() || file.fail())
	{
		archivo_clientes_tiene_error = true;
		return;
	}

	do
	{
		cliente = new Cliente;
		if (!file.read(reinterpret_cast<char*>(cliente), sizeof(Cliente)))
		{
			break;
		}

		cliente->SiguentePuntero = nullptr;
		cliente->AnteriorPuntero = nullptr;

		agregar_cliente_lista(cliente);
	}
	while (true);

	file.close();
}

void guardar_en_archivo_clientes()
{
	ir_primer_nodo_clientes_lista();
	Cliente* tmpNode = ptr_clientes;
	ofstream file;

	file.open("clientes.bin", ios::out | ios::binary | ios::trunc);

	if (!file.is_open() || file.fail())
	{
		archivo_clientes_tiene_error = true;
	}

	while (tmpNode != nullptr)
	{
		file.write(reinterpret_cast<char*>(tmpNode), sizeof(Cliente));
		tmpNode = tmpNode->SiguentePuntero;
	}

	file.close();
}

Cliente* buscar_cliente_por_nombre(char nombre[50])
{
	ir_primer_nodo_clientes_lista();
	Cliente* c = nullptr;

	c = ptr_clientes;
	while (c != nullptr)
	{
		if (strcmp(nombre, c->Nombre) == 0)
			return c;

		c = c->SiguentePuntero;
	}

	return nullptr;
}

void eliminar_cliente_por_nombre(char nombre[50])
{
	Cliente* c = buscar_cliente_por_nombre(nombre);

	if (c->AnteriorPuntero == nullptr)
	{
		ir_primer_nodo_clientes_lista();
		if (c->SiguentePuntero != nullptr)
		{
			ptr_clientes = c->SiguentePuntero;
			c->SiguentePuntero->AnteriorPuntero = nullptr;
			c->SiguentePuntero = nullptr;
		}
		else
		{
			ptr_clientes = nullptr;
		}
	}
	else if (c->SiguentePuntero == nullptr)
	{
		ir_ultimo_nodo_clientes_lista();
		if (c->AnteriorPuntero != nullptr)
		{
			ptr_clientes = c->AnteriorPuntero;
			c->AnteriorPuntero->SiguentePuntero = nullptr;
			c->AnteriorPuntero = nullptr;
		}
		else
		{
			ptr_clientes = nullptr;
		}
	}
	else
	{
		c->SiguentePuntero->AnteriorPuntero = c->AnteriorPuntero;
		c->AnteriorPuntero->SiguentePuntero = c->SiguentePuntero;
	}

	delete c;
}
