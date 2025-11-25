#pragma once
#ifndef KB65_AUTOCLICKER_H
#define KB65_AUTOCLICKER_H

#include "stdafx.h"
#include "resource.h"





// GENERAL MACROS
#define HIDE	0
#define SHOW	1

#define SUCCESS	0
#define FAIL	1
#define OK		2
#define UNKNOWN 3



// MOUSE SUBPAGE
#define ACTIVATEMOUSE_VIA_TRAY			900
#define ACTIVATEMOUSE					901

#define MOUSETIMERFRAME					902
#define MOUSEENTERHOUR					903
#define MOUSEENTERMINUTE				904
#define MOUSEENTERSECOND				905
#define MOUSEENTERMILLISECOND			906

#define MOUSECLICKTYPEFRAME				907
#define MOUSELMB						908
#define MOUSECLICKTYPE					909

#define MOUSECLICKREPEATFRAME			910
#define MOUSEREPEATINFINITY				911
#define MOUSEREPEATTIMES				912
#define MOUSEREPEATTIMESENTRY			913
#define MOUSEREPEATTIMESSPIN			914
#define MOUSEREPEATCOUNTDOWN			915
#define MOUSEREPEATCOUNTDOWNHOUR		916
#define MOUSEREPEATCOUNTDOWNMINUTE		917
#define MOUSEREPEATCOUNTDOWNSECOND		918

#define MOUSECLICKSTARTBUTTON			919
#define MOUSECLICKSTOPBUTTON			920
#define MOUSECLICKHOTKEYBUTTON			921
#define MOUSECLICKHOTKEY				922



// KEYBOARD SUBPAGE
#define ACTIVATEKEYBOARD_VIA_TRAY		923
#define ACTIVATEKEYBOARD				924

#define KEYBOARDTIMERFRAME				925
#define KEYBOARDENTERHOUR				926
#define KEYBOARDENTERMINUTE				927
#define KEYBOARDENTERSECOND				928
#define KEYBOARDENTERMILLISECOND		929

#define KEYBOARDKEYFRAME				930
#define KEYBOARDSELECTAUTOMATEDKEY		931
#define KEYBOARDHOLDCHECKBOX			932

#define KEYBOARDPRESSREPEATFRAME		933
#define KEYBOARDREPEATINFINITY			934
#define KEYBOARDREPEATTIMES				935
#define KEYBOARDREPEATTIMESENTRY		936
#define KEYBOARDREPEATTIMESSPIN			937
#define KEYBOARDREPEATCOUNTDOWN			938
#define KEYBOARDREPEATCOUNTDOWNHOUR		939
#define KEYBOARDREPEATCOUNTDOWNMINUTE	940
#define KEYBOARDREPEATCOUNTDOWNSECOND	941

#define KEYBOARDPRESSSTARTBUTTON		942
#define KEYBOARDPRESSSTOPBUTTON			943
#define KEYBOARDPRESSHOTKEYBUTTON		944
#define KEYBOARDPRESSHOTKEY				945


// SETTINGS PAGE
#define INFOBUTTON						946
#define LOADSCRIPTSBUTTON				947
#define SAVESCRIPTSBUTTON				948
#define SETTINGSBUTTON					949

#define SETTINGSFRAME					950
#define THEMESFRAME						951
#define THEMESLISTCOMBOBOX				952
#define RANDINTERVALHOLDTIMEFRAME		953
#define RANDOMINTERVALENTER				954
#define HOLDTIMEENTER					955
#define ALWAYSONTOP						956
#define MINIMIZEONTRAY					957
#define DISABLETOOLTIPS					958
#define DEBUGHOTKEYBUTTON				959
#define BACKTOMAINBUTTON				960


// OTHER ID'S
#define OPEN_VIA_TRAY					961
#define QUIT_VIA_TRAY					962
#define MINIMIZETRAY					963
#define MAXIMIZETRAY					(WM_USER + 1)





/* buttons.cpp */
extern HWND
activateMouseCheckBox,
mouseLmB,
mouseClickType,
mouseRepeatInfinity,
mouseRepeatTimes,
mouseCountdown,
mouseClickStart,
mouseClickStop,
mouseHotkeyButton,

activateKeyboardCheckBox,
keyboardSelectedKey,
keyboardHoldCheckBox,
keyboardRepeatInfinity,
keyboardRepeatTimes,
keyboardCountdown,
keyboardPressStart,
keyboardPressStop,
keyboardHotkeyButton,

infoButton,
loadScriptsButton,
saveScriptsButton,
settingsButton,

themesList,
alwaysOnTop,
minimizeOnTray,
disableTooltips,
debugHotkeyButton,
backToMainButton;

extern LRESULT isAlwaysOnTopChecked;

void LoadingButtons(HWND hWnd, HINSTANCE hInstance);



/* entries.cpp */
extern HWND
mouseTimerFrame,
mouseClickTypeFrame,
mouseClickRepeatFrame,
mouseRepeatTimesEntry,
mouseRepeatTimesSpin,
mouseCountdownHour,
mouseCountdownMinute,
mouseCountdownSecond,
mouseEnterHour,
mouseEnterMinute,
mouseEnterSecond,
mouseEnterMilliSecond,

keyboardTimerFrame,
keyboardKeyFrame,
keyboardPressRepeatFrame,
keyboardRepeatTimesEntry,
keyboardRepeatTimesSpin,
keyboardCountdownHour,
keyboardCountdownMinute,
keyboardCountdownSecond,
keyboardEnterHour,
keyboardEnterMinute,
keyboardEnterSecond,
keyboardEnterMilliSecond,

