#include "main.h"
#include <commctrl.h>





HDC hdcCheckBox;
SIZE textSize;


HWND
activateMouseCheckBox,
mouseLmB,
mouseSingleOrDouble,
mouseRepeatInfinity,
mouseRepeatTimes,
mouseRepeatTimer,
mouseClickStart,
mouseClickStop,
mouseHotkeyButton,

activateKeyboardCheckBox,
keyboardSelectedKey,
keyboardRepeatInfinity,
keyboardRepeatTimes,
keyboardRepeatTimer,
keyboardPressStart,
keyboardPressStop,
keyboardHotkeyButton,

infoButton,
loadScriptsButton,
saveScriptsButton,
settingsButton,

themesList,
minimizeOnTray,
alwaysOnTop,
debugHotkeyButton,
backToMainButton,

tooltipWindow;

LRESULT isAlwaysOnTopChecked;


void ButtonToolTip(HWND hWnd, HWND button);



void AutoClickerButtons(HWND hWnd, HINSTANCE hInstance)
{
	hdcCheckBox = GetDC(hWnd);

	GetTextExtentPoint32(
		hdcCheckBox,
		"Activate Mouse ",
		static_cast<int>(_tcslen("Activate Mouse ")),
		&textSize);

	activateMouseCheckBox = CreateWindow(
		"BUTTON", "Activate Mouse",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_AUTOCHECKBOX,
		140.0 * DPIScale(), 6.0 * DPIScale(),
		textSize.cx * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)ACTIVATEMOUSE, hInstance, NULL
	);
	SendMessage(activateMouseCheckBox, BM_SETCHECK, BST_CHECKED, 0);


	mouseLmB = CreateWindow(
		"COMBOBOX", NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL,
		155.0 * DPIScale(), 65.0 * DPIScale(),
		90.0 * DPIScale(), 3.0 * 30.0 * DPIScale(),
		hWnd, (HMENU)MOUSELMB, hInstance, NULL
	);
	SendMessage(mouseLmB, CB_ADDSTRING, 0, (LPARAM)"Left");
	SendMessage(mouseLmB, CB_ADDSTRING, 0, (LPARAM)"Middle");
	SendMessage(mouseLmB, CB_ADDSTRING, 0, (LPARAM)"Right");
	SendMessage(mouseLmB, CB_SETCURSEL, 0, 0);


	mouseSingleOrDouble = CreateWindow(
		"COMBOBOX", NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL,
		155.0 * DPIScale(), 95.0 * DPIScale(),
		90.0 * DPIScale(), 3.0 * 30.0 * DPIScale(),
		hWnd, (HMENU)MOUSESINGLEORDOUBLE, hInstance, NULL
	);
	SendMessage(mouseSingleOrDouble, CB_ADDSTRING, 0, (LPARAM)"Single (x1)");
	SendMessage(mouseSingleOrDouble, CB_ADDSTRING, 0, (LPARAM)"Double (x2)");
	SendMessage(mouseSingleOrDouble, CB_ADDSTRING, 0, (LPARAM)"Xtra (x16)");
	SendMessage(mouseSingleOrDouble, CB_SETCURSEL, 0, 0);



	mouseRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		WS_GROUP | BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		272.0 * DPIScale(), 62.0 * DPIScale(),
		60.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATINFINITY, hInstance, NULL);

	mouseRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		272.0 * DPIScale(), 92.0 * DPIScale(),
		15.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATTIMES, hInstance, NULL);

	mouseRepeatTimer = CreateWindow(
		"BUTTON", "Countdown",
		BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		272.0 * DPIScale(), 122.0 * DPIScale(),
		82.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)MOUSEREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(mouseRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	mouseClickStart = CreateWindow(
		"BUTTON", "Start",
		BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		175.0 * DPIScale(), 133.0 * DPIScale(),
		50.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKSTARTBUTTON, hInstance, NULL
	);

	mouseClickStop = CreateWindow(
		"BUTTON", "Stop",
		BS_PUSHBUTTON | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		175.0 * DPIScale(), 155.0 * DPIScale(),
		50.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKSTOPBUTTON, hInstance, NULL
	);

	mouseHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F5",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_CENTER | BS_MULTILINE,
		4.0 * DPIScale(), 133.0 * DPIScale(),
		122.0 * DPIScale(), 44.0 * DPIScale(),
		hWnd, (HMENU)MOUSECLICKHOTKEYBUTTON, hInstance, NULL
	);
}



void KeyboardPresserButtons(HWND hWnd, HINSTANCE hInstance)
{
	GetTextExtentPoint32(
		hdcCheckBox,
		"Activate Keyboard ",
		static_cast<int>(_tcslen("Activate Keyboard ")),
		&textSize);

	activateKeyboardCheckBox = CreateWindow(
		"BUTTON", "Activate Keyboard",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_AUTOCHECKBOX,
		140.0 * DPIScale(), 188.0 * DPIScale(),
		textSize.cx * DPIScale(), 22.0 * DPIScale(),
		hWnd, (HMENU)ACTIVATEKEYBOARD, hInstance, NULL
	);
	SendMessage(activateKeyboardCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);



	keyboardSelectedKey = (isWindowsNT())
		?
		CreateWindowW(
		L"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_VSCROLL,
		155.0 * DPIScale(), 247.0 * DPIScale(),
		90.0 * DPIScale(), 250.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL)
		:
		CreateWindowA(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_VSCROLL,
		155.0 * DPIScale(), 247.0 * DPIScale(),
		90.0 * DPIScale(), 250.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDSELECTAUTOMATEDKEY, hInstance, NULL);

	PopulateComboBox(keyboardSelectedKey, GetKeyboardLayout(GetCurrentThreadId()));
	keyboardKey = GetKeyboardKey(keyboardSelectedKey);



	keyboardRepeatInfinity = CreateWindow(
		"BUTTON", "Infinity",
		BS_AUTORADIOBUTTON | WS_DISABLED | WS_VISIBLE | WS_CHILD | WS_GROUP,
		272.0 * DPIScale(), 244.0 * DPIScale(),
		60.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATINFINITY, hInstance, NULL);

	keyboardRepeatTimes = CreateWindow(
		"BUTTON", "",
		BS_AUTORADIOBUTTON | WS_DISABLED | WS_VISIBLE | WS_CHILD,
		272.0 * DPIScale(), 274.0 * DPIScale(),
		15.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATTIMES, hInstance, NULL);

	keyboardRepeatTimer = CreateWindow(
		"BUTTON", "Countdown",
		WS_DISABLED | BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD,
		272.0 * DPIScale(), 304.0 * DPIScale(),
		82.0 * DPIScale(), 20.0 * DPIScale(),
		hWnd, (HMENU)KEYBOARDREPEATCOUNTDOWN, hInstance, NULL);

	SendMessage(keyboardRepeatInfinity, BM_SETCHECK, BST_CHECKED, 0);



	keyboardPressStart = CreateWindow(
		"BUTTON", "Start",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON,
		175.0 * DPIScale(), 315.0 * DPIScale(),
		50.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd,
		(HMENU)KEYBOARDPRESSSTARTBUTTON,
		hInstance,
		NULL
	);

	keyboardPressStop = CreateWindow(
		"BUTTON", "Stop",
		WS_DISABLED | WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON,
		175.0 * DPIScale(), 337.0 * DPIScale(),
		50.0 * DPIScale(), 22.0 * DPIScale(),
		hWnd,
		(HMENU)KEYBOARDPRESSSTOPBUTTON,
		hInstance,
		NULL
	);

	keyboardHotkeyButton = CreateWindow(
		"BUTTON", "Hotkey: F6",
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_CENTER | BS_MULTILINE,
		4.0 * DPIScale(), 315.0 * DPIScale(),
		122.0 * DPIScale(), 44.0 * DPIScale(),
		hWnd,
		(HMENU)KEYBOARDPRESSHOTKEYBUTTON,
		hInstance,
		NULL
	);
}



void SettingsButtons(HWND hWnd, HINSTANCE hInstance)
{
	infoButton = CreateWindow(
		"BUTTON", 0,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_ICON,
		373.0 * DPIScale(), 253.0 * DPIScale(),
		24.0 * DPIScale(), 24.0 * DPIScale(),
		hWnd,
		(HMENU)INFOBUTTON,
		hInstance,
		NULL
	);
	ButtonToolTip(hWnd, infoButton);
	HICON infoIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_INFO), IMAGE_ICON, 24.0 * DPIScale(), 24.0 * DPIScale(), LR_CREATEDIBSECTION);
	SendMessage(infoButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)infoIcon);


	loadScriptsButton = CreateWindow(
		"BUTTON", 0,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_ICON,
		373.0 * DPIScale(), 280.0 * DPIScale(),
		24.0 * DPIScale(), 24.0 * DPIScale(),
		hWnd,
		(HMENU)LOADSCRIPTSBUTTON,
		hInstance,
		NULL
	);
	ButtonToolTip(hWnd, loadScriptsButton);
	HICON loadScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOADSCRIPT), IMAGE_ICON, 18.0 * DPIScale(), 18.0 * DPIScale(), LR_CREATEDIBSECTION);
	SendMessage(loadScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)loadScriptsIcon);


	saveScriptsButton = CreateWindow(
		"BUTTON", 0,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_ICON,
		373.0 * DPIScale(), 307.0 * DPIScale(),
		24.0 * DPIScale(), 24.0 * DPIScale(),
		hWnd,
		(HMENU)SAVESCRIPTSBUTTON,
		hInstance,
		NULL
	);
	ButtonToolTip(hWnd, saveScriptsButton);
	HICON saveScriptsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SAVESCRIPT), IMAGE_ICON, 18.0 * DPIScale(), 18.0 * DPIScale(), LR_CREATEDIBSECTION);
	SendMessage(saveScriptsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)saveScriptsIcon);


	settingsButton = CreateWindow(
		"BUTTON", 0,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_ICON,
		373.0 * DPIScale(), 334.0 * DPIScale(),
		24.0 * DPIScale(), 24.0 * DPIScale(),
		hWnd,
		(HMENU)SETTINGSBUTTON,
		hInstance,
		NULL
	);
	ButtonToolTip(hWnd, settingsButton);
	HICON settingsIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SETTINGS), IMAGE_ICON, 16.0 * DPIScale(), 16.0 * DPIScale(), LR_CREATEDIBSECTION);
	SendMessage(settingsButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)settingsIcon);



	themesList = CreateWindow(
		"COMBOBOX", NULL,
		CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_HSCROLL | WS_TABSTOP | WS_CHILD,
		132.0 * DPIScale(), 82.0 * DPIScale(),
		136.0 * DPIScale(), 5.0 * 25.0 * DPIScale(),
		hWnd, (HMENU)THEMESLISTCOMBOBOX, hInstance, NULL
	);

	const TCHAR* themes[] =
	{
		"Default", "Burlywood", "Gray", "Soccer Pitch", "Oceanic",
	};

	for (int i = 0; i < (sizeof(themes)/sizeof(themes[0])); ++i)
		SendMessage(themesList, CB_ADDSTRING, 0, (LPARAM)themes[i]);
	SendMessage(themesList, CB_SETCURSEL, 0, 0);



	GetTextExtentPoint32(
		hdcCheckBox,
		"Minimize on System Tray",
		static_cast<int>(_tcslen("Minimize on System Tray")),
		&textSize);

	minimizeOnTray = CreateWindow(
		"BUTTON", "Minimize on System Tray",
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD,
		120.0 * DPIScale(), 130.0 * DPIScale(),
		textSize.cx * DPIScale(), 22.0 * DPIScale(),
		hWnd,
		(HMENU)MINIMIZEONTRAY,
		hInstance,
		NULL
	);


	GetTextExtentPoint32(
		hdcCheckBox,
		"Always on Top",
		static_cast<int>(_tcslen("Always on Top")),
		&textSize);

	alwaysOnTop = CreateWindow(
		"BUTTON", "Always on Top",
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD,
		120.0 * DPIScale(), 160.0 * DPIScale(),
		textSize.cx * DPIScale(), 22.0 * DPIScale(),
		hWnd,
		(HMENU)ALWAYSONTOP,
		hInstance,
		NULL
	);


	debugHotkeyButton = CreateWindow(
		"BUTTON", "Find HEX keycode",
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD,
		120.0 * DPIScale(), 200.0 * DPIScale(),
		160.0 * DPIScale(), 50.0 * DPIScale(),
		hWnd,
		(HMENU)DEBUGHOTKEYBUTTON,
		hInstance,
		NULL
	);


	backToMainButton = CreateWindow(
		"BUTTON", "Back",
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD,
		175.0 * DPIScale(), 315.0 * DPIScale(),
		50.0 * DPIScale(), 44.0 * DPIScale(),
		hWnd,
		(HMENU)BACKTOMAINBUTTON,
		hInstance,
		NULL
	);
}



void LoadingButtons(HWND hWnd, HINSTANCE hInstance)
{
	AutoClickerButtons(hWnd, hInstance);
	KeyboardPresserButtons(hWnd, hInstance);
	SettingsButtons(hWnd, hInstance);
}



void ButtonToolTip(HWND hWnd, HWND button)
{
	tooltipWindow = CreateWindowEx(
		WS_EX_TOPMOST, TOOLTIPS_CLASS,
		NULL, TTS_NOPREFIX,
		0, 0, 0, 0,
		hWnd, NULL, NULL, NULL);

	TOOLINFO infoWnd;
	infoWnd.cbSize = sizeof(TOOLINFO);
	infoWnd.hinst = GetModuleHandle(NULL);
	infoWnd.hwnd = button;
	infoWnd.uFlags = TTF_SUBCLASS;
	infoWnd.uId = (UINT_PTR)button;
	infoWnd.lpszText =
	(
		(button == infoButton)
		? "Read the Web Manual"
		: (button == loadScriptsButton)
		? "Load hotkeys"
		: (button == saveScriptsButton)
		? "Save hotkeys as .ini file"
		: "Settings"
	);

	GetClientRect(button, &infoWnd.rect);
	SendMessage(tooltipWindow, TTM_ADDTOOL, 0, (LPARAM)&infoWnd);
}