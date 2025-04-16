#include "main.h"
#include <shellapi.h>





NOTIFYICONDATA nid;
HMENU trayMenu;
LRESULT isTrayChecked;

void SystemTrayInit(HWND hWnd, HINSTANCE hInstance)
{
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = hWnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_USER + 1;
	nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	lstrcpyn(nid.szTip, ("KB65 Autoclicker"), ARRAYSIZE(nid.szTip));
}



void MinimizeToTray()
{
	Shell_NotifyIcon(NIM_ADD, &nid);
}



void ShowTrayMenu(HWND hWnd, POINT pt, bool mouseActive, bool keyboardActive)
{
	trayMenu = CreatePopupMenu();

	{
		AppendMenu(trayMenu, MF_STRING | (mouseActive ? MF_CHECKED : MF_UNCHECKED), ACTIVATEMOUSETRAY, "Activate Mouse");
		AppendMenu(trayMenu, MF_STRING | (keyboardActive ? MF_CHECKED : MF_UNCHECKED), ACTIVATEKEYBOARDTRAY, "Activate Keyboard");

		AppendMenu(trayMenu, MF_SEPARATOR, NULL, 0);

		AppendMenu(trayMenu, MF_STRING, OPENTRAY, "Open");
		AppendMenu(trayMenu, MF_STRING, QUITTRAY, "Quit");
	}

	SetForegroundWindow(hWnd);
	TrackPopupMenu(trayMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
	DestroyMenu(trayMenu);
}



void RemoveTrayIcon()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);
}