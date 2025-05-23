#include "main.h"
#include <stdio.h>
#include <time.h>





bool
hideHotkeys = false,
isClickerTimerActive = false,
isPresserTimerActive = false;


TCHAR
mouseTimerArray[5],
mouseClickRepeatTimesArray[6],
mouseClickRepeatTimerArray[3],

keyboardTimerArray[5],
keyboardPressRepeatTimesArray[6],
keyboardPressRepeatTimerArray[3];




static unsigned int
mouseClickRepeatTimerDuration = 0,
keyboardPressRepeatTimerDuration = 0;


unsigned int
mouseTimerDuration = 1000,
mouseClickRepeatTimes,
mouseClickRepeatTimesLimit = 0,
mouseClickRepeatCountdown,
keyboardTimerDuration = 1000,

keyboardPressRepeatTimes,
keyboardPressRepeatTimesLimit,
keyboardPressRepeatCountdown,
holdTime;


int GetRepeatTimer(HWND hWnd, int modType);
int CountdownStarter(HWND hWnd, int modType);
int UpdateCountdown(int modType);
bool SetAutoclickerTimer(HWND hWnd);
bool SetAutopresserTimer(HWND hWnd);
bool GetRandomIntervalHoldTime(int durationOfMods, int modType);


int GetRepeatTimer(HWND hWnd, int modType)
{
	if (modType == AUTOCLICKER ? isClickerTimerActive : isPresserTimerActive)
		return 0;

	switch(modType)
	{
		case AUTOCLICKER:
		{
			if (IsDlgButtonChecked(hWnd, MOUSEREPEATTIMES) == BST_CHECKED)
			{
				GetWindowText(mouseRepeatTimesEntry, mouseClickRepeatTimesArray, 6);
				mouseClickRepeatTimesLimit = atoi(mouseClickRepeatTimesArray);

				switch(mouseClickRepeatTimesLimit)
				{
					case 0:
						return 1;

					case 1:
						StartAutoClicker(hWnd, clickType, mouseButton);
						return 1;
				}

				mouseClickRepeatTimes = 1;
				return 0;
			}

			if (IsDlgButtonChecked(hWnd, MOUSEREPEATCOUNTDOWN) == BST_CHECKED)
			{
				if (CountdownStarter(hWnd, AUTOCLICKER) == -1)
					return 1;

				GetWindowText(mouseRepeatTimerSecond, mouseClickRepeatTimerArray, 3);
				mouseClickRepeatTimerDuration = atoi(mouseClickRepeatTimerArray) * 1000;

				GetWindowText(mouseRepeatTimerMinute, mouseClickRepeatTimerArray, 3);
				mouseClickRepeatTimerDuration += atoi(mouseClickRepeatTimerArray) * 60000;

				GetWindowText(mouseRepeatTimerHour, mouseClickRepeatTimerArray, 3);
				mouseClickRepeatTimerDuration += atoi(mouseClickRepeatTimerArray) * 3600000;

				SetTimer(hWnd, AUTOCLICKERCOUNTDOWN, mouseClickRepeatTimerDuration, NULL);
				SetTimer(hWnd, AUTOCLICKER_TICKTOCK, 1000, NULL);

				return 0;
			}

			break;
		}

		case AUTOPRESSER:
		{
			if (IsDlgButtonChecked(hWnd, KEYBOARDREPEATTIMES) == BST_CHECKED)
			{
				GetWindowText(keyboardRepeatTimesEntry, keyboardPressRepeatTimesArray, 6);
				keyboardPressRepeatTimesLimit = atoi(keyboardPressRepeatTimesArray);

				switch(keyboardPressRepeatTimesLimit)
				{
					case 0:
						return 1;

					case 1:
						StartAutoPresser(keyboardKey);
						return 1;
				}

				keyboardPressRepeatTimes = 1;
				return 0;
			}

			if (IsDlgButtonChecked(hWnd, KEYBOARDREPEATCOUNTDOWN) == BST_CHECKED)
			{
				if (CountdownStarter(hWnd, AUTOPRESSER) == -1)
					return 1;

				GetWindowText(keyboardRepeatTimerSecond, keyboardPressRepeatTimerArray, 3);
				keyboardPressRepeatTimerDuration = atoi(keyboardPressRepeatTimerArray) * 1000;

				GetWindowText(keyboardRepeatTimerMinute, keyboardPressRepeatTimerArray, 3);
				keyboardPressRepeatTimerDuration += atoi(keyboardPressRepeatTimerArray) * 60000;

				GetWindowText(keyboardRepeatTimerHour, keyboardPressRepeatTimerArray, 3);
				keyboardPressRepeatTimerDuration += atoi(keyboardPressRepeatTimerArray) * 3600000;

				SetTimer(hWnd, AUTOPRESSERCOUNTDOWN, keyboardPressRepeatTimerDuration, NULL);
				SetTimer(hWnd, AUTOPRESSER_TICKTOCK, 1000, NULL);

				return 0;
			}

			break;
		}
	}
}