settingsFrame,
selectThemeFrame,
randIntervalAndHoldTimeFrame,
randomIntervalEnter,
holdTimeEnter;

void LoadingEntries(HWND hWnd, HINSTANCE hInstance);



/* fonts.cpp */
extern HFONT globalFont;

void LoadingFonts (HWND hWnd);



/* initloader.cpp */
extern WCHAR
bufSaveMouseHotkeySpecW[12],
bufSaveMouseHotkeyW[20],
bufSaveKeyboardHotkeySpecW[12],
bufSaveKeyboardHotkeyW[20];

void LoadInit(HWND hWnd);
void SaveInit(HWND hWnd);



/* input.cpp */
#define HOTKEYAUTOCLICKER	1
#define HOTKEYAUTOPRESSER	2

#define LEFT	0
#define RIGHT	1
#define MIDDLE	2

#define SINGLE	0
#define DOUBLE	1
#define HOLD	2

extern int mouseButton, clickType;
extern LRESULT isKeyboardHoldMode;
extern UINT
mouseHotkey,
mouseSpecialKey,
keyboardKey,
keyboardHotkey,
keyboardSpecialKey;

extern char
*mouseHotkeyTextA,
*mouseHotkeySpecialTextA,
*keyboardHotkeyTextA,
*keyboardHotkeySpecialTextA,
*hotkeyTextA,
*hotkeySpecialTextA;

extern WCHAR
*mouseHotkeyTextW,
*mouseHotkeySpecialTextW,
*keyboardHotkeyTextW,
*keyboardHotkeySpecialTextW,
*hotkeyTextW,
*hotkeySpecialTextW;

void GetHotkey(HWND hWnd, UINT* hotkey, bool* hotkeySelected, int selectMod);
void LoadHotkeyW(HWND hWnd, WCHAR *hotkeySpecTxtW, UINT *specialKey, WCHAR *hotkeyTxtW, UINT *hotkey, int selectMod);
void LoadHotkeyA(HWND hWnd, char *hotkeySpecTxtA, UINT *specialKey, char *hotkeyTxtA, UINT *hotkey, int selectMod);
void GetDebugHexCode(HWND debugHotkeyButton);
int GetMouseButton(HWND mouseLmBText);
int GetMouseClickType(HWND mouseClickTypeWnd);
UINT GetKeyboardKey(HWND keyboardSelectedKey);
void SingleClick();
void DoubleClick();
void HoldMouse();
void HoldKey();
void ReleaseMouse();
void ReleaseKey();
void StartPressing(UINT keyboardKey);



/* images.cpp */
void LoadingImages();
void GetImages(HDC hdc, int themeOption);
void DestroyImages();




/* misc.cpp */
#define AUTOCLICKER 0
#define AUTOPRESSER 1

extern OSVERSIONINFO winver;
extern bool
mouseActive,
keyboardActive;

int DPIScale(int value);
bool isWindowsNT();
bool isWindowsXPLater();
void RealignZOrderChain(HWND hWnd);
void ActiveAppearance(HWND hWnd, int mod, bool isEnabled);
void HotkeySelectionAppearance(HWND hWnd, WORD hotkeyButtonId, bool isEnabled);
void DebugAppearance(HWND hWnd, bool isEnabled);
void PopulateComboBox(HWND keyboardSelectedKey, HKL hkl);



/* pages.cpp */
#define MAINPAGE		0
#define SETTINGSPAGE	1

void ShowPage(int page);



/* systemtray.cpp */
extern LRESULT isTrayChecked;

void SystemTrayInit(HWND hWnd, HINSTANCE hInstance);
void MinimizeToTray();
void ShowTrayMenu(HWND hWnd, POINT pt, bool mouseActive, bool keyboardActive);
void RemoveTrayIcon();



/* texts.cpp */

// To prevent "conversion from size_t to int" warning.
#define STRLEN_INT(x) static_cast<int>(strlen(x))

void PageTexts(HDC hdc, int pageTexts);



/* themes.cpp */

// THEMENUMBERS
#define THEMEDEFAULT	0
#define THEMEBURLYWOOD	1
#define THEMEGOLD		2  // v1.0.1
#define THEMEGREY		3
#define THEMEMAGIC		4  // v1.0.1
#define THEMEROCKET		5  // v1.0.2
#define THEMESOCCER		6
#define THEMEOCEANIC	7

extern int themeOption;
extern HBRUSH themeColor;
extern COLORREF lineColor1, lineColor2;

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color, int lineWidth);
void SelectTheme();



/* timer.cpp */
typedef enum
{
	CLICKER,
	CLICKER_TICKTOCK,
	HOLDCLICK,
	RELEASECLICK,

	PRESSER,
	PRESSER_TICKTOCK,
	HOLDKEY,
	RELEASEKEY
} TimerNames;

extern MMRESULT timers[8];
extern bool holdingMouseInProgress, holdingKeyInProgress;

int StartAutomation(HWND hWnd, int mod);
int UpdateCountdown(int mod);

void ToggleMenusDuringAutomation(HWND hWnd, int mod, int hideShow);



/* tooltip.cpp */
extern LRESULT isDisableTooltipsChecked;

void LoadingTooltips(HWND hWnd);
void Tooltips(HWND hWnd, int mode);



#endif