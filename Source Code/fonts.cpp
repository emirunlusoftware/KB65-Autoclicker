#include "KB65 Autoclicker.h"





HFONT globalFont = NULL, tooltipFont = NULL;
void LoadFonts (HWND hWnd)
{
	globalFont = CreateFont(
		DPI::Scale(-11),
		DPI::Scale(-5),
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

	NONCLIENTMETRICS ncm = { 0 };
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
	tooltipFont = CreateFontIndirect(&ncm.lfMessageFont);

	HWND hWndChild = GetWindow(hWnd, GW_CHILD);
	while (hWndChild)
	{
		SendMessage(hWndChild, WM_SETFONT, (WPARAM)globalFont, TRUE);
		hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
	}
}



void DestroyFonts()
{
	if (globalFont)
	{
		DeleteObject(globalFont);
		globalFont = NULL;
	}
	if (tooltipFont)
	{
		DeleteObject(tooltipFont);
		tooltipFont = NULL;
	}
}