#include "main.h"





void AutoClickerTexts(HDC hdc)
{
	TextOut(hdc,
		58.0 * DPIScale(),
		30.0 * DPIScale(),
		"hours", strlen("hours"));

	TextOut(hdc,
		58.0 * DPIScale(),
		54.0 * DPIScale(),
		"minutes", strlen("minutes"));

	TextOut(hdc,
		58.0 * DPIScale(),
		78.0 * DPIScale(),
		"seconds", strlen("seconds"));

	TextOut(hdc,
		58.0 * DPIScale(),
		102.0 * DPIScale(),
		"milliseconds", strlen("milliseconds"));

	for (double xPos = 297.0; xPos <= 329.0; xPos += 32.0)
		TextOut(hdc,
			xPos * DPIScale(),
			149.0 * DPIScale(),
			":", 1);
}



void KeyboardPresserTexts(HDC hdc)
{
	TextOut(hdc,
		58.0 * DPIScale(),
		212.0 * DPIScale(),
		"hours", strlen("hours"));

	TextOut(hdc,
		58.0 * DPIScale(),
		236.0 * DPIScale(),
		"minutes", strlen("minutes"));

	TextOut(hdc,
		58.0 * DPIScale(),
		260.0 * DPIScale(),
		"seconds", strlen("seconds"));

	TextOut(hdc,
		58.0 * DPIScale(),
		284.0 * DPIScale(),
		"milliseconds", strlen("milliseconds"));

	for (double xPos = 297.0; xPos <= 329.0; xPos += 32.0)
		TextOut(hdc,
			xPos * DPIScale(),
			331.0 * DPIScale(),
			":", 1);
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
				5.0 * DPIScale(),
				348.0 * DPIScale(),
				"v1.0.1", strlen("v1.0.1"));
			break;
		}
	}
}