#include "main.h"
#include <stdio.h>





static int
currentKey = 0;

UINT
mouseButton	= MOUSEEVENTF_LEFTDOWN,
mouseSpecialKey = 0,
mouseHotkey = VK_F5,
clickType = SINGLE,

keyboardKey	= VK_RETURN,
keyboardHotkey = VK_F6,
keyboardSpecialKey = 0,
keyboardHotkeyTemp = 0;

UINT *specialKey = 0;

char
*mouseHotkeyTextA = "F5",
*mouseHotkeySpecialTextA = "NULL",
*keyboardHotkeyTextA = "F6",
*keyboardHotkeySpecialTextA = "NULL",
*hotkeyTextA,
*hotkeySpecialTextA,
hotkeyAsciiBuffer[30],
debugBuffer[20];

WCHAR
*mouseHotkeyTextW = L"F5",
*mouseHotkeySpecialTextW = L"NULL",
*keyboardHotkeyTextW = L"F6",
*keyboardHotkeySpecialTextW = L"NULL",
*hotkeyTextW,
*hotkeySpecialTextW,
hotkeyUnicodeBuffer[30];

static bool keysEqual = false;

BYTE keyState[256];


static WCHAR defaultChar[3];
wchar_t* GetUnicodeChar(UINT vk)
{
	static WCHAR defaultUnicodeHotkey[2];
	GetKeyboardState(keyState);
	int controlKeysToClear[] =
	{
		VK_SHIFT, VK_LSHIFT, VK_RSHIFT,
		VK_CONTROL, VK_LCONTROL, VK_RCONTROL,
		VK_MENU, VK_LMENU, VK_RMENU
	};

	for (int i = 0; i < sizeof(controlKeysToClear)/sizeof(controlKeysToClear[0]); ++i)
		keyState[controlKeysToClear[i]] = 0;

	UINT scanCode = MapVirtualKey(vk, 0);
	ToUnicode(vk, scanCode, keyState, defaultChar, 3, 0);
	defaultUnicodeHotkey[0] = defaultChar[0];
	defaultUnicodeHotkey[1] = '\0';

	return defaultUnicodeHotkey;
}


static WORD win98Char[3];
char* GetAsciiChar(UINT vk)
{
	static char defaultAsciiHotkey[2];
	GetKeyboardState(keyState);
	int controlKeysToClear[] =
	{
		VK_SHIFT, VK_LSHIFT, VK_RSHIFT,
		VK_CONTROL, VK_LCONTROL, VK_RCONTROL,
		VK_MENU, VK_LMENU, VK_RMENU
	};

	for (int i = 0; i < sizeof(controlKeysToClear)/sizeof(controlKeysToClear[0]); ++i)
		keyState[controlKeysToClear[i]] = 0;

	UINT scanCode = MapVirtualKey(vk, 0);
	ToAscii(vk, scanCode, keyState, win98Char, 0);
	defaultAsciiHotkey[0] = win98Char[0];
	defaultAsciiHotkey[1] = '\0';

	return defaultAsciiHotkey;
}



void GetHotkey(HWND hWnd, UINT *hotkey, bool *hotkeySelected, int selectMod)
{
	if (selectMod == HOTKEYAUTOCLICKER)
	{
		specialKey = &mouseSpecialKey;
		*specialKey = 0;
	}
	else
	{
		specialKey = &keyboardSpecialKey;
		*specialKey = 0;
	}

	MSG hotMsg;
	while (!(*hotkeySelected))
	{
		if (GetMessage(&hotMsg, NULL, 0, 0))
		{
			TranslateMessage(&hotMsg);
			DispatchMessage(&hotMsg);
		}

		for (currentKey = 0x08; currentKey < 0xFF; ++currentKey)
		{
			// If you press a button
			if (GetAsyncKeyState(currentKey) & 0x8000)
			{
				/*
					If you detect the keys such as:
					• Some control buttons (includes ESC)
					• A-Z, 0-9
					• OEM buttons
				*/
				if ((currentKey >= 0x08 && currentKey <= 0x14)
					|| (currentKey >= 0x20 && currentKey <= 0x5A)
					|| (currentKey >= 0x60 && currentKey <= 0xA5)
					|| (currentKey >= 0xBA && currentKey <= 0xE2)
					|| currentKey == VK_ESCAPE
				)
				{
					if (currentKey == *specialKey)
						break;

					switch (currentKey)
					{
						// SHIFT key
						case VK_SHIFT:
						case VK_LSHIFT:
						case VK_RSHIFT:
							Sleep(50);
							*specialKey = MOD_SHIFT;
							hotkeySpecialTextA = "SHIFT";
							hotkeySpecialTextW = L"SHIFT";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, "SHIFT + ?");
							continue;

						// CTRL key
						case VK_CONTROL:
						case VK_LCONTROL:
						case VK_RCONTROL:
							Sleep(50);
							*specialKey = MOD_CONTROL;
							hotkeySpecialTextA = "CTRL";
							hotkeySpecialTextW = L"CTRL";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, "CTRL + ?");
							continue;

						// ALT key
						case VK_MENU:
						case VK_LMENU:
						case VK_RMENU:
							Sleep(50);
							*specialKey = MOD_ALT;
							hotkeySpecialTextA = "ALT";
							hotkeySpecialTextW = L"ALT";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, "ALT + ?");
							continue;
					}



					switch(currentKey)
					{
						case VK_F1:
							hotkeyTextA = "F1";
							hotkeyTextW = L"F1";
							break;
						case VK_F2:
							hotkeyTextA = "F2";
							hotkeyTextW = L"F2";
							break;
						case VK_F3:
							hotkeyTextA = "F3";
							hotkeyTextW = L"F3";
							break;
						case VK_F4:
							hotkeyTextA = "F4";
							hotkeyTextW = L"F4";
							break;
						case VK_F5:
							hotkeyTextA = "F5";
							hotkeyTextW = L"F5";
							break;
						case VK_F6:
							hotkeyTextA = "F6";
							hotkeyTextW = L"F6";
							break;
						case VK_F7:
							hotkeyTextA = "F7";
							hotkeyTextW = L"F7";
							break;
						case VK_F8:
							hotkeyTextA = "F8";
							hotkeyTextW = L"F8";
							break;
						case VK_F9:
							hotkeyTextA = "F9";
							hotkeyTextW = L"F9";
							break;
						case VK_F10:
							hotkeyTextA = "F10";
							hotkeyTextW = L"F10";
							break;
						case VK_F11:
							hotkeyTextA = "F11";
							hotkeyTextW = L"F11";
							break;
						case VK_F12:
							hotkeyTextA = "F12";
							hotkeyTextW = L"F12";
							break;


						case VK_NUMLOCK:
							hotkeyTextA = "NUM LOCK";
							hotkeyTextW = L"NUM LOCK";
							break;
						case VK_NUMPAD0:
							hotkeyTextA = "NUM0";
							hotkeyTextW = L"NUM0";
							break;
						case VK_NUMPAD1:
							hotkeyTextA = "NUM1";
							hotkeyTextW = L"NUM1";
							break;
						case VK_NUMPAD2:
							hotkeyTextA = "NUM2";
							hotkeyTextW = L"NUM2";
							break;
						case VK_NUMPAD3:
							hotkeyTextA = "NUM3";
							hotkeyTextW = L"NUM3";
							break;
						case VK_NUMPAD4:
							hotkeyTextA = "NUM4";
							hotkeyTextW = L"NUM4";
							break;
						case VK_NUMPAD5:
							hotkeyTextA = "NUM5";
							hotkeyTextW = L"NUM5";
							break;
						case VK_NUMPAD6:
							hotkeyTextA = "NUM6";
							hotkeyTextW = L"NUM6";
							break;
						case VK_NUMPAD7:
							hotkeyTextA = "NUM7";
							hotkeyTextW = L"NUM7";
							break;
						case VK_NUMPAD8:
							hotkeyTextA = "NUM8";
							hotkeyTextW = L"NUM8";
							break;
						case VK_NUMPAD9:
							hotkeyTextA = "NUM9";
							hotkeyTextW = L"NUM9";
							break;
						case VK_MULTIPLY:
							hotkeyTextA = "NUM *";
							hotkeyTextW = L"NUM *";
							break;
						case VK_ADD:
							hotkeyTextA = "NUM +";
							hotkeyTextW = L"NUM +";
							break;
						case VK_SEPARATOR:
							hotkeyTextA = "NUM SEPR";
							hotkeyTextW = L"NUM SEPR";
							break;
						case VK_SUBTRACT:
							hotkeyTextA = "NUM -";
							hotkeyTextW = L"NUM -";
							break;
						case VK_DECIMAL:
							hotkeyTextA = "NUM ,";
							hotkeyTextW = L"NUM ,";
							break;
						case VK_DIVIDE:
							hotkeyTextA = "NUM /";
							hotkeyTextW = L"NUM /";
							break;


						case VK_BACK:
							hotkeyTextA = "BACKSPACE";
							hotkeyTextW = L"BACKSPACE";
							break;
						case VK_CAPITAL:
							hotkeyTextA = "CAPS LOCK";
							hotkeyTextW = L"CAPS LOCK";
							break;
						case VK_CLEAR:
							hotkeyTextA = "CLEAR";
							hotkeyTextW = L"CLEAR";
							break;
						case VK_DELETE:
							hotkeyTextA = "DELETE";
							hotkeyTextW = L"DELETE";
							break;
						case VK_DOWN:
							hotkeyTextA = "DOWN";
							hotkeyTextW = L"DOWN";
							break;
						case VK_RETURN:
							hotkeyTextA = "ENTER";
							hotkeyTextW = L"ENTER";
							break;
						case VK_END:
							hotkeyTextA = "END";
							hotkeyTextW = L"END";
							break;
						case VK_ESCAPE:
							hotkeyTextA = "ESC";
							hotkeyTextW = L"ESC";
							break;
						case VK_EXECUTE:
							hotkeyTextA = "EXECUTE";
							hotkeyTextW = L"EXECUTE";
							break;
						case VK_HELP:
							hotkeyTextA = "HELP";
							hotkeyTextW = L"HELP";
							break;
						case VK_HOME:
							hotkeyTextA = "HOME";
							hotkeyTextW = L"HOME";
							break;
						case VK_INSERT:
							hotkeyTextA = "INSERT";
							hotkeyTextW = L"INSERT";
							break;
						case VK_LEFT:
							hotkeyTextA = "LEFT";
							hotkeyTextW = L"LEFT";
							break;
						case VK_NEXT:
							hotkeyTextA = "PG DN";
							hotkeyTextW = L"PG DN";
							break;
						case VK_PRIOR:
							hotkeyTextA = "PG UP";
							hotkeyTextW = L"PG UP";
							break;
						case VK_PAUSE:
							hotkeyTextA = "PAUSE";
							hotkeyTextW = L"PAUSE";
							break;
						case VK_PRINT:
							hotkeyTextA = "PRINT";
							hotkeyTextW = L"PRINT";
							break;
						case VK_SNAPSHOT:
							hotkeyTextA = "PRT SC";
							hotkeyTextW = L"PRT SC";
							break;
						case VK_RIGHT:
							hotkeyTextA = "RIGHT";
							hotkeyTextW = L"RIGHT";
							break;
						case VK_SCROLL:
							hotkeyTextA = "SCRLK";
							hotkeyTextW = L"SCRLK";
							break;
						case VK_SELECT:
							hotkeyTextA = "SELECT";
							hotkeyTextW = L"SELECT";
							break;
						case VK_SPACE:
							hotkeyTextA = "SPACE";
							hotkeyTextW = L"SPACE";
							break;
						case VK_TAB:
							hotkeyTextA = "TAB";
							hotkeyTextW = L"TAB";
							break;
						case VK_UP:
							hotkeyTextA = "UP";
							hotkeyTextW = L"UP";
							break;


						default:
						{
							if (isWindowsNT())
							{
								hotkeyTextW = GetUnicodeChar(currentKey);

								// & is a special character, you need to write "&&" to display "&".
								if (wcscmp(hotkeyTextW, L"&") == 0)
									hotkeyTextW = L"&&";
							}

							else
							{
								hotkeyTextA = GetAsciiChar(currentKey);

								// & is a special character, you need to write "&&" to display "&".
								if (strcmp(hotkeyTextA, "&") == 0)
									hotkeyTextA = "&&";
							}

							break;
						}
					}

					*hotkeySelected = true;
					*hotkey = currentKey;
					break;
				}
			}
		}
	}

	if (isWindowsNT())
	{
		if (*specialKey == 0)
		{
			swprintf(hotkeyUnicodeBuffer, L"Hotkey: %ls", hotkeyTextW);
			hotkeySpecialTextW = L"NULL";
		}
		else
			swprintf(hotkeyUnicodeBuffer,  L"Hotkey: %ls + %ls", hotkeySpecialTextW, hotkeyTextW);

		SetWindowTextW(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, hotkeyUnicodeBuffer);

		if (selectMod == HOTKEYAUTOCLICKER)
		{
			static WCHAR mouseHotkeyBufW[20], mouseHotkeySpecialBufW[12];

			wcscpy(mouseHotkeyBufW, hotkeyTextW);
			mouseHotkeyTextW = mouseHotkeyBufW;

			wcscpy(mouseHotkeySpecialBufW, hotkeySpecialTextW);
			mouseHotkeySpecialTextW = mouseHotkeySpecialBufW;
		}
		else
		{
			static WCHAR keyboardHotkeyBufW[20], keyboardHotkeySpecialBufW[12];

			wcscpy(keyboardHotkeyBufW, hotkeyTextW);
			keyboardHotkeyTextW = keyboardHotkeyBufW;

			wcscpy(keyboardHotkeySpecialBufW, hotkeySpecialTextW);
			keyboardHotkeySpecialTextW = keyboardHotkeySpecialBufW;
		}
	}
	else
	{
		if (*specialKey == 0)
		{
			sprintf(hotkeyAsciiBuffer, "Hotkey: %s", hotkeyTextA);
			hotkeySpecialTextA = "NULL";
		}
		else
			sprintf(hotkeyAsciiBuffer,  "Hotkey: %s + %s", hotkeySpecialTextA, hotkeyTextA);

		SetWindowTextA(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, hotkeyAsciiBuffer);

		if (selectMod == HOTKEYAUTOCLICKER)
		{
			static char mouseHotkeyBufA[20], mouseHotkeySpecialBufA[12];

			strcpy(mouseHotkeyBufA, hotkeyTextA);
			mouseHotkeyTextA = mouseHotkeyBufA;

			strcpy(mouseHotkeySpecialBufA, hotkeySpecialTextA);
			mouseHotkeySpecialTextA = mouseHotkeySpecialBufA;
		}
		else
		{
			static char keyboardHotkeyBufA[20], keyboardHotkeySpecialBufA[12];

			strcpy(keyboardHotkeyBufA, hotkeyTextA);
			keyboardHotkeyTextA = keyboardHotkeyBufA;

			strcpy(keyboardHotkeySpecialBufA, hotkeySpecialTextA);
			keyboardHotkeySpecialTextA = keyboardHotkeySpecialBufA;
		}
	}


	if ((mouseHotkey == keyboardHotkey) && (mouseSpecialKey == keyboardSpecialKey))
	{
		keysEqual = true;
		keyboardHotkeyTemp = mouseHotkey;
		UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
		RegisterHotKey(hWnd,
		MOUSECLICKHOTKEY,
		*specialKey,
		*hotkey);
	}
	else
	{
		if (keysEqual && selectMod == HOTKEYAUTOCLICKER)
		{
			RegisterHotKey(hWnd,
				KEYBOARDPRESSHOTKEY,
				*specialKey,
				keyboardHotkeyTemp);
			keysEqual = false;
		}

		RegisterHotKey(hWnd,
			selectMod == HOTKEYAUTOCLICKER ? MOUSECLICKHOTKEY : KEYBOARDPRESSHOTKEY,
			*specialKey,
			*hotkey);
	}
}



void LoadHotkey(HWND hWnd, UINT *specialKey, UINT *hotkey, int selectMod);

void LoadHotkeyW(HWND hWnd, WCHAR *hotkeySpecTxtW, UINT *specialKey, WCHAR *hotkeyTxtW, UINT *hotkey, int selectMod)
{
	if (*specialKey == 0)
		swprintf(hotkeyUnicodeBuffer, L"Hotkey: %ls", hotkeyTxtW);
	else
		swprintf(hotkeyUnicodeBuffer,  L"Hotkey: %ls + %ls", hotkeySpecTxtW, hotkeyTxtW);

	SetWindowTextW(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, hotkeyUnicodeBuffer);
	LoadHotkey(hWnd, specialKey, hotkey, selectMod);
}



void LoadHotkeyA(HWND hWnd, char *hotkeySpecTxtA, UINT *specialKey, char *hotkeyTxtA, UINT *hotkey, int selectMod)
{
	if (*specialKey == 0)
		sprintf(hotkeyAsciiBuffer, "Hotkey: %s", hotkeyTxtA);
	else
		sprintf(hotkeyAsciiBuffer,  "Hotkey: %s + %s", hotkeySpecTxtA, hotkeyTxtA);

	SetWindowTextA(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, hotkeyAsciiBuffer);
	LoadHotkey(hWnd, specialKey, hotkey, selectMod);
}



void LoadHotkey(HWND hWnd, UINT *specialKey, UINT *hotkey, int selectMod)
{
	if (selectMod == HOTKEYAUTOPRESSER && (mouseHotkey == keyboardHotkey) && (mouseSpecialKey == keyboardSpecialKey))
	{
		keyboardHotkeyTemp = mouseHotkey;
		UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
		RegisterHotKey(hWnd, MOUSECLICKHOTKEY, *specialKey, *hotkey);
	}
	else
	{
		RegisterHotKey(hWnd,
			selectMod == HOTKEYAUTOCLICKER ? MOUSECLICKHOTKEY : KEYBOARDPRESSHOTKEY,
			*specialKey,
			*hotkey);
	}
}




bool isKeyPressed;
void GetDebugHexCode(HWND debugHotkeyButton)
{
	isKeyPressed = false;
	SetWindowText(debugHotkeyButton, "Select a Key");

	while (!isKeyPressed)
	{
		MSG debugMsg;
		if (GetMessage(&debugMsg, NULL, 0, 0))
		{
			TranslateMessage(&debugMsg);
			DispatchMessage(&debugMsg);
		}

		for (int keyHexNumber = 0; keyHexNumber < 256; ++keyHexNumber)
		{
			if (GetAsyncKeyState(keyHexNumber) & 0x8000)
			{
				sprintf(debugBuffer,  "You pressed: 0x%02x", keyHexNumber);
				isKeyPressed = true;
				break;
			}
		}
	}

	SetWindowText(debugHotkeyButton, debugBuffer);
}



int GetMouseButton(HWND mouseLmB)
{
	if (SendMessage(mouseLmB, CB_GETCURSEL, 0, 0) != CB_ERR)
	{
		char mouseButtonText[10];
		SendMessage(mouseLmB, CB_GETLBTEXT, SendMessage(mouseLmB, CB_GETCURSEL, 0, 0), (LPARAM)mouseButtonText);

		if (strcmp(mouseButtonText, "Left") == 0)
			return MOUSEEVENTF_LEFTDOWN;

		else if (strcmp(mouseButtonText, "Middle") == 0)
			return MOUSEEVENTF_MIDDLEDOWN;

		else if (strcmp(mouseButtonText, "Right") == 0)
			return MOUSEEVENTF_RIGHTDOWN;
	}
	// Default
	return MOUSEEVENTF_LEFTDOWN;
}



int GetMouseClickType(HWND mouseClickStartTypeParam)
{
	if (SendMessage(mouseLmB, CB_GETCURSEL, 0, 0) != CB_ERR)
	{
		char mouseClickStartTypeText[16];
		SendMessage(mouseClickStartTypeParam, CB_GETLBTEXT, SendMessage(mouseClickStartTypeParam, CB_GETCURSEL, 0, 0), (LPARAM)mouseClickStartTypeText);

		if (strcmp(mouseClickStartTypeText, "Single (x1)") == 0)
			return 1;

		else if (strcmp(mouseClickStartTypeText, "Double (x2)") == 0)
			return 2;

		else if (strcmp(mouseClickStartTypeText, "Xtra (x16)") == 0)
			return 16;
	}
	// Default
	return 1;
}



UINT GetKeyboardKey(HWND keyboardSelectedKey)
{
	LRESULT index = SendMessage(keyboardSelectedKey, CB_GETCURSEL, 0, 0);

	if (isWindowsNT())
		return (UINT)SendMessageW(keyboardSelectedKey, CB_GETITEMDATA, (WPARAM)index, 0);
	else
		return (UINT)SendMessageA(keyboardSelectedKey, CB_GETITEMDATA, (WPARAM)index, 0);
}


bool holdingInProgress = 0;
VOID CALLBACK HoldTimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	KillTimer(hWnd, HOLDTIME);
	holdingInProgress = 0;
	PostMessage(hWnd, CONT_CLICKERHOLDTIME, 0, 0);
}

void ContinueClickerHoldTime();
UINT g_clickType, g_mouseButton;
void StartAutoClicker(HWND hWnd, UINT clickType, UINT mouseButton)
{
	g_clickType = clickType;
	g_mouseButton = mouseButton;
	INPUT mouseClickStart[32] = {0};

	mouseClickStart[0].type = INPUT_MOUSE;
	mouseClickStart[0].mi.dwFlags = mouseButton;

	if (holdTimeEditValue != 0)
	{
		holdingInProgress = 1;
		SendInput(1, mouseClickStart, sizeof(INPUT));
		SetTimer(hWnd, HOLDTIME, holdTimeEditValue, HoldTimeProc);
	}
	else
	{
		mouseClickStart[1].type = INPUT_MOUSE;
		mouseClickStart[1].mi.dwFlags = mouseButton * 2;

		switch (clickType)
		{
			case SINGLE:
				SendInput(2, mouseClickStart, sizeof(INPUT));
				break;

			case DOUBLE:
			{
				mouseClickStart[2].type = INPUT_MOUSE;
				mouseClickStart[2].mi.dwFlags = mouseButton;

				mouseClickStart[3].type = INPUT_MOUSE;
				mouseClickStart[3].mi.dwFlags = mouseButton * 2;

				SendInput(clickType * 2, mouseClickStart, sizeof(INPUT));
				break;
			}

			case XTRA:
			{
				for (int i = 2; i < sizeof(mouseClickStart)/sizeof(mouseClickStart[0]); i+=2)
				{
					mouseClickStart[i].type = INPUT_MOUSE;
					mouseClickStart[i].mi.dwFlags = mouseButton;

					mouseClickStart[i+1].type = INPUT_MOUSE;
					mouseClickStart[i+1].mi.dwFlags = mouseButton * 2;
				}
				SendInput(clickType * 2, mouseClickStart, sizeof(INPUT));
				break;
			}
		}
	}
}

void StopClickerHoldTime()
{
	holdingInProgress = 0;
	INPUT cancelledClick[1] = {0};

	cancelledClick[0].type = INPUT_MOUSE;
	cancelledClick[0].mi.dwFlags = g_mouseButton * 2;
	SendInput(1, cancelledClick, sizeof(INPUT));
}

void ContinueClickerHoldTime()
{
	INPUT mouseClickStart[32] = {0};

	mouseClickStart[0].type = INPUT_MOUSE;
	mouseClickStart[0].mi.dwFlags = g_mouseButton * 2;

	switch (g_clickType)
	{
		case SINGLE:
			SendInput(1, mouseClickStart, sizeof(INPUT));
			break;

		case DOUBLE:
		{
			mouseClickStart[1].type = INPUT_MOUSE;
			mouseClickStart[1].mi.dwFlags = g_mouseButton;

			mouseClickStart[2].type = INPUT_MOUSE;
			mouseClickStart[2].mi.dwFlags = g_mouseButton * 2;

			SendInput((g_clickType * 2) - 1, mouseClickStart, sizeof(INPUT));
			break;
		}

		case XTRA:
		{
			for (int i = 1; i < sizeof(mouseClickStart)/sizeof(mouseClickStart[0]); i+=2)
			{
				mouseClickStart[i].type = INPUT_MOUSE;
				mouseClickStart[i].mi.dwFlags = g_mouseButton;

				mouseClickStart[i+1].type = INPUT_MOUSE;
				mouseClickStart[i+1].mi.dwFlags = g_mouseButton * 2;
			}
			SendInput((g_clickType * 2) - 1, mouseClickStart, sizeof(INPUT));
			break;
		}
	}
}



void StartAutoPresser(UINT keyboardKey)
{
	INPUT keyboardPress[2] = {0, 0};

	keyboardPress[0].type = INPUT_KEYBOARD;
	keyboardPress[0].ki.wVk = static_cast<WORD>(keyboardKey);

	keyboardPress[1].type = INPUT_KEYBOARD;
	keyboardPress[1].ki.wVk = static_cast<WORD>(keyboardKey);
	keyboardPress[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, keyboardPress, sizeof(INPUT));
}