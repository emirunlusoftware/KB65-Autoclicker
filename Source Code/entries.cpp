#include "KB65 Autoclicker.h"





HWND
mouseTimerFrame,
mouseEnterHour,
mouseEnterMinute,
mouseEnterSecond,
mouseEnterMilliSecond,
mouseClickTypeFrame,
mouseClickRepeatFrame,
mouseRepeatTimesEntry,
mouseRepeatTimesSpin,
mouseCountdownHour,
mouseCountdownMinute,
mouseCountdownSecond,


keyboardTimerFrame,
keyboardEnterHour,
keyboardEnterMinute,
keyboardEnterSecond,
keyboardEnterMilliSecond,
keyboardKeyFrame,
keyboardPressRepeatFrame,
keyboardRepeatTimesEntry,
keyboardRepeatTimesSpin,
keyboardCountdownHour,
keyboardCountdownMinute,
keyboardCountdownSecond,


settingsFrame,
selectThemeFrame,
randIntervalAndHoldTimeFrame,
randomIntervalEnter,
holdTimeEnter;

EntriesInfo entriesInfo[] =
{
	{5, 4, 120, 125, &mouseTimerFrame},
	{10, 27, 44, 22, &mouseEnterHour},
	{10, 51, 44, 22, &mouseEnterMinute},
	{10, 75, 44, 22, &mouseEnterSecond},
	{10, 99, 44, 22, &mouseEnterMilliSecond},
	{150, 39, 100, 82, &mouseClickTypeFrame},
	{264, 39, 101, 138, &mouseClickRepeatFrame},
	{292, 92, 64, 20, &mouseRepeatTimesEntry},
	{292, 92, 64, 20, &mouseRepeatTimesSpin},
	{270, 147, 25, 21, &mouseCountdownHour},
	{302, 147, 25, 21, &mouseCountdownMinute},
	{334, 147, 25, 21, &mouseCountdownSecond},

	{5, 186, 120, 125, &keyboardTimerFrame},
	{10, 209, 44, 22, &keyboardEnterHour},
	{10, 233, 44, 22, &keyboardEnterMinute},
	{10, 257, 44, 22, &keyboardEnterSecond},
	{10, 281, 44, 22, &keyboardEnterMilliSecond},
	{150, 221, 100, 80, &keyboardKeyFrame},
	{264, 221, 101, 138, &keyboardPressRepeatFrame},
	{292, 274, 64, 20, &keyboardRepeatTimesEntry},
	{292, 274, 64, 20, &keyboardRepeatTimesSpin},
	{270, 329, 25, 21, &keyboardCountdownHour},
	{302, 329, 25, 21, &keyboardCountdownMinute},
	{334, 329, 25, 21, &keyboardCountdownSecond},

	{75, 9, 250, 293, &settingsFrame},
	{120, 39, 160, 56, &selectThemeFrame},
	{120, 104, 160, 54, &randIntervalAndHoldTimeFrame},
	{142, 125, 44, 21, &randomIntervalEnter},
	{214, 125, 44, 21, &holdTimeEnter}
};

const size_t entriesInfoSize = sizeof(entriesInfo)/sizeof(entriesInfo[0]);



