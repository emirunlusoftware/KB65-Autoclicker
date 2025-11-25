#include "KB65 Autoclicker.h"





int
mouseClickRepeatTimes = 0,
mouseClickRepeatTimesLimit = 0,
mouseTimerDuration = 1000,

keyboardPressRepeatTimes = 0,
keyboardPressRepeatTimesLimit = 0,
keyboardTimerDuration = 1000,

randIntervalValue = 0,
holdTimeValue = 0;


MMRESULT timers[8] = {0};


int StartAutomation(HWND hWnd, int mod);
int CountdownStarter(HWND hWnd, int mod);
int SetAutomationInterval(HWND hWnd, int mod);

VOID CALLBACK ClickerProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK HoldClickProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK ReleaseClickProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK ClickerTicktockProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

VOID CALLBACK PresserProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK HoldKeyProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK ReleaseKeyProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
VOID CALLBACK PresserTicktockProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);



inline int RandomInterval()
{
	return ((rand() % (2 * randIntervalValue + 1)) - randIntervalValue);
}



int StartAutomation(HWND hWnd, int mod)
{
	// Get "Repeat Times" or "Countdown Timer" data if Times radio button or Countdown radio button is checked.
	if (IsDlgButtonChecked(hWnd, mod == AUTOCLICKER ? MOUSEREPEATINFINITY : KEYBOARDREPEATINFINITY) != BST_CHECKED)
	{
		switch(mod)
		{
			case AUTOCLICKER:
			{
				if (IsDlgButtonChecked(hWnd, MOUSEREPEATTIMES) == BST_CHECKED)
				{
					if (clickType == HOLD)
						break;

					char mouseClickRepeatTimesArray[6] = {0};
					GetWindowText(mouseRepeatTimesEntry, mouseClickRepeatTimesArray, 6);
					mouseClickRepeatTimesLimit = atoi(mouseClickRepeatTimesArray);

					switch(mouseClickRepeatTimesLimit)
					{
						case 0:
							return OK;

						case 1:
							SingleClick();
							return OK;
					}

					mouseClickRepeatTimes = 1;
				}
				else if (IsDlgButtonChecked(hWnd, MOUSEREPEATCOUNTDOWN) == BST_CHECKED)
				{
					if (CountdownStarter(hWnd, AUTOCLICKER) == FAIL)
						return FAIL;
				}

				break;
			}

			case AUTOPRESSER:
			{
				if (IsDlgButtonChecked(hWnd, KEYBOARDREPEATTIMES) == BST_CHECKED)
				{
					if (isKeyboardHoldMode)
						break;

					char keyboardPressRepeatTimesArray[6] = {0};
					GetWindowText(keyboardRepeatTimesEntry, keyboardPressRepeatTimesArray, 6);
					keyboardPressRepeatTimesLimit = atoi(keyboardPressRepeatTimesArray);

					switch(keyboardPressRepeatTimesLimit)
					{
						case 0:
							return OK;

						case 1:
							StartPressing(keyboardKey);
							return OK;
					}

					keyboardPressRepeatTimes = 1;
				}
				else if (IsDlgButtonChecked(hWnd, KEYBOARDREPEATCOUNTDOWN) == BST_CHECKED)
				{
					if (CountdownStarter(hWnd, AUTOPRESSER) == FAIL)
						return FAIL;
				}

				break;
			}
		}
	}

	// Set click/press interval.
	if (SetAutomationInterval(hWnd, mod) == FAIL)
		return FAIL;

	// Lastly, disable some windows during automation process...
	ToggleMenusDuringAutomation(hWnd, mod, HIDE);

	// If all the functions have done their job fine,
	// exit the function by returning the code SUCCESS
	// that indicates all jobs have been done successfully.
	return SUCCESS;
}



int CountdownStarter(HWND hWnd, int mod)
{
	char countdownDigitsArr[3];
	int h = 0, m = 0, s = 0;

	GetWindowText(mod == AUTOCLICKER ? mouseCountdownHour : keyboardCountdownHour, countdownDigitsArr, sizeof(countdownDigitsArr));
	h = atoi(countdownDigitsArr);
	GetWindowText(mod == AUTOCLICKER ? mouseCountdownMinute : keyboardCountdownMinute, countdownDigitsArr, sizeof(countdownDigitsArr));
	m = atoi(countdownDigitsArr);
	GetWindowText(mod == AUTOCLICKER ? mouseCountdownSecond : keyboardCountdownSecond, countdownDigitsArr, sizeof(countdownDigitsArr));
	s = atoi(countdownDigitsArr);

	if (m > 59 || s > 59)
	{
		MessageBox(hWnd, "Minute and Second value must be less than 60.", "Invalid Countdown Values", MB_OK | MB_ICONEXCLAMATION);
		return FAIL;
	}
	else if (h == 0 && m == 0 && s == 0)
	{
		return FAIL;
	}
	else if (h < 0 && m < 0 && s < 0)
	{
		MessageBox(hWnd, "Hour/Minute/Second value is invalid.", "Invalid Countdown Values", MB_OK | MB_ICONEXCLAMATION);
		return FAIL;
	}

	if (mod == AUTOCLICKER)
	{
		timers[CLICKER_TICKTOCK] = timeSetEvent(1000, 0, ClickerTicktockProc, (DWORD_PTR)hWnd, TIME_PERIODIC);
	}
	else if (mod == AUTOPRESSER)
	{
		timers[PRESSER_TICKTOCK] = timeSetEvent(1000, 0, PresserTicktockProc, (DWORD_PTR)hWnd, TIME_PERIODIC);
	}

	return SUCCESS;
}



int hUpdatedMouse = 0, mUpdatedMouse = 0, sUpdatedMouse = 0;
int MouseUpdateCountdown()
{
	char mouseDigits[3];

	GetWindowText(mouseCountdownHour, mouseDigits, sizeof(mouseDigits));
	hUpdatedMouse = atoi(mouseDigits);
	GetWindowText(mouseCountdownMinute, mouseDigits, sizeof(mouseDigits));
	mUpdatedMouse = atoi(mouseDigits);
	GetWindowText(mouseCountdownSecond, mouseDigits, sizeof(mouseDigits));
	sUpdatedMouse = atoi(mouseDigits);

	int mouseSecondsLeft = ((hUpdatedMouse * 3600) + (mUpdatedMouse * 60) + sUpdatedMouse) - 1;
	sUpdatedMouse = mouseSecondsLeft % 60;
	mUpdatedMouse = (mouseSecondsLeft / 60) % 60;
	hUpdatedMouse = (mouseSecondsLeft / 3600);

	if (mUpdatedMouse == 59 && sUpdatedMouse == 59)
	{
		sprintf(mouseDigits, "%02d", hUpdatedMouse);
		SetWindowText(mouseCountdownHour, mouseDigits);
	}
	if (sUpdatedMouse == 59)
	{
		sprintf(mouseDigits, "%02d", mUpdatedMouse);
		SetWindowText(mouseCountdownMinute, mouseDigits);
	}
	sprintf(mouseDigits, "%02d", sUpdatedMouse);
	SetWindowText(mouseCountdownSecond, mouseDigits);

	return mouseSecondsLeft;
}



int hUpdatedKeyboard = 0, mUpdatedKeyboard = 0, sUpdatedKeyboard = 0;
int KeyboardUpdateCountdown()
{
	char keyboardDigits[3];

	GetWindowText(keyboardCountdownHour, keyboardDigits, sizeof(keyboardDigits));
	hUpdatedKeyboard = atoi(keyboardDigits);
	GetWindowText(keyboardCountdownMinute, keyboardDigits, sizeof(keyboardDigits));
	mUpdatedKeyboard = atoi(keyboardDigits);
	GetWindowText(keyboardCountdownSecond, keyboardDigits, sizeof(keyboardDigits));
	sUpdatedKeyboard = atoi(keyboardDigits);

	int keyboardSecondsLeft = ((hUpdatedKeyboard * 3600) + (mUpdatedKeyboard * 60) + sUpdatedKeyboard) - 1;
	sUpdatedKeyboard = keyboardSecondsLeft % 60;
	mUpdatedKeyboard = (keyboardSecondsLeft / 60) % 60;
	hUpdatedKeyboard = (keyboardSecondsLeft / 3600);

	if (mUpdatedKeyboard == 59 && sUpdatedKeyboard == 59)
	{
		sprintf(keyboardDigits, "%02d", hUpdatedKeyboard);
		SetWindowText(keyboardCountdownHour, keyboardDigits);
	}
	if (sUpdatedKeyboard == 59)
	{
		sprintf(keyboardDigits, "%02d", mUpdatedKeyboard);
		SetWindowText(keyboardCountdownMinute, keyboardDigits);
	}
	sprintf(keyboardDigits, "%02d", sUpdatedKeyboard);
	SetWindowText(keyboardCountdownSecond, keyboardDigits);

	return keyboardSecondsLeft;
}



void ToggleMenusDuringAutomation(HWND hWnd, int mod, int hideShow)
{
	static bool mouseRunning = false, keyboardRunning = false;
	switch(mod)
	{
		case AUTOCLICKER:
			EnableWindow(mouseClickStart, hideShow);
			for (int id = MOUSEREPEATINFINITY; id <= MOUSEREPEATCOUNTDOWNSECOND; id++)
			{
				HWND hWndGet = GetDlgItem(hWnd, id);
				if (hWndGet)
					EnableWindow(hWndGet, hideShow);
			}
			EnableWindow(mouseClickStop, !hideShow);
			mouseRunning = !hideShow;
			break;

		case AUTOPRESSER:
			EnableWindow(keyboardPressStart, hideShow);
			for (int id = KEYBOARDREPEATINFINITY; id <= KEYBOARDREPEATCOUNTDOWNSECOND; id++)
			{
				HWND hWndGet = GetDlgItem(hWnd, id);
				if (hWndGet)
					EnableWindow(hWndGet, hideShow);
			}
			EnableWindow(keyboardPressStop, !hideShow);
			keyboardRunning = !hideShow;
			break;
	}

	if (mouseRunning == 0 && keyboardRunning == 0)
		hideShow = SHOW;
	else
		hideShow = HIDE;

	EnableWindow(mouseHotkeyButton, hideShow);
	EnableWindow(keyboardHotkeyButton, hideShow);
	EnableWindow(loadScriptsButton, hideShow);
	EnableWindow(saveScriptsButton, hideShow);
}



int SetAutomationInterval(HWND hWnd, int mod)
{
	char timerArray[5] = {0};
	int *timerDuration = (mod == AUTOCLICKER ? &mouseTimerDuration : &keyboardTimerDuration);

	GetWindowText(mod == AUTOCLICKER ? mouseEnterMilliSecond : keyboardEnterMilliSecond, timerArray, 5);
	*timerDuration = atoi(timerArray);

	GetWindowText(mod == AUTOCLICKER ? mouseEnterSecond : keyboardEnterSecond, timerArray, 5);
	*timerDuration += atoi(timerArray) * 1000;

	GetWindowText(mod == AUTOCLICKER ? mouseEnterMinute : keyboardEnterMinute, timerArray, 5);
	*timerDuration += atoi(timerArray) * 60 * 1000;

	GetWindowText(mod == AUTOCLICKER ? mouseEnterHour : keyboardEnterHour, timerArray, 5);
	*timerDuration += atoi(timerArray) * 60 * 60 * 1000;


	char randIntervalArray[5] = {0}, holdTimeArray[5] = {0};
	GetWindowText(randomIntervalEnter, randIntervalArray, 5);
	GetWindowText(holdTimeEnter, holdTimeArray, 5);
	randIntervalValue = atoi(randIntervalArray);
	holdTimeValue = atoi(holdTimeArray);

	if (*timerDuration == 0) // timeSetEvent won't work with 0 ms value.
		*timerDuration = 1;  // Use 1 ms instead.

	if (*timerDuration <= (randIntervalValue + holdTimeValue) * 1.25f)
	{
		if (mod == AUTOCLICKER)
			MessageBox(hWnd, "Mouse Timer must be higher than:\n(Random Interval + Hold Time) x 1.25", "Error", MB_ICONEXCLAMATION);
		else if (mod == AUTOPRESSER)
			MessageBox(hWnd, "Keyboard Timer must be higher than:\n(Random Interval + Hold Time) x 1.25", "Error", MB_ICONEXCLAMATION);

		return FAIL;
	}

	if (mod == AUTOCLICKER)
	{
		switch(clickType)
		{
			case SINGLE:
			{
				if (holdTimeValue == 0)
				{
					SingleClick();
					timers[CLICKER] = timeSetEvent(*timerDuration + RandomInterval(), 0, ClickerProc, (DWORD_PTR)hWnd, TIME_PERIODIC);
				}
				else
					HoldClickProc(0,0, (DWORD_PTR)hWnd,0,0);

				break;
			}
			case DOUBLE:
				DoubleClick();
				timers[CLICKER] = timeSetEvent(*timerDuration + RandomInterval(), 0, ClickerProc, (DWORD_PTR)hWnd, TIME_PERIODIC);
				break;
			case HOLD:
				HoldMouse();
				break;
		}
	}
	else if (mod == AUTOPRESSER)
	{
		if (isKeyboardHoldMode != BST_CHECKED)
		{
			StartPressing(keyboardKey);
			timers[PRESSER] = timeSetEvent(*timerDuration + RandomInterval(), 0, PresserProc, (DWORD_PTR)hWnd, TIME_PERIODIC);
		}
		else
			HoldKey();
	}

	return SUCCESS;
}



VOID CALLBACK ClickerProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	if (clickType == SINGLE)
		SingleClick();
	else if (clickType == DOUBLE)
		DoubleClick();

	if (mouseClickRepeatTimes)
	{
		mouseClickRepeatTimes++;
		if (mouseClickRepeatTimes == mouseClickRepeatTimesLimit)
		{
			HWND hWnd = (HWND)dwUser;
			PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);
		}
	}

	if (randIntervalValue > 0)
	{
		timeKillEvent(timers[CLICKER]);
		timers[CLICKER] = timeSetEvent(mouseTimerDuration + RandomInterval(), 0, ClickerProc, dwUser, TIME_ONESHOT);
	}
}

bool holdingMouseInProgress = false;
VOID CALLBACK HoldClickProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	HoldMouse();
	holdingMouseInProgress = true;
	if (clickType == SINGLE)
		timers[RELEASECLICK] = timeSetEvent(holdTimeValue, 0, ReleaseClickProc, dwUser, TIME_ONESHOT);
	else if (clickType == DOUBLE)
		timers[RELEASECLICK] = timeSetEvent(holdTimeValue/2, 0, ReleaseClickProc, dwUser, TIME_ONESHOT);
}

VOID CALLBACK ReleaseClickProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	static bool holdDoubleNow = false;
	holdingMouseInProgress = false;
	switch(clickType)
	{
		case SINGLE:
		{
			ReleaseMouse();
			if (mouseClickRepeatTimes)
			{
				mouseClickRepeatTimes++;
				if (mouseClickRepeatTimes == mouseClickRepeatTimesLimit)
				{
					HWND hWnd = (HWND)dwUser;
					PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);
					return;
				}
			}
			timers[HOLDCLICK] = timeSetEvent(mouseTimerDuration + RandomInterval() - holdTimeValue, 0, HoldClickProc, dwUser, TIME_ONESHOT);
			break;
		}
		case DOUBLE:
		{
			ReleaseMouse();
			if (mouseClickRepeatTimes)
			{
				if (holdDoubleNow)
				{
					mouseClickRepeatTimes++;
					if (mouseClickRepeatTimes == mouseClickRepeatTimesLimit)
					{
						HWND hWnd = (HWND)dwUser;
						PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);
						return;
					}
				}
			}
			holdDoubleNow = !holdDoubleNow;
			timers[HOLDCLICK] = timeSetEvent(holdDoubleNow ? holdTimeValue/2 : (mouseTimerDuration + RandomInterval() - holdTimeValue), 0, HoldClickProc, dwUser, TIME_ONESHOT);
			break;
		}
	}
}

VOID CALLBACK ClickerTicktockProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	if (MouseUpdateCountdown() == 0)
	{
		HWND hWnd = (HWND)dwUser;
		PostMessage(hWnd, WM_COMMAND, MOUSECLICKSTOPBUTTON, 0);
	}
}

VOID CALLBACK PresserProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	StartPressing(keyboardKey);

	if (keyboardPressRepeatTimes)
	{
		keyboardPressRepeatTimes++;
		if (keyboardPressRepeatTimes == keyboardPressRepeatTimesLimit)
		{
			HWND hWnd = (HWND)dwUser;
			PostMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTOPBUTTON, 0);
		}
	}

	if (randIntervalValue > 0)
	{
		timeKillEvent(timers[PRESSER]);
		timers[PRESSER] = timeSetEvent(keyboardTimerDuration + RandomInterval(), 0, PresserProc, dwUser, TIME_ONESHOT);
	}
}

bool holdingKeyInProgress = false;
VOID CALLBACK HoldKeyProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	holdingKeyInProgress = true;
	HoldKey();
	timers[RELEASEKEY] = timeSetEvent(holdTimeValue, 0, ReleaseKeyProc, dwUser, TIME_ONESHOT);
}

VOID CALLBACK ReleaseKeyProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	holdingKeyInProgress = false;
	ReleaseKey();
	if (keyboardPressRepeatTimes)
	{
		keyboardPressRepeatTimes++;
		if (keyboardPressRepeatTimes == keyboardPressRepeatTimesLimit)
		{
			HWND hWnd = (HWND)dwUser;
			PostMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTOPBUTTON, 0);
			return;
		}
	}
	timers[HOLDKEY] = timeSetEvent(keyboardTimerDuration + RandomInterval() - holdTimeValue, 0, HoldKeyProc, dwUser, TIME_ONESHOT);
}

VOID CALLBACK PresserTicktockProc(UINT id, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	if (KeyboardUpdateCountdown() == 0)
	{
		HWND hWnd = (HWND)dwUser;
		PostMessage(hWnd, WM_COMMAND, KEYBOARDPRESSSTOPBUTTON, 0);
	}
}