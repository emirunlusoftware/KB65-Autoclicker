#include "KB65 Autoclicker.h"





HWND
mouseTimerFrame,
mouseClickTypeFrame,
mouseClickRepeatFrame,
mouseRepeatTimesEntry,
mouseRepeatTimesSpin,
mouseCountdownHour,
mouseCountdownMinute,
mouseCountdownSecond,
mouseEnterHour,
mouseEnterMinute,
mouseEnterSecond,
mouseEnterMilliSecond,

keyboardTimerFrame,
keyboardKeyFrame,
keyboardPressRepeatFrame,
keyboardRepeatTimesEntry,
keyboardRepeatTimesSpin,
keyboardCountdownHour,
keyboardCountdownMinute,
keyboardCountdownSecond,
keyboardEnterHour,
keyboardEnterMinute,
keyboardEnterSecond,
keyboardEnterMilliSecond,

settingsFrame,
selectThemeFrame,
randIntervalAndHoldTimeFrame,
randomIntervalEnter,
holdTimeEnter;


void AutoClickerEntries(HWND hWnd, HINSTANCE hInstance)
{
	mouseTimerFrame = CreateWindowEx(
		0, "BUTTON", "Mouse Timer",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(5), DPIScale(4),
		DPIScale(120), DPIScale(125),
		hWnd, (HMENU)MOUSETIMERFRAME, hInstance, NULL
	);


	mouseEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(10), DPIScale(27),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)MOUSEENTERHOUR, hInstance, NULL
	);
	SendMessage(mouseEnterHour, EM_SETLIMITTEXT, 3, 0);


	mouseEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(10), DPIScale(51),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)MOUSEENTERMINUTE, hInstance, NULL
	);
	SendMessage(mouseEnterMinute, EM_SETLIMITTEXT, 4, 0);


	mouseEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(10), DPIScale(75),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)MOUSEENTERSECOND, hInstance, NULL
	);
	SendMessage(mouseEnterSecond, EM_SETLIMITTEXT, 4, 0);


	mouseEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(10), DPIScale(99),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)MOUSEENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(mouseEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	mouseClickTypeFrame = CreateWindowEx(
		0, "BUTTON", "Clicker Type",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(150), DPIScale(39),
		DPIScale(100), DPIScale(82),
		hWnd, (HMENU)MOUSECLICKTYPEFRAME, hInstance, NULL
	);


	mouseClickRepeatFrame = CreateWindowEx(
		0, "BUTTON", "Click Repeat",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(264), DPIScale(39),
		DPIScale(101), DPIScale(138),
		hWnd, (HMENU)MOUSECLICKREPEATFRAME, hInstance, NULL
	);


	mouseRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(292), DPIScale(92),
		DPIScale(64), DPIScale(20),
		hWnd, (HMENU)MOUSEREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(mouseRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	mouseRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		hWnd, (HMENU)MOUSEREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(mouseRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)mouseRepeatTimesEntry, 0);
	SendMessage(mouseRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));


	mouseCountdownHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(270), DPIScale(147),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNHOUR, hInstance, NULL);
	SendMessage(mouseCountdownHour, EM_SETLIMITTEXT, 2, 0);

	mouseCountdownMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(302), DPIScale(147),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNMINUTE, hInstance, NULL);
	SendMessage(mouseCountdownMinute, EM_SETLIMITTEXT, 2, 0);

	mouseCountdownSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(334), DPIScale(147),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNSECOND, hInstance, NULL);
	SendMessage(mouseCountdownSecond, EM_SETLIMITTEXT, 2, 0);
}



void AutoPresserEntries(HWND hWnd, HINSTANCE hInstance)
{
	keyboardTimerFrame = CreateWindowEx(
		0, "BUTTON", "Keyboard Timer",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(5), DPIScale(186),
		DPIScale(120), DPIScale(125),
		hWnd, (HMENU)KEYBOARDTIMERFRAME, hInstance, NULL
	);


	keyboardEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(10), DPIScale(209),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)KEYBOARDENTERHOUR, hInstance, NULL
	);
	SendMessage(keyboardEnterHour, EM_SETLIMITTEXT, 3, 0);


	keyboardEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(10), DPIScale(233),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)KEYBOARDENTERMINUTE, hInstance, NULL
	);
	SendMessage(keyboardEnterMinute, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(10), DPIScale(257),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)KEYBOARDENTERSECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(10), DPIScale(281),
		DPIScale(44), DPIScale(22),
		hWnd, (HMENU)KEYBOARDENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardKeyFrame = CreateWindowEx(
		0, "BUTTON", "Keyboard Key",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(150), DPIScale(221),
		DPIScale(100), DPIScale(80),
		hWnd, (HMENU)KEYBOARDKEYFRAME, hInstance, NULL
	);


	keyboardPressRepeatFrame = CreateWindowEx(
		0, "BUTTON", "Press Repeat",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPIScale(264), DPIScale(221),
		DPIScale(101), DPIScale(138),
		hWnd, (HMENU)KEYBOARDPRESSREPEATFRAME, hInstance, NULL
	);


	keyboardRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(292), DPIScale(274),
		DPIScale(64), DPIScale(20),
		hWnd, (HMENU)KEYBOARDREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(keyboardRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	keyboardRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE | WS_DISABLED,
		0, 0, 0, 0,
		hWnd, (HMENU)KEYBOARDREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)keyboardRepeatTimesEntry, 0);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));


	keyboardCountdownHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(270), DPIScale(329),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNHOUR, hInstance, NULL);
	SendMessage(keyboardCountdownHour, EM_SETLIMITTEXT, 2, 0);

	keyboardCountdownMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(302), DPIScale(329),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNMINUTE, hInstance, NULL);
	SendMessage(keyboardCountdownMinute, EM_SETLIMITTEXT, 2, 0);

	keyboardCountdownSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(334), DPIScale(329),
		DPIScale(25), DPIScale(21),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNSECOND, hInstance, NULL);
	SendMessage(keyboardCountdownSecond, EM_SETLIMITTEXT, 2, 0);
}



void SettingsEntries(HWND hWnd, HINSTANCE hInstance)
{
	settingsFrame = CreateWindowEx(
		0, "BUTTON", "Settings",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPIScale(75), DPIScale(15 - 6),
		DPIScale(250), DPIScale(293),
		hWnd, (HMENU)SETTINGSFRAME, hInstance, NULL
	);


	selectThemeFrame = CreateWindowEx(
		0, "BUTTON", "Select Theme",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPIScale(120), DPIScale(45 - 6),
		DPIScale(160), DPIScale(56),
		hWnd, (HMENU)THEMESFRAME, hInstance, NULL
	);


	randIntervalAndHoldTimeFrame = CreateWindowEx(
		0, "BUTTON", "Random Interval / Hold Time",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPIScale(120), DPIScale(110 - 6),
		DPIScale(160), DPIScale(54),
		hWnd, (HMENU)RANDINTERVALHOLDTIMEFRAME, hInstance, NULL
	);

	randomIntervalEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP,
		DPIScale(142), DPIScale(125),
		DPIScale(44), DPIScale(21),
		hWnd, (HMENU)RANDOMINTERVALENTER, hInstance, NULL
	);
	SendMessage(randomIntervalEnter, EM_SETLIMITTEXT, 3, 0);

	holdTimeEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP,
		DPIScale(214), DPIScale(125),
		DPIScale(44), DPIScale(21),
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
	AutoPresserEntries(hWnd, hInstance);
	SettingsEntries(hWnd, hInstance);
}