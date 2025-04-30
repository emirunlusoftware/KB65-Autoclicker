#include "main.h"





int themeOption = THEMEDEFAULT;

HPEN hPen, hSafePen;

HBRUSH
themeColor = (HBRUSH) (COLOR_BTNSHADOW);

COLORREF
lineColor1 = RGB(128, 128, 128),
lineColor2 = GetSysColor(NULL);


void DrawLine(HDC hdc, double x1, double y1, double x2, double y2, COLORREF color, int lineWidth)
{
	hPen = CreatePen(PS_SOLID, lineWidth * DPIScale(), color);
	hSafePen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, x1 * DPIScale(), y1 * DPIScale(), NULL);
	LineTo(hdc, x2 * DPIScale(), y2 * DPIScale());


	/*
		1- SelectObject(hSafePen) to disable hPen
		2- DeleteObject(hPen) to delete hPen safely
	*/

	SelectObject(hdc, hSafePen);
	DeleteObject(hPen);
}



void SelectThemeText(TCHAR themeText[])
{
	if (strcmp(themeText, "Default") == 0)
	{
		themeOption = THEMEDEFAULT;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Burlywood") == 0)
	{
		themeOption = THEMEBURLYWOOD;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Gold") == 0)
	{
		themeOption = THEMEGOLD;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Gray") == 0)
	{
		themeOption = THEMEGREY;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Lilac") == 0)
	{
		themeOption = THEMELILAC;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Soccer Pitch") == 0)
	{
		themeOption = THEMESOCCER;
		SelectTheme(themeOption);
	}
	else if (strcmp(themeText, "Oceanic") == 0)
	{
		themeOption = THEMEOCEANIC;
		SelectTheme(themeOption);
	}
}



void SelectTheme(int themeOption)
{
	if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
		DeleteObject(themeColor);

	switch(themeOption)
	{
		case THEMEDEFAULT:
			themeColor = (HBRUSH) (COLOR_BTNSHADOW);
			lineColor1 = lineColor2 = RGB(128, 128, 128);
			break;

		case THEMEBURLYWOOD:
			themeColor = CreateSolidBrush(RGB(222, 184, 135));
			lineColor1 = RGB(155, 117, 53);
			lineColor2 = RGB(235, 197, 150);
			break;

		case THEMEGOLD:
			themeColor = CreateSolidBrush(RGB(255, 215, 0));
			lineColor1 = RGB(220, 220, 220);
			lineColor2 = RGB(245, 208, 15);
			break;

		case THEMEGREY:
			themeColor = CreateSolidBrush(RGB(128, 128, 128));
			lineColor1 = RGB(220, 220, 220);
			lineColor2 = RGB(169, 169, 169);
			break;

		case THEMELILAC:
			themeColor = CreateSolidBrush(RGB(200, 162, 200));
			lineColor1 = RGB(220, 182, 220);
			lineColor2 = RGB(195, 155, 192);
			break;

		case THEMESOCCER:
			themeColor = CreateSolidBrush(RGB(143, 209, 92));
			lineColor1 = RGB(210, 210, 220);
			lineColor2 = RGB(231, 243, 230);
			break;

		case THEMEOCEANIC:
			themeColor = CreateSolidBrush(RGB(70, 230, 214));
			lineColor1 = RGB(210, 210, 220);
			lineColor2 = RGB(80, 241, 226);
			break;
	}
}