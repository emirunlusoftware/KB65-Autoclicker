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

LRESULT isAlwaysOnTopChecked = 0;



void AutoClickerButtons(HWND hWnd, HINSTANCE hInstance)
{
	hdcCheckBox = GetDC(hWnd);

	GetTextExtentPoint32(
		hdcCheckBox,
		"Activate Mouse ",
		STRLEN_INT("Activate Mouse "),
		&textSize);

	activateMouseCheckBox = CreateWindow(
		"BUTTON", "Activate Mouse",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(140), DPIScale(6),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)ACTIVATEMOUSE, hInstance, NULL
	);
	SendMessage(activateMouseCheckBox, BM_SETCHECK, BST_CHECKED, 0);


	mouseLmB = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(155), DPIScale(59),
		DPIScale(90), DPIScale(30 * 3),
		hWnd, (HMENU)MOUSELMB, hInstance, NULL
	);
	const char* mouseLmBArray[] = {"Left", "Right", "Middle"};
	for (int i = 0; i < (sizeof(mouseLmBArray)/sizeof(mouseLmBArray[0])); ++i)
		SendMessage(mouseLmB, CB_ADDSTRING, 0, (LPARAM)mouseLmBArray[i]);

	SendMessage(mouseLmB, CB_SETCURSEL, 0, 0);


	mouseClickType = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(155), DPIScale(89),
		DPIScale(90), DPIScale(30 * 3),
		hWnd, (HMENU)MOUSECLICKTYPE, hInstance, NULL
	);
	const char* clickTypeArray[] = {"Single (x1)", "Double (x2)", "Hold"};
	for (int i = 0; i < (sizeof(clickTypeArray)/sizeof(clickTypeArray[0])); ++i)
		SendMessage(mouseClickType, CB_ADDSTRING, 0, (LPARAM)clickTypeArray[i]);

	SendMessage(mouseClickType, CB_SETCURSEL, 0, 0);



	mouseRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(272), DPIScale(62),
		DPIScale(60), DPIScale(20),
		hWnd, (HMENU)MOUSEREPEATINFINITY, hInstance, NULL);

	mouseRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(272), DPIScale(92),
		DPIScale(15), DPIScale(20),
		hWnd, (HMENU)MOUSEREPEATTIMES, hInstance, NULL);

	mouseCountdown = CreateWindow(
		"BUTTON", "Countdown",
		BS_AUTORADIOBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(272), DPIScale(122),
		DPIScale(82), DPIScale(20),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(mouseRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	mouseClickStart = CreateWindow(
		"BUTTON", "Start",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(175), DPIScale(133),
		DPIScale(50), DPIScale(22),
		hWnd, (HMENU)MOUSECLICKSTARTBUTTON, hInstance, NULL
	);

	mouseClickStop = CreateWindow(
		"BUTTON", "Stop",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(175), DPIScale(155),
		DPIScale(50), DPIScale(22),
		hWnd, (HMENU)MOUSECLICKSTOPBUTTON, hInstance, NULL
	);

	mouseHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F5",
		BS_CENTER | BS_MULTILINE | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(4), DPIScale(133),
		DPIScale(122), DPIScale(44),
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

	activateKeyboardCheckBox = CreateWindow(
		"BUTTON", "Activate Keyboard",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(140), DPIScale(188),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)ACTIVATEKEYBOARD, hInstance, NULL
	);
	SendMessage(activateKeyboardCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);



	keyboardSelectedKey = (isWindowsNT())
		?
		CreateWindowW(L"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(155), DPIScale(241),
		DPIScale(90), DPIScale(250),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL)
		:
		CreateWindowA("COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(155), DPIScale(241),
		DPIScale(90), DPIScale(250),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL);

	PopulateComboBox(keyboardSelectedKey, GetKeyboardLayout(GetCurrentThreadId()));
	keyboardKey = GetKeyboardKey(keyboardSelectedKey);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Hold",
		STRLEN_INT("Hold  "),
		&textSize);

	keyboardHoldCheckBox = CreateWindow(
		"BUTTON", "Hold",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(176), DPIScale(270),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)KEYBOARDHOLDCHECKBOX, hInstance, NULL
	);



	keyboardRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		BS_AUTORADIOBUTTON | WS_GROUP | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPIScale(272), DPIScale(244),
		DPIScale(60), DPIScale(20),
		hWnd, (HMENU)KEYBOARDREPEATINFINITY, hInstance, NULL);

	keyboardRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPIScale(272), DPIScale(274),
		DPIScale(15), DPIScale(20),
		hWnd, (HMENU)KEYBOARDREPEATTIMES, hInstance, NULL);

	keyboardCountdown = CreateWindow(
		"BUTTON", "Countdown",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_DISABLED,
		DPIScale(272), DPIScale(304),
		DPIScale(82), DPIScale(20),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(keyboardRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	keyboardPressStart = CreateWindow(
		"BUTTON", "Start",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(175), DPIScale(315),
		DPIScale(50), DPIScale(22),
		hWnd, (HMENU)KEYBOARDPRESSSTARTBUTTON, hInstance, NULL
	);

	keyboardPressStop = CreateWindow(
		"BUTTON", "Stop",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_DISABLED,
		DPIScale(175), DPIScale(337),
		DPIScale(50), DPIScale(22),
		hWnd, (HMENU)KEYBOARDPRESSSTOPBUTTON, hInstance, NULL
	);

	keyboardHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F6",
		BS_CENTER | BS_MULTILINE | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(4), DPIScale(315),
		DPIScale(122), DPIScale(44),
		hWnd, (HMENU)KEYBOARDPRESSHOTKEYBUTTON, hInstance, NULL
	);
}



void SettingsButtons(HWND hWnd, HINSTANCE hInstance)
{
	infoButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(373), DPIScale(254),
		DPIScale(24), DPIScale(24),
		hWnd, (HMENU)INFOBUTTON, hInstance, NULL
	);
	HICON infoIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_INFO), IMAGE_ICON, DPIScale(24), DPIScale(24), LR_CREATEDIBSECTION);
	SendMessage(infoButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)infoIcon);


	loadScriptsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(373), DPIScale(281),
		DPIScale(24), DPIScale(24),
		hWnd, (HMENU)LOADSCRIPTSBUTTON, hInstance, NULL
	);
	HICON loadScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOADSCRIPT), IMAGE_ICON, DPIScale(18), DPIScale(18), LR_CREATEDIBSECTION);
	SendMessage(loadScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)loadScriptsIcon);


	saveScriptsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(373), DPIScale(308),
		DPIScale(24), DPIScale(24),
		hWnd, (HMENU)SAVESCRIPTSBUTTON, hInstance, NULL
	);
	HICON saveScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SAVESCRIPT), IMAGE_ICON, DPIScale(18), DPIScale(18), LR_CREATEDIBSECTION);
	SendMessage(saveScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)saveScriptsIcon);


	settingsButton = CreateWindow(
		"BUTTON", 0,
		BS_ICON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		DPIScale(373), DPIScale(335),
		DPIScale(24), DPIScale(24),
		hWnd, (HMENU)SETTINGSBUTTON, hInstance, NULL
	);
	HICON settingsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SETTINGS), IMAGE_ICON, DPIScale(16), DPIScale(16), LR_CREATEDIBSECTION);
	SendMessage(settingsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)settingsIcon);



	themesList = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_HSCROLL | WS_CHILD | WS_TABSTOP,
		DPIScale(132), DPIScale(59),
		DPIScale(136), DPIScale(25 * 8),
		hWnd, (HMENU)THEMESLISTCOMBOBOX, hInstance, NULL
	);

	const char* themes[] = {
	"Default", "Burlywood", "Gold", "Gray",
	"Magic Flower", "Rocket", "Soccer Pitch", "Oceanic"
};
	for (int i = 0; i < sizeof(themes)/sizeof(themes[0]); i++)
		SendMessage(themesList, CB_ADDSTRING, 0, (LPARAM)themes[i]);
	SendMessage(themesList, CB_SETCURSEL, 0, 0);



	GetTextExtentPoint32(
		hdcCheckBox,
		"Always on Top",
		STRLEN_INT("Always on Top"),
		&textSize);

	alwaysOnTop = CreateWindow(
		"BUTTON", "Always on Top",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPIScale(120), DPIScale(165),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)ALWAYSONTOP, hInstance, NULL
	);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Minimize on System Tray",
		STRLEN_INT("Minimize on System Tray"),
		&textSize);

	minimizeOnTray = CreateWindow(
		"BUTTON", "Minimize on System Tray",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPIScale(120), DPIScale(190),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)MINIMIZEONTRAY, hInstance, NULL
	);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Disable tooltips",
		STRLEN_INT("Disable tooltips"),
		&textSize);

	disableTooltips = CreateWindow(
		"BUTTON", "Disable tooltips",
		BS_AUTOCHECKBOX | WS_CHILD | WS_TABSTOP,
		DPIScale(120), DPIScale(215),
		DPIScale(textSize.cx), DPIScale(22),
		hWnd, (HMENU)DISABLETOOLTIPS, hInstance, NULL
	);


	debugHotkeyButton = CreateWindow(
		"BUTTON", "Find HEX keycode",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP,
		DPIScale(119), DPIScale(247),
		DPIScale(162), DPIScale(44),
		hWnd, (HMENU)DEBUGHOTKEYBUTTON, hInstance, NULL
	);


	backToMainButton = CreateWindow(
		"BUTTON", "Back",
		BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP,
		DPIScale(175), DPIScale(315),
		DPIScale(50), DPIScale(44),
		hWnd, (HMENU)BACKTOMAINBUTTON, hInstance, NULL
	);

	DeleteObject(hdcCheckBox);
}



void LoadingButtons(HWND hWnd, HINSTANCE hInstance)
{
	AutoClickerButtons(hWnd, hInstance);
	AutoPresserButtons(hWnd, hInstance);
	SettingsButtons(hWnd, hInstance);
}