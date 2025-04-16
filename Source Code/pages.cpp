#include "main.h"





void MainPage(bool isVisible)
{
	// Mouse Subpage
	ShowWindow(activateMouseCheckBox, isVisible);

	ShowWindow(mouseClickTimer, isVisible);
	ShowWindow(mouseEnterHour, isVisible);
	ShowWindow(mouseEnterMinute, isVisible);
	ShowWindow(mouseEnterSecond, isVisible);
	ShowWindow(mouseEnterMilliSecond, isVisible);

	ShowWindow(mouseClickType, isVisible);
	ShowWindow(mouseLmB, isVisible);
	ShowWindow(mouseSingleOrDouble, isVisible);

	ShowWindow(mouseClickRepeat, isVisible);
	ShowWindow(mouseRepeatInfinity, isVisible);
	ShowWindow(mouseRepeatTimes, isVisible);
	ShowWindow(mouseRepeatTimesEntry, isVisible);
	ShowWindow(mouseRepeatTimesSpin, isVisible);
	ShowWindow(mouseRepeatTimer, isVisible);
	ShowWindow(mouseRepeatTimerHour, isVisible);
	ShowWindow(mouseRepeatTimerMinute, isVisible);
	ShowWindow(mouseRepeatTimerSecond, isVisible);

	ShowWindow(mouseHotkeyButton, isVisible);
	ShowWindow(mouseClickStart, isVisible);
	ShowWindow(mouseClickStop, isVisible);


	// Keyboard Subpage
	ShowWindow(activateKeyboardCheckBox, isVisible);

	ShowWindow(keyboardPressTimer, isVisible);
	ShowWindow(keyboardEnterHour, isVisible);
	ShowWindow(keyboardEnterMinute, isVisible);
	ShowWindow(keyboardEnterSecond, isVisible);
	ShowWindow(keyboardEnterMilliSecond, isVisible);

	ShowWindow(keyboardSelectKey, isVisible);
	ShowWindow(keyboardSelectedKey, isVisible);

	ShowWindow(keyboardPressRepeat, isVisible);
	ShowWindow(keyboardRepeatInfinity, isVisible);
	ShowWindow(keyboardRepeatTimes, isVisible);
	ShowWindow(keyboardRepeatTimesEntry, isVisible);
	ShowWindow(keyboardRepeatTimesSpin, isVisible);
	ShowWindow(keyboardRepeatTimer, isVisible);
	ShowWindow(keyboardRepeatTimerHour, isVisible);
	ShowWindow(keyboardRepeatTimerMinute, isVisible);
	ShowWindow(keyboardRepeatTimerSecond, isVisible);

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
	ShowWindow(themeSelect, isVisible);
	ShowWindow(themesList, isVisible);
	ShowWindow(minimizeOnTray, isVisible);
	ShowWindow(alwaysOnTop, isVisible);
	ShowWindow(debugHotkeyButton, isVisible);
	ShowWindow(backToMainButton, isVisible);
}



void ShowPages(int page)
{
	switch (page)
	{
		case MAINPAGE:
			SettingsPage(HIDE);
			MainPage(SHOW);
			break;

		case SETTINGSPAGE:
			MainPage(HIDE);
			SettingsPage(SHOW);
			break;
	}
}