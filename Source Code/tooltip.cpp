#include "KB65 Autoclicker.h"





HWND tooltipWindow = NULL;
TOOLINFO infoWnd = {0};
LRESULT isDisableTooltipsChecked = 0;

void LoadTooltips(HWND hWnd);
void ToolTipMode(HWND hWnd, HWND window, int mode);
void Tooltips(HWND hWnd, int mode);



void LoadTooltips(HWND hWnd)
{
	tooltipWindow = CreateWindowEx(
		WS_EX_TOPMOST, TOOLTIPS_CLASS,
		NULL, TTS_NOPREFIX,
		0, 0, 0, 0,
		hWnd, NULL, GetModuleHandle(NULL), NULL);

	Tooltips(hWnd, SHOW);
}



void ToolTipMode(HWND hWnd, HWND window, int mode)
{
	switch(mode)
	{
		case SHOW:
		{
			infoWnd.cbSize = sizeof(TOOLINFO);
			infoWnd.hinst = GetModuleHandle(NULL);
			infoWnd.hwnd = hWnd;
			infoWnd.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
			infoWnd.uId = (UINT_PTR)window;
			SendMessage(tooltipWindow, TTM_SETMAXTIPWIDTH, 0, DPI::Scale(275));

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
				infoWnd.lpszText = "Go to the official KB65 Autoclicker GitHub website";
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
				infoWnd.lpszText = "Shows the hexadecimal virtual code of the key you pressed (just for nerds).";

			GetClientRect(window, &infoWnd.rect);
			SendMessage(tooltipWindow, TTM_ADDTOOL, 0, (LPARAM)&infoWnd);
			SendMessage(tooltipWindow, TTM_SETDELAYTIME, TTDT_AUTOPOP, 16000);
			SendMessage(tooltipWindow, WM_SETFONT, (WPARAM)tooltipFont, true);

			break;
		}
		case HIDE:
		{
			infoWnd.cbSize = sizeof(TOOLINFO);
			infoWnd.hwnd = hWnd;
			infoWnd.uFlags = TTF_IDISHWND;
			infoWnd.uId = (UINT_PTR)window;
			SendMessage(tooltipWindow, TTM_DELTOOL, 0, (LPARAM)&infoWnd);

			break;
		}
	}
}



void Tooltips(HWND hWnd, int mode)
{
	ToolTipMode(hWnd, mouseLmB, mode);
	ToolTipMode(hWnd, mouseClickType, mode);
	ToolTipMode(hWnd, mouseHotkeyButton, mode);
	ToolTipMode(hWnd, mouseRepeatInfinity, mode);
	ToolTipMode(hWnd, mouseRepeatTimes, mode);
	ToolTipMode(hWnd, mouseRepeatTimesEntry, mode);
	ToolTipMode(hWnd, mouseCountdown, mode);

	ToolTipMode(hWnd, keyboardHoldCheckBox, mode);
	ToolTipMode(hWnd, keyboardHotkeyButton, mode);
	ToolTipMode(hWnd, keyboardRepeatInfinity, mode);
	ToolTipMode(hWnd, keyboardRepeatTimes, mode);
	ToolTipMode(hWnd, keyboardRepeatTimesEntry, mode);
	ToolTipMode(hWnd, keyboardCountdown, mode);

	ToolTipMode(hWnd, infoButton, mode);
	ToolTipMode(hWnd, loadScriptsButton, mode);
	ToolTipMode(hWnd, saveScriptsButton, mode);
	ToolTipMode(hWnd, settingsButton, mode);

	ToolTipMode(hWnd, minimizeOnTray, mode);
	ToolTipMode(hWnd, alwaysOnTop, mode);
	ToolTipMode(hWnd, randomIntervalEnter, mode);
	ToolTipMode(hWnd, holdTimeEnter, mode);
	ToolTipMode(hWnd, debugHotkeyButton, mode);
	ToolTipMode(hWnd, disableTooltips, mode);
}