void AutoClickerEntries(HWND hWnd, HINSTANCE hInstance)
{
	mouseTimerFrame = CreateWindowEx(
		0, "BUTTON", "Mouse Timer",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[0].x), DPI::Scale(entriesInfo[0].y),
		DPI::Scale(entriesInfo[0].w), DPI::Scale(entriesInfo[0].h),
		hWnd, (HMENU)MOUSETIMERFRAME, hInstance, NULL
	);


	mouseEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[1].x), DPI::Scale(entriesInfo[1].y),
		DPI::Scale(entriesInfo[1].w), DPI::Scale(entriesInfo[1].h),
		hWnd, (HMENU)MOUSEENTERHOUR, hInstance, NULL
	);
	SendMessage(mouseEnterHour, EM_SETLIMITTEXT, 3, 0);


	mouseEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[2].x), DPI::Scale(entriesInfo[2].y),
		DPI::Scale(entriesInfo[2].w), DPI::Scale(entriesInfo[2].h),
		hWnd, (HMENU)MOUSEENTERMINUTE, hInstance, NULL
	);
	SendMessage(mouseEnterMinute, EM_SETLIMITTEXT, 4, 0);


	mouseEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[3].x), DPI::Scale(entriesInfo[3].y),
		DPI::Scale(entriesInfo[3].w), DPI::Scale(entriesInfo[3].h),
		hWnd, (HMENU)MOUSEENTERSECOND, hInstance, NULL
	);
	SendMessage(mouseEnterSecond, EM_SETLIMITTEXT, 4, 0);


	mouseEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[4].x), DPI::Scale(entriesInfo[4].y),
		DPI::Scale(entriesInfo[4].w), DPI::Scale(entriesInfo[4].h),
		hWnd, (HMENU)MOUSEENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(mouseEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	mouseClickTypeFrame = CreateWindowEx(
		0, "BUTTON", "Clicker Type",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[5].x), DPI::Scale(entriesInfo[5].y),
		DPI::Scale(entriesInfo[5].w), DPI::Scale(entriesInfo[5].h),
		hWnd, (HMENU)MOUSECLICKTYPEFRAME, hInstance, NULL
	);


	mouseClickRepeatFrame = CreateWindowEx(
		0, "BUTTON", "Click Repeat",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[6].x), DPI::Scale(entriesInfo[6].y),
		DPI::Scale(entriesInfo[6].w), DPI::Scale(entriesInfo[6].h),
		hWnd, (HMENU)MOUSECLICKREPEATFRAME, hInstance, NULL
	);


	mouseRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[7].x), DPI::Scale(entriesInfo[7].y),
		DPI::Scale(entriesInfo[7].w), DPI::Scale(entriesInfo[7].h),
		hWnd, (HMENU)MOUSEREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(mouseRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	mouseRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[8].x), DPI::Scale(entriesInfo[8].y),
		DPI::Scale(entriesInfo[8].w), DPI::Scale(entriesInfo[8].h),
		hWnd, (HMENU)MOUSEREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(mouseRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)mouseRepeatTimesEntry, 0);
	SendMessage(mouseRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));


	mouseCountdownHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[9].x), DPI::Scale(entriesInfo[9].y),
		DPI::Scale(entriesInfo[9].w), DPI::Scale(entriesInfo[9].h),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNHOUR, hInstance, NULL);
	SendMessage(mouseCountdownHour, EM_SETLIMITTEXT, 2, 0);

	mouseCountdownMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[10].x), DPI::Scale(entriesInfo[10].y),
		DPI::Scale(entriesInfo[10].w), DPI::Scale(entriesInfo[10].h),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNMINUTE, hInstance, NULL);
	SendMessage(mouseCountdownMinute, EM_SETLIMITTEXT, 2, 0);

	mouseCountdownSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(entriesInfo[11].x), DPI::Scale(entriesInfo[11].y),
		DPI::Scale(entriesInfo[11].w), DPI::Scale(entriesInfo[11].h),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWNSECOND, hInstance, NULL);
	SendMessage(mouseCountdownSecond, EM_SETLIMITTEXT, 2, 0);
}



