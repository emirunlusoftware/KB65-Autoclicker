#include "KB65 Autoclicker.h"





void AutoClickerTexts(HDC hdc)
{
	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(30),
		"hours", STRLEN_INT("hours"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(54),
		"minutes", STRLEN_INT("minutes"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(78),
		"seconds", STRLEN_INT("seconds"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(102),
		"milliseconds", STRLEN_INT("milliseconds"));

	// Display colons ( : ) between hour/minute/second editboxes.
	for (int xPos = 297; xPos <= 329; xPos += 32)
		TextOut(hdc, DPI::Scale(xPos), DPI::Scale(149), ":", 1);
}



void KeyboardPresserTexts(HDC hdc)
{
	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(212),
		"hours", STRLEN_INT("hours"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(236),
		"minutes", STRLEN_INT("minutes"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(260),
		"seconds", STRLEN_INT("seconds"));

	TextOut(hdc,
		DPI::Scale(58),
		DPI::Scale(284),
		"milliseconds", STRLEN_INT("milliseconds"));

	// Display colons ( : ) between hour/minute/second editboxes.
	for (int xPos = 297; xPos <= 329; xPos += 32)
		TextOut(hdc, DPI::Scale(xPos), DPI::Scale(331), ":", 1);
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
				DPI::Scale(5), DPI::Scale(348),
				"v1.0.3.1", STRLEN_INT("v1.0.3.1"));
			break;
		}
	}
}