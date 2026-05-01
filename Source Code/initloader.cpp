#include "KB65 Autoclicker.h"
#include <commdlg.h>





void LoadIni(HWND hWnd, int mod, HDROP hDropFiles)
{
	if (isWindowsNT())
	{
		WCHAR szFile[MAX_PATH] = L"";
		OPENFILENAMEW ofnLoadW = {0};

		if (mod == FROM_DROPFILES)
		{
			if (DragQueryFileW(hDropFiles, 0, szFile, MAX_PATH))
			{
				const wchar_t* extensionW = PathFindExtensionW(szFile);
				if (_wcsicmp(extensionW, L".ini") == 0)
				{
					ofnLoadW.lpstrFile = szFile;
					goto skip_gofn_func_for_dropfilesW;
				}
				else return;
			}
			else return;
		}

		// Windows NT 4.0 only
		if (winverOld.dwMajorVersion == 4 && winverOld.dwMinorVersion == 0 && winverOld.dwPlatformId == VER_PLATFORM_WIN32_NT)
			ofnLoadW.lStructSize = OPENFILENAME_SIZE_VERSION_400;
		else
			ofnLoadW.lStructSize = sizeof(ofnLoadW);
		ofnLoadW.hwndOwner = hWnd;
		ofnLoadW.lpstrFile = szFile;
		ofnLoadW.nMaxFile = sizeof(szFile);
		ofnLoadW.lpstrFilter = L"INI (*.ini)\0*.ini\0All Files\0*.*\0";
		ofnLoadW.nFilterIndex = 1;
		ofnLoadW.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

		if (GetOpenFileNameW(&ofnLoadW))
		{
skip_gofn_func_for_dropfilesW:
			WCHAR bufLoadW[30];

			static WCHAR
			bufLoadMouseHotkeySpecW[12],
			bufLoadMouseHotkeyW[20],
			bufLoadKeyboardHotkeySpecW[12],
			bufLoadKeyboardHotkeyW[20];


			if (GetPrivateProfileStringW(L"Mouse", L"MouseHotkeySpecKeyName", L"", bufLoadMouseHotkeySpecW, sizeof(bufLoadMouseHotkeySpecW)/sizeof(wchar_t), ofnLoadW.lpstrFile) == 0)
				return; // might be broken or inappropriate .ini file. skip loading process.

			mouseHotkeySpecialTextW = bufLoadMouseHotkeySpecW;
			mouseSpecialKey = GetPrivateProfileIntW(L"Mouse", L"MouseHotkeySpecKeyValue", 0, ofnLoadW.lpstrFile);
			
			GetPrivateProfileStringW(L"Mouse", L"MouseHotkeyKeyName", L"F5", bufLoadMouseHotkeyW, sizeof(bufLoadMouseHotkeyW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			mouseHotkeyTextW = bufLoadMouseHotkeyW;
			mouseHotkey = GetPrivateProfileIntW(L"Mouse", L"MouseHotkeyKeyValue", 116, ofnLoadW.lpstrFile);

			LoadHotkeyW(hWnd, mouseHotkeySpecialTextW, &mouseSpecialKey, mouseHotkeyTextW, HOTKEYAUTOCLICKER);


			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalHour", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterHour, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalMin", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterMinute, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalSec", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterSecond, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseIntervalMilliSec", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseEnterMilliSecond, bufLoadW);

			SendMessage(mouseLmB, CB_SETCURSEL, GetPrivateProfileIntW(L"Mouse", L"MouseLMB", 0, ofnLoadW.lpstrFile), 0);
			mouseButton = GetMouseButton(mouseLmB);

			SendMessage(mouseClickType, CB_SETCURSEL, GetPrivateProfileIntW(L"Mouse", L"MouseClickType", 0, ofnLoadW.lpstrFile), 0);
			clickType = GetMouseClickType(mouseClickType);

			CheckRadioButton(hWnd, MOUSEREPEATINFINITY, MOUSEREPEATCOUNTDOWN, GetPrivateProfileIntW(L"Mouse", L"MouseClickRepeatChecked", 911, ofnLoadW.lpstrFile));

			GetPrivateProfileStringW(L"Mouse", L"MouseClickTimes", L"5", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseRepeatTimesEntry, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseCountdownHour", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseCountdownHour, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseCountdownMin", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseCountdownMinute, bufLoadW);

			GetPrivateProfileStringW(L"Mouse", L"MouseCountdownSec", L"05", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(mouseCountdownSecond, bufLoadW);



			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeySpecKeyName", L"", bufLoadKeyboardHotkeySpecW, sizeof(bufLoadKeyboardHotkeySpecW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			keyboardHotkeySpecialTextW = bufLoadKeyboardHotkeySpecW;
			keyboardSpecialKey = GetPrivateProfileIntW(L"Keyboard", L"KeyboardHotkeySpecKeyValue", 1, ofnLoadW.lpstrFile);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeyName", L"F6", bufLoadKeyboardHotkeyW, sizeof(bufLoadKeyboardHotkeyW)/sizeof(wchar_t), ofnLoadW.lpstrFile);
			keyboardHotkeyTextW = bufLoadKeyboardHotkeyW;
			keyboardHotkey = GetPrivateProfileIntW(L"Keyboard", L"KeyboardHotkeyKeyValue", 117, ofnLoadW.lpstrFile);

			LoadHotkeyW(hWnd, keyboardHotkeySpecialTextW, &keyboardSpecialKey, keyboardHotkeyTextW, HOTKEYAUTOPRESSER);


			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalHour", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterHour, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMin", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterMinute, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalSec", L"1", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterSecond, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMilliSec", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardEnterMilliSecond, bufLoadW);

			keyboardKey = GetPrivateProfileIntW(L"Keyboard", L"KeyboardSelectedKey", (int)'0', ofnLoadW.lpstrFile);
			int totalEntryCount = (int)SendMessage(keyboardSelectedKey, CB_GETCOUNT, 0, 0);
			LRESULT myData = 0;
			for (int index = 0; index < totalEntryCount; ++index)
			{
				myData = SendMessage(keyboardSelectedKey, CB_GETITEMDATA, (WPARAM)index, 0);
				if (keyboardKey == myData)
				{
					SendMessage(keyboardSelectedKey, CB_SETCURSEL, index, 0);
					break;
				}
			}
			if (keyboardKey != myData)
			{
				SendMessage(keyboardSelectedKey, CB_SETCURSEL, 0, 0);
				keyboardKey = '0';
			}
			UpdateHotkeysAfterLangChange();

			isKeyboardHoldMode = GetPrivateProfileIntW(L"Keyboard", L"KeyboardHoldModeActive", 0, ofnLoadW.lpstrFile);
			SendMessage(keyboardHoldCheckBox, BM_SETCHECK, isKeyboardHoldMode, 0);

			CheckRadioButton(hWnd, KEYBOARDREPEATINFINITY, KEYBOARDREPEATCOUNTDOWN, GetPrivateProfileIntW(L"Keyboard", L"KeyboardPressRepeatChecked", 934, ofnLoadW.lpstrFile));

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardPressTimes", L"5", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardRepeatTimesEntry, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardCountdownHour", L"00", bufLoadW,sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardCountdownHour, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardCountdownMin", L"00", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardCountdownMinute, bufLoadW);

			GetPrivateProfileStringW(L"Keyboard", L"KeyboardCountdownSec", L"05", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(keyboardCountdownSecond, bufLoadW);

			mouseActive = !GetPrivateProfileIntW(L"Mouse", L"MouseActivated", 0 ,ofnLoadW.lpstrFile);
			SendMessageW(hWnd, WM_COMMAND, ACTIVATEMOUSE, 0);

			keyboardActive = !GetPrivateProfileIntW(L"Keyboard", L"KeyboardActivated", 0, ofnLoadW.lpstrFile);
			SendMessageW(hWnd, WM_COMMAND, ACTIVATEKEYBOARD, 0);



			themeOption = GetPrivateProfileIntW(L"Settings", L"Theme", 0, ofnLoadW.lpstrFile);
			SendMessage(themesList, CB_SETCURSEL, themeOption, 0);
			SelectTheme(hWnd);
			InvalidateRect(hWnd, NULL, true);

			GetPrivateProfileStringW(L"Settings", L"RandomInterval", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(randomIntervalEnter, bufLoadW);

			GetPrivateProfileStringW(L"Settings", L"HoldTime", L"0", bufLoadW, sizeof(bufLoadW)/sizeof(bufLoadW[0]), ofnLoadW.lpstrFile);
			SetWindowTextW(holdTimeEnter, bufLoadW);

			isTrayChecked = GetPrivateProfileIntW(L"Settings", L"MinimizeOnSystemTray", 1, ofnLoadW.lpstrFile);
			SendMessage(minimizeOnTray, BM_SETCHECK, isTrayChecked, 0);

			isAlwaysOnTopChecked = GetPrivateProfileIntW(L"Settings", L"AlwaysOnTop", 0, ofnLoadW.lpstrFile);
			SendMessage(alwaysOnTop, BM_SETCHECK, isAlwaysOnTopChecked, 0);
			SetWindowPos(hWnd, (isAlwaysOnTopChecked == BST_CHECKED) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

			isDisableTooltipsChecked = GetPrivateProfileIntW(L"Settings", L"DisabledTooltips", 0, ofnLoadW.lpstrFile);
			if (isDisableTooltipsChecked != SendMessage(disableTooltips, BM_GETCHECK, 0, 0))
				Tooltips(hWnd, !isDisableTooltipsChecked);
			SendMessage(disableTooltips, BM_SETCHECK, isDisableTooltipsChecked, 0);
		}
	}

	else
	{
		char szFile[MAX_PATH] = "";
		OPENFILENAMEA ofnLoadA = {0};

		if (mod == FROM_DROPFILES)
		{
			if (DragQueryFileA(hDropFiles, 0, szFile, MAX_PATH))
			{
				const char* extensionA = PathFindExtensionA(szFile);
				if (_stricmp(extensionA, ".ini") == 0)
				{
					ofnLoadA.lpstrFile = szFile;
					goto skip_gofn_func_for_dropfilesA;
				}
				else return;
			}
			else return;
		}

		ofnLoadA.lStructSize = 76;
		ofnLoadA.hwndOwner = hWnd;
		ofnLoadA.lpstrFile = szFile;
		ofnLoadA.nMaxFile = sizeof(szFile);
		ofnLoadA.lpstrFilter = "INI (*.ini)\0*.ini\0All Files\0*.*\0";
		ofnLoadA.nFilterIndex = 1;
		ofnLoadA.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofnLoadA))
		{
skip_gofn_func_for_dropfilesA:
			char bufLoadA[30];

			static char
			bufLoadMouseHotkeySpecA[12],
			bufLoadMouseHotkeyA[20],
			bufLoadKeyboardHotkeySpecA[12],
			bufLoadKeyboardHotkeyA[20];


			if (GetPrivateProfileStringA("Mouse", "MouseHotkeySpecKeyName", "", bufLoadMouseHotkeySpecA, sizeof(bufLoadMouseHotkeySpecA)/sizeof(char), ofnLoadA.lpstrFile) == 0)
				return; // might be broken or inappropriate .ini file. skip loading process.
			mouseHotkeySpecialTextA = bufLoadMouseHotkeySpecA;
			mouseSpecialKey = GetPrivateProfileIntA("Mouse", "MouseHotkeySpecKeyValue", 0, ofnLoadA.lpstrFile);
			
			GetPrivateProfileStringA("Mouse", "MouseHotkeyKeyName", "F5", bufLoadMouseHotkeyA, sizeof(bufLoadMouseHotkeyA)/sizeof(char), ofnLoadA.lpstrFile);
			mouseHotkeyTextA = bufLoadMouseHotkeyA;
			mouseHotkey = GetPrivateProfileIntA("Mouse", "MouseHotkeyKeyValue", 116, ofnLoadA.lpstrFile);

			LoadHotkeyA(hWnd, mouseHotkeySpecialTextA, &mouseSpecialKey, mouseHotkeyTextA, HOTKEYAUTOCLICKER);


			GetPrivateProfileStringA("Mouse", "MouseIntervalHour", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterHour, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalMin", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterMinute, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalSec", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterSecond, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseIntervalMilliSec", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseEnterMilliSecond, bufLoadA);

			SendMessageA(mouseLmB, CB_SETCURSEL, GetPrivateProfileIntA("Mouse", "MouseLMB", 0, ofnLoadA.lpstrFile), 0);
			mouseButton = GetMouseButton(mouseLmB);

			SendMessageA(mouseClickType, CB_SETCURSEL, GetPrivateProfileIntA("Mouse", "MouseClickType", 0, ofnLoadA.lpstrFile), 0);
			clickType = GetMouseClickType(mouseClickType);

			CheckRadioButton(hWnd, MOUSEREPEATINFINITY, MOUSEREPEATCOUNTDOWN, GetPrivateProfileIntA("Mouse", "MouseClickRepeatChecked", 911, ofnLoadA.lpstrFile));

			GetPrivateProfileStringA("Mouse", "MouseClickTimes", "5", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseRepeatTimesEntry, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseCountdownHour", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseCountdownHour, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseCountdownMin", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseCountdownMinute, bufLoadA);

			GetPrivateProfileStringA("Mouse", "MouseCountdownSec", "05", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(mouseCountdownSecond, bufLoadA);



			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeySpecKeyName", "", bufLoadKeyboardHotkeySpecA, sizeof(bufLoadKeyboardHotkeySpecA)/sizeof(char), ofnLoadA.lpstrFile);
			keyboardHotkeySpecialTextA = bufLoadKeyboardHotkeySpecA;
			keyboardSpecialKey = GetPrivateProfileIntA("Keyboard", "KeyboardHotkeySpecKeyValue", 1, ofnLoadA.lpstrFile);

			GetPrivateProfileStringA("Keyboard", "KeyboardHotkeyKeyName", "F6", bufLoadKeyboardHotkeyA, sizeof(bufLoadKeyboardHotkeyA)/sizeof(char), ofnLoadA.lpstrFile);
			keyboardHotkeyTextA = bufLoadKeyboardHotkeyA;
			keyboardHotkey = GetPrivateProfileIntA("Keyboard", "KeyboardHotkeyKeyValue", 117, ofnLoadA.lpstrFile);

			LoadHotkeyA(hWnd, keyboardHotkeySpecialTextA, &keyboardSpecialKey, keyboardHotkeyTextA, HOTKEYAUTOPRESSER);


			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalHour", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterHour, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalMin", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterMinute, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalSec", "1", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterSecond, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardIntervalMilliSec", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardEnterMilliSecond, bufLoadA);

			keyboardKey = GetPrivateProfileIntA("Keyboard", "KeyboardSelectedKey", (int)'0', ofnLoadA.lpstrFile);
			int totalEntryCount = (int)SendMessage(keyboardSelectedKey, CB_GETCOUNT, 0, 0);
			LRESULT myData = 0;
			for (int index = 0; index < totalEntryCount; ++index)
			{
				myData = SendMessage(keyboardSelectedKey, CB_GETITEMDATA, (WPARAM)index, 0);
				if (keyboardKey == myData)
				{
					SendMessage(keyboardSelectedKey, CB_SETCURSEL, index, 0);
					break;
				}
			}
			if (keyboardKey != myData)
			{
				SendMessage(keyboardSelectedKey, CB_SETCURSEL, 0, 0);
				keyboardKey = '0';
			}
			UpdateHotkeysAfterLangChange();

			isKeyboardHoldMode = GetPrivateProfileIntA("Keyboard", "KeyboardHoldModeActive", 0, ofnLoadA.lpstrFile);
			SendMessageA(keyboardHoldCheckBox, BM_SETCHECK, isKeyboardHoldMode, 0);

			CheckRadioButton(hWnd, KEYBOARDREPEATINFINITY, KEYBOARDREPEATCOUNTDOWN, GetPrivateProfileIntA("Keyboard", "KeyboardPressRepeatChecked", 934, ofnLoadA.lpstrFile));

			GetPrivateProfileStringA("Keyboard", "KeyboardPressTimes", "5", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardRepeatTimesEntry, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardCountdownHour", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardCountdownHour, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardCountdownMin", "00", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardCountdownMinute, bufLoadA);

			GetPrivateProfileStringA("Keyboard", "KeyboardCountdownSec", "05", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(keyboardCountdownSecond, bufLoadA);

			mouseActive = !GetPrivateProfileIntA("Mouse", "MouseActivated", 0, ofnLoadA.lpstrFile);
			SendMessageA(hWnd, WM_COMMAND, ACTIVATEMOUSE, 0);

			keyboardActive = !GetPrivateProfileIntA("Keyboard", "KeyboardActivated", 0, ofnLoadA.lpstrFile);
			SendMessageA(hWnd, WM_COMMAND, ACTIVATEKEYBOARD, 0); 



			themeOption = GetPrivateProfileIntA("Settings", "Theme", 0, ofnLoadA.lpstrFile);
			SendMessageA(themesList, CB_SETCURSEL, themeOption, 0);
			SelectTheme(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);

			GetPrivateProfileStringA("Settings", "RandomInterval", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(randomIntervalEnter, bufLoadA);

			GetPrivateProfileStringA("Settings", "HoldTime", "0", bufLoadA, sizeof(bufLoadA)/sizeof(bufLoadA[0]), ofnLoadA.lpstrFile);
			SetWindowTextA(holdTimeEnter, bufLoadA);

			isTrayChecked = GetPrivateProfileIntA("Settings", "MinimizeOnSystemTray", 1, ofnLoadA.lpstrFile);
			SendMessageA(minimizeOnTray, BM_SETCHECK, isTrayChecked, 0);

			isAlwaysOnTopChecked = GetPrivateProfileIntA("Settings", "AlwaysOnTop", 0, ofnLoadA.lpstrFile);
			SendMessageA(alwaysOnTop, BM_SETCHECK, isAlwaysOnTopChecked, 0);
			SetWindowPos(hWnd, (isAlwaysOnTopChecked == BST_CHECKED) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

			isDisableTooltipsChecked = GetPrivateProfileIntA("Settings", "DisabledTooltips", 0, ofnLoadA.lpstrFile);
			if (isDisableTooltipsChecked != SendMessage(disableTooltips, BM_GETCHECK, 0, 0))
				Tooltips(hWnd, !isDisableTooltipsChecked);
			SendMessage(disableTooltips, BM_SETCHECK, isDisableTooltipsChecked, 0);
		}
	}
}



void SaveIni(HWND hWnd)
{
	if (isWindowsNT())
	{
		WCHAR szFile[MAX_PATH] = L"KB65 Autoclicker.ini";
		OPENFILENAMEW ofnSaveW = {0};

		// Windows NT 4.0 only
		if (winverOld.dwMajorVersion == 4 && winverOld.dwMinorVersion == 0 && winverOld.dwPlatformId == VER_PLATFORM_WIN32_NT)
			ofnSaveW.lStructSize = OPENFILENAME_SIZE_VERSION_400;
		else
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


			swprintf(bufSaveW, L"%d", mouseActive);
			WritePrivateProfileStringW(L"Mouse", L"MouseActivated", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveMouseHotkeySpecW, mouseHotkeySpecialTextW);
			swprintf(bufSaveW, L"%u", mouseSpecialKey);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeySpecKeyName", bufSaveMouseHotkeySpecW, ofnSaveW.lpstrFile);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeySpecKeyValue", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveMouseHotkeyW, mouseHotkeyTextW);
			swprintf(bufSaveW, L"%u", mouseHotkey);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyKeyName", bufSaveMouseHotkeyW, ofnSaveW.lpstrFile);
			WritePrivateProfileStringW(L"Mouse", L"MouseHotkeyKeyValue", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalSec", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseEnterMilliSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseIntervalMilliSec", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", mouseButton);
			WritePrivateProfileStringW(L"Mouse", L"MouseLMB", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", clickType);
			WritePrivateProfileStringW(L"Mouse", L"MouseClickType", bufSaveW, ofnSaveW.lpstrFile);


			if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", MOUSEREPEATINFINITY);
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", MOUSEREPEATTIMES);
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", MOUSEREPEATCOUNTDOWN);
			else // Default value
				swprintf(bufSaveW, L"%d", MOUSEREPEATINFINITY);
			WritePrivateProfileStringW(L"Mouse", L"MouseClickRepeatChecked", bufSaveW, ofnSaveW.lpstrFile);


			GetWindowTextW(mouseRepeatTimesEntry, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseClickTimes", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseCountdownHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseCountdownHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseCountdownMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseCountdownMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(mouseCountdownSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Mouse", L"MouseCountdownSec", bufSaveW, ofnSaveW.lpstrFile);



			swprintf(bufSaveW, L"%d", keyboardActive);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardActivated", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveKeyboardHotkeySpecW, keyboardHotkeySpecialTextW);
			swprintf(bufSaveW, L"%u", keyboardSpecialKey);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeySpecKeyName", bufSaveKeyboardHotkeySpecW, ofnSaveW.lpstrFile);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeySpecKeyValue", bufSaveW, ofnSaveW.lpstrFile);

			wcscpy(bufSaveKeyboardHotkeyW, keyboardHotkeyTextW);
			swprintf(bufSaveW, L"%u", keyboardHotkey);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeyName", bufSaveKeyboardHotkeyW, ofnSaveW.lpstrFile);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHotkeyKeyValue", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", (int)SendMessage(keyboardSelectedKey, CB_GETITEMDATA, (int)SendMessage(keyboardSelectedKey, CB_GETCURSEL, 0, 0), 0));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardSelectedKey", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", (int)isKeyboardHoldMode);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardHoldModeActive", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalSec", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardEnterMilliSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardIntervalMilliSec", bufSaveW, ofnSaveW.lpstrFile);


			if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", KEYBOARDREPEATINFINITY);
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", KEYBOARDREPEATTIMES);
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				swprintf(bufSaveW, L"%d", KEYBOARDREPEATCOUNTDOWN);
			else // Default value
				swprintf(bufSaveW, L"%d", KEYBOARDREPEATINFINITY);
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressRepeatChecked", bufSaveW, ofnSaveW.lpstrFile);


			GetWindowTextW(keyboardRepeatTimesEntry, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardPressTimes", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardCountdownHour, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardCountdownHour", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardCountdownMinute, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardCountdownMin", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(keyboardCountdownSecond, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Keyboard", L"KeyboardCountdownSec", bufSaveW, ofnSaveW.lpstrFile);



			swprintf(bufSaveW, L"%d", themeOption);
			WritePrivateProfileStringW(L"Settings", L"Theme", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(randomIntervalEnter, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Settings", L"RandomInterval", bufSaveW, ofnSaveW.lpstrFile);

			GetWindowTextW(holdTimeEnter, bufSaveW, sizeof(bufSaveW)/sizeof(bufSaveW[0]));
			WritePrivateProfileStringW(L"Settings", L"HoldTime", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", (int)isAlwaysOnTopChecked);
			WritePrivateProfileStringW(L"Settings", L"AlwaysOnTop", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", (int)isTrayChecked);
			WritePrivateProfileStringW(L"Settings", L"MinimizeOnSystemTray", bufSaveW, ofnSaveW.lpstrFile);

			swprintf(bufSaveW, L"%d", (int)isDisableTooltipsChecked);
			WritePrivateProfileStringW(L"Settings", L"DisabledTooltips", bufSaveW, ofnSaveW.lpstrFile);
		}
	}
	else
	{
		char szFile[MAX_PATH] = "KB65 Autoclicker.ini";
		OPENFILENAMEA ofnSaveA = {0};
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


			sprintf(bufSaveA, "%d", mouseActive);
			WritePrivateProfileStringA("Mouse", "MouseActivated", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveMouseHotkeySpecA, mouseHotkeySpecialTextA);
			sprintf(bufSaveA, "%u", mouseSpecialKey);
			WritePrivateProfileStringA("Mouse", "MouseHotkeySpecKeyName", bufSaveMouseHotkeySpecA, ofnSaveA.lpstrFile);
			WritePrivateProfileStringA("Mouse", "MouseHotkeySpecKeyValue", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveMouseHotkeyA, mouseHotkeyTextA);
			sprintf(bufSaveA, "%u", mouseHotkey);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyKeyName", bufSaveMouseHotkeyA, ofnSaveA.lpstrFile);
			WritePrivateProfileStringA("Mouse", "MouseHotkeyKeyValue", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalSec", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseEnterMilliSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseIntervalMilliSec", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", mouseButton);
			WritePrivateProfileStringA("Mouse", "MouseLMB", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", clickType);
			WritePrivateProfileStringA("Mouse", "MouseClickType", bufSaveA, ofnSaveA.lpstrFile);


			if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", MOUSEREPEATINFINITY);
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", MOUSEREPEATTIMES);
			else if (SendMessage(GetDlgItem(hWnd, MOUSEREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", MOUSEREPEATCOUNTDOWN);
			else // Default value
				sprintf(bufSaveA, "%d", MOUSEREPEATINFINITY);
			WritePrivateProfileStringA("Mouse", "MouseClickRepeatChecked", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseRepeatTimesEntry, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseClickTimes", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseCountdownHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseCountdownHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseCountdownMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseCountdownMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(mouseCountdownSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Mouse", "MouseCountdownSec", bufSaveA, ofnSaveA.lpstrFile);



			sprintf(bufSaveA, "%d", keyboardActive);
			WritePrivateProfileStringA("Keyboard", "KeyboardActivated", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveKeyboardHotkeySpecA, keyboardHotkeySpecialTextA);
			sprintf(bufSaveA, "%u", keyboardSpecialKey);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeySpecKeyName", bufSaveKeyboardHotkeySpecA, ofnSaveA.lpstrFile);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeySpecKeyValue", bufSaveA, ofnSaveA.lpstrFile);

			strcpy(bufSaveKeyboardHotkeyA, keyboardHotkeyTextA);
			sprintf(bufSaveA, "%u", keyboardHotkey);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyKeyName", bufSaveKeyboardHotkeyA, ofnSaveA.lpstrFile);
			WritePrivateProfileStringA("Keyboard", "KeyboardHotkeyKeyValue", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", (int)SendMessage(keyboardSelectedKey, CB_GETITEMDATA, (int)SendMessage(keyboardSelectedKey, CB_GETCURSEL, 0, 0), 0));
			WritePrivateProfileStringA("Keyboard", "KeyboardSelectedKey", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", (int)isKeyboardHoldMode);
			WritePrivateProfileStringA("Keyboard", "KeyboardHoldModeActive", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalSec", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardEnterMilliSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardIntervalMilliSec", bufSaveA, ofnSaveA.lpstrFile);


			if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATINFINITY), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", KEYBOARDREPEATINFINITY);
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATTIMES), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", KEYBOARDREPEATTIMES);
			else if (SendMessage(GetDlgItem(hWnd, KEYBOARDREPEATCOUNTDOWN), BM_GETCHECK, 0, 0) == BST_CHECKED)
				sprintf(bufSaveA, "%d", KEYBOARDREPEATCOUNTDOWN);
			else // Default value
				sprintf(bufSaveA, "%d", KEYBOARDREPEATINFINITY);
			WritePrivateProfileStringA("Keyboard", "KeyboardPressRepeatChecked", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardRepeatTimesEntry, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardPressTimes", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardCountdownHour, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardCountdownHour", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardCountdownMinute, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardCountdownMin", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(keyboardCountdownSecond, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Keyboard", "KeyboardCountdownSec", bufSaveA, ofnSaveA.lpstrFile);



			sprintf(bufSaveA, "%d", themeOption);
			WritePrivateProfileStringA("Settings", "Theme", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(randomIntervalEnter, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Settings", "RandomInterval", bufSaveA, ofnSaveA.lpstrFile);

			GetWindowTextA(holdTimeEnter, bufSaveA, sizeof(bufSaveA)/sizeof(bufSaveA[0]));
			WritePrivateProfileStringA("Settings", "HoldTime", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", (int)isAlwaysOnTopChecked);
			WritePrivateProfileStringA("Settings", "AlwaysOnTop", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", (int)isTrayChecked);
			WritePrivateProfileStringA("Settings", "MinimizeOnSystemTray", bufSaveA, ofnSaveA.lpstrFile);

			sprintf(bufSaveA, "%d", (int)isDisableTooltipsChecked);
			WritePrivateProfileStringA("Settings", "DisabledTooltips", bufSaveA, ofnSaveA.lpstrFile);
		}
	}
}