#include "KB65 Autoclicker.h"





void AutoClickerTexts(HDC hdc)
{
	TextOut(hdc,
		DPIScale(58),
		DPIScale(30),
		"hours", STRLEN_INT("hours"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(54),
		"minutes", STRLEN_INT("minutes"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(78),
		"seconds", STRLEN_INT("seconds"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(102),
		"milliseconds", STRLEN_INT("milliseconds"));

	// Display colons ( : ) between hour/minute/second edits.
	for (int xPos = 297; xPos <= 329; xPos += 32)
		TextOut(hdc, DPIScale(xPos), DPIScale(149), ":", 1);
}



void KeyboardPresserTexts(HDC hdc)
{
	TextOut(hdc,
		DPIScale(58),
		DPIScale(212),
		"hours", STRLEN_INT("hours"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(236),
		"minutes", STRLEN_INT("minutes"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(260),
		"seconds", STRLEN_INT("seconds"));

	TextOut(hdc,
		DPIScale(58),
		DPIScale(284),
		"milliseconds", STRLEN_INT("milliseconds"));

	// Display colons ( : ) between hour/minute/second edits.
	for (int xPos = 297; xPos <= 329; xPos += 32)
		TextOut(hdc, DPIScale(xPos), DPIScale(331), ":", 1);
}



void PageTexts(HDC hdc, int pageTexts)
{
	switch(pageTexts)
	{
		case MAINPAGE:
		{
			AutoClickerTexts(hdc);
			KeyboardPresserTexts(hdc);
			break;
		}
		case SETTINGSPAGE:
		{
			TextOut(hdc,
				DPIScale(5), DPIScale(348),
				"v1.0.2", STRLEN_INT("v1.0.2"));
			break;
		}
	}
}