#include "main.h"
#include <shellapi.h>
#include <time.h>





HDC hdc;
HINSTANCE hInst = GetModuleHandle(NULL);
HWND hWnd;
OSVERSIONINFO winver;
PAINTSTRUCT ps;
WNDCLASSEX wcex = {0};


UINT
option					= 0;

static bool
mouseActive				= true,
keyboardActive			= false,
mouseHotkeySelected		= true,
keyboardHotkeySelected	= true;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		case WM_CREATE:
		{
			winver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&winver);

			srand(time(NULL));
			LoadingEntries(hWnd, hInst);
			LoadingButtons(hWnd, hInst);
			LoadingFonts(hWnd);
			LoadingImages();

			RegisterHotKey(hWnd, MOUSECLICKHOTKEY, 0, mouseHotkey);
			break;
		}



		case WM_CTLCOLORSTATIC:
		{
			if (themeOption != THEMEDEFAULT)
			{
				HDC wcexStatic = (HDC)wParam;
				SetBkMode(wcexStatic, TRANSPARENT);
				return (INT_PTR)themeColor;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		case WM_ERASEBKGND:
		{
			hdc = (HDC)wParam;
			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hdc, &rect, themeColor);
			return 1;
		}

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			HFONT hSafeFont = (HFONT)SelectObject(hdc, globalFont);
			SetBkMode(hdc, TRANSPARENT);

			switch(option)
			{
				case MAINPAGE:
				{
					PageTexts(hdc, MAINPAGE);
					DrawLine(hdc, 0, 182.0, (370.0 + 30.0), 182.0, lineColor1, 1);
					if (themeOption != THEMEDEFAULT)
						DrawLine(hdc, 387.0, 0, 387.0, 364.0, lineColor2, 34);

					break;
				}

				case SETTINGSPAGE:
				{
					PageTexts(hdc, SETTINGSPAGE);
					if (themeOption != THEMEDEFAULT)
						DrawLine(hdc, 387.0, 0, 387.0, 364.0, lineColor2, 34);

					break;
				}
			}

			GetImages(hdc, themeOption);

			SelectObject(hdc, hSafeFont);
			EndPaint(hWnd, &ps);
			break;
		}



		case WM_COMMAND:
		{

			switch (LOWORD(wParam))
			{

				case ACTIVATEMOUSE:
				case ACTIVATEMOUSETRAY:
				{
					KillTimer(hWnd, AUTOCLICKERTIMER);
					KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
					KillTimer(hWnd, AUTOCLICKER_TICKTOCK);

					isClickerTimerActive = false;

					mouseActive = !mouseActive;
					SendMessage(activateMouseCheckBox, BM_SETCHECK, mouseActive, 0);

					if ((mouseHotkey == keyboardHotkey && mouseSpecialKey == keyboardSpecialKey) && mouseActive)
						UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);

					mouseActive
						? RegisterHotKey(hWnd, MOUSECLICKHOTKEY, mouseSpecialKey, mouseHotkey)
						: UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);

					if ((mouseHotkey == keyboardHotkey) && !mouseActive)
						RegisterHotKey(hWnd, KEYBOARDPRESSHOTKEY, keyboardSpecialKey, mouseHotkey);

					ActiveAppearance(hWnd, AUTOCLICKER, mouseActive, isPresserTimerActive);

					break;
				}

				case ACTIVATEKEYBOARD:
				case ACTIVATEKEYBOARDTRAY:
				{
					KillTimer(hWnd, AUTOPRESSERTIMER);
					KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
					KillTimer(hWnd, AUTOPRESSER_TICKTOCK);

					isPresserTimerActive = false;

					keyboardActive = !keyboardActive;
					SendMessage(activateKeyboardCheckBox, BM_SETCHECK, keyboardActive, 0);
					keyboardActive
						? RegisterHotKey(hWnd, KEYBOARDPRESSHOTKEY, keyboardSpecialKey, keyboardHotkey)
						: UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);

					ActiveAppearance(hWnd, AUTOPRESSER, keyboardActive, isClickerTimerActive);

					break;
				}


				case MOUSELMB:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
						mouseButton = GetMouseButton(mouseLmB);
					break;
				}

				case MOUSESINGLEORDOUBLE:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
						clickType = GetMouseClickType(mouseSingleOrDouble);
					break;
				}

				case KEYBOARDSELECTAUTOMATEDKEY:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
						keyboardKey = GetKeyboardKey(keyboardSelectedKey);
					break;
				}

				case MOUSECLICKHOTKEYBUTTON:
				{
					UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);
					mouseHotkeySelected = FALSE;

					HotkeySelectionAppearance(hWnd, mouseActive, keyboardActive, HIDE);
					HotkeyButtonAppearance(mouseHotkeyButton, HIDE);
					SetWindowText(mouseHotkeyButton, "Select a Key");

					GetHotkey(hWnd, &mouseHotkey, &mouseHotkeySelected, HOTKEYAUTOCLICKER);
					HotkeySelectionAppearance(hWnd, mouseActive, keyboardActive, SHOW);
					HotkeyButtonAppearance(mouseHotkeyButton, SHOW);

					break;
				}

				case KEYBOARDPRESSHOTKEYBUTTON:
				{
					UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
					keyboardHotkeySelected = FALSE;

					HotkeySelectionAppearance(hWnd, mouseActive, keyboardActive, HIDE);
					HotkeyButtonAppearance(keyboardHotkeyButton, HIDE);
					SetWindowText(keyboardHotkeyButton, "Select a Key");

					GetHotkey(hWnd, &keyboardHotkey, &keyboardHotkeySelected, HOTKEYAUTOPRESSER);
					HotkeySelectionAppearance(hWnd, mouseActive, keyboardActive, SHOW);
					HotkeyButtonAppearance(keyboardHotkeyButton, SHOW);

					break;
				}

				case MOUSECLICKSTARTBUTTON:
				case MOUSECLICKSTOPBUTTON:
				{
					KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
					KillTimer(hWnd, AUTOCLICKER_TICKTOCK);

					if (holdingInProgress == 1)
					{
						KillTimer(hWnd, HOLDTIME);
						PostMessage(hWnd, STOP_CLICKERHOLDTIME, 0, 0);
					}

					if (GetRepeatTimer(hWnd, AUTOCLICKER) == 1)
						break;

					if (SetAppTimer(hWnd, TIMERAUTOCLICKER) == 1)
						MessageBox(hWnd, "Mouse Timer must be under Random Interval and Hold Time.", "Error", MB_ICONEXCLAMATION);
					break;
				}

				case KEYBOARDPRESSSTARTBUTTON:
				case KEYBOARDPRESSSTOPBUTTON:
				{
					KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
					KillTimer(hWnd, AUTOPRESSER_TICKTOCK);

					if (GetRepeatTimer(hWnd, AUTOPRESSER))
						break;

					if (SetAppTimer(hWnd, TIMERAUTOPRESSER) == 1)
						MessageBox(hWnd, "Keyboard Timer must be under Random Interval.", "Error", MB_ICONEXCLAMATION);
					break;
				}


				case INFOBUTTON:
				{
					ShellExecute(NULL, "open", "https://raw.githubusercontent.com/emirunlusoftware/KB65-Autoclicker/9ec821d3880aa3cee98261dea9d88c6668b1b5b1/KB65%20Autoclicker%20User%20Guide.pdf", NULL, NULL, SW_SHOWNORMAL);
					break;
				}

				case LOADSCRIPTSBUTTON:
				{
					LoadInit(hWnd);
					break;
				}
				case SAVESCRIPTSBUTTON:
				{
					SaveInit(hWnd);
					break;
				}
				case SETTINGSBUTTON:
				{
					option = SETTINGSPAGE;
					InvalidateRect(hWnd, NULL, TRUE); 
					ShowPages(option);
					break;
				}

				case THEMESLISTCOMBOBOX:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						if (SendMessage(themesList, CB_GETCURSEL, 0, 0) != CB_ERR)
						{
							TCHAR themeText[16];
							SendMessage(themesList, CB_GETLBTEXT, SendMessage(themesList, CB_GETCURSEL, 0, 0), (LPARAM)themeText);
							SelectThemeText(themeText);
							InvalidateRect(hWnd, NULL, TRUE);
						}
					}
					break;
				}

				case MINIMIZEONTRAY:
				{
					isTrayChecked = SendMessage(minimizeOnTray, BM_GETCHECK, 0, 0);
					break;
				}

				case ALWAYSONTOP:
				{
					isAlwaysOnTopChecked = SendMessage(alwaysOnTop, BM_GETCHECK, 0, 0);

					if (isAlwaysOnTopChecked == BST_CHECKED)
						SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					else
						SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

					break;
				}

				case DEBUGHOTKEYBUTTON:
				{
					DebugAppearance(hWnd, HIDE);
					GetDebugHexCode(debugHotkeyButton);
					DebugAppearance(hWnd, SHOW);
					break;
				}

				case BACKTOMAINBUTTON:
				{
					option = MAINPAGE;
					InvalidateRect(hWnd, NULL, TRUE);
					ShowPages(option);
					break;
				}

				case OPENTRAY:
				{
					ShowWindow(hWnd, SW_RESTORE);
					SetForegroundWindow(hWnd);
					RemoveTrayIcon();
					break;
				}

				case QUITTRAY:
				{
					KillTimer(hWnd, AUTOCLICKERTIMER);
					KillTimer(hWnd, AUTOPRESSERTIMER);
					PostQuitMessage(0);
					break;
				}

			}
			break;
		}



		case WM_HOTKEY:
		{
			Sleep(1);
			if (mouseHotkeySelected && keyboardHotkeySelected)
			{
				if ((mouseHotkey == keyboardHotkey) && (mouseSpecialKey == keyboardSpecialKey) && mouseActive && keyboardActive)
				{
					KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
					KillTimer(hWnd, AUTOCLICKER_TICKTOCK);
					KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
					KillTimer(hWnd, AUTOPRESSER_TICKTOCK);

					if (holdingInProgress == 1)
					{
						KillTimer(hWnd, HOLDTIME);
						PostMessage(hWnd, STOP_CLICKERHOLDTIME, 0, 0);
					}

					if (GetRepeatTimer(hWnd, AUTOCLICKER) || GetRepeatTimer(hWnd, AUTOPRESSER))
						break;

					if (SetAppTimer(hWnd, TIMERAUTOCLICKER) == 1)
						MessageBox(hWnd, "Mouse Timer must be under Random Interval and Hold Time.", "Error", MB_ICONEXCLAMATION);
					if (SetAppTimer(hWnd, TIMERAUTOPRESSER) == 1)
						MessageBox(hWnd, "Keyboard Timer must be under Random Interval.", "Error", MB_ICONEXCLAMATION);

					break;
				}

				// Activate Autoclicker by Hotkey
				if ((wParam == MOUSECLICKHOTKEY) && mouseActive)
				{
					KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
					KillTimer(hWnd, AUTOCLICKER_TICKTOCK);

					if (holdingInProgress == 1)
					{
						KillTimer(hWnd, HOLDTIME);
						PostMessage(hWnd, STOP_CLICKERHOLDTIME, 0, 0);
					}

					if (GetRepeatTimer(hWnd, AUTOCLICKER))
						break;

					if (SetAppTimer(hWnd, TIMERAUTOCLICKER) == 1)
						MessageBox(hWnd, "Mouse Timer must be under Random Interval and Hold Time.", "Error", MB_ICONEXCLAMATION);
					break;
				}

				if ((wParam == KEYBOARDPRESSHOTKEY) && keyboardActive)
				{
					KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
					KillTimer(hWnd, AUTOPRESSER_TICKTOCK);

					if (GetRepeatTimer(hWnd, AUTOPRESSER))
						break;

					if (SetAppTimer(hWnd, TIMERAUTOPRESSER) == 1)
						MessageBox(hWnd, "Keyboard Timer must be under Random Interval.", "Error", MB_ICONEXCLAMATION);
					break;
				}
			}

			break;
		}



		case WM_TIMER:
		{
			if (wParam == AUTOCLICKERTIMER)
			{
				StartAutoClicker(hWnd, clickType, mouseButton);

				if (randIntervalEditValue != 0)
				{
					KillTimer(hWnd, AUTOCLICKERTIMER);
					SetTimer(hWnd, AUTOCLICKERTIMER, mouseTimerDuration + RandomInterval(), NULL);
				}

				RepeatTimes(hWnd, AUTOCLICKER);
			}
			if (wParam == AUTOCLICKERCOUNTDOWN)
			{
				KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
				SetAppTimer(hWnd, TIMERAUTOCLICKER);
			}
			if (wParam == AUTOCLICKER_TICKTOCK)
			{
				if (!UpdateCountdown(AUTOCLICKER))
					KillTimer(hWnd, AUTOCLICKER_TICKTOCK);
			}


			if (wParam == AUTOPRESSERTIMER)
			{
				StartAutoPresser(keyboardKey);

				if (randIntervalEditValue != 0)
				{
					KillTimer(hWnd, AUTOPRESSERTIMER);
					SetTimer(hWnd, AUTOPRESSERTIMER, keyboardTimerDuration + RandomInterval(), NULL);
				}

				RepeatTimes(hWnd, AUTOPRESSER);
			}
			if (wParam == AUTOPRESSERCOUNTDOWN)
			{
				KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
				SetAppTimer(hWnd, TIMERAUTOPRESSER);
			}
			if (wParam == AUTOPRESSER_TICKTOCK)
			{
				if (!UpdateCountdown(AUTOPRESSER))
					KillTimer(hWnd, AUTOPRESSER_TICKTOCK);
			}

			break;
		}



		case WM_SYSCOMMAND:
		{
			// Minimize to System Tray if Tray Check Box is checked
			if (wParam == SC_MINIMIZE && isTrayChecked)
			{
				MinimizeToTray();
				ShowWindow(hWnd, SW_HIDE);
				break;
			}
			else return DefWindowProc(hWnd, message, wParam, lParam);

			break;
		}



		case WM_INPUTLANGCHANGE:
			SendMessage(keyboardSelectedKey, CB_RESETCONTENT, 0, 0);
			PopulateComboBox(keyboardSelectedKey, (HKL)lParam);
			break;



		case WM_KEYUP:
		{
			if (wParam == VK_ESCAPE && wParam != MOUSECLICKHOTKEY && wParam != KEYBOARDPRESSHOTKEY)
			{
				switch(option)
				{
					/*
						End the program by pressing ESC. 
						You don't need to kill timers because
						when the timers running, ESC cannot end the program.
						So, just delete objects that we created.
					*/
					case MAINPAGE:
					{
						if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
							DeleteObject(themeColor);

						DeleteObject(wcex.hbrBackground);
						DeleteObject(globalFont);
						PostQuitMessage(0);
						return 0;
					}

					case SETTINGSPAGE:
						option = MAINPAGE;
						InvalidateRect(hWnd, NULL, TRUE);
						ShowPages(option);
						break;
				}
			}

			break;
		}



		case MAXIMIZETRAY:
		{
			if (LOWORD(lParam) == WM_LBUTTONUP) // Left Mouse Click
			{
				ShowWindow(hWnd, SW_RESTORE);
				SetForegroundWindow(hWnd);
				RemoveTrayIcon();
			}

			if (LOWORD(lParam) == WM_RBUTTONUP) // Right Mouse Click
			{
				POINT pt;
				GetCursorPos(&pt);
				ShowTrayMenu(hWnd, pt, mouseActive, keyboardActive);
			}

			break;
		}



		// Mouse with Hold Time Trigger
		case CONT_CLICKERHOLDTIME:
			ContinueClickerHoldTime();
			break;

		// Mouse with Hold Time Stopper
		case STOP_CLICKERHOLDTIME:
			StopClickerHoldTime();
			break;



		case WM_CLOSE:
		{
			if (mouseHotkeySelected && keyboardHotkeySelected)
				DestroyWindow(hWnd);

			return 0;
		}

		case WM_DESTROY:
		{
			KillTimer(hWnd, AUTOCLICKERTIMER);
			KillTimer(hWnd, AUTOCLICKERCOUNTDOWN);
			KillTimer(hWnd, AUTOCLICKER_TICKTOCK);
			KillTimer(hWnd, AUTOPRESSERTIMER);
			KillTimer(hWnd, AUTOPRESSERCOUNTDOWN);
			KillTimer(hWnd, AUTOPRESSER_TICKTOCK);
			KillTimer(hWnd, HOLDTIME);

			if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
				DeleteObject(themeColor);

			DeleteObject(wcex.hbrBackground);
			DeleteObject(globalFont);
			PostQuitMessage(0);
			return 0;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}





TCHAR szTitle[] = "KB65 Autoclicker";
TCHAR szWindowClass[] = "KB65 Autoclicker Window";


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH) (COLOR_BTNSHADOW);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassEx(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	RECT WindowDimensions =
	{
		0, 0,
		static_cast<int>(400.0 * DPIScale()),
		static_cast<int>(364.0 * DPIScale())
	}; // posLeft, posTop, posRight, posBottom

	AdjustWindowRect(&WindowDimensions, WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int posX = (screenWidth - (WindowDimensions.right - WindowDimensions.left)) / 2;
	int posY = (screenHeight - (WindowDimensions.bottom - WindowDimensions.top)) / 2;

	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		posX, posY,
		WindowDimensions.right - WindowDimensions.left,
		WindowDimensions.bottom - WindowDimensions.top,
		NULL, NULL, hInst, NULL);

	SetForegroundWindow(hWnd);

	if (!hWnd)
		return FALSE;

	SystemTrayInit(hWnd, hInstance);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HANDLE hMutex = CreateMutex(
		NULL, TRUE,
		"KB65 Autoclicker Mutex"
	);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);
	UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return (int) msg.wParam;
}