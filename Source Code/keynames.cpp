#include "main.h"
#include <stdio.h>


#ifdef _WIN32
#define sprintf _stprintf_s
#endif





unsigned int
keyboardHotkeyTemp = 0,
mouseHotkey = VK_F5,
keyboardHotkey = VK_F6;


bool keysEqual = false;


static TCHAR defaultHotkey[2], hotkeyBuffer[24];
static TCHAR *hotkeyText, *hotkeySpecialText;
static int currentKey, specialKey;


void GetHotkey(HWND hWnd, unsigned int* hotkey, bool* hotkeySelected, int selectMod)
{
	MSG hotMsg;
	specialKey = 0;
	while (!(*hotkeySelected))
	{
        if (GetMessage(&hotMsg, NULL, 0, 0))
        {
            TranslateMessage(&hotMsg);
            DispatchMessage(&hotMsg);
        }

		for (currentKey = 0; currentKey < 256; ++currentKey)
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
					if (currentKey == specialKey)
						continue;

					switch (currentKey)
					{
						// SHIFT key
						case VK_SHIFT:
						case VK_LSHIFT:
						case VK_RSHIFT:
							Sleep(50);
							specialKey = MOD_SHIFT;
							hotkeySpecialText = "SHIFT";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, TEXT("SHIFT + ?"));
							continue;

						// CTRL key
						case VK_CONTROL:
						case VK_LCONTROL:
						case VK_RCONTROL:
							Sleep(50);
							specialKey = MOD_CONTROL;
							hotkeySpecialText = "CTRL";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, TEXT("CTRL + ?"));
							continue;

						// ALT key
						case VK_MENU:
						case VK_LMENU:
						case VK_RMENU:
							Sleep(50);
							specialKey = MOD_ALT;
							hotkeySpecialText = "ALT";
							SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, TEXT("ALT + ?"));
							continue;

						case VK_BACK:
							hotkeyText = "BACKSPACE";
							break;
						case VK_CAPITAL:
							hotkeyText = "CAPS LOCK";
							break;
						case VK_CLEAR:
							hotkeyText = "CLEAR";
							break;
						case VK_DELETE:
							hotkeyText = "DELETE";
							break;
						case VK_DOWN:
							hotkeyText = "DOWN";
							break;
						case VK_RETURN:
							hotkeyText = "ENTER";
							break;
						case VK_END:
							hotkeyText = "END";
							break;
						case VK_ESCAPE:
							hotkeyText = "ESC";
							break;
						case VK_EXECUTE:
							hotkeyText = "EXECUTE";
							break;
						case VK_HELP:
							hotkeyText = "HELP";
							break;
						case VK_HOME:
							hotkeyText = "HOME";
							break;
						case VK_INSERT:
							hotkeyText = "INSERT";
							break;
						case VK_LEFT:
							hotkeyText = "LEFT";
							break;


						case VK_NUMLOCK:
							hotkeyText = "NUM LOCK";
							break;
						case VK_NUMPAD0:
							hotkeyText = "NUM0";
							break;
						case VK_NUMPAD1:
							hotkeyText = "NUM1";
							break;
						case VK_NUMPAD2:
							hotkeyText = "NUM2";
							break;
						case VK_NUMPAD3:
							hotkeyText = "NUM3";
							break;
						case VK_NUMPAD4:
							hotkeyText = "NUM4";
							break;
						case VK_NUMPAD5:
							hotkeyText = "NUM5";
							break;
						case VK_NUMPAD6:
							hotkeyText = "NUM6";
							break;
						case VK_NUMPAD7:
							hotkeyText = "NUM7";
							break;
						case VK_NUMPAD8:
							hotkeyText = "NUM8";
							break;
						case VK_NUMPAD9:
							hotkeyText = "NUM9";
							break;
						case VK_MULTIPLY:
							hotkeyText = "NUM *";
							break;
						case VK_ADD:
							hotkeyText = "NUM +";
							break;
						case VK_SEPARATOR:
							hotkeyText = "NUM SEPR";
							break;
						case VK_SUBTRACT:
							hotkeyText = "NUM -";
							break;
						case VK_DECIMAL:
							hotkeyText = "NUM ,";
							break;
						case VK_DIVIDE:
							hotkeyText = "NUM /";
							break;

						case VK_NEXT:
							hotkeyText = "PG DN";
							break;
						case VK_PRIOR:
							hotkeyText = "PG UP";
							break;
						case VK_PAUSE:
							hotkeyText = "PAUSE";
							break;
						case VK_PRINT:
							hotkeyText = "PRINT";
							break;
						case VK_SNAPSHOT:
							hotkeyText = "PRT SC";
							break;
						case VK_RIGHT:
							hotkeyText = "RIGHT";
							break;
						case VK_SCROLL:
							hotkeyText = "SCRLK";
							break;
						case VK_SELECT:
							hotkeyText = "SELECT";
							break;
						case VK_SPACE:
							hotkeyText = "SPACE";
							break;
						case VK_TAB:
							hotkeyText = "TAB";
							break;
						case VK_UP:
							hotkeyText = "UP";
							break;


						case VK_F1:
							hotkeyText = "F1";
							break;
						case VK_F2:
							hotkeyText = "F2";
							break;
						case VK_F3:
							hotkeyText = "F3";
							break;
						case VK_F4:
							hotkeyText = "F4";
							break;
						case VK_F5:
							hotkeyText = "F5";
							break;
						case VK_F6:
							hotkeyText = "F6";
							break;
						case VK_F7:
							hotkeyText = "F7";
							break;
						case VK_F8:
							hotkeyText = "F8";
							break;
						case VK_F9:
							hotkeyText = "F9";
							break;
						case VK_F10:
							hotkeyText = "F10";
							break;
						case VK_F11:
							hotkeyText = "F11";
							break;
						case VK_F12:
							hotkeyText = "F12";
							break;


						case VK_OEM_1:
							hotkeyText = ";";
							break;
						case VK_OEM_PLUS:
							hotkeyText = "=";
							break;
						case VK_OEM_COMMA:
							hotkeyText = ",";
							break;
						case VK_OEM_MINUS:
							hotkeyText = "-";
							break;
						case VK_OEM_PERIOD:
							hotkeyText = ".";
							break;
						case VK_OEM_2:
							hotkeyText = "/";
							break;
						case VK_OEM_3:
							hotkeyText = "`";
							break;
						case VK_OEM_4:
							hotkeyText = "[";
							break;
						case VK_OEM_5:
							hotkeyText = "\\";
							break;
						case VK_OEM_6:
							hotkeyText = "]";
							break;
						case VK_OEM_7:
							hotkeyText = "'";
							break;
						case VK_OEM_8:
							hotkeyText = "*";
							break;
						case VK_OEM_102:
							hotkeyText = "<>";
							break;


						default:
							defaultHotkey[0] = (TCHAR)currentKey;
							defaultHotkey[1] = '\0';
							hotkeyText = defaultHotkey;
							break;
					}

					*hotkeySelected = true;
					*hotkey = currentKey;
					break;
				}
			}
		}
    }
	if (specialKey == 0)
		sprintf(hotkeyBuffer,  TEXT("Hotkey: %s"), hotkeyText);
	else
		sprintf(hotkeyBuffer,  TEXT("Hotkey: %s + %s"), hotkeySpecialText, hotkeyText);

	SetWindowText(selectMod == HOTKEYAUTOCLICKER ? mouseHotkeyButton : keyboardHotkeyButton, hotkeyBuffer);


	if (mouseHotkey == keyboardHotkey)
	{
		keysEqual = true;
		keyboardHotkeyTemp = mouseHotkey;
		UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
		RegisterHotKey(hWnd,
		MOUSECLICKHOTKEY,
		specialKey,
		*hotkey);
	}
	else
	{
		if (keysEqual && selectMod == HOTKEYAUTOCLICKER)
		{
			RegisterHotKey(hWnd,
				KEYBOARDPRESSHOTKEY,
				specialKey,
				keyboardHotkeyTemp);
			keysEqual = false;
		}

		RegisterHotKey(hWnd,
			selectMod == HOTKEYAUTOCLICKER ? MOUSECLICKHOTKEY : KEYBOARDPRESSHOTKEY,
			specialKey,
			*hotkey);
	}
}