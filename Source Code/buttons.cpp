#include "KB65 Autoclicker.h"





HDC hdcCheckBox;
SIZE textSize;


HWND
activateMouseCheckBox,
mouseLmB,
mouseClickType,
mouseRepeatInfinity,
mouseRepeatTimes,
mouseCountdown,
mouseClickStart,
mouseClickStop,
mouseHotkeyButton,

activateKeyboardCheckBox,
keyboardSelectedKey,
keyboardHoldCheckBox,
keyboardRepeatInfinity,
keyboardRepeatTimes,
keyboardCountdown,
keyboardPressStart,
keyboardPressStop,
keyboardHotkeyButton,

infoButton,
loadScriptsButton,
saveScriptsButton,
settingsButton,

themesList,
alwaysOnTop,
minimizeOnTray,
disableTooltips,
debugHotkeyButton,
backToMainButton;

ButtonsInfo buttonsInfo[28] =
{
	{140, 6, 0, 22, &activateMouseCheckBox},
	{155, 59, 90, 25 * 3, &mouseLmB},
	{155, 89, 90, 25 * 3, &mouseClickType},
	{272, 62, 60, 20, &mouseRepeatInfinity},
	{272, 92, 15, 20, &mouseRepeatTimes},
	{272, 122, 82, 20, &mouseCountdown},
	{175, 133, 50, 22, &mouseClickStart},
	{175, 155, 50, 22, &mouseClickStop},
	{4, 133, 122, 44, &mouseHotkeyButton},

	{140, 188, 0, 22, &activateKeyboardCheckBox},
	{155, 241, 90, 250, &keyboardSelectedKey},
	{176, 270, 0, 22, &keyboardHoldCheckBox},
	{272, 244, 60, 20, &keyboardRepeatInfinity},
	{272, 274, 15, 20, &keyboardRepeatTimes},
	{272, 304, 82, 20, &keyboardCountdown},
	{175, 315, 50, 22, &keyboardPressStart},
	{175, 337, 50, 22, &keyboardPressStop},
	{4, 315, 122, 44, &keyboardHotkeyButton},

	{373, 254, 24, 24, &infoButton},
	{373, 281, 24, 24, &loadScriptsButton},
	{373, 308, 24, 24, &saveScriptsButton},
	{373, 335, 24, 24, &settingsButton},

	{132, 59, 136, 25 * 8, &themesList},
	{120, 165, 0, 22, &alwaysOnTop},
	{120, 190, 0, 22, &minimizeOnTray},
	{120, 215, 0, 22, &disableTooltips},
	{119, 247, 162, 44, &debugHotkeyButton},
	{175, 315, 50, 44, &backToMainButton}
};

const size_t buttonsInfoSize = sizeof(buttonsInfo)/sizeof(buttonsInfo[0]);
LRESULT isAlwaysOnTopChecked = 0;



