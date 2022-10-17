#include "libs.h"
#include "structs.h"
#include "validaciones.h"
#include "funciones_usuario.h"
#include "funciones_cliente.h"

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_inicio_seccion(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_registro_admin(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_opciones_usuarios(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_opciones_cliente(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_nuevo_usuario(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_nuevo_cliente(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_actualizar_usuario(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_actualizar_cliente(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_MenuPrincipal), nullptr, WndProc);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			leer_usuarios();
			leer_clientes();

			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_InicioDeSeccion), nullptr, wnd_prec_inicio_seccion);

			if (!usuario_logiado)
			{
				DestroyWindow(hWnd);
			}

			return 0;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_OPT_USUARIOS:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_OpcionesUsuario), nullptr, wnd_prec_opciones_usuarios);
				}
				break;
			case IDC_BTN_OPT_CLIENTES:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_OpcionesCliente), nullptr, wnd_prec_opciones_cliente);
				}
				break;
			case IDC_BTN_OPT_PROMOCIONES:
				{
				}
				break;
			case IDC_BTN_OPT_CONSUMOS:
				{
				}
				break;
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_inicio_seccion(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			return 0;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_BTN_INICIO_SECCION:
				{
					Usuario* u = new Usuario;
					const HWND hedAlias = GetDlgItem(hWnd, IDC_EDIT_ALIAS);
					const HWND hedPassword = GetDlgItem(hWnd, IDC_EDIT_PASSWORD);

					GetWindowTextA(hedAlias, (LPSTR)u->AliasDeUsuario, sizeof(u->AliasDeUsuario));
					GetWindowTextA(hedPassword, (LPSTR)u->Password, sizeof(u->Password));

					if (es_login_correcto(u->AliasDeUsuario, u->Password))
					{
						usuario_logiado = true;
						MessageBox(nullptr, L"Bienvenido :)", L"Info", MB_OK | MB_ICONINFORMATION);
						DestroyWindow(hWnd);
					}
					else
						MessageBox(nullptr, L"El alias o la contrase�a es incorrecta", L"Error", MB_OK | MB_ICONERROR);
				}
				break;

			case ID_BTN_REGISTRARCE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_RegistroNuevoAdmin), nullptr, wnd_prec_registro_admin);
				break;
			}
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_registro_admin(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			const HWND hComboBox = GetDlgItem(hWnd, IDC_COMBO_COMERCIOS);
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Tienda de la esquina");
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Spa");
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Gym");
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Ciber");
			SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			return 0;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_GUARDAR:
				{
					Usuario* u = new Usuario;
					const HWND hcbComercio = GetDlgItem(hWnd, IDC_COMBO_COMERCIOS);
					const HWND hedNombre = GetDlgItem(hWnd, IDC_EDIT_NOMBRE);
					const HWND hedUsername = GetDlgItem(hWnd, IDC_EDIT_USERNAME);
					const HWND hedPassword = GetDlgItem(hWnd, IDC_EDIT_PASSWORD);

					GetWindowTextA(hcbComercio, (LPSTR)u->NombreComercio, sizeof(u->NombreComercio));
					GetWindowTextA(hedNombre, (LPSTR)u->NombreDeUsuario, sizeof(u->NombreDeUsuario));
					GetWindowTextA(hedUsername, (LPSTR)u->AliasDeUsuario, sizeof(u->AliasDeUsuario));
					GetWindowTextA(hedPassword, (LPSTR)u->Password, sizeof(u->Password));

					if (!nombre_comercio_es_valido(u->NombreComercio))
					{
						MessageBox(nullptr,
						           L"El nombre del comercio es invalido\nLongitud de 5 a 15 caracteres alfanum�ricos o espacios.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!nombre_usuario_es_valido(u->NombreDeUsuario))
					{
						MessageBox(nullptr,
						           L"El nombre de usuario es invalido\nSolamente se permiten letras, m�ximo 15",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_usuario_es_valido(u->AliasDeUsuario))
					{
						MessageBox(nullptr,
						           L"El alias del usuario es invalido\nSolo se permite caracteres alfanum�ricos, m�nimo 3 y m�ximo 10",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!password_usuario_es_valida(u->Password))
					{
						MessageBox(nullptr,
						           L"La contrase�a es invalida\nM�nimo 3 y m�ximo 10 caracteres, se debe solicitar una letra, un n�mero y un car�cter especial.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}

					u->EsSuperAdmin = true;
					u->EsAdmin = true;

					agregar_usuario_lista(u);
					guardar_en_archivo_usuario();

					MessageBox(nullptr, L"Se a guardado correctamente el nuevo usuario", L"Info",
					           MB_OK | MB_ICONINFORMATION);
					DestroyWindow(hWnd);
				}
				break;
			}
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_opciones_usuarios(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			Usuario* u = nullptr;
			ir_primer_nodo_usuarios_lista();

			u = ptr_usuarios;
			while (u != nullptr)
			{
				SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_ADDSTRING, 0, (LPARAM)u->AliasDeUsuario);
				u = u->SiguentePuntero;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_NUEVO_USUARIO:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_RegistrarUsuario), nullptr, wnd_prec_nuevo_usuario);

					Usuario* u = nullptr;
					ir_primer_nodo_usuarios_lista();

					u = ptr_usuarios;
					SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_RESETCONTENT, 0, 0);
					while (u != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_ADDSTRING, 0, (LPARAM)u->AliasDeUsuario);
						u = u->SiguentePuntero;
					}
				}
				break;
			case IDC_BTN_ACTUALIZAR_USUARIO:
				{
					char alias_usuario[255];
					const HWND hlUsuarios = GetDlgItem(hWnd, IDC_LIST_USUARIOS);

					const int idx = SendMessage(hlUsuarios, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessageA(hlUsuarios, LB_GETTEXT, (WPARAM)idx, (LPARAM)alias_usuario);

					usuario_seleccionado = buscar_usuario_por_alias(alias_usuario);

					if (usuario_seleccionado == nullptr)
					{
						MessageBox(nullptr,
						           L"Tiene que selecionar un usuario o vuelva a selecionarlo y vuelva a intentarlo",
						           L"Advertencia",
						           MB_OK | MB_ICONWARNING);
						break;
					}

					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_ActualizacionUsuario), nullptr,
					          wnd_prec_actualizar_usuario);

					Usuario* u = nullptr;
					ir_primer_nodo_usuarios_lista();

					u = ptr_usuarios;
					SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_RESETCONTENT, 0, 0);
					while (u != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_ADDSTRING, 0, (LPARAM)u->AliasDeUsuario);
						u = u->SiguentePuntero;
					}
				}
				break;
			case IDC_BTN_BORRAR_USUARIO:
				{
					char alias_usuario[255];
					const HWND hlUsuarios = GetDlgItem(hWnd, IDC_LIST_USUARIOS);

					const int idx = SendMessage(hlUsuarios, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessageA(hlUsuarios, LB_GETTEXT, (WPARAM)idx, (LPARAM)alias_usuario);

					usuario_seleccionado = buscar_usuario_por_alias(alias_usuario);

					if (usuario_seleccionado == nullptr)
					{
						MessageBox(nullptr,
						           L"Tiene que selecionar un usuario o vuelva a selecionarlo y vuelva a intentarlo",
						           L"Advertencia",
						           MB_OK | MB_ICONWARNING);
						break;
					}

					int msgboxID = MessageBox(
						NULL,
						(LPCWSTR)L"Estas seguro que deseas eliminar al usuario selecionado?",
						(LPCWSTR)L"Advertencia",
						MB_ICONWARNING | MB_OKCANCEL);

					if (msgboxID != IDOK)
						break;

					eliminar_usuario_por_alias(alias_usuario);
					guardar_en_archivo_usuario();

					Usuario* u = nullptr;
					ir_primer_nodo_usuarios_lista();

					u = ptr_usuarios;
					SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_RESETCONTENT, 0, 0);
					while (u != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_USUARIOS, LB_ADDSTRING, 0, (LPARAM)u->AliasDeUsuario);
						u = u->SiguentePuntero;
					}
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_opciones_cliente(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			Cliente* c = nullptr;
			ir_primer_nodo_clientes_lista();

			c = ptr_clientes;
			while (c != nullptr)
			{
				SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_ADDSTRING, 0, (LPARAM)c->Nombre);
				c = c->SiguentePuntero;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_NUEVO_CLIENTE:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_RegistrarCliente), nullptr, wnd_prec_nuevo_cliente);

					Cliente* c = nullptr;
					ir_primer_nodo_clientes_lista();

					c = ptr_clientes;
					SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_RESETCONTENT, 0, 0);
					while (c != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_ADDSTRING, 0, (LPARAM)c->Nombre);
						c = c->SiguentePuntero;
					}
				}
				break;
			case IDC_BTN_ACTUALIZAR_CLIENTE:
				{
					char nombre[255];
					const HWND hlClientes = GetDlgItem(hWnd, IDC_LIST_CLIENTES);

					const int idx = SendMessage(hlClientes, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessageA(hlClientes, LB_GETTEXT, (WPARAM)idx, (LPARAM)nombre);

					cliente_seleccionado = buscar_cliente_por_nombre(nombre);

					if (cliente_seleccionado == nullptr)
					{
						MessageBox(nullptr,
						           L"Tiene que selecionar un cliente o vuelva a selecionarlo y vuelva a intentarlo",
						           L"Advertencia",
						           MB_OK | MB_ICONWARNING);
						break;
					}

					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALO_ActualizacionCliente), nullptr,
					          wnd_prec_actualizar_cliente);

					Cliente* c = nullptr;
					ir_primer_nodo_clientes_lista();

					c = ptr_clientes;
					SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_RESETCONTENT, 0, 0);
					while (c != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_ADDSTRING, 0, (LPARAM)c->Nombre);
						c = c->SiguentePuntero;
					}
				}
				break;
			case IDC_BTN_BORRAR_CLIENTE:
				{
					char nombre[255];
					const HWND hlClientes = GetDlgItem(hWnd, IDC_LIST_CLIENTES);

					const int idx = SendMessage(hlClientes, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessageA(hlClientes, LB_GETTEXT, (WPARAM)idx, (LPARAM)nombre);

					cliente_seleccionado = buscar_cliente_por_nombre(nombre);

					if (cliente_seleccionado == nullptr)
					{
						MessageBox(nullptr,
						           L"Tiene que selecionar un cliente o vuelva a selecionarlo y vuelva a intentarlo",
						           L"Advertencia",
						           MB_OK | MB_ICONWARNING);
						break;
					}

					int msgboxID = MessageBox(
						NULL,
						(LPCWSTR)L"Estas seguro que deseas eliminar al cliente selecionado?",
						(LPCWSTR)L"Advertencia",
						MB_ICONWARNING | MB_OKCANCEL);

					if (msgboxID != IDOK)
						break;

					eliminar_cliente_por_nombre(nombre);
					guardar_en_archivo_clientes();

					Cliente* c = nullptr;
					ir_primer_nodo_clientes_lista();

					c = ptr_clientes;
					SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_RESETCONTENT, 0, 0);
					while (c != nullptr)
					{
						SendDlgItemMessageA(hWnd, IDC_LIST_CLIENTES, LB_ADDSTRING, 0, (LPARAM)c->Nombre);
						c = c->SiguentePuntero;
					}
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_nuevo_usuario(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			SetDlgItemTextA(hWnd, IDC_STATIC_NOMBRE_COMERSIO, nombre_comercio_selecionado);
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_GUARDAR:
				{
					char nombre_usuario[50], alias_usuario[10], password[30];
					GetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, nombre_usuario, sizeof(nombre_usuario));
					GetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, alias_usuario, sizeof(alias_usuario));
					GetDlgItemTextA(hWnd, IDC_EDIT_PASSWORD, password, sizeof(password));

					if (!nombre_usuario_es_valido(nombre_usuario))
					{
						MessageBox(nullptr,
						           L"El nombre de usuario es invalido\nSolamente se permiten letras, m�ximo 15",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_usuario_es_valido(alias_usuario))
					{
						MessageBox(nullptr,
						           L"El alias del usuario es invalido\nSolo se permite caracteres alfanum�ricos, m�nimo 3 y m�ximo 10",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!password_usuario_es_valida(password))
					{
						MessageBox(nullptr,
						           L"La contrase�a es invalida\nM�nimo 3 y m�ximo 10 caracteres, se debe solicitar una letra, un n�mero y un car�cter especial.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}

					Usuario* u = new Usuario;
					strcpy_s(u->NombreComercio, nombre_comercio_selecionado);
					strcpy_s(u->NombreDeUsuario, nombre_usuario);
					strcpy_s(u->AliasDeUsuario, alias_usuario);
					strcpy_s(u->Password, password);
					u->EsSuperAdmin = false;

					if (IsDlgButtonChecked(hWnd, IDC_RADIO_ADMIN) == BST_CHECKED)
						u->EsAdmin = true;
					else if (IsDlgButtonChecked(hWnd, IDC_RADIO_CAJERO) == BST_CHECKED)
						u->EsCajero = true;

					agregar_usuario_lista(u);
					guardar_en_archivo_usuario();
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_nuevo_cliente(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			tm ltm;
			const time_t now = time(0);
			char fechaTexto[11], tmp[5];

			localtime_s(&ltm, &now);
			_itoa_s(ltm.tm_mday, tmp, 10);
			strcpy_s(fechaTexto, tmp);
			strcat_s(fechaTexto, "/");
			_itoa_s(ltm.tm_mon + 1, tmp, 10);
			strcat_s(fechaTexto, tmp);
			strcat_s(fechaTexto, "/");
			_itoa_s(ltm.tm_year + 1900, tmp, 10);
			strcat_s(fechaTexto, tmp);

			SetDlgItemTextA(hWnd, IDC_STATIC_NOMBRE_COMERSIO, nombre_comercio_selecionado);
			SetDlgItemTextA(hWnd, IDC_STATIC_FECHA, fechaTexto);
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_GUARDAR:
				{
					char nombre[50], alias[15], telefono[11], email[25], fecha[11];
					GetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, nombre, sizeof(nombre));
					GetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, alias, sizeof(alias));
					GetDlgItemTextA(hWnd, IDC_EDIT_TELEFONO, telefono, sizeof(telefono));
					GetDlgItemTextA(hWnd, IDC_EDIT_EMAIL, email, sizeof(email));
					GetDlgItemTextA(hWnd, IDC_STATIC_FECHA, fecha, sizeof(fecha));

					if (!nombre_cliente_es_valido(nombre))
					{
						MessageBox(nullptr,
						           L"El nombre del cliente es invalido\nSolo caracteres alfab�ticos y espacios, m�nimo 5 y m�ximo 50.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_cliente_es_valido(alias))
					{
						MessageBox(nullptr,
						           L"El alias del cliente es invalido\nSolo caracteres alfab�ticos y espacios, m�nimo 5 y m�ximo 15.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!telefono_cliente_es_valido(telefono))
					{
						MessageBox(nullptr,
						           L"El telefono es invalida\nSolo caracteres num�ricos, de exactamente 10 caracteres.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!email_cliente_es_valido(email))
					{
						MessageBox(nullptr,
						           L"El email es invalida\nValidaci�n de formato email, m�nimo 5 y m�ximo 25.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}

					Cliente* c = new Cliente;
					strcpy_s(c->Nombre, nombre);
					strcpy_s(c->Alias, alias);
					strcpy_s(c->Telefono, telefono);
					strcpy_s(c->Email, email);
					strcpy_s(c->NombreComercio, nombre_comercio_selecionado);
					strcpy_s(c->Fecha, fecha);

					agregar_cliente_lista(c);
					guardar_en_archivo_clientes();
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

// TODO Falta el proceso para la foto de perfil
// TODO Falta crear pantalla y proceso para cambiar la contrase�a
LRESULT CALLBACK wnd_prec_actualizar_usuario(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			SetDlgItemTextA(hWnd, IDC_STATIC_NOMBRE_COMERSIO, nombre_comercio_selecionado);
			SetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, usuario_seleccionado->NombreDeUsuario);
			SetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, usuario_seleccionado->AliasDeUsuario);
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_GUARDAR:
				{
					char nombre_usuario[50], alias_usuario[10];
					GetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, nombre_usuario, sizeof(nombre_usuario));
					GetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, alias_usuario, sizeof(alias_usuario));

					if (!nombre_usuario_es_valido(nombre_usuario))
					{
						MessageBox(nullptr,
						           L"El nombre de usuario es invalido\nSolamente se permiten letras, m�ximo 15",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_usuario_es_valido(alias_usuario))
					{
						MessageBox(nullptr,
						           L"El alias del usuario es invalido\nSolo se permite caracteres alfanum�ricos, m�nimo 3 y m�ximo 10",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}

					strcpy_s(usuario_seleccionado->NombreDeUsuario, nombre_usuario);
					strcpy_s(usuario_seleccionado->AliasDeUsuario, alias_usuario);

					guardar_en_archivo_usuario();
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}

LRESULT CALLBACK wnd_prec_actualizar_cliente(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			SetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, cliente_seleccionado->Nombre);
			SetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, cliente_seleccionado->Alias);
			SetDlgItemTextA(hWnd, IDC_EDIT_TELEFONO, cliente_seleccionado->Telefono);
			SetDlgItemTextA(hWnd, IDC_EDIT_EMAIL, cliente_seleccionado->Email);
			SetDlgItemTextA(hWnd, IDC_STATIC_NOMBRE_COMERSIO, cliente_seleccionado->NombreComercio);
			SetDlgItemTextA(hWnd, IDC_STATIC_FECHA, cliente_seleccionado->Fecha);
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BTN_GUARDAR:
				{
					char nombre[50], alias[15], telefono[11], email[25];
					GetDlgItemTextA(hWnd, IDC_EDIT_NOMBRE, nombre, sizeof(nombre));
					GetDlgItemTextA(hWnd, IDC_EDIT_USERNAME, alias, sizeof(alias));
					GetDlgItemTextA(hWnd, IDC_EDIT_TELEFONO, telefono, sizeof(telefono));
					GetDlgItemTextA(hWnd, IDC_EDIT_EMAIL, email, sizeof(email));

					if (!nombre_cliente_es_valido(nombre))
					{
						MessageBox(nullptr,
						           L"El nombre del cliente es invalido\nSolo caracteres alfab�ticos y espacios, m�nimo 5 y m�ximo 50.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_cliente_es_valido(alias))
					{
						MessageBox(nullptr,
						           L"El alias del cliente es invalido\nSolo caracteres alfab�ticos y espacios, m�nimo 5 y m�ximo 15.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!telefono_cliente_es_valido(telefono))
					{
						MessageBox(nullptr,
						           L"El telefono es invalida\nSolo caracteres num�ricos, de exactamente 10 caracteres.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!email_cliente_es_valido(email))
					{
						MessageBox(nullptr,
						           L"El email es invalida\nValidaci�n de formato email, m�nimo 5 y m�ximo 25.",
						           L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					strcpy_s(cliente_seleccionado->Nombre, nombre);
					strcpy_s(cliente_seleccionado->Alias, alias);
					strcpy_s(cliente_seleccionado->Telefono, telefono);
					strcpy_s(cliente_seleccionado->Email, email);

					guardar_en_archivo_clientes();
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}
