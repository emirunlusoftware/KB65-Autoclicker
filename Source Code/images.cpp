#include "main.h"





HICON soccerBall, anchorImage;
void LoadingImages()
{
	soccerBall = (HICON)LoadImage(
		GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_SOCCER),
		IMAGE_ICON,
		24.0 * DPIScale(), 24.0 * DPIScale(),
		LR_CREATEDIBSECTION);

	anchorImage = (HICON)LoadImage(
		GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_ANCHOR),
		IMAGE_ICON,
		24.0 * DPIScale(), 24.0 * DPIScale(),
		LR_CREATEDIBSECTION);
}



void GetImages(HDC hdc, int themeOption)
{
	switch(themeOption)
	{
		case THEMESOCCER:
			DrawIconEx(
				hdc,
				373.0 * DPIScale(),
				10.0 * DPIScale(),
				soccerBall,
				0, 0,
				0,
				NULL,
				DI_NORMAL
			);
			break;

		case THEMEOCEANIC:
			DrawIconEx(
				hdc,
				373.0 * DPIScale(),
				10.0 * DPIScale(),
				anchorImage,
				0, 0,
				0,
				NULL,
				DI_NORMAL
			);
			break;
	}
}