int h = 0, m = 0, s = 0;
int CountdownStarter(HWND hWnd, int modType)
{
	char starterDigits[3];
	switch(modType)
	{
		case AUTOCLICKER:
		{
			GetWindowText(mouseRepeatTimerHour, starterDigits, sizeof(starterDigits));
			int h = atoi(starterDigits);
			GetWindowText(mouseRepeatTimerMinute, starterDigits, sizeof(starterDigits));
			int m = atoi(starterDigits);
			GetWindowText(mouseRepeatTimerSecond, starterDigits, sizeof(starterDigits));
			int s = atoi(starterDigits);

			if (m > 59 || s > 59)
			{
				MessageBox(hWnd, "Hour/Minute/Second value must be less than 60.", "Invalid Countdown Values", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			}
			else if (h == 0 && m == 0 && s == 0)
			{
				return -1;
			}
			else if (h < 0 && m < 0 && s < 0)
			{
				MessageBox(hWnd, "Hour/Minute/Second value is invalid.", "Invalid Countdown Values", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			}

			break;
		}

		case AUTOPRESSER:
		{
			GetWindowText(keyboardRepeatTimerHour, starterDigits, sizeof(starterDigits));
			int h = atoi(starterDigits);
			GetWindowText(keyboardRepeatTimerMinute, starterDigits, sizeof(starterDigits));
			int m = atoi(starterDigits);
			GetWindowText(keyboardRepeatTimerSecond, starterDigits, sizeof(starterDigits));
			int s = atoi(starterDigits);

			if (m > 59 || s > 59)
			{
				MessageBox(NULL, "Hour/Minute/Second value must be less than 60.", "Invalid Countdown Values", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			}
			else if (h == 0 && m == 0 && s == 0)
			{
				return -1;
			}

			break;
		}
	}

	return 0;
}



int UpdateCountdown(int modType)
{
	char digits[3];
	switch(modType)
	{
		case AUTOCLICKER:
			GetWindowText(mouseRepeatTimerHour, digits, sizeof(digits));
			h = atoi(digits);
			GetWindowText(mouseRepeatTimerMinute, digits, sizeof(digits));
			m = atoi(digits);
			GetWindowText(mouseRepeatTimerSecond, digits, sizeof(digits));
			s = atoi(digits);
			break;

		case AUTOPRESSER:
			GetWindowText(keyboardRepeatTimerHour, digits, sizeof(digits));
			h = atoi(digits);
			GetWindowText(keyboardRepeatTimerMinute, digits, sizeof(digits));
			m = atoi(digits);
			GetWindowText(keyboardRepeatTimerSecond, digits, sizeof(digits));
			s = atoi(digits);
	}

	int secondsLeft = (h * 3600 + m * 60 + s) - 1;
	s = secondsLeft % 60;
	m = (secondsLeft / 60) % 60;
	h = (secondsLeft / 3600);

	switch(modType)
	{
		case AUTOCLICKER:
			sprintf(digits, "%02d", h);
			SetWindowText(mouseRepeatTimerHour, digits);
			sprintf(digits, "%02d", m);
			SetWindowText(mouseRepeatTimerMinute, digits);
			sprintf(digits, "%02d", s);
			SetWindowText(mouseRepeatTimerSecond, digits);
			break;

		case AUTOPRESSER:
			sprintf(digits, "%02d", h);
			SetWindowText(keyboardRepeatTimerHour, digits);
			sprintf(digits, "%02d", m);
			SetWindowText(keyboardRepeatTimerMinute, digits);
			sprintf(digits, "%02d", s);
			SetWindowText(keyboardRepeatTimerSecond, digits);
			break;
	}

	return secondsLeft;
}



bool SetAppTimer(HWND hWnd, int selectMod)
{
	switch(selectMod)
	{
		case TIMERAUTOCLICKER:
			if (SetAutoclickerTimer(hWnd) == 1)
				return 1;
			break;

		case TIMERAUTOPRESSER:
			if (SetAutopresserTimer(hWnd) == 1)
				return 1;
			break;
	}


	if ((isClickerTimerActive || isPresserTimerActive) && !hideHotkeys)
		hideHotkeys = true;
	else if (!isClickerTimerActive && !isPresserTimerActive)
		hideHotkeys = false;

	HWND hDlg;
	switch(selectMod)
	{
		case TIMERAUTOCLICKER:
			EnableWindow(mouseClickStart, !isClickerTimerActive);
			for (int ID = MOUSEREPEATINFINITY; ID <= MOUSEREPEATTIMERSECOND; ++ID)
			{
				hDlg = GetDlgItem(hWnd, ID);
				if (hDlg)
					EnableWindow(hDlg, !isClickerTimerActive);
			}
			EnableWindow(mouseClickStop, isClickerTimerActive);
			break;

		case TIMERAUTOPRESSER:
			EnableWindow(keyboardPressStart, !isPresserTimerActive);
			for (int ID = KEYBOARDREPEATINFINITY; ID <= KEYBOARDREPEATTIMERSECOND; ++ID)
			{
				hDlg = GetDlgItem(hWnd, ID);
				if (hDlg)
					EnableWindow(hDlg, !isPresserTimerActive);
			}
			EnableWindow(keyboardPressStop, isPresserTimerActive);
			break;
	}

	char holdTimeArray[5];
	GetWindowText(holdTimeEnter, holdTimeArray, 4);
	holdTime = atoi(holdTimeArray);

	EnableWindow(mouseHotkeyButton, !hideHotkeys);
	EnableWindow(keyboardHotkeyButton, !hideHotkeys);
	EnableWindow(loadScriptsButton, !hideHotkeys);
	EnableWindow(saveScriptsButton, !hideHotkeys);

	return 0;
}



bool SetAutoclickerTimer(HWND hWnd)
{
	if (isClickerTimerActive)
	{
		KillTimer(hWnd, AUTOCLICKERTIMER);
		isClickerTimerActive = false;
	}

	else
	{
		GetWindowText(mouseEnterMilliSecond, mouseTimerArray, 5);
		mouseTimerDuration = atoi(mouseTimerArray);

		GetWindowText(mouseEnterSecond, mouseTimerArray, 5);
		mouseTimerDuration += atoi(mouseTimerArray) * 1000;

		GetWindowText(mouseEnterMinute, mouseTimerArray, 5);
		mouseTimerDuration += atoi(mouseTimerArray) * 60 * 1000;

		GetWindowText(mouseEnterHour, mouseTimerArray, 4);
		mouseTimerDuration += atoi(mouseTimerArray) * 60 * 60 * 1000;


		if (GetRandomIntervalHoldTime(mouseTimerDuration, AUTOCLICKER) == 1)
			return 1;

		StartAutoClicker(hWnd, clickType, mouseButton);
		RepeatTimes(hWnd, AUTOCLICKER);

		SetTimer(hWnd, AUTOCLICKERTIMER, mouseTimerDuration + RandomInterval(), NULL);
		isClickerTimerActive = true;
	}

	return 0;
}



bool SetAutopresserTimer(HWND hWnd)
{
	if (isPresserTimerActive)
	{
		KillTimer(hWnd, AUTOPRESSERTIMER);
		isPresserTimerActive = false;
	}

	else
	{
		GetWindowText(keyboardEnterMilliSecond, keyboardTimerArray, 5);
		keyboardTimerDuration = atoi(keyboardTimerArray);

		GetWindowText(keyboardEnterSecond, keyboardTimerArray, 5);
		keyboardTimerDuration += atoi(keyboardTimerArray) * 1000;

		GetWindowText(keyboardEnterMinute, keyboardTimerArray, 5);
		keyboardTimerDuration += atoi(keyboardTimerArray) * 60000;

		GetWindowText(keyboardEnterHour, keyboardTimerArray, 4);
		keyboardTimerDuration += atoi(keyboardTimerArray) * 3600000;


		if (GetRandomIntervalHoldTime(keyboardTimerDuration, AUTOPRESSER) == 1)
			return 1;

		if (keyboardSpecialKey == 0)
		{
			StartAutoPresser(keyboardKey);
			RepeatTimes(hWnd, AUTOPRESSER);
		}
		SetTimer(hWnd, AUTOPRESSERTIMER, keyboardTimerDuration + RandomInterval(), NULL);
		isPresserTimerActive = true;
	}

	return 0;
}



void RepeatTimes(HWND hWnd, int modType)
{
	switch(modType)
	{
		case AUTOCLICKER:
		{
			if (IsDlgButtonChecked(hWnd, MOUSEREPEATTIMES) == BST_CHECKED)
			{
				if (mouseClickRepeatTimes == mouseClickRepeatTimesLimit)
				{
					SetAppTimer(hWnd, TIMERAUTOCLICKER);
					return;
				}

				mouseClickRepeatTimes++;
				return;
			}
			break;
		}

		case AUTOPRESSER:
		{
			if (IsDlgButtonChecked(hWnd, KEYBOARDREPEATTIMES) == BST_CHECKED)
			{
				if (keyboardPressRepeatTimes == keyboardPressRepeatTimesLimit)
				{
					SetAppTimer(hWnd, TIMERAUTOPRESSER);
					return;
				}

				keyboardPressRepeatTimes++;
				return;
			}
			break;
		}
	}
}



int randIntervalEditValue, holdTimeEditValue;
bool GetRandomIntervalHoldTime(int durationOfMods, int modType)
{
	char randIntervalArray[5] = {0}, holdTimeArray[5] = {0};
	GetWindowText(randomIntervalEnter, randIntervalArray, 5);
	GetWindowText(holdTimeEnter, holdTimeArray, 5);

	randIntervalEditValue = atoi(randIntervalArray);
	holdTimeEditValue = atoi(holdTimeArray);
	switch(modType)
	{
		case AUTOCLICKER:
			if ((durationOfMods <= randIntervalEditValue + holdTimeEditValue)
				&& !(durationOfMods == 0 && randIntervalEditValue == 0 && holdTimeEditValue == 0))
				return 1;

		case AUTOPRESSER:
			if ((durationOfMods <= randIntervalEditValue)
				&& !(durationOfMods == 0 && randIntervalEditValue == 0))
				return 1;
	}
	return 0;
}



inline int RandomInterval()
{
	return ((rand() % (2 * randIntervalEditValue + 1)) - randIntervalEditValue);
}