void AutoPresserEntries(HWND hWnd, HINSTANCE hInstance)
{
	keyboardTimerFrame = CreateWindowEx(
		0, "BUTTON", "Keyboard Timer",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[12].x), DPI::Scale(entriesInfo[12].y),
		DPI::Scale(entriesInfo[12].w), DPI::Scale(entriesInfo[12].h),
		hWnd, (HMENU)KEYBOARDTIMERFRAME, hInstance, NULL
	);


	keyboardEnterHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[13].x), DPI::Scale(entriesInfo[13].y),
		DPI::Scale(entriesInfo[13].w), DPI::Scale(entriesInfo[13].h),
		hWnd, (HMENU)KEYBOARDENTERHOUR, hInstance, NULL
	);
	SendMessage(keyboardEnterHour, EM_SETLIMITTEXT, 3, 0);


	keyboardEnterMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[14].x), DPI::Scale(entriesInfo[14].y),
		DPI::Scale(entriesInfo[14].w), DPI::Scale(entriesInfo[14].h),
		hWnd, (HMENU)KEYBOARDENTERMINUTE, hInstance, NULL
	);
	SendMessage(keyboardEnterMinute, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "1",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[15].x), DPI::Scale(entriesInfo[15].y),
		DPI::Scale(entriesInfo[15].w), DPI::Scale(entriesInfo[15].h),
		hWnd, (HMENU)KEYBOARDENTERSECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardEnterMilliSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "0",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[16].x), DPI::Scale(entriesInfo[16].y),
		DPI::Scale(entriesInfo[16].w), DPI::Scale(entriesInfo[16].h),
		hWnd, (HMENU)KEYBOARDENTERMILLISECOND, hInstance, NULL
	);
	SendMessage(keyboardEnterMilliSecond, EM_SETLIMITTEXT, 4, 0);


	keyboardKeyFrame = CreateWindowEx(
		0, "BUTTON", "Keyboard Key",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[17].x), DPI::Scale(entriesInfo[17].y),
		DPI::Scale(entriesInfo[17].w), DPI::Scale(entriesInfo[17].h),
		hWnd, (HMENU)KEYBOARDKEYFRAME, hInstance, NULL
	);


	keyboardPressRepeatFrame = CreateWindowEx(
		0, "BUTTON", "Press Repeat",
		BS_GROUPBOX | BS_CENTER | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[18].x), DPI::Scale(entriesInfo[18].y),
		DPI::Scale(entriesInfo[18].w), DPI::Scale(entriesInfo[18].h),
		hWnd, (HMENU)KEYBOARDPRESSREPEATFRAME, hInstance, NULL
	);


	keyboardRepeatTimesEntry = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "5",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[19].x), DPI::Scale(entriesInfo[19].y),
		DPI::Scale(entriesInfo[19].w), DPI::Scale(entriesInfo[19].h),
		hWnd, (HMENU)KEYBOARDREPEATTIMESENTRY, hInstance, NULL);
	SendMessage(keyboardRepeatTimesEntry, EM_SETLIMITTEXT, 5, 0);

	keyboardRepeatTimesSpin = CreateWindow(UPDOWN_CLASS, NULL,
		UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE,
		DPI::Scale(entriesInfo[20].x), DPI::Scale(entriesInfo[20].y),
		DPI::Scale(entriesInfo[20].w), DPI::Scale(entriesInfo[20].h),
		hWnd, (HMENU)KEYBOARDREPEATTIMESSPIN, hInstance, NULL);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETBUDDY, (WPARAM)keyboardRepeatTimesEntry, 0);
	SendMessage(keyboardRepeatTimesSpin, UDM_SETRANGE32, 0, MAKELPARAM(65535, 0));
	EnableWindow(keyboardRepeatTimesSpin, SW_HIDE);


	keyboardCountdownHour = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[21].x), DPI::Scale(entriesInfo[21].y),
		DPI::Scale(entriesInfo[21].w), DPI::Scale(entriesInfo[21].h),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNHOUR, hInstance, NULL);
	SendMessage(keyboardCountdownHour, EM_SETLIMITTEXT, 2, 0);

	keyboardCountdownMinute = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "00",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[22].x), DPI::Scale(entriesInfo[22].y),
		DPI::Scale(entriesInfo[22].w), DPI::Scale(entriesInfo[22].h),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNMINUTE, hInstance, NULL);
	SendMessage(keyboardCountdownMinute, EM_SETLIMITTEXT, 2, 0);

	keyboardCountdownSecond = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", "05",
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(entriesInfo[23].x), DPI::Scale(entriesInfo[23].y),
		DPI::Scale(entriesInfo[23].w), DPI::Scale(entriesInfo[23].h),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWNSECOND, hInstance, NULL);
	SendMessage(keyboardCountdownSecond, EM_SETLIMITTEXT, 2, 0);
}



void SettingsEntries(HWND hWnd, HINSTANCE hInstance)
{
	settingsFrame = CreateWindowEx(
		0, "BUTTON", "Settings",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPI::Scale(entriesInfo[24].x), DPI::Scale(entriesInfo[24].y),
		DPI::Scale(entriesInfo[24].w), DPI::Scale(entriesInfo[24].h),
		hWnd, (HMENU)SETTINGSFRAME, hInstance, NULL
	);


	selectThemeFrame = CreateWindowEx(
		0, "BUTTON", "Select Theme",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPI::Scale(entriesInfo[25].x), DPI::Scale(entriesInfo[25].y),
		DPI::Scale(entriesInfo[25].w), DPI::Scale(entriesInfo[25].h),
		hWnd, (HMENU)THEMESFRAME, hInstance, NULL
	);


	randIntervalAndHoldTimeFrame = CreateWindowEx(
		0, "BUTTON", "Random Interval / Hold Time",
		BS_GROUPBOX | BS_CENTER | WS_CHILD,
		DPI::Scale(entriesInfo[26].x), DPI::Scale(entriesInfo[26].y),
		DPI::Scale(entriesInfo[26].w), DPI::Scale(entriesInfo[26].h),
		hWnd, (HMENU)RANDINTERVALHOLDTIMEFRAME, hInstance, NULL
	);

	randomIntervalEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP,
		DPI::Scale(entriesInfo[27].x), DPI::Scale(entriesInfo[27].y),
		DPI::Scale(entriesInfo[27].w), DPI::Scale(entriesInfo[27].h),
		hWnd, (HMENU)RANDOMINTERVALENTER, hInstance, NULL
	);
	SendMessage(randomIntervalEnter, EM_SETLIMITTEXT, 3, 0);

	holdTimeEnter = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT", 0,
		ES_NUMBER | ES_CENTER | WS_CHILD | WS_TABSTOP,
		DPI::Scale(entriesInfo[28].x), DPI::Scale(entriesInfo[28].y),
		DPI::Scale(entriesInfo[28].w), DPI::Scale(entriesInfo[28].h),
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



void LoadEntries(HWND hWnd, HINSTANCE hInstance)
{
	AutoClickerEntries(hWnd, hInstance);
	AutoPresserEntries(hWnd, hInstance);
	SettingsEntries(hWnd, hInstance);
}