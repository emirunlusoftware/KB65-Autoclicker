#include "KB65 Autoclicker.h"





namespace TextScaling
{
	DWORD textScale = 100;

	// Windows XP & earlier don't have RegGetValue function
	// Load the function dynamically...
	LONG fRegGetValue(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue)
	{
		DWORD dataSize = sizeof(textScale);
		HMODULE hAdvApi = GetModuleHandleW(L"advapi32.dll");

		if (hAdvApi)
		{
			static RegGetValuePtr pRegGetValue = NULL;

			if (!pRegGetValue)
			{
				pRegGetValue = (RegGetValuePtr)GetProcAddress(hAdvApi, "RegGetValueW");
			}

			if (pRegGetValue)
			{
				LONG regQueryResult = pRegGetValue(hkey, lpSubKey, lpValue, RRF_RT_REG_DWORD, NULL, &textScale, &dataSize);
				return regQueryResult;
			}
		}

		return ERROR_NOT_SUPPORTED;
	}
}



namespace DPI
{
	int g_dpi = 96;
	bool isWindows10Later = false;

	typedef BOOL (WINAPI* SetProcessDpiAwarenessContextPtr)(HANDLE);
	typedef HMONITOR (WINAPI* MonitorFromPointPtr)(POINT, DWORD);
	typedef HRESULT (WINAPI* GetDpiForMonitorPtr)(HMONITOR, int, UINT*, UINT*);
	typedef BOOL (WINAPI* AdjustWindowRectExForDpiPtr)(LPRECT, DWORD, BOOL, DWORD, UINT);


	namespace Init
	{
		void CheckWindowsVersion()
		{
			typedef LONG NTSTATUS;
			typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

			winverOld.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&winverOld);

			HMODULE hNtDll = LoadLibraryW(L"ntdll.dll");
			if (hNtDll)
			{
				RtlGetVersionPtr pRtlGv = (RtlGetVersionPtr)GetProcAddress(hNtDll, "RtlGetVersion");
				if (pRtlGv)
				{
					winver.dwOSVersionInfoSize = sizeof(winver);
					pRtlGv(&winver);
					isWindows10Later = (winver.dwMajorVersion >= 10);
				}
				FreeLibrary(hNtDll);
			}
		}

		void SetDPITextSizeAtStart()
		{
			if (isWindows10Later)
			{
				// Get TextScaleFactor value from registry.
				if (TextScaling::fRegGetValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Accessibility", L"TextScaleFactor") != ERROR_SUCCESS)
				{
					TextScaling::textScale = 100;
				}
			}

			// Get DPI value.
			if (isWindows10Later)
			{
				UINT dpi_X = 0, dpi_Y = 0;

				HMODULE hUser32 = LoadLibraryW(L"user32.dll");
				MonitorFromPointPtr loadedFnMonitor = NULL;
				if (hUser32)
				{
					SetProcessDpiAwarenessContextPtr loadedFn =
						(SetProcessDpiAwarenessContextPtr)GetProcAddress(hUser32, "SetProcessDpiAwarenessContext");

					if (loadedFn)
						loadedFn((HANDLE)-4);

					loadedFnMonitor = (MonitorFromPointPtr)GetProcAddress(hUser32, "MonitorFromPoint");

					FreeLibrary(hUser32);
				}

				HMODULE hShcore = LoadLibraryW(L"shcore.dll");
				if (hShcore)
				{
					GetDpiForMonitorPtr loadedFn =
						(GetDpiForMonitorPtr)GetProcAddress(hShcore, "GetDpiForMonitor");

					if (loadedFn)
					{
						POINT pt = {0, 0};
						HMONITOR hMonitor = loadedFnMonitor(pt, MONITOR_DEFAULTTOPRIMARY);
						loadedFn(hMonitor, MDT_EFFECTIVE_DPI, &dpi_X, &dpi_Y);
						g_dpi = dpi_Y;
					}

					FreeLibrary(hShcore);
				}
			}
			else
			{
				HDC hdc = GetDC(NULL);
				if (hdc)
				{
					g_dpi = GetDeviceCaps(hdc, LOGPIXELSX);
					ReleaseDC(NULL, hdc);
				}
				if (g_dpi <= 0)
					g_dpi = 96;
			}
		}
	}



	BOOL AdjustWindowRectExOrDpi(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle, UINT dpi)
	{
		// AdjustWindowRectExForDpi()
		// (Windows 10 and later)
		if (isWindows10Later)
		{
			HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
			if (hUser32)
			{
				static AdjustWindowRectExForDpiPtr pAdjust = NULL;

				if (!pAdjust)
				{
					pAdjust = (AdjustWindowRectExForDpiPtr)GetProcAddress(hUser32, "AdjustWindowRectExForDpi");
				}

				if (pAdjust)
				{
					return pAdjust(lpRect, dwStyle, bMenu, dwExStyle, dpi);
				}
			}
		}

		// AdjustWindowRectEx()
		// (windows 8.1 and older)
		return AdjustWindowRectEx(lpRect, dwStyle, bMenu, dwExStyle);
	}


	void InitWin32Environment()
	{
		Init::CheckWindowsVersion();
		Init::SetDPITextSizeAtStart();
	}
}



void UpdateMainWindow(HWND hWnd, int appWidth, int appHeight)
{
	RECT WndDimensions =
	{
		0, 0, // (X1, Y1)
		DPI::Scale(appWidth), DPI::Scale(appHeight) // (X2, Y2)
	};
	DPI::AdjustWindowRectExOrDpi(&WndDimensions, WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE, 0, DPI::g_dpi);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN),
		screenHeight = GetSystemMetrics(SM_CYSCREEN),
		posX = (screenWidth - (WndDimensions.right - WndDimensions.left)) / 2,
		posY = (screenHeight - (WndDimensions.bottom - WndDimensions.top)) / 2;

	SetWindowPos(hWnd, NULL,
		posX, posY,
		WndDimensions.right - WndDimensions.left,
		WndDimensions.bottom - WndDimensions.top,
		SWP_NOZORDER);
}