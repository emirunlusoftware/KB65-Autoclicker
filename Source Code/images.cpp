#include "KB65 Autoclicker.h"





HICON
soccerBallImage, anchorImage, rocketImage, flowerImage,
infoIcon, loadScriptsIcon, saveScriptsIcon, settingsIcon;

HICON* icons[8] = {
	&soccerBallImage, &anchorImage, &rocketImage, &flowerImage,
	&infoIcon, &loadScriptsIcon, &saveScriptsIcon, &settingsIcon
};



void LoadImages()
{
	for (UINT iconId = IDI_SOCCER, index = 0; iconId <= IDI_FLOWER; iconId++, index++)
	{
		*icons[index] = (HICON)LoadImage(
		GetModuleHandle(NULL),
		MAKEINTRESOURCE(iconId),
		IMAGE_ICON,
		DPI::Scale(24), DPI::Scale(24),
		LR_CREATEDIBSECTION);
	}

	infoIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_INFO), IMAGE_ICON, DPI::Scale(24), DPI::Scale(24), LR_CREATEDIBSECTION);
	loadScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOADSCRIPT), IMAGE_ICON, DPI::Scale(18), DPI::Scale(18), LR_CREATEDIBSECTION);
	saveScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SAVESCRIPT), IMAGE_ICON, DPI::Scale(18), DPI::Scale(18), LR_CREATEDIBSECTION);
	settingsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SETTINGS), IMAGE_ICON, DPI::Scale(16), DPI::Scale(16), LR_CREATEDIBSECTION);
	SendMessage(infoButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)infoIcon);
	SendMessage(loadScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)loadScriptsIcon);
	SendMessage(settingsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)settingsIcon);
	SendMessage(saveScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)saveScriptsIcon);
}



void GetImages(HDC hdc, int themeOption)
{
	switch(themeOption)
	{
		case THEMEMAGIC:
			DrawIconEx(
				hdc,
				DPI::Scale(373),
				DPI::Scale(10),
				flowerImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMEROCKET:
			DrawIconEx(
				hdc,
				DPI::Scale(373),
				DPI::Scale(10),
				rocketImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMESOCCER:
			DrawIconEx(
				hdc,
				DPI::Scale(373),
				DPI::Scale(10),
				soccerBallImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMEOCEANIC:
			DrawIconEx(
				hdc,
				DPI::Scale(373),
				DPI::Scale(10),
				anchorImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;
	}
}



void DestroyImages()
{
	for (size_t index = 0; index < sizeof(icons)/sizeof(icons[0]); index++)
	{
		DestroyIcon(*icons[index]);
		*icons[index] = NULL;
	}
}