#include "libs.h"
#include "structs.h"
#include "validaciones.h"
#include "funciones_usuario.h"

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_inicio_seccion(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK wnd_prec_registro_admin(HWND, UINT, WPARAM, LPARAM);

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
				}
				break;
			case IDC_BTN_OPT_CLIENTES:
				{
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
						MessageBox(nullptr, L"El alias o la contraseña es incorrecta", L"Error", MB_OK | MB_ICONERROR);
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
						MessageBox(nullptr, L"El nombre del comercio es invalido\nLongitud de 5 a 15 caracteres alfanuméricos o espacios.", L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!nombre_usuario_es_valido(u->NombreDeUsuario))
					{
						MessageBox(nullptr, L"El nombre de usuario es invalido\nSolamente se permiten letras, máximo 15", L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!alias_usuario_es_valido(u->AliasDeUsuario))
					{
						MessageBox(nullptr, L"El alias del usuario es invalido\nSolo se permite caracteres alfanuméricos, mínimo 3 y máximo 10", L"Error", MB_OK | MB_ICONERROR);
						break;
					}
					else if (!password_usuario_es_valida(u->Password))
					{
						MessageBox(nullptr, L"La contraseña es invalida\nMínimo 3 y máximo 10 caracteres, se debe solicitar una letra, un número y un carácter especial.", L"Error", MB_OK | MB_ICONERROR);
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