void AutoClickerButtons(HWND hWnd, HINSTANCE hInstance)
{
	hdcCheckBox = GetDC(hWnd);

	GetTextExtentPoint32(
		hdcCheckBox,
		"Activate Mouse ",
		STRLEN_INT("Activate Mouse "),
		&textSize);
	buttonsInfo[0].w = textSize.cx;

	activateMouseCheckBox = CreateWindow(
		"BUTTON", "Activate Mouse",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[0].x), DPI::Scale(buttonsInfo[0].y),
		DPI::Scale(buttonsInfo[0].w), DPI::Scale(buttonsInfo[0].h),
		hWnd, (HMENU)ACTIVATEMOUSE, hInstance, NULL
	);
	SendMessage(activateMouseCheckBox, BM_SETCHECK, BST_CHECKED, 0);


	mouseLmB = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[1].x), DPI::Scale(buttonsInfo[1].y),
		DPI::Scale(buttonsInfo[1].w), DPI::Scale(buttonsInfo[1].h),
		hWnd, (HMENU)MOUSELMB, hInstance, NULL
	);
	const char* mouseLmBArray[] = {"Left", "Right", "Middle"};
	for (size_t i = 0; i < (sizeof(mouseLmBArray)/sizeof(mouseLmBArray[0])); ++i)
		SendMessage(mouseLmB, CB_ADDSTRING, 0, (LPARAM)mouseLmBArray[i]);

	SendMessage(mouseLmB, CB_SETCURSEL, 0, 0);


	mouseClickType = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[2].x), DPI::Scale(buttonsInfo[2].y),
		DPI::Scale(buttonsInfo[2].w), DPI::Scale(buttonsInfo[2].h),
		hWnd, (HMENU)MOUSECLICKTYPE, hInstance, NULL
	);
	const char* clickTypeArray[] = {"Single (x1)", "Double (x2)", "Hold"};
	for (size_t i = 0; i < (sizeof(clickTypeArray)/sizeof(clickTypeArray[0])); ++i)
		SendMessage(mouseClickType, CB_ADDSTRING, 0, (LPARAM)clickTypeArray[i]);

	SendMessage(mouseClickType, CB_SETCURSEL, 0, 0);



	mouseRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[3].x), DPI::Scale(buttonsInfo[3].y),
		DPI::Scale(buttonsInfo[3].w), DPI::Scale(buttonsInfo[3].h),
		hWnd, (HMENU)MOUSEREPEATINFINITY, hInstance, NULL);

	mouseRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[4].x), DPI::Scale(buttonsInfo[4].y),
		DPI::Scale(buttonsInfo[4].w), DPI::Scale(buttonsInfo[4].h),
		hWnd, (HMENU)MOUSEREPEATTIMES, hInstance, NULL);

	mouseCountdown = CreateWindow(
		"BUTTON", "Countdown",
		BS_AUTORADIOBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[5].x), DPI::Scale(buttonsInfo[5].y),
		DPI::Scale(buttonsInfo[5].w), DPI::Scale(buttonsInfo[5].h),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(mouseRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	mouseClickStart = CreateWindow(
		"BUTTON", "Start",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[6].x), DPI::Scale(buttonsInfo[6].y),
		DPI::Scale(buttonsInfo[6].w), DPI::Scale(buttonsInfo[6].h),
		hWnd, (HMENU)MOUSECLICKSTARTBUTTON, hInstance, NULL
	);

	mouseClickStop = CreateWindow(
		"BUTTON", "Stop",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[7].x), DPI::Scale(buttonsInfo[7].y),
		DPI::Scale(buttonsInfo[7].w), DPI::Scale(buttonsInfo[7].h),
		hWnd, (HMENU)MOUSECLICKSTOPBUTTON, hInstance, NULL
	);

	mouseHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F5",
		BS_CENTER | BS_MULTILINE | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[8].x), DPI::Scale(buttonsInfo[8].y),
		DPI::Scale(buttonsInfo[8].w), DPI::Scale(buttonsInfo[8].h),
		hWnd, (HMENU)MOUSECLICKHOTKEYBUTTON, hInstance, NULL
	);
}



void AutoPresserButtons(HWND hWnd, HINSTANCE hInstance)
{
	GetTextExtentPoint32(
		hdcCheckBox,
		"Activate Keyboard ",
		STRLEN_INT("Activate Keyboard "),
		&textSize);
	buttonsInfo[9].w = textSize.cx;

	activateKeyboardCheckBox = CreateWindow(
		"BUTTON", "Activate Keyboard",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[9].x), DPI::Scale(buttonsInfo[9].y),
		DPI::Scale(buttonsInfo[9].w), DPI::Scale(buttonsInfo[9].h),
		hWnd, (HMENU)ACTIVATEKEYBOARD, hInstance, NULL
	);
	SendMessage(activateKeyboardCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);



	keyboardSelectedKey = (isWindowsNT())
		?
		CreateWindowW(L"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[10].x), DPI::Scale(buttonsInfo[10].y),
		DPI::Scale(buttonsInfo[10].w), DPI::Scale(buttonsInfo[10].h),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL)
		:
		CreateWindowA("COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[10].x), DPI::Scale(buttonsInfo[10].y),
		DPI::Scale(buttonsInfo[10].w), DPI::Scale(buttonsInfo[10].h),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL);

	PopulateComboBox(keyboardSelectedKey, GetKeyboardLayout(GetCurrentThreadId()));
	keyboardKey = GetKeyboardKey(keyboardSelectedKey);
	SendMessage(keyboardSelectedKey, CB_SETMINVISIBLE, 15, 0);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Hold",
		STRLEN_INT("Hold  "),
		&textSize);
	buttonsInfo[11].w = textSize.cx;

	keyboardHoldCheckBox = CreateWindow(
		"BUTTON", "Hold",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[11].x), DPI::Scale(buttonsInfo[11].y),
		DPI::Scale(buttonsInfo[11].w), DPI::Scale(buttonsInfo[11].h),
		hWnd, (HMENU)KEYBOARDHOLDCHECKBOX, hInstance, NULL
	);



	keyboardRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		BS_AUTORADIOBUTTON | WS_GROUP | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPI::Scale(buttonsInfo[12].x), DPI::Scale(buttonsInfo[12].y),
		DPI::Scale(buttonsInfo[12].w), DPI::Scale(buttonsInfo[12].h),
		hWnd, (HMENU)KEYBOARDREPEATINFINITY, hInstance, NULL);

	keyboardRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPI::Scale(buttonsInfo[13].x), DPI::Scale(buttonsInfo[13].y),
		DPI::Scale(buttonsInfo[13].w), DPI::Scale(buttonsInfo[13].h),
		hWnd, (HMENU)KEYBOARDREPEATTIMES, hInstance, NULL);

	keyboardCountdown = CreateWindow(
		"BUTTON", "Countdown",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPI::Scale(buttonsInfo[14].x), DPI::Scale(buttonsInfo[14].y),
		DPI::Scale(buttonsInfo[14].w), DPI::Scale(buttonsInfo[14].h),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(keyboardRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	keyboardPressStart = CreateWindow(
		"BUTTON", "Start",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[15].x), DPI::Scale(buttonsInfo[15].y),
		DPI::Scale(buttonsInfo[15].w), DPI::Scale(buttonsInfo[15].h),
		hWnd, (HMENU)KEYBOARDPRESSSTARTBUTTON, hInstance, NULL
	);

	keyboardPressStop = CreateWindow(
		"BUTTON", "Stop",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPI::Scale(buttonsInfo[16].x), DPI::Scale(buttonsInfo[16].y),
		DPI::Scale(buttonsInfo[16].w), DPI::Scale(buttonsInfo[16].h),
		hWnd, (HMENU)KEYBOARDPRESSSTOPBUTTON, hInstance, NULL
	);

	keyboardHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F6",
		BS_CENTER | BS_MULTILINE | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[17].x), DPI::Scale(buttonsInfo[17].y),
		DPI::Scale(buttonsInfo[17].w), DPI::Scale(buttonsInfo[17].h),
		hWnd, (HMENU)KEYBOARDPRESSHOTKEYBUTTON, hInstance, NULL
	);
}



void SettingsButtons(HWND hWnd, HINSTANCE hInstance)
{
	infoButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[18].x), DPI::Scale(buttonsInfo[18].y),
		DPI::Scale(buttonsInfo[18].w), DPI::Scale(buttonsInfo[18].h),
		hWnd, (HMENU)INFOBUTTON, hInstance, NULL
	);

	loadScriptsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[19].x), DPI::Scale(buttonsInfo[19].y),
		DPI::Scale(buttonsInfo[19].w), DPI::Scale(buttonsInfo[19].h),
		hWnd, (HMENU)LOADSCRIPTSBUTTON, hInstance, NULL
	);

	saveScriptsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[20].x), DPI::Scale(buttonsInfo[20].y),
		DPI::Scale(buttonsInfo[20].w), DPI::Scale(buttonsInfo[20].h),
		hWnd, (HMENU)SAVESCRIPTSBUTTON, hInstance, NULL
	);

	settingsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPI::Scale(buttonsInfo[21].x), DPI::Scale(buttonsInfo[21].y),
		DPI::Scale(buttonsInfo[21].w), DPI::Scale(buttonsInfo[21].h),
		hWnd, (HMENU)SETTINGSBUTTON, hInstance, NULL
	);

	themesList = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_HSCROLL | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[22].x), DPI::Scale(buttonsInfo[22].y),
		DPI::Scale(buttonsInfo[22].w), DPI::Scale(buttonsInfo[22].h),
		hWnd, (HMENU)THEMESLISTCOMBOBOX, hInstance, NULL
	);

	const char* themes[] = {
	"Default", "Burlywood", "Gold", "Gray",
	"Magic Flower", "Rocket", "Soccer Pitch", "Oceanic"
	};
	for (size_t i = 0; i < sizeof(themes)/sizeof(themes[0]); ++i)
		SendMessage(themesList, CB_ADDSTRING, 0, (LPARAM)themes[i]);
	SendMessage(themesList, CB_SETCURSEL, 0, 0);



	GetTextExtentPoint32(
		hdcCheckBox,
		"Always on Top",
		STRLEN_INT("Always on Top"),
		&textSize);
	buttonsInfo[23].w = textSize.cx;

	alwaysOnTop = CreateWindow(
		"BUTTON", "Always on Top",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[23].x), DPI::Scale(buttonsInfo[23].y),
		DPI::Scale(buttonsInfo[23].w), DPI::Scale(buttonsInfo[23].h),
		hWnd, (HMENU)ALWAYSONTOP, hInstance, NULL
	);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Minimize on System Tray",
		STRLEN_INT("Minimize on System Tray"),
		&textSize);
	buttonsInfo[24].w = textSize.cx;

	minimizeOnTray = CreateWindow(
		"BUTTON", "Minimize on System Tray",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[24].x), DPI::Scale(buttonsInfo[24].y),
		DPI::Scale(buttonsInfo[24].w), DPI::Scale(buttonsInfo[24].h),
		hWnd, (HMENU)MINIMIZEONTRAY, hInstance, NULL
	);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Disable tooltips",
		STRLEN_INT("Disable tooltips"),
		&textSize);
	buttonsInfo[25].w = textSize.cx;

	disableTooltips = CreateWindow(
		"BUTTON", "Disable tooltips",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[25].x), DPI::Scale(buttonsInfo[25].y),
		DPI::Scale(buttonsInfo[25].w), DPI::Scale(buttonsInfo[25].h),
		hWnd, (HMENU)DISABLETOOLTIPS, hInstance, NULL
	);


	debugHotkeyButton = CreateWindow(
		"BUTTON", "Find HEX keycode",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[26].x), DPI::Scale(buttonsInfo[26].y),
		DPI::Scale(buttonsInfo[26].w), DPI::Scale(buttonsInfo[26].h),
		hWnd, (HMENU)DEBUGHOTKEYBUTTON, hInstance, NULL
	);


	backToMainButton = CreateWindow(
		"BUTTON", "Back",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP,
		DPI::Scale(buttonsInfo[27].x), DPI::Scale(buttonsInfo[27].y),
		DPI::Scale(buttonsInfo[27].w), DPI::Scale(buttonsInfo[27].h),
		hWnd, (HMENU)BACKTOMAINBUTTON, hInstance, NULL
	);

	DeleteObject(hdcCheckBox);
}



void LoadButtons(HWND hWnd, HINSTANCE hInstance)
{
	AutoClickerButtons(hWnd, hInstance);
	AutoPresserButtons(hWnd, hInstance);
	SettingsButtons(hWnd, hInstance);
}