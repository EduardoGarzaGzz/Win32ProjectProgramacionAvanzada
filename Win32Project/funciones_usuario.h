#pragma once

#include "libs.h"
#include "structs.h"

bool usuario_logiado = false;
bool archivo_usuarios_tiene_error = false;

void ir_primer_nodo_usuarios_lista()
{
	if (ptr_usuarios == nullptr) return;
	while (ptr_usuarios->AnteriorPuntero != nullptr)
	{
		ptr_usuarios = ptr_usuarios->AnteriorPuntero;
	}
}

void ir_ultimo_nodo_usuarios_lista()
{
	if (ptr_usuarios == nullptr) return;
	while (ptr_usuarios->SiguentePuntero != nullptr)
	{
		ptr_usuarios = ptr_usuarios->SiguentePuntero;
	}
}

void agregar_usuario_lista(Usuario* u)
{
	u->SiguentePuntero = nullptr;
	u->AnteriorPuntero = nullptr;

	if (ptr_usuarios == nullptr)
	{
		ptr_usuarios = u;
		return;
	}

	ir_ultimo_nodo_usuarios_lista();

	ptr_usuarios->SiguentePuntero = u;
	u->AnteriorPuntero = ptr_usuarios;
}

void leer_usuarios()
{
	Usuario* user = nullptr;
	ifstream file;

	file.open("user.bin", ios::in | ios::binary);

	if (!file.is_open() || file.fail())
	{
		archivo_usuarios_tiene_error = true;
		return;
	}

	do
	{
		user = new Usuario;
		if (!file.read(reinterpret_cast<char*>(user), sizeof(Usuario)))
		{
			break;
		}

		user->SiguentePuntero = nullptr;
		user->AnteriorPuntero = nullptr;

		agregar_usuario_lista(user);
	}
	while (true);

	file.close();
}

void guardar_en_archivo_usuario()
{
	ir_primer_nodo_usuarios_lista();
	Usuario* tmpNode = ptr_usuarios;
	ofstream file;

	file.open("usuarios.bin", ios::out | ios::binary | ios::trunc);

	if (!file.is_open() || file.fail()) {
		archivo_usuarios_tiene_error = true;
	}

	while (tmpNode != nullptr) {
		file.write(reinterpret_cast<char*>(tmpNode), sizeof(Usuario));
		tmpNode = tmpNode->SiguentePuntero;
	}

	file.close();
}
