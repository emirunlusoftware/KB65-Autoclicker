#include "KB65 Autoclicker.h"





HFONT globalFont = NULL;
void LoadingFonts (HWND hWnd)
{
	globalFont = CreateFont(
		DPIScale(-11),
		DPIScale(-5),
		0, 0,
		FW_NORMAL,
		0, 0, 0,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Tahoma"
	);

	HWND hWndChild = GetWindow(hWnd, GW_CHILD);
	while (hWndChild)
	{
		SendMessage(hWndChild, WM_SETFONT, (WPARAM)globalFont, TRUE);
		hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
	}
}