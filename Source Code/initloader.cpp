#include "main.h"
#include <commdlg.h>
#include <stdio.h>



void LoadInit(HWND hWnd)
{
	if (isWindowsNT())
	{
		OPENFILENAMEW ofnLoadW = {0};
		ZeroMemory(&ofnLoadW, sizeof(ofnLoadW));
		WCHAR szFile[MAX_PATH] = L"";
		ofnLoadW.lStructSize = sizeof(ofnLoadW);
		ofnLoadW.hwndOwner = hWnd;
		ofnLoadW.lpstrFile = szFile;
		ofnLoadW.lpstrFile[0] = L'\0';
		ofnLoadW.nMaxFile = sizeof(szFile);
		ofnLoadW.lpstrFilter = L"INI (*.ini)\0*.ini\0All Files\0*.*\0";
		ofnLoadW.nFilterIndex = 1;
		ofnLoadW.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameW(&ofnLoadW))
		{
			WCHAR bufLoadW[30];

			static WCHAR
			bufLoadMouseHotkeySpecW[12],
			bufLoadMouseHotkeyW[20],
			bufLoadKeyboardHotkeySpecW[12],
			bufLoadKeyboardHotkeyW[20];


			GetPrivateProfileStringW(L"Mouse", L"MouseHotkeyNameSpecial", L"", bufLoadMouseHotkeySpecW, sizeof(bufLoadMouseHotkeySpecW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			mouseHotkeySpecialTextW = bufLoadMouseHotkeySpecW;

			GetPrivateProfileStringW(L"Mouse", L"MouseHotkeyKeySpecial", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			mouseSpecialKey = _wtoi(bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseHotkeyNameNormal", L"F5", bufLoadMouseHotkeyW, sizeof(bufLoadMouseHotkeyW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			mouseHotkeyTextW = bufLoadMouseHotkeyW;

			GetPrivateProfileStringW(L"Mouse", L"MouseHotkeyKeyNormal", L"116", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			mouseHotkey = _wtoi(bufLoadW);

			LoadHotkeyW(hWnd, mouseHotkeySpecialTextW, &mouseSpecialKey, mouseHotkeyTextW, &mouseHotkey, HOTKEYAUTOCLICKER);



			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalHour", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterHour, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalMin", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterMinute, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalSec", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterSecond, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalMilliSec", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterMilliSecond, bufLoadW);


			GetPrivateProfileStringW(L"Mouse", L"MouseLMB", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SendMessage(mouseLmB, CB_SETCURSEL, _wtoi(bufLoadW), 0);
			mouseButton = GetMouseButton(mouseLmB);

			GetPrivateProfileStringW(L"Mouse", L"MouseClickType", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SendMessage(mouseSingleOrDouble, CB_SETCURSEL, _wtoi(bufLoadW), 0);
			clickType = GetMouseClickType(mouseSingleOrDouble);


			GetPrivateProfileStringW(L"Mouse", L"MouseClickRepeatChecked", L"911", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			CheckRadioButton(hWnd, MOUSEREPEATINFINITY, MOUSEREPEATCOUNTDOWN, _wtoi(bufLoadW));

			GetPrivateProfileStringW(L"Mouse", L"MouseClickTimes", L"5", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseRepeatTimesEntry, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseClickTimerHour", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseRepeatTimerHour, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseClickTimerMin", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseRepeatTimerMinute, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseClickTimerSec", L"05", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseRepeatTimerSecond, bufLoadW);



			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyNameSpecial", L"", bufLoadKeyboardHotkeySpecW, sizeof(bufLoadKeyboardHotkeySpecW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			keyboardHotkeySpecialTextW = bufLoadKeyboardHotkeySpecW;

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeySpecial", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			keyboardSpecialKey = _wtoi(bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyNameNormal", L"F6", bufLoadKeyboardHotkeyW, sizeof(bufLoadKeyboardHotkeyW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			keyboardHotkeyTextW = bufLoadKeyboardHotkeyW;

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeyNormal", L"117", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			keyboardHotkey = _wtoi(bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardSelectedKey", L"13", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SendMessage(keyboardSelectedKey, CB_SETCURSEL, (WPARAM)_wtoi(bufLoadW), 0);
			keyboardKey = GetKeyboardKey(keyboardSelectedKey);

			LoadHotkeyW(hWnd, keyboardHotkeySpecialTextW, &keyboardSpecialKey, keyboardHotkeyTextW, &keyboardHotkey, HOTKEYAUTOPRESSER);


			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalHour", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterHour, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMin", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterMinute, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalSec", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterSecond, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMilliSec", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterMilliSecond, bufLoadW);


			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressRepeatChecked", L"933", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			CheckRadioButton(hWnd, KEYBOARDREPEATINFINITY, KEYBOARDREPEATCOUNTDOWN, _wtoi(bufLoadW));

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressTimes", L"5", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardRepeatTimesEntry, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerHour", L"00", bufLoadW,sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardRepeatTimerHour, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerMin", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardRepeatTimerMinute, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerSec", L"05", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardRepeatTimerSecond, bufLoadW);



			GetPrivateProfileStringW(L"Settings", L"Theme", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			themeOption = _wtoi(bufLoadW);
			SendMessage(themesList, CB_SETCURSEL, themeOption, 0);
			SelectTheme(themeOption);
			InvalidateRect(hWnd, NULL, TRUE);

			GetPrivateProfileStringW(L"Settings", L"RandomInterval", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(randomIntervalEnter, bufLoadW);

			GetPrivateProfileStringW(L"Settings", L"MouseHoldTime", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(holdTimeEnter, bufLoadW);

			GetPrivateProfileStringW(L"Settings", L"MinimizeOnSystemTray", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			isTrayChecked = _wtoi(bufLoadW);
			SendMessage(minimizeOnTray, BM_SETCHECK, isTrayChecked, 0);

			GetPrivateProfileStringW(L"Settings", L"AlwaysOnTop", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			isAlwaysOnTopChecked = _wtoi(bufLoadW);
			SendMessage(alwaysOnTop, BM_SETCHECK, isAlwaysOnTopChecked, 0);
			SetWindowPos(hWnd, (isAlwaysOnTopChecked == BST_CHECKED) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
	}

	else
	{
		OPENFILENAMEA ofnLoadA = {0};
		ZeroMemory(&ofnLoadA, sizeof(ofnLoadA));
		char szFile[MAX_PATH] = "";
		ofnLoadA.lStructSize = 76;
		ofnLoadA.hwndOwner = hWnd;
		ofnLoadA.lpstrFile = szFile;
		ofnLoadA.lpstrFile[0] = '\0';
		ofnLoadA.nMaxFile = sizeof(szFile);
		ofnLoadA.lpstrFilter = "INI (*.ini)\0*.ini\0All Files\0*.*\0";
		ofnLoadA.nFilterIndex = 1;
		ofnLoadA.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofnLoadA))
		{
			char bufLoadA[30];

			static char
			bufLoadMouseHotkeySpecA[12],
			bufLoadMouseHotkeyA[20],
			bufLoadKeyboardHotkeySpecA[12],
			bufLoadKeyboardHotkeyA[20];


			GetPrivateProfileStringA("Mouse", "MouseHotkeyNameSpecial", "", bufLoadMouseHotkeySpecA, sizeof(bufLoadMouseHotkeySpecA)/sizeof(char), ofnLoadA.lpstrFile);
			mouseHotkeySpecialTextA = bufLoadMouseHotkeySpecA;

			GetPrivateProfileStringA("Mouse", "MouseHotkeyKeySpecial", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			mouseSpecialKey = atoi(bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseHotkeyNameNormal", "F5", bufLoadMouseHotkeyA, sizeof(bufLoadMouseHotkeyA)/sizeof(char), ofnLoadA.lpstrFile);
			mouseHotkeyTextA = bufLoadMouseHotkeyA;

			GetPrivateProfileStringA("Mouse", "MouseHotkeyKeyNormal", "116", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			mouseHotkey = atoi(bufLoadA);

			LoadHotkeyA(hWnd, mouseHotkeySpecialTextA, &mouseSpecialKey, mouseHotkeyTextA, &mouseHotkey, HOTKEYAUTOCLICKER);



			GetPrivateProfileStringA("Mouse", "MouseIntervalHour", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterHour, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalMin", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterMinute, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalSec", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterSecond, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalMilliSec", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterMilliSecond, bufLoadA);


			GetPrivateProfileStringA("Mouse", "MouseLMB", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SendMessageA(mouseLmB, CB_SETCURSEL, atoi(bufLoadA), 0);
			mouseButton = GetMouseButton(mouseLmB);

			GetPrivateProfileStringA("Mouse", "MouseClickType", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SendMessageA(mouseSingleOrDouble, CB_SETCURSEL, atoi(bufLoadA), 0);
			clickType = GetMouseClickType(mouseSingleOrDouble);


			GetPrivateProfileStringA("Mouse", "MouseClickRepeatChecked", "911", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			CheckRadioButton(hWnd, MOUSEREPEATINFINITY, MOUSEREPEATCOUNTDOWN, atoi(bufLoadA));

			GetPrivateProfileStringA("Mouse", "MouseClickTimes", "5", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseRepeatTimesEntry, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseClickTimerHour", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseRepeatTimerHour, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseClickTimerMin", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseRepeatTimerMinute, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseClickTimerSec", "05", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseRepeatTimerSecond, bufLoadA);



			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeyNameSpecial", "", bufLoadKeyboardHotkeySpecA, sizeof(bufLoadKeyboardHotkeySpecA)/sizeof(char), ofnLoadA.lpstrFile);
			keyboardHotkeySpecialTextA = bufLoadKeyboardHotkeySpecA;

			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeyKeySpecial", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			keyboardSpecialKey = atoi(bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeyNameNormal", "F6", bufLoadKeyboardHotkeyA, sizeof(bufLoadKeyboardHotkeyA)/sizeof(char), ofnLoadA.lpstrFile);
			keyboardHotkeyTextA = bufLoadKeyboardHotkeyA;

			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeyKeyNormal", "117", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			keyboardHotkey = atoi(bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardSelectedKey", "13", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SendMessageA(keyboardSelectedKey, CB_SETCURSEL, (WPARAM)atoi(bufLoadA), 0);
			keyboardKey = GetKeyboardKey(keyboardSelectedKey);

			LoadHotkeyA(hWnd, keyboardHotkeySpecialTextA, &keyboardSpecialKey, keyboardHotkeyTextA, &keyboardHotkey, HOTKEYAUTOPRESSER);


			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalHour", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterHour, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalMin", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterMinute, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalSec", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterSecond, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalMilliSec", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterMilliSecond, bufLoadA);


			GetPrivateProfileStringA("Keyboard", "KeyboardPressRepeatChecked", "933", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			CheckRadioButton(hWnd, KEYBOARDREPEATINFINITY, KEYBOARDREPEATCOUNTDOWN, atoi(bufLoadA));

			GetPrivateProfileStringA("Keyboard", "KeyboardPressTimes", "5", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardRepeatTimesEntry, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardPressTimerHour", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardRepeatTimerHour, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardPressTimerMin", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardRepeatTimerMinute, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardPressTimerSec", "05", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardRepeatTimerSecond, bufLoadA);



			GetPrivateProfileStringA("Settings", "Theme", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			themeOption = atoi(bufLoadA);
			SendMessageA(themesList, CB_SETCURSEL, themeOption, 0);
			SelectTheme(themeOption);
			InvalidateRect(hWnd, NULL, TRUE);

			GetPrivateProfileStringA("Settings", "RandomInterval", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(randomIntervalEnter, bufLoadA);

			GetPrivateProfileStringA("Settings", "MouseHoldTime", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(holdTimeEnter, bufLoadA);

			GetPrivateProfileStringA("Settings", "MinimizeOnSystemTray", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			isTrayChecked = atoi(bufLoadA);
			SendMessageA(minimizeOnTray, BM_SETCHECK, isTrayChecked, 0);

			GetPrivateProfileStringA("Settings", "AlwaysOnTop", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			isAlwaysOnTopChecked = atoi(bufLoadA);
			SendMessageA(alwaysOnTop, BM_SETCHECK, isAlwaysOnTopChecked, 0);
			SetWindowPos(hWnd, (isAlwaysOnTopChecked == BST_CHECKED) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
	}
}



void SaveInit(HWND hWnd)
{
	if (isWindowsNT())
	{
		OPENFILENAMEW ofnSaveW = {0};
		ZeroMemory(&ofnSaveW, sizeof(ofnSaveW));
		WCHAR szFile[MAX_PATH] = L"KB65 Autoclicker.ini";
		ofnSaveW.lStructSize = sizeof(ofnSaveW);
		ofnSaveW.hwndOwner = hWnd;
		ofnSaveW.lpstrFilter = L"INI (*.ini)\0*.ini\0";
		ofnSaveW.lpstrFile = szFile;
		ofnSaveW.nMaxFile = sizeof(szFile);
		ofnSaveW.Flags = OFN_OVERWRITEPROMPT;
		ofnSaveW.lpstrDefExt = L"ini";

		if (GetSaveFileNameW(&ofnSaveW))
		{
			WCHAR bufSaveW[30];

			static WCHAR
			bufSaveMouseHotkeySpecW[12],
			bufSaveMouseHotkeyW[20],
			bufSaveKeyboardHotkeySpecW[12],
			bufSaveKeyboardHotkeyW[20];


			wcscpy(bufSaveMouseHotkeySpecW, mouseHotkeySpecialTextW);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyNameSpecial", bufSaveMouseHotkeySpecW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%u", mouseSpecialKey);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyKeySpecial", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveMouseHotkeyW, mouseHotkeyTextW);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyNameNormal", bufSaveMouseHotkeyW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%u", mouseHotkey);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyKeyNormal", bufSaveW, ofnSaveW.lpstrFile);


			GetWindowTextW(mouseEnterHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalSec", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterMilliSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalMilliSec", bufSaveW, ofnSaveW.lpstrFile);


			mouseButton = SendMessage(mouseLmB, CB_GETCURSEL, 0, 0);
			swprintf(bufSaveW, L"%u", mouseButton);
			WritePrivateProfileStringW(L"Mouse", L"MouseLMB", bufSaveW, ofnSaveW.lpstrFile);

			clickType = SendMessage(mouseSingleOrDouble, CB_GETCURSEL, 0, 0);
			swprintf(bufSaveW, L"%u", clickType);
			WritePrivateProfileStringW(L"Mouse", L"MouseClickType", bufSaveW, ofnSaveW.lpstrFile);


			int selectedMouse;
			if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 911;
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 912;
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 915;
			swprintf(bufSaveW, L"%d", selectedMouse);
			WritePrivateProfileStringW(L"Mouse", L"MouseClickRepeatChecked", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseRepeatTimesEntry, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseClickTimes", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseRepeatTimerHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseClickTimerHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseRepeatTimerMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseClickTimerMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseRepeatTimerSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseClickTimerSec", bufSaveW, ofnSaveW.lpstrFile);



			wcscpy(bufSaveKeyboardHotkeySpecW, keyboardHotkeySpecialTextW);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyNameSpecial", bufSaveKeyboardHotkeySpecW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%u", keyboardSpecialKey);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeySpecial", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveKeyboardHotkeyW, keyboardHotkeyTextW);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyNameNormal", bufSaveKeyboardHotkeyW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%u", keyboardHotkey);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeyNormal", bufSaveW, ofnSaveW.lpstrFile);

			keyboardKey = SendMessage(keyboardSelectedKey, CB_GETCURSEL, 0, 0);
			swprintf(bufSaveW, L"%u", keyboardKey);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardSelectedKey", bufSaveW, ofnSaveW.lpstrFile);



			GetWindowTextW(keyboardEnterHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalSec", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterMilliSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMilliSec", bufSaveW, ofnSaveW.lpstrFile);


			int selectedKeyboard;
			if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 933;
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 934;
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 937;
			swprintf(bufSaveW, L"%d", selectedKeyboard);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressRepeatChecked", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardRepeatTimesEntry, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressTimes", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardRepeatTimerHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardRepeatTimerMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardRepeatTimerSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressTimerSec", bufSaveW, ofnSaveW.lpstrFile);



			swprintf(bufSaveW, L"%d", themeOption);
			WritePrivateProfileStringW(L"Settings", L"Theme", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(randomIntervalEnter, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Settings", L"RandomInterval", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(holdTimeEnter, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Settings", L"MouseHoldTime", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", isTrayChecked);
			WritePrivateProfileStringW(L"Settings", L"MinimizeOnSystemTray", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", isAlwaysOnTopChecked);
			WritePrivateProfileStringW(L"Settings", L"AlwaysOnTop", bufSaveW, ofnSaveW.lpstrFile);
		}
	}
	else
	{
		OPENFILENAMEA ofnSaveA = {0};
		ZeroMemory(&ofnSaveA, sizeof(ofnSaveA));
		char szFile[MAX_PATH] = "KB65 Autoclicker.ini";
		ofnSaveA.lStructSize = 76;
		ofnSaveA.hwndOwner = hWnd;
		ofnSaveA.lpstrFilter = "INI (*.ini)\0*.ini\0";
		ofnSaveA.lpstrFile = szFile;
		ofnSaveA.nMaxFile = sizeof(szFile);
		ofnSaveA.Flags = OFN_OVERWRITEPROMPT;
		ofnSaveA.lpstrDefExt = "ini";

		if (GetSaveFileNameA(&ofnSaveA))
		{
			char bufSaveA[30];

			static char
			bufSaveMouseHotkeySpecA[12],
			bufSaveMouseHotkeyA[20],
			bufSaveKeyboardHotkeySpecA[12],
			bufSaveKeyboardHotkeyA[20];


			strcpy(bufSaveMouseHotkeySpecA, mouseHotkeySpecialTextA);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyNameSpecial", bufSaveMouseHotkeySpecA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%u", mouseSpecialKey);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyKeySpecial", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveMouseHotkeyA, mouseHotkeyTextA);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyNameNormal", bufSaveMouseHotkeyA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%u", mouseHotkey);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyKeyNormal", bufSaveA, ofnSaveA.lpstrFile);


			GetWindowTextA(mouseEnterHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalSec", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterMilliSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalMilliSec", bufSaveA, ofnSaveA.lpstrFile);


			mouseButton = SendMessage(mouseLmB, CB_GETCURSEL, 0, 0);
			sprintf(bufSaveA, "%u", mouseButton);
			WritePrivateProfileStringA("Mouse", "MouseLMB", bufSaveA, ofnSaveA.lpstrFile);

			clickType = SendMessage(mouseSingleOrDouble, CB_GETCURSEL, 0, 0);
			sprintf(bufSaveA, "%u", clickType);
			WritePrivateProfileStringA("Mouse", "MouseClickType", bufSaveA, ofnSaveA.lpstrFile);


			int selectedMouse;
			if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 911;
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 912;
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedMouse = 915;
			sprintf(bufSaveA, "%d", selectedMouse);
			WritePrivateProfileStringA("Mouse", "MouseClickRepeatChecked", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseRepeatTimesEntry, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseClickTimes", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseRepeatTimerHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseClickTimerHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseRepeatTimerMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseClickTimerMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseRepeatTimerSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseClickTimerSec", bufSaveA, ofnSaveA.lpstrFile);



			strcpy(bufSaveKeyboardHotkeySpecA, keyboardHotkeySpecialTextA);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyNameSpecial", bufSaveKeyboardHotkeySpecA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%u", keyboardSpecialKey);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyKeySpecial", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveKeyboardHotkeyA, keyboardHotkeyTextA);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyNameNormal", bufSaveKeyboardHotkeyA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%u", keyboardHotkey);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyKeyNormal", bufSaveA, ofnSaveA.lpstrFile);

			keyboardKey = SendMessage(keyboardSelectedKey, CB_GETCURSEL, 0, 0);
			sprintf(bufSaveA, "%u", keyboardKey);
			WritePrivateProfileStringA("Keyboard", "KeyboardSelectedKey", bufSaveA, ofnSaveA.lpstrFile);



			GetWindowTextA(keyboardEnterHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalSec", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterMilliSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalMilliSec", bufSaveA, ofnSaveA.lpstrFile);


			int selectedKeyboard;
			if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 933;
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 934;
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				selectedKeyboard = 937;
			sprintf(bufSaveA, "%d", selectedKeyboard);
			WritePrivateProfileStringA("Keyboard", "KeyboardPressRepeatChecked", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardRepeatTimesEntry, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardPressTimes", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardRepeatTimerHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardPressTimerHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardRepeatTimerMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardPressTimerMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardRepeatTimerSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardPressTimerSec", bufSaveA, ofnSaveA.lpstrFile);



			sprintf(bufSaveA, "%d", themeOption);
			WritePrivateProfileStringA("Settings", "Theme", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(randomIntervalEnter, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Settings", "RandomInterval", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(holdTimeEnter, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Settings", "MouseHoldTime", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", isTrayChecked);
			WritePrivateProfileStringA("Settings", "MinimizeOnSystemTray", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", isAlwaysOnTopChecked);
			WritePrivateProfileStringA("Settings", "AlwaysOnTop", bufSaveA, ofnSaveA.lpstrFile);
		}
	}
}