#include "KB65 Autoclicker.h"





void MainPage(bool isVisible)
{
	// Mouse Subpage
	ShowWindow(activateMouseCheckBox, isVisible);

	ShowWindow(mouseTimerFrame, isVisible);
	ShowWindow(mouseEnterHour, isVisible);
	ShowWindow(mouseEnterMinute, isVisible);
	ShowWindow(mouseEnterSecond, isVisible);
	ShowWindow(mouseEnterMilliSecond, isVisible);

	ShowWindow(mouseClickTypeFrame, isVisible);
	ShowWindow(mouseLmB, isVisible);
	ShowWindow(mouseClickType, isVisible);

	ShowWindow(mouseClickRepeatFrame, isVisible);
	ShowWindow(mouseRepeatInfinity, isVisible);
	ShowWindow(mouseRepeatTimes, isVisible);
	ShowWindow(mouseRepeatTimesEntry, isVisible);
	ShowWindow(mouseRepeatTimesSpin, isVisible);
	ShowWindow(mouseCountdown, isVisible);
	ShowWindow(mouseCountdownHour, isVisible);
	ShowWindow(mouseCountdownMinute, isVisible);
	ShowWindow(mouseCountdownSecond, isVisible);

	ShowWindow(mouseHotkeyButton, isVisible);
	ShowWindow(mouseClickStart, isVisible);
	ShowWindow(mouseClickStop, isVisible);


	// Keyboard Subpage
	ShowWindow(activateKeyboardCheckBox, isVisible);

	ShowWindow(keyboardTimerFrame, isVisible);
	ShowWindow(keyboardEnterHour, isVisible);
	ShowWindow(keyboardEnterMinute, isVisible);
	ShowWindow(keyboardEnterSecond, isVisible);
	ShowWindow(keyboardEnterMilliSecond, isVisible);

	ShowWindow(keyboardKeyFrame, isVisible);
	ShowWindow(keyboardSelectedKey, isVisible);
	ShowWindow(keyboardHoldCheckBox, isVisible);

	ShowWindow(keyboardPressRepeatFrame, isVisible);
	ShowWindow(keyboardRepeatInfinity, isVisible);
	ShowWindow(keyboardRepeatTimes, isVisible);
	ShowWindow(keyboardRepeatTimesEntry, isVisible);
	ShowWindow(keyboardRepeatTimesSpin, isVisible);
	ShowWindow(keyboardCountdown, isVisible);
	ShowWindow(keyboardCountdownHour, isVisible);
	ShowWindow(keyboardCountdownMinute, isVisible);
	ShowWindow(keyboardCountdownSecond, isVisible);

	ShowWindow(keyboardHotkeyButton, isVisible);
	ShowWindow(keyboardPressStart, isVisible);
	ShowWindow(keyboardPressStop, isVisible);


	// Other buttons
	ShowWindow(infoButton, isVisible);
	ShowWindow(loadScriptsButton, isVisible);
	ShowWindow(saveScriptsButton, isVisible);
	ShowWindow(settingsButton, isVisible);
}



void SettingsPage(bool isVisible)
{
	ShowWindow(settingsFrame, isVisible);
	ShowWindow(selectThemeFrame, isVisible);
	ShowWindow(themesList, isVisible);
	ShowWindow(randIntervalAndHoldTimeFrame, isVisible);
	ShowWindow(randomIntervalEnter, isVisible);
	ShowWindow(holdTimeEnter, isVisible);
	ShowWindow(alwaysOnTop, isVisible);
	ShowWindow(minimizeOnTray, isVisible);
	ShowWindow(disableTooltips, isVisible);
	ShowWindow(debugHotkeyButton, isVisible);
	ShowWindow(backToMainButton, isVisible);
}



void ShowPage(int page)
{
	switch (page)
	{
		case MAINPAGE:
			MainPage(SHOW);
			SettingsPage(HIDE);
			break;

		case SETTINGSPAGE:
			MainPage(HIDE);
			SettingsPage(SHOW);
			break;
	}
}