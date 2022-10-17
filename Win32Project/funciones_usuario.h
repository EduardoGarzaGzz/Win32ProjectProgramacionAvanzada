#pragma once

#include "libs.h"
#include "structs.h"

bool usuario_logiado = false;
bool archivo_usuarios_tiene_error = false;
Usuario* usuario_seleccionado = nullptr;
char nombre_comercio_selecionado[15];

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

	file.open("usuarios.bin", ios::in | ios::binary);

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

	if (!file.is_open() || file.fail())
	{
		archivo_usuarios_tiene_error = true;
	}

	while (tmpNode != nullptr)
	{
		file.write(reinterpret_cast<char*>(tmpNode), sizeof(Usuario));
		tmpNode = tmpNode->SiguentePuntero;
	}

	file.close();
}

bool es_login_correcto(char alias[10], char password[30])
{
	ir_primer_nodo_usuarios_lista();
	Usuario* u = nullptr;

	u = ptr_usuarios;
	if (u == nullptr) return false;
	while (u != nullptr)
	{
		if (strcmp(alias, u->AliasDeUsuario) == 0 && strcmp(password, u->Password) == 0)
		{
			strcpy_s(nombre_comercio_selecionado, u->NombreComercio);
			return true;
		}


		u = u->SiguentePuntero;
	}

	return false;
}

Usuario* buscar_usuario_por_alias(char alias[10])
{
	ir_primer_nodo_usuarios_lista();
	Usuario* u = nullptr;

	u = ptr_usuarios;
	while (u != nullptr)
	{
		if (strcmp(alias, u->AliasDeUsuario) == 0)
			return u;

		u = u->SiguentePuntero;
	}

	return nullptr;
}

void eliminar_usuario_por_alias(char alias[10])
{
	Usuario* u = buscar_usuario_por_alias(alias);

	if (u->AnteriorPuntero == nullptr)
	{
		ir_primer_nodo_usuarios_lista();
		if (u->SiguentePuntero != nullptr)
		{
			ptr_usuarios = u->SiguentePuntero;
			u->SiguentePuntero->AnteriorPuntero = nullptr;
			u->SiguentePuntero = nullptr;
		}
		else
		{
			ptr_usuarios = nullptr;
		}
	}
	else if (u->SiguentePuntero == nullptr)
	{
		ir_ultimo_nodo_usuarios_lista();
		if (u->AnteriorPuntero != nullptr)
		{
			ptr_usuarios = u->AnteriorPuntero;
			u->AnteriorPuntero->SiguentePuntero = nullptr;
			u->AnteriorPuntero = nullptr;
		}
		else
		{
			ptr_usuarios = nullptr;
		}
	}
	else
	{
		u->SiguentePuntero->AnteriorPuntero = u->AnteriorPuntero;
		u->AnteriorPuntero->SiguentePuntero = u->SiguentePuntero;
	}

	delete u;
}
