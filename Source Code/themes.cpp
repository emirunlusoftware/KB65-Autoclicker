#include "KB65 Autoclicker.h"





int themeOption = THEMEDEFAULT;

HBRUSH
themeColor = (HBRUSH) (COLOR_BTNSHADOW);

COLORREF
lineColor1 = RGB(144, 144, 144),
lineColor2 = GetSysColor(NULL);


void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color, int lineWidth)
{
	HPEN hPen = CreatePen(PS_SOLID, DPIScale(lineWidth), color);
	HPEN hSafePen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, DPIScale(x1), DPIScale(y1), NULL);
	LineTo(hdc, DPIScale(x2), DPIScale(y2));


	/*
		1- SelectObject(hSafePen) to disable hPen
		2- DeleteObject(hPen) to delete hPen safely
	*/

	SelectObject(hdc, hSafePen);
	DeleteObject(hPen);
}



void SelectTheme()
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
			themeColor = (HBRUSH) (COLOR_BTNSHADOW);
			lineColor1 = lineColor2 = RGB(144, 144, 144);
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

		case THEMEMAGIC:
			themeColor = CreateSolidBrush(RGB(224, 163, 224));
			lineColor1 = RGB(222, 192, 222);
			lineColor2 = RGB(217, 156, 215);
			break;

		case THEMEROCKET:
			themeColor = CreateSolidBrush(RGB(201, 35, 31));
			lineColor1 = RGB(220, 220, 220);
			lineColor2 = RGB(201, 225, 231);
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