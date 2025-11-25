#include "KB65 Autoclicker.h"





HICON soccerBallImage, anchorImage, rocketImage, flowerImage;
HICON* icons[4] = {&soccerBallImage, &anchorImage, &rocketImage, &flowerImage};
void LoadingImages()
{
	for (int iconId = IDI_SOCCER, index = 0; iconId <= IDI_FLOWER; iconId++, index++)
	{
		*icons[index] = (HICON)LoadImage(
		GetModuleHandle(NULL),
		MAKEINTRESOURCE(iconId),
		IMAGE_ICON,
		DPIScale(24), DPIScale(24),
		LR_CREATEDIBSECTION);
	}
}



void GetImages(HDC hdc, int themeOption)
{
	switch(themeOption)
	{
		case THEMEMAGIC:
			DrawIconEx(
				hdc,
				DPIScale(373),
				DPIScale(10),
				flowerImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMEROCKET:
			DrawIconEx(
				hdc,
				DPIScale(373),
				DPIScale(10),
				rocketImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMESOCCER:
			DrawIconEx(
				hdc,
				DPIScale(373),
				DPIScale(10),
				soccerBallImage,
				0, 0, 0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMEOCEANIC:
			DrawIconEx(
				hdc,
				DPIScale(373),
				DPIScale(10),
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
	for (int index = 0; index < sizeof(icons)/sizeof(icons[0]); index++)
		DestroyIcon(*icons[index]);
}