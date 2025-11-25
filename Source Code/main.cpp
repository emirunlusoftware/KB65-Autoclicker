#include "KB65 Autoclicker.h"
#include <shellapi.h>
#include <time.h>





HDC hdc;
HINSTANCE hInst = GetModuleHandle(NULL);
HWND hWnd;
PAINTSTRUCT ps;


UINT currentPage = 0;

static bool
mouseHotkeySelected = true,
keyboardHotkeySelected = true,
mouseRunning = false,
keyboardRunning = false;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			winver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&winver);

			srand(time(NULL));
			timeBeginPeriod(1);

			LoadingButtons(hWnd, hInst);
			LoadingEntries(hWnd, hInst);
			LoadingFonts(hWnd);
			LoadingTooltips(hWnd);
			LoadingImages();

			SystemTrayInit(hWnd, hInst);

			RealignZOrderChain(hWnd);

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
			PageTexts(hdc, currentPage);

			if (currentPage == MAINPAGE)
				DrawLine(hdc, 0, 182, (370 + 30), 182, lineColor1, 1);
			if (themeOption != THEMEDEFAULT)
				DrawLine(hdc, 387, 0, 387, 364, lineColor2, 34);

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
				case ACTIVATEMOUSE_VIA_TRAY:
				{
					SendMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);

					mouseActive = !mouseActive;
					SendMessage(activateMouseCheckBox, BM_SETCHECK, mouseActive, 0);

					if ((mouseHotkey == keyboardHotkey && mouseSpecialKey == keyboardSpecialKey))
					{
						if (mouseActive)
							UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
						else
						{
							UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);
							UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
							RegisterHotKey(hWnd, KEYBOARDPRESSHOTKEY, keyboardSpecialKey, mouseHotkey);
						}
					}

					mouseActive
						? RegisterHotKey(hWnd, MOUSECLICKHOTKEY, mouseSpecialKey, mouseHotkey)
						: UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);

					ActiveAppearance(hWnd, AUTOCLICKER, mouseActive);

					break;
				}

				case ACTIVATEKEYBOARD:
				case ACTIVATEKEYBOARD_VIA_TRAY:
				{
					SendMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTOPBUTTON, 0);

					keyboardActive = !keyboardActive;
					SendMessage(activateKeyboardCheckBox, BM_SETCHECK, keyboardActive, 0);
					if (keyboardActive)
					{
						UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
						RegisterHotKey(hWnd, KEYBOARDPRESSHOTKEY, keyboardSpecialKey, keyboardHotkey);
					}
					else
						UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);

					ActiveAppearance(hWnd, AUTOPRESSER, keyboardActive);

					break;
				}


				case MOUSELMB:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
						mouseButton = GetMouseButton(mouseLmB);
					break;
				}

				case MOUSECLICKTYPE:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE && !mouseRunning)
						clickType = GetMouseClickType(mouseClickType);
					break;
				}

				case KEYBOARDSELECTAUTOMATEDKEY:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
						keyboardKey = GetKeyboardKey(keyboardSelectedKey);
					break;
				}

				case KEYBOARDHOLDCHECKBOX:
				{
					isKeyboardHoldMode = SendMessage(keyboardHoldCheckBox, BM_GETCHECK, 0, 0);
					break;
				}



				case MOUSECLICKHOTKEYBUTTON:
				case KEYBOARDPRESSHOTKEYBUTTON:
				{
					UnregisterHotKey(hWnd, LOWORD(wParam) == MOUSECLICKHOTKEYBUTTON ? MOUSECLICKHOTKEY : KEYBOARDPRESSHOTKEY);

					HotkeySelectionAppearance(hWnd, LOWORD(wParam), HIDE);
					if (LOWORD(wParam) == MOUSECLICKHOTKEYBUTTON)
					{
						SetWindowText(mouseHotkeyButton, "Select a Key");
						GetHotkey(hWnd, &mouseHotkey, &mouseHotkeySelected, HOTKEYAUTOCLICKER);
					}
					else if (LOWORD(wParam) == KEYBOARDPRESSHOTKEYBUTTON)
					{
						SetWindowText(keyboardHotkeyButton, "Select a Key");
						GetHotkey(hWnd, &keyboardHotkey, &keyboardHotkeySelected, HOTKEYAUTOPRESSER);
					}
					HotkeySelectionAppearance(hWnd, LOWORD(wParam), SHOW);

					break;
				}



				case MOUSECLICKSTARTBUTTON:
				case MOUSECLICKSTOPBUTTON:
				{
					if (LOWORD(wParam) == MOUSECLICKSTARTBUTTON)
					{
						mouseRunning = true;
						if (StartAutomation(hWnd, AUTOCLICKER) != SUCCESS)
							break;
					}
					else if (LOWORD(wParam) == MOUSECLICKSTOPBUTTON)
					{
						mouseRunning = false;

						if (clickType == HOLD || holdingMouseInProgress)
							ReleaseMouse();

						for (int mIndex = CLICKER; mIndex < PRESSER; mIndex++)
						{
							if (timers[mIndex])
								timeKillEvent(timers[mIndex]);
						}
						ToggleMenusDuringAutomation(hWnd, AUTOCLICKER, SHOW);
					}
					break;
				}

				case KEYBOARDPRESSSTARTBUTTON:
				case KEYBOARDPRESSSTOPBUTTON:
				{
					if (LOWORD(wParam) == KEYBOARDPRESSSTARTBUTTON)
					{
						keyboardRunning = true;
						if (StartAutomation(hWnd, AUTOPRESSER) != SUCCESS)
							break;

					}
					else if (LOWORD(wParam) == KEYBOARDPRESSSTOPBUTTON)
					{
						keyboardRunning = false;

						if (isKeyboardHoldMode == BST_CHECKED || holdingKeyInProgress)
							ReleaseKey();

						for (int kIndex = PRESSER; kIndex <= PRESSER_TICKTOCK; kIndex++)
						{
							if (timers[kIndex])
								timeKillEvent(timers[kIndex]);
						}
						ToggleMenusDuringAutomation(hWnd, AUTOPRESSER, SHOW);
					}
					break;
				}



				case INFOBUTTON:
				{
					ShellExecute(NULL, "open", "https://raw.githubusercontent.com/emirunlusoftware/KB65-Autoclicker/c77c5d059e46337bd6a509e103cde20f558ecfe7/KB65%20Autoclicker%20User%20Guide.pdf", NULL, NULL, SW_SHOWNORMAL);
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
					currentPage = SETTINGSPAGE;
					InvalidateRect(hWnd, NULL, TRUE); 
					ShowPage(currentPage);
					break;
				}

				case THEMESLISTCOMBOBOX:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						SelectTheme();
						InvalidateRect(hWnd, NULL, TRUE);
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
					SetWindowPos(hWnd, isAlwaysOnTopChecked == BST_CHECKED
						? HWND_TOPMOST
						: HWND_NOTOPMOST,
						0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					break;
				}

				case DISABLETOOLTIPS:
				{
					isDisableTooltipsChecked = SendMessage(disableTooltips, BM_GETCHECK, 0, 0);

					if (isDisableTooltipsChecked == BST_CHECKED)
						Tooltips(hWnd, HIDE);
					else
						Tooltips(hWnd, SHOW);

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
					currentPage = MAINPAGE;
					InvalidateRect(hWnd, NULL, TRUE);
					ShowPage(currentPage);
					break;
				}

				case OPEN_VIA_TRAY:
				{
					ShowWindow(hWnd, SW_RESTORE);
					SetForegroundWindow(hWnd);
					RemoveTrayIcon();
					break;
				}

				case QUIT_VIA_TRAY:
				{
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;
				}

				// Press ESC to go to previous page, or exit the program.
				// Doesn't work if ESC is set as hotkey.
				case IDCANCEL:
				{
					switch(currentPage)
					{
						case MAINPAGE:
							PostMessage(hWnd, WM_CLOSE, 0, 0);
							break;

						case SETTINGSPAGE:
							currentPage = MAINPAGE;
							InvalidateRect(hWnd, NULL, TRUE);
							ShowPage(currentPage);
							break;
					}
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
					// if autoclicker OR autopresser is still active, stop all of them by pressing hotkey.
					if (mouseRunning || keyboardRunning)
					{
						if (mouseRunning)
							PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);
						if (keyboardRunning)
							PostMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTOPBUTTON, 0);
					}
					else
					{
						PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTARTBUTTON, 0);
						PostMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTARTBUTTON, 0);
					}
					break;
				}

				// Activate Autoclicker by Hotkey
				if ((wParam == MOUSECLICKHOTKEY) && mouseActive)
				{
					PostMessage(hWnd, WM_COMMAND, !mouseRunning ? MOUSECLICKSTARTBUTTON : MOUSECLICKSTOPBUTTON, 0);
					break;
				}

				// Activate Autopresser by Hotkey
				if ((wParam == KEYBOARDPRESSHOTKEY) && keyboardActive)
				{
					PostMessage(hWnd, WM_COMMAND, !keyboardRunning ? KEYBOARDPRESSSTARTBUTTON : KEYBOARDPRESSSTOPBUTTON, 0);
					break;
				}
			}
			break;
		}



		case WM_SYSCOMMAND:
		{
			// Minimize to System Tray if this checkbox checked
			if (wParam == SC_MINIMIZE && isTrayChecked)
			{
				ShowWindow(hWnd, SW_HIDE);
				MinimizeToTray();
				break;
			}
			else return DefWindowProc(hWnd, message, wParam, lParam);
		}



		case WM_INPUTLANGCHANGE:
			SendMessage(keyboardSelectedKey, CB_RESETCONTENT, 0, 0);
			PopulateComboBox(keyboardSelectedKey, (HKL)lParam);
			break;



		case MAXIMIZETRAY:
		{
			if (LOWORD(lParam) == WM_LBUTTONUP) // Left Mouse Click
			{
				ShowWindow(hWnd, SW_RESTORE);
				SetForegroundWindow(hWnd);
				RemoveTrayIcon();
			}

			else if (LOWORD(lParam) == WM_RBUTTONUP) // Right Mouse Click
			{
				POINT pt;
				GetCursorPos(&pt);
				ShowTrayMenu(hWnd, pt, mouseActive, keyboardActive);
			}

			break;
		}



		case WM_CLOSE:
		{
			if (mouseHotkeySelected && keyboardHotkeySelected)
				DestroyWindow(hWnd);

			return 0;
		}

		case WM_DESTROY:
		{
			for (int tmrIndex = 0; tmrIndex <= RELEASEKEY; tmrIndex++)
				timeKillEvent(timers[tmrIndex]);
			timeEndPeriod(1);

			UnregisterHotKey(hWnd, MOUSECLICKHOTKEY);
			UnregisterHotKey(hWnd, KEYBOARDPRESSHOTKEY);
			DestroyImages();
			DeleteObject(globalFont);
			if (themeColor != (HBRUSH)(COLOR_BTNSHADOW))
				DeleteObject(themeColor);

			PostQuitMessage(0);
			return 0;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}





char szTitle[] = "KB65 Autoclicker";
char szWindowClass[] = "KB65 Autoclicker Window";
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = {0};

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

	// posLeft, posTop, posRight, posBottom
	RECT WindowDimensions =
	{
		0, 0, DPIScale(400), DPIScale(364)
	};

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

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HANDLE hMutex = CreateMutex(NULL, TRUE, "KB65 Autoclicker Mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
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

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return (int) msg.wParam;
}