#include "KB65 Autoclicker.h"





void TitleBarColor(HWND hWnd);


int themeOption = THEMEDEFAULT;

HBRUSH
themeColor = (HBRUSH) (COLOR_BTNSHADOW),
hColumnColor = (HBRUSH) (COLOR_BTNSHADOW);

COLORREF
titleColor = GetSysColor(COLOR_BTNSHADOW),
lineColor = RGB(144, 144, 144),
columnColor = GetSysColor(COLOR_BTNSHADOW);



void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color, int lineWidth)
{
	HPEN hPen = CreatePen(PS_SOLID, DPI::Scale(lineWidth), color);
	HPEN hSafePen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, DPI::Scale(x1), DPI::Scale(y1), NULL);
	LineTo(hdc, DPI::Scale(x2), DPI::Scale(y2));


	// 1- SelectObject(hSafePen) to disable hPen
	// 2- DeleteObject(hPen) to delete hPen safely

	SelectObject(hdc, hSafePen);
	DeleteObject(hPen);
}



void SelectTheme(HWND hWnd)
{
	if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
		DeleteObject(themeColor);

	themeOption = (int)SendMessage(themesList, CB_GETCURSEL, 0, 0);

	/*
		0: DEFAULT
		1: BURLYWOOD
		2: GOLD
		3: GRAY
		4: MAGIC FLOWER
		5: ROCKET
		6: SOCCER PITCH
		7: OCEANIC
	*/
	switch(themeOption)
	{
		case THEMEDEFAULT:
		default:
			titleColor = DWM_COLOR_DEFAULT;
			themeColor = (HBRUSH) (COLOR_BTNSHADOW);
			lineColor = RGB(144, 144, 144);
			break;

		case THEMEBURLYWOOD:
			titleColor = RGB(222, 184, 135);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(155, 117, 53);
			columnColor = RGB(235, 197, 150);
			break;

		case THEMEGOLD:
			titleColor = RGB(255, 215, 0);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(220, 220, 220);
			columnColor = RGB(245, 208, 15);
			break;

		case THEMEGREY:
			titleColor = RGB(128, 128, 128);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(220, 220, 220);
			columnColor = RGB(169, 169, 169);
			break;

		case THEMEMAGIC:
			titleColor = RGB(224, 163, 224);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(222, 192, 222);
			columnColor = RGB(217, 156, 215);
			break;

		case THEMEROCKET:
			titleColor = RGB(201, 35, 31);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(220, 220, 220);
			columnColor = RGB(201, 225, 231);
			break;

		case THEMESOCCER:
			titleColor = RGB(143, 209, 92);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(210, 210, 220);
			columnColor = RGB(231, 243, 230);
			break;

		case THEMEOCEANIC:
			titleColor = RGB(70, 230, 214);
			themeColor = CreateSolidBrush(titleColor);
			lineColor = RGB(210, 210, 220);
			columnColor = RGB(80, 241, 226);
			break;
	}

	if (isWindows11Later())
		TitleBarColor(hWnd);
}



// Windows 11+
void TitleBarColor(HWND hWnd)
{
	typedef HRESULT (WINAPI *pDwmSetWindowAttribute)(HWND, DWORD, LPCVOID, DWORD);

	HMODULE hDwm = LoadLibraryW(L"dwmapi.dll");
	if (hDwm)
	{
		pDwmSetWindowAttribute fDwmSetWindowAttribute = 
			(pDwmSetWindowAttribute)GetProcAddress(hDwm, "DwmSetWindowAttribute");

		if (fDwmSetWindowAttribute)
			fDwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &titleColor, sizeof(titleColor));

		FreeLibrary(hDwm);
	}
}



void DeleteBrush()
{
	if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
		DeleteObject(themeColor);
	if (hColumnColor != (HBRUSH)(COLOR_BTNSHADOW))
		DeleteObject(hColumnColor);
}