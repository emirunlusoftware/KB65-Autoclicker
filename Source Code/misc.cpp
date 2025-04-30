#include "main.h"
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>





int idNumber;
HWND hWndGet;
LONG_PTR hotkeyButtonStyle, debugButtonStyle;


float DPIScale()
{
	HDC DPIhdc = GetDC(NULL);
	int dpi = GetDeviceCaps(DPIhdc, LOGPIXELSX);
	ReleaseDC(NULL, DPIhdc);

	return (dpi / 96.0f);
}



bool isWindowsNT()
{
	// • true [Windows NT (2000/XP/Vista etc.)]
	// • false [Windows 98/ME]
	return !(winver.dwMajorVersion == 4 && winver.dwMinorVersion >= 10);
}



bool isWindowsXPLater()
{
	// Settings like EM_SETCUEBANNER aren't supported on Windows 2000
    return (winver.dwMajorVersion >= 5 && winver.dwMinorVersion >= 1);
}



void ActiveAppearance(HWND hWnd, int modType, bool isEnabled, int specParam)
{
	for (idNumber = (modType == AUTOCLICKER ? MOUSECLICKTIMER : KEYBOARDPRESSTIMER);
		idNumber < (modType == AUTOCLICKER ? MOUSECLICKHOTKEYBUTTON: KEYBOARDPRESSHOTKEYBUTTON);
		++idNumber)
	{
		hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, isEnabled);
	}

	EnableWindow(modType == AUTOCLICKER ? mouseClickStart : keyboardPressStart, isEnabled);
	EnableWindow(modType == AUTOCLICKER ? mouseClickStop : keyboardPressStop, isEnabled);
	EnableWindow(mouseHotkeyButton, specParam ? HIDE : SHOW);
	EnableWindow(keyboardHotkeyButton, specParam ? HIDE : SHOW);
	if (modType == AUTOCLICKER)
	{
		EnableWindow(mouseClickStart, isEnabled);
		EnableWindow(mouseClickStop, HIDE);
	}
	else
	{
		EnableWindow(keyboardPressStart, isEnabled);
		EnableWindow(keyboardPressStop, HIDE);
	}
}



void HotkeySelectionAppearance(HWND hWnd, int mouseActive, int keyboardActive, bool isEnabled)
{
	EnableWindow(activateMouseCheckBox, isEnabled);
	EnableWindow(loadScriptsButton, isEnabled);
	EnableWindow(saveScriptsButton, isEnabled);
	for (idNumber = MOUSECLICKTIMER; idNumber <= MOUSECLICKSTARTBUTTON; ++idNumber)
	{
		hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, !isEnabled ? HIDE : mouseActive);
	}
	EnableWindow(keyboardHotkeyButton, isEnabled);

	EnableWindow(activateKeyboardCheckBox, isEnabled);
	for (idNumber = KEYBOARDPRESSTIMER; idNumber <= KEYBOARDPRESSSTARTBUTTON; ++idNumber)
	{
		hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, !isEnabled ? HIDE : keyboardActive);
	}
	EnableWindow(mouseHotkeyButton, isEnabled);
}



void HotkeyButtonAppearance(HWND hotkeyButton, bool isEnabled)
{
	hotkeyButtonStyle = GetWindowLongPtr(hotkeyButton, GWL_STYLE);
	!isEnabled
		? hotkeyButtonStyle |= (WS_THICKFRAME | WS_VSCROLL)
		: hotkeyButtonStyle &= ~(WS_THICKFRAME | WS_VSCROLL);

	SetWindowLongPtr(hotkeyButton, GWL_STYLE, hotkeyButtonStyle);
	SetWindowPos(hotkeyButton, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}



void DebugAppearance(HWND hWnd, bool isEnabled)
{
	for (idNumber = SETTINGSFRAME; idNumber <= BACKTOMAINBUTTON; ++idNumber)
	{
		hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, !isEnabled ? HIDE : SHOW);
	}

	debugButtonStyle = GetWindowLongPtr(debugHotkeyButton, GWL_STYLE);
	!isEnabled
		? debugButtonStyle |= (WS_THICKFRAME | WS_VSCROLL)
		: debugButtonStyle &= ~(WS_THICKFRAME | WS_VSCROLL);

	SetWindowLongPtr(debugHotkeyButton, GWL_STYLE, debugButtonStyle);
	SetWindowPos(debugHotkeyButton, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}



void PopulateComboBox(HWND keyboardSelectedKey, HKL hkl)
{
	BYTE keyState[256] = { 0 };

	const wchar_t* otherKeys[] =
	{
		L"F1", L"F2", L"F3", L"F4", L"F5", L"F6",
		L"F7", L"F8", L"F9", L"F10", L"F11", L"F12",

		L"Num Lock",
		L"Num 0", L"Num 1", L"Num 2", L"Num 3", L"Num 4",
		L"Num 5", L"Num 6", L"Num 7", L"Num 8", L"Num 9",
		L"Num +", L"Num -", L"Num *", L"Num /", L"Num ,",

		L"Insert", L"Prt Sc", L"Scroll Lock", L"Pause",
		L"Delete", L"Home", L"End", L"Page Up", L"Page Down",
		L"Ctrl", L"Shift", L"Alt", L"Up", L"Down", L"Left", L"Right",
		L"Esc", L"Tab", L"Caps Lock", L"Spacebar", L"Enter", L"Backspace",
	};

	const int otherKeysVkCodes[] =
	{
		VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,  // F1 - F6
		VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, // F7 - F12

		VK_NUMLOCK, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, // Numpad (1)
		VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, // Numpad (2)
		VK_ADD, VK_SUBTRACT, VK_MULTIPLY, VK_DIVIDE, VK_DECIMAL,  // Numpad operations

		VK_INSERT, VK_SNAPSHOT, VK_SCROLL, VK_PAUSE, VK_DELETE,  // Misc keys
		VK_HOME, VK_END, VK_PRIOR, VK_NEXT, VK_CONTROL, VK_SHIFT, VK_MENU, // Navigation and modifiers
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE, VK_TAB, VK_CAPITAL, VK_SPACE, VK_RETURN, VK_BACK // Arrow keys and other controls
	};

	if (isWindowsNT())
	{
		// 1) Populate with digits and letters
		for (UINT vk = '0'; vk <= 'Z'; ++vk)
		{
			WCHAR buffer[2] = { 0 };
			int result = ToUnicodeEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 2, 0, hkl);
			if (result > 0)
			{
				WCHAR keyAlnumStr[2] = { buffer[0], 0 };
				LRESULT index = SendMessageW(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyAlnumStr);
				SendMessageW(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode to current index.
			}
		}

		// 2) Populate with special OEM letters (Þ, Ç, Ð etc.)
		for (UINT vk = 0xBA; vk <= 0xE2; ++vk)
		{
			WCHAR buffer[2] = { 0 };
			int result = ToUnicodeEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 2, 0, hkl);
			if (result > 0 )
			{
				WCHAR keyOEMCharStr[2] = { buffer[0], 0 };
				LRESULT index = SendMessageW(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyOEMCharStr);
				SendMessageW(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode data to current index.
			}
		}

		for (int arrIndex = 0; arrIndex < (sizeof(otherKeys)/sizeof(otherKeys[0])); ++arrIndex)
		{
			LRESULT index = SendMessageW(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)otherKeys[arrIndex]);
			SendMessageW(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)otherKeysVkCodes[arrIndex]); // Embed vkCode data to current index.
		}
	}

	else // Windows 98/ME
	{
		// 1) Populate with digits and letters
		for (UINT vk = '0'; vk <= 'Z'; ++vk)
		{
			WORD buffer[2] = { 0 };
			int result = ToAsciiEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 0, hkl);
			if (result > 0)
			{
				char keyAlnumStr[2] = { buffer[0], 0 };
				LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyAlnumStr);
				SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode to current index.
			}
		}

		// 2) Populate with special OEM letters (Þ, Ç, Ð etc.)
		for (UINT vk = 0xBA; vk <= 0xE2; ++vk)
		{
			WORD buffer[2] = { 0 };
			int result = ToAsciiEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 0, hkl);
			if (result > 0)
			{
				char keyOEMCharStr[2] = { buffer[0], 0 };
				LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyOEMCharStr);
				SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode data to current index.
			}
		}

		char otherAsciiKeysArray[20];
		for (int arrIndex = 0; arrIndex < (sizeof(otherKeys)/sizeof(otherKeys[0])); ++arrIndex)
		{
			wcstombs(otherAsciiKeysArray, otherKeys[arrIndex], sizeof(otherAsciiKeysArray));
			LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)otherAsciiKeysArray);
			SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)otherKeysVkCodes[arrIndex]); // Embed vkCode data to current index.
		}
	}

	SendMessage(keyboardSelectedKey, CB_SETCURSEL, 0, 0);
}