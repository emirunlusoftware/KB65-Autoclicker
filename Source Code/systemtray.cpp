#include "KB65 Autoclicker.h"
#include <shellapi.h>





NOTIFYICONDATA nid;
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
	lstrcpyn(nid.szTip, "KB65 Autoclicker", ARRAYSIZE(nid.szTip));
}



void MinimizeToTray()
{
	Shell_NotifyIcon(NIM_ADD, &nid);
}



void ShowTrayMenu(HWND hWnd, POINT pt, bool mouseActive, bool keyboardActive)
{
	HMENU trayMenu = CreatePopupMenu();


	AppendMenu(trayMenu, MF_STRING | (mouseActive ? MF_CHECKED : MF_UNCHECKED), ACTIVATEMOUSE_VIA_TRAY, "Activate Mouse");
	AppendMenu(trayMenu, MF_STRING | (keyboardActive ? MF_CHECKED : MF_UNCHECKED), ACTIVATEKEYBOARD_VIA_TRAY, "Activate Keyboard");

	AppendMenu(trayMenu, MF_SEPARATOR, NULL, 0);

	AppendMenu(trayMenu, MF_STRING, OPEN_VIA_TRAY, "Open");
	AppendMenu(trayMenu, MF_STRING, QUIT_VIA_TRAY, "Quit");


	SetForegroundWindow(hWnd);
	TrackPopupMenu(trayMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
	PostMessage(hWnd, WM_NULL, 0, 0);
	DestroyMenu(trayMenu);
}



void RemoveTrayIcon()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);
}