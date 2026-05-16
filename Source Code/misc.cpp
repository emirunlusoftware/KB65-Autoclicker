#include "KB65 Autoclicker.h"
#include <ctype.h>
#include <wctype.h>





bool
mouseActive = true,
keyboardActive = false;

// Minimum OS version: 4.0 (Windows NT 4.0)
// Maximum OS version: 6.2 (Windows 8)
// use with GetVersionEx(&winverOld)
OSVERSIONINFO winverOld = {0};

// Minimum OS version: 5.0 (Windows 2000)
// Maximum OS version: 10.0 (Windows 10/11 & later)
RTL_OSVERSIONINFOW winver = {0};



bool isWindowsNT()
{
	// • true [Windows NT (NT 4.0/2000/XP/Vista etc.)]
	// • false [Windows 98/ME]
	return (winverOld.dwPlatformId == VER_PLATFORM_WIN32_NT);
}


bool isWindowsXPLater()
{
	// Settings like EM_SETCUEBANNER aren't supported on Windows 2000
	return (winver.dwMajorVersion == 5 && winver.dwMinorVersion >= 1) || (winver.dwMajorVersion > 5);
}


bool isWindows10Later()
{
	// DPI, Text Scale etc.
	return (winver.dwMajorVersion >= 10);
}


bool isWindows11Later()
{
	// DWMWA_CAPTION_COLOR requires Windows 11+
	return (winver.dwMajorVersion >= 10 && winver.dwBuildNumber >= 22000);
}



void RealignZOrderChain(HWND hWnd)
{
	HWND hWndGetPrev = HWND_BOTTOM;

	for (int id = ACTIVATEMOUSE_VIA_TRAY; id <= BACKTOMAINBUTTON; ++id)
	{
		HWND hWndGet = GetDlgItem(hWnd, id);
		if (hWndGet != NULL)
		{
			SetWindowPos(hWndGet, hWndGetPrev, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			hWndGetPrev = hWndGet;
		}
	}
}



// Windows Vista and later.
// Changes the message filter for 3 messages below to handle WM_DROPFILES messages (a.k.a Drag & Drop)
// Otherwise you won't be able to catch WM_DROPFILES messages (a.k.a no Drag & Drop).
void ChangeDragDropMsgFilter(HWND hWnd)
{
	HMODULE hUser32 = LoadLibraryW(L"user32.dll");
	if (hUser32)
	{
		CHANGEWINDOWMESSAGEFILTEREX pfnChangeWindowMessageFilterEx =
			(CHANGEWINDOWMESSAGEFILTEREX)GetProcAddress(hUser32, "ChangeWindowMessageFilterEx");

		if (pfnChangeWindowMessageFilterEx)
		{
			pfnChangeWindowMessageFilterEx(hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
			pfnChangeWindowMessageFilterEx(hWnd, WM_COPYDATA, MSGFLT_ALLOW, NULL);
			pfnChangeWindowMessageFilterEx(hWnd, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);
		}
		FreeLibrary(hUser32);
	}
}



void ActiveAppearance(HWND hWnd, int mod, bool isEnabled)
{
	for (int idNumber = (mod == AUTOCLICKER ? MOUSETIMERFRAME : KEYBOARDTIMERFRAME);
		idNumber < (mod == AUTOCLICKER ? MOUSECLICKHOTKEYBUTTON: KEYBOARDPRESSHOTKEYBUTTON);
		++idNumber)
	{
		HWND hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, isEnabled);
	}
	EnableWindow(mod == AUTOCLICKER ? mouseClickStart : keyboardPressStart, isEnabled);

	if (IsWindowEnabled(mod == AUTOCLICKER ? mouseClickStop : keyboardPressStop))
		EnableWindow(mod == AUTOCLICKER ? mouseClickStop : keyboardPressStop, HIDE);
}



void HotkeyButtonAppearance(HWND hotkeyButton, bool isEnabled)
{
	LONG_PTR hotkeyButtonStyle = GetWindowLongPtr(hotkeyButton, GWL_STYLE);
	isEnabled
		? hotkeyButtonStyle &= ~(WS_THICKFRAME | WS_VSCROLL)
		: hotkeyButtonStyle |= (WS_THICKFRAME | WS_VSCROLL);

	SetWindowLongPtr(hotkeyButton, GWL_STYLE, hotkeyButtonStyle);
	SetWindowPos(hotkeyButton, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}



void HotkeySelectionAppearance(HWND hWnd, WORD hotkeyButtonId, bool isEnabled)
{
	DragAcceptFiles(hWnd, isEnabled);
	EnableWindow(activateMouseCheckBox, isEnabled);
	EnableWindow(activateKeyboardCheckBox, isEnabled);
	EnableWindow(loadScriptsButton, isEnabled);
	EnableWindow(saveScriptsButton, isEnabled);

	for (int idNumber = MOUSETIMERFRAME; idNumber <= MOUSECLICKSTARTBUTTON; ++idNumber)
	{
		HWND hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, !isEnabled ? HIDE : mouseActive);
	}
	for (int idNumber = KEYBOARDTIMERFRAME; idNumber <= KEYBOARDPRESSSTARTBUTTON; ++idNumber)
	{
		HWND hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, !isEnabled ? HIDE : keyboardActive);
	}

	EnableWindow(mouseHotkeyButton, isEnabled);
	EnableWindow(keyboardHotkeyButton, isEnabled);

	if (hotkeyButtonId == MOUSECLICKHOTKEYBUTTON)
		HotkeyButtonAppearance(mouseHotkeyButton, isEnabled);
	else if (hotkeyButtonId == KEYBOARDPRESSHOTKEYBUTTON)
		HotkeyButtonAppearance(keyboardHotkeyButton, isEnabled);
}



void DebugAppearance(HWND hWnd, bool isEnabled)
{
	for (int idNumber = SETTINGSFRAME; idNumber <= BACKTOMAINBUTTON; ++idNumber)
	{
		HWND hWndGet = GetDlgItem(hWnd, idNumber);

		if (hWndGet != NULL)
			EnableWindow(hWndGet, isEnabled ? SHOW : HIDE);
	}

	LONG_PTR debugButtonStyle = GetWindowLongPtr(debugHotkeyButton, GWL_STYLE);
	isEnabled
		? debugButtonStyle &= ~(WS_THICKFRAME | WS_VSCROLL)
		: debugButtonStyle |= (WS_THICKFRAME | WS_VSCROLL);

	SetWindowLongPtr(debugHotkeyButton, GWL_STYLE, debugButtonStyle);
	SetWindowPos(debugHotkeyButton, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}



void PopulateComboBox(HWND keyboardSelectedKey, HKL hkl)
{
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


	BYTE keyState[256] = {0};

	if (isWindowsNT())
	{
		// 1) Populate with digits and letters
		for (UINT vk = '0'; vk <= 'Z'; ++vk)
		{
			WCHAR buffer[3] = { 0 };
			int result = ToUnicodeEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 3, 0, hkl);
			if (result > 0)
			{
				WCHAR keyAlnumStr[2] = { buffer[0], '\0' };
				LRESULT index = SendMessageW(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyAlnumStr);
				SendMessageW(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode to current index.
			}
		}

		// 2) Populate with special OEM letters (Þ, Ç, Ð etc.)
		for (UINT vk = 0xBA; vk <= 0xE2; ++vk)
		{
			WCHAR buffer[3] = { 0 };
			int result = ToUnicodeEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 3, 0, hkl);


			// Dead keys are the keys which appear on the screen
			// after you pressed the same key at second time
			// (e.g. ^ (circumflex) ` (backtick) ~ (tilde))
			// ---Problem---
			// Dead keys* aren't being added to keyboardSelectedKey combobox,
			// also ToUnicodeEx are returning -1 due to this keys.
			// Thus, the keys aren't being seen in the combobox.
			// ---Solution---
			// Handle -1 value and call ToUnicodeEx function again.
			if (result == -1)
				result = ToUnicodeEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 3, 0, hkl);

			if (result > 0)
			{
				WCHAR keyOEMCharStr[2] = { buffer[0], '\0' };
				LRESULT index = SendMessageW(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyOEMCharStr);
				SendMessageW(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode data to current index.
			}
		}

		for (UINT arrIndex = 0; arrIndex < (sizeof(otherKeys)/sizeof(otherKeys[0])); ++arrIndex)
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
			WORD buffer[3] = { 0 };
			int result = ToAsciiEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 0, hkl);
			if (result > 0)
			{
				char keyAlnumStr[2] = { buffer[0], '\0' };
				LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyAlnumStr);
				SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode to current index.
			}
		}

		// 2) Populate with special OEM letters (Þ, Ç, Ð etc.)
		for (UINT vk = 0xBA; vk <= 0xE2; ++vk)
		{
			WORD buffer[3] = { 0 };
			int result = ToAsciiEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 0, hkl);

			if (result == -1)
				result = ToAsciiEx(vk, MapVirtualKey(vk, 0), keyState, buffer, 0, hkl);

			if (result > 0)
			{
				char keyOEMCharStr[2] = { buffer[0], '\0' };
				LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)keyOEMCharStr);
				SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)vk); // Embed vkCode data to current index.
			}
		}

		char otherAsciiKeysArray[20];
		for (UINT arrIndex = 0; arrIndex < (sizeof(otherKeys)/sizeof(otherKeys[0])); ++arrIndex)
		{
			wcstombs(otherAsciiKeysArray, otherKeys[arrIndex], sizeof(otherAsciiKeysArray));
			LRESULT index = SendMessageA(keyboardSelectedKey, CB_ADDSTRING, 0, (LPARAM)otherAsciiKeysArray);
			SendMessageA(keyboardSelectedKey, CB_SETITEMDATA, (WPARAM)index, (LPARAM)otherKeysVkCodes[arrIndex]); // Embed vkCode data to current index.
		}
	}


	// SendMessage is required for initialization process of the program.
	if (keyboardKey == '0')
		SendMessage(keyboardSelectedKey, CB_SETCURSEL, 0, 0);
	else
	{
		int totalEntryCount = (int)SendMessage(keyboardSelectedKey, CB_GETCOUNT, 0, 0);
		for (int index = 0; index < totalEntryCount; ++index)
		{
			LRESULT myData = SendMessage(keyboardSelectedKey, CB_GETITEMDATA, (WPARAM)index, 0);
			if (keyboardKey == myData)
			{
				SendMessage(keyboardSelectedKey, CB_SETCURSEL, index, 0);
				return;
			}
		}

		// Some virtual key codes might not match with the new one when the keyboard layout is updated.
		// Set a fallback and set the combobox and keyboardKey to number 0.
		SendMessage(keyboardSelectedKey, CB_SETCURSEL, 0, 0);
		keyboardKey = '0';
	}
}



// .ini optimized of PathFileExtensionW (from shlwapi.h)
bool IniExtensionFoundW(LPCWSTR filePath)
{
	if (!filePath)
		return false;

	size_t pathLen = wcslen(filePath);

	// The shortest file name with extension is ".ini" that's length is four.
	if (pathLen >= 4)
	{
		const wchar_t* extension = filePath + (pathLen - 4);
		if (extension[0] == L'.' &&
			(extension[1] == L'i' || extension[1] == L'I') &&
			(extension[2] == L'n' || extension[2] == L'N') &&
			(extension[3] == L'i' || extension[3] == L'I'))
		{
			return true;
		}
	}

	return false;
}

bool IniExtensionFoundA(LPCSTR filePath)
{
	if (!filePath)
		return false;

	size_t pathLen = strlen(filePath);
	if (pathLen >= 4)
	{
		const char* extension = filePath + (pathLen - 4);
		if (extension[0] == '.' &&
			(extension[1] == 'i' || extension[1] == 'I') &&
			(extension[2] == 'n' || extension[2] == 'N') &&
			(extension[3] == 'i' || extension[3] == 'I'))
		{
			return true;
		}
	}

	return false;
}