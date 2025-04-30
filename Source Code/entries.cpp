#include "main.h"
#include <commctrl.h>





HWND
mouseClickTimer,
mouseClickType,
mouseClickRepeat,
mouseRepeatTimesEntry,
mouseRepeatTimesSpin,
mouseRepeatTimerHour,
mouseRepeatTimerMinute,
mouseRepeatTimerSecond,
mouseEnterHour,
mouseEnterMinute,
mouseEnterSecond,
mouseEnterMilliSecond,

keyboardPressTimer,
keyboardPressRepeat,
keyboardRepeatTimesEntry,
keyboardRepeatTimesSpin,
keyboardRepeatTimerHour,
keyboardRepeatTimerMinute,
keyboardRepeatTimerSecond,
keyboardEnterHour,
keyboardEnterMinute,
keyboardEnterSecond,
keyboardEnterMilliSecond,
keyboardSelectKey,

settingsFrame,
themeSelect,
randIntervalAndHoldTimeFrame,
randomIntervalEnter,
holdTimeEnter;


void AutoClickerEntries(HWND hWnd, HINSTANCE hInstance)
{
	mouseClickTimer = CreateWindowEx(
		0, "BUTTON", "Mouse Timer",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		5.0 * DPIScale(), 4.0 * DPIScale(),
		120.0 * DPIScale(), 125.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKTIMER, hInstance, NULL
	);


	mouseEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 27.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSEENTERHOUR, hInstance, NULL
	);
	SendMessage(mouseEnterHour, EM_SETLIMITTEXT, 3, 0);


	mouseEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 51.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSEENTERMINUTE, hInstance, NULL
	);
	SendMessage(mouseEnterMinute, EM_SETLIMITTEXT, 4, 0);


	mouseEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 75.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSEENTERSECOND, hInstance, NULL
	);
	SendMessage(mouseEnterSecond, EM_SETLIMITTEXT, 4, 0);


	mouseEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 99.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSEENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(mouseEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	mouseClickType = CreateWindowEx(
		0, "BUTTON", "Clicker Type",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		150.0 * DPIScale(), 45.0 * DPIScale(),
		100.0 * DPIScale(), 82.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKTYPE, hInstance, NULL
	);


	mouseClickRepeat = CreateWindowEx(
		0, "BUTTON", "Click Repeat",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		264.0 * DPIScale(), 39.0 * DPIScale(),
		101.0 * DPIScale(), 138.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKREPEAT, hInstance, NULL
	);


	mouseRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		WS_VISIBLE | WS_TABSTOP |  WS_CHILD | ES_NUMBER | ES_CENTER,
		292.0 * DPIScale(), 92.0 * DPIScale(),
		64.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(mouseRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	mouseRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		WS_VISIBLE | WS_CHILD | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT,
		0, 0, 0, 0,
		hWnd, (HMENU)MOUSEREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(mouseRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)mouseRepeatTimesEntry, 0);
	SendMessage(mouseRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));


	mouseRepeatTimerHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		270.0 * DPIScale(), 147.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATTIMERHOUR, hInstance, NULL);
	SendMessage(mouseRepeatTimerHour, EM_SETLIMITTEXT, 2, 0);

	mouseRepeatTimerMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		302.0 * DPIScale(), 147.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATTIMERMINUTE, hInstance, NULL);
	SendMessage(mouseRepeatTimerMinute, EM_SETLIMITTEXT, 2, 0);

	mouseRepeatTimerSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		334.0 * DPIScale(), 147.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATTIMERSECOND, hInstance, NULL);
	SendMessage(mouseRepeatTimerSecond, EM_SETLIMITTEXT, 2, 0);
}



void KeyboardPresserEntries(HWND hWnd, HINSTANCE hInstance)
{
	keyboardPressTimer = CreateWindowEx(
		0, "BUTTON", "Keyboard Timer",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		5.0 * DPIScale(), 186.0 * DPIScale(),
		120.0 * DPIScale(), 125.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDPRESSTIMER, hInstance, NULL
	);


	keyboardEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 209.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDENTERHOUR, hInstance, NULL
	);
	SendMessage(keyboardEnterHour, EM_SETLIMITTEXT, 3, 0);


	keyboardEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 233.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDENTERMINUTE, hInstance, NULL
	);
	SendMessage(keyboardEnterMinute, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 257.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDENTERSECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		10.0 * DPIScale(), 281.0 * DPIScale(),
		44.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardSelectKey = CreateWindowEx(
		0, "BUTTON", "Keyboard Key",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		150.0 * DPIScale(), 227.0 * DPIScale(),
		100.0 * DPIScale(), 52.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDSELECTKEY, hInstance, NULL
	);


	keyboardPressRepeat = CreateWindowEx(
		0, "BUTTON", "Press Repeat",
		BS_GROUPBOX | BS_CENTER | WS_VISIBLE | WS_CHILD,
		264.0 * DPIScale(), 221.0 * DPIScale(),
		101.0 * DPIScale(), 138.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDPRESSREPEAT, hInstance, NULL
	);


	keyboardRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		ES_NUMBER | ES_CENTER | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD ,
		292.0 * DPIScale(), 274.0 * DPIScale(),
		64.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(keyboardRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	keyboardRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		0, 0, 0, 0,
		hWnd, (HMENU)KEYBOARDREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)keyboardRepeatTimesEntry, 0);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));


	keyboardRepeatTimerHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		270.0 * DPIScale(), 329.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATTIMERHOUR, hInstance, NULL);
	SendMessage(keyboardRepeatTimerHour, EM_SETLIMITTEXT, 2, 0);

	keyboardRepeatTimerMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		302.0 * DPIScale(), 329.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATTIMERMINUTE, hInstance, NULL);
	SendMessage(keyboardRepeatTimerMinute, EM_SETLIMITTEXT, 2, 0);

	keyboardRepeatTimerSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		ES_NUMBER | ES_CENTER | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		334.0 * DPIScale(), 329.0 * DPIScale(),
		25.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATTIMERSECOND, hInstance, NULL);
	SendMessage(keyboardRepeatTimerSecond, EM_SETLIMITTEXT, 2, 0);
}



void SettingsEntries(HWND hWnd, HINSTANCE hInstance)
{
	settingsFrame = CreateWindowEx(
		0, "BUTTON", "Settings",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		75.0 * DPIScale(), (15.0 - 6.0) * DPIScale(),
		250.0 * DPIScale(), 293.0 * DPIScale(),
		hWnd, (HMENU)SETTINGSFRAME, hInstance, NULL
	);


	themeSelect = CreateWindowEx(
		0, "BUTTON", "Select Theme",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		120.0 * DPIScale(), (45.0 - 6.0) * DPIScale(),
		160.0 * DPIScale(), 56.0 * DPIScale(),
		hWnd, (HMENU)THEMEGROUPBOX, hInstance, NULL
	);


	randIntervalAndHoldTimeFrame = CreateWindowEx(
		0, "BUTTON", "Random Interval / Hold Time",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		120.0 * DPIScale(), (170.0 - 6.0) * DPIScale(),
		160.0 * DPIScale(), 54.0 * DPIScale(),
		hWnd, (HMENU)RANDINTERVALHOLDTIMEFRAME, hInstance, NULL
	);

	randomIntervalEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		142.0 * DPIScale(), 185.0 * DPIScale(),
		44.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)RANDOMINTERVALENTER, hInstance, NULL
	);
	SendMessage(randomIntervalEnter, EM_SETLIMITTEXT, 3, 0);

	holdTimeEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		WS_TABSTOP | WS_CHILD | ES_NUMBER | ES_CENTER,
		214.0 * DPIScale(), 185.0 * DPIScale(),
		44.0 * DPIScale(), 21.0 * DPIScale(),
		hWnd, (HMENU)HOLDTIMEENTER, hInstance, NULL
	);
	SendMessage(holdTimeEnter, EM_SETLIMITTEXT, 3, 0);

	if (isWindowsXPLater())
	{
		SendMessage(randomIntervalEnter, EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"±ms");
		SendMessage(holdTimeEnter, EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"ms");
	}
	else
	{
		SetWindowText(randomIntervalEnter, "0");
		SetWindowText(holdTimeEnter, "0");
	}

}



void LoadingEntries(HWND hWnd, HINSTANCE hInstance)
{
	AutoClickerEntries(hWnd, hInstance);
	KeyboardPresserEntries(hWnd, hInstance);
	SettingsEntries(hWnd, hInstance);
}