#include "KB65 Autoclicker.h"





HWND tooltipWindow = NULL;
TOOLINFO infoWnd = {0};
LRESULT isDisableTooltipsChecked = 0;

void LoadingTooltips(HWND hWnd);
void AddToolTip(HWND hWnd, HWND window, int mode);
void Tooltips(HWND hWnd, int mode);



void LoadingTooltips(HWND hWnd)
{
	tooltipWindow = CreateWindowEx(
		WS_EX_TOPMOST, TOOLTIPS_CLASS,
		NULL, TTS_NOPREFIX,
		0, 0, 0, 0,
		hWnd, NULL, GetModuleHandle(NULL), NULL);

	Tooltips(hWnd, SHOW);
}



void AddToolTip(HWND hWnd, HWND window, int mode)
{
	if (mode == SHOW)
	{
		infoWnd.cbSize = sizeof(TOOLINFO);
		infoWnd.hinst = GetModuleHandle(NULL);
		infoWnd.hwnd = hWnd;
		infoWnd.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
		infoWnd.uId = (UINT_PTR)window;
		SendMessage(tooltipWindow, TTM_SETMAXTIPWIDTH, 0, 275);

		if (window == mouseLmB)
			infoWnd.lpszText = "Select a mouse button: Left, Right or Middle";
		else if (window == mouseClickType)
			infoWnd.lpszText = "Select a clicking type: Single/Double click or just hold.";
		else if (window == keyboardHoldCheckBox)
			infoWnd.lpszText = "Activates the hold mode that presses and keeps the key held down. It is equivalent of Mouse Hold Mode.";
		else if (window == mouseHotkeyButton || window == keyboardHotkeyButton)
			infoWnd.lpszText = "Choose a hotkey to start the automation with a specific key.";
		else if (window == mouseRepeatInfinity || window == keyboardRepeatInfinity)
			infoWnd.lpszText = "Infinity: Repeat until you stop.";
		else if (window == mouseRepeatTimes || window == keyboardRepeatTimes)
			infoWnd.lpszText = "Times: Determines how many times it repeat.";
		else if (window == mouseRepeatTimesEntry || window == keyboardRepeatTimesEntry)
			infoWnd.lpszText = "Enter a number to determine how many times the automation will repeat.\nThe maximum allowed value is 65535.";
		else if (window == mouseCountdown || window == keyboardCountdown)
			infoWnd.lpszText = "Countdown: Sets a countdown timer; the process stops when the timer is up.";
		else if (window == infoButton)
			infoWnd.lpszText = "Read the Web Manual";
		else if (window == loadScriptsButton)
			infoWnd.lpszText = "Load hotkeys";
		else if (window == saveScriptsButton)
			infoWnd.lpszText = "Save hotkeys as .ini file";
		else if (window == settingsButton)
			infoWnd.lpszText = "Settings";
		else if (window == alwaysOnTop)
			infoWnd.lpszText = "Pins the active window above all other windows, so the window stays on top even when you select other windows.";
		else if (window == minimizeOnTray)
			infoWnd.lpszText = "Minimizes the program to the system tray instead of the taskbar when you clicked on \"Minimize\" button.";
		else if (window == disableTooltips)
			infoWnd.lpszText = "Hides the info pop-up currently being shown, along with any other info pop-ups.";
		else if (window == randomIntervalEnter)
			infoWnd.lpszText = "Adds a random delay to make automation more natural.";
		else if (window == holdTimeEnter)
			infoWnd.lpszText = "Sets a time that how long the button is held before it’s released.";
		else if (window == debugHotkeyButton)
			infoWnd.lpszText = "Shows the hexadecimal number of the button you pressed (just for nerds).";

		GetClientRect(window, &infoWnd.rect);
		SendMessage(tooltipWindow, TTM_ADDTOOL, 0, (LPARAM)&infoWnd);
	}
	else if (mode == HIDE)
	{
		infoWnd.cbSize = sizeof(TOOLINFO);
		infoWnd.hwnd = hWnd;
		infoWnd.uFlags = TTF_IDISHWND;
		infoWnd.uId = (UINT_PTR)window;
		SendMessage(tooltipWindow, TTM_DELTOOL, 0, (LPARAM)&infoWnd);
	}
}



void Tooltips(HWND hWnd, int mode)
{
	AddToolTip(hWnd, mouseLmB, mode);
	AddToolTip(hWnd, mouseClickType, mode);
	AddToolTip(hWnd, mouseHotkeyButton, mode);
	AddToolTip(hWnd, mouseRepeatInfinity, mode);
	AddToolTip(hWnd, mouseRepeatTimes, mode);
	AddToolTip(hWnd, mouseRepeatTimesEntry, mode);
	AddToolTip(hWnd, mouseCountdown, mode);

	AddToolTip(hWnd, keyboardHoldCheckBox, mode);
	AddToolTip(hWnd, keyboardHotkeyButton, mode);
	AddToolTip(hWnd, keyboardRepeatInfinity, mode);
	AddToolTip(hWnd, keyboardRepeatTimes, mode);
	AddToolTip(hWnd, keyboardRepeatTimesEntry, mode);
	AddToolTip(hWnd, keyboardCountdown, mode);

	AddToolTip(hWnd, infoButton, mode);
	AddToolTip(hWnd, loadScriptsButton, mode);
	AddToolTip(hWnd, saveScriptsButton, mode);
	AddToolTip(hWnd, settingsButton, mode);

	AddToolTip(hWnd, minimizeOnTray, mode);
	AddToolTip(hWnd, alwaysOnTop, mode);
	AddToolTip(hWnd, randomIntervalEnter, mode);
	AddToolTip(hWnd, holdTimeEnter, mode);
	AddToolTip(hWnd, debugHotkeyButton, mode);
	AddToolTip(hWnd, disableTooltips, mode);
}