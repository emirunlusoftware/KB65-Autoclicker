#pragma once
#include "stdafx.h"
#include "resource.h"



// MOUSE SUBPAGE
#define ACTIVATEMOUSETRAY			900
#define ACTIVATEMOUSE				901

#define MOUSECLICKTIMER				902
#define MOUSEENTERHOUR				903
#define MOUSEENTERMINUTE			904
#define MOUSEENTERSECOND			905
#define MOUSEENTERMILLISECOND		906

#define MOUSECLICKTYPE				907
#define MOUSELMB					908
#define MOUSESINGLEORDOUBLE			909

#define MOUSECLICKREPEAT			910
#define MOUSEREPEATINFINITY			911
#define MOUSEREPEATTIMES			912
#define MOUSEREPEATTIMESENTRY		913
#define MOUSEREPEATTIMESSPIN		914
#define MOUSEREPEATCOUNTDOWN		915
#define MOUSEREPEATTIMERHOUR		916
#define MOUSEREPEATTIMERMINUTE		917
#define MOUSEREPEATTIMERSECOND		918

#define MOUSECLICKSTARTBUTTON		919
#define MOUSECLICKSTOPBUTTON		920
#define MOUSECLICKHOTKEYBUTTON		921
#define MOUSECLICKHOTKEY			922



// KEYBOARD SUBPAGE
#define ACTIVATEKEYBOARDTRAY		923
#define ACTIVATEKEYBOARD			924

#define KEYBOARDPRESSTIMER			925
#define KEYBOARDENTERHOUR			926
#define KEYBOARDENTERMINUTE			927
#define KEYBOARDENTERSECOND			928
#define KEYBOARDENTERMILLISECOND	929

#define KEYBOARDSELECTKEY			930
#define KEYBOARDSELECTAUTOMATEDKEY	931

#define KEYBOARDPRESSREPEAT			932
#define KEYBOARDREPEATINFINITY		933
#define KEYBOARDREPEATTIMES			934
#define KEYBOARDREPEATTIMESENTRY	935
#define KEYBOARDREPEATTIMESSPIN		936
#define KEYBOARDREPEATCOUNTDOWN		937
#define KEYBOARDREPEATTIMERHOUR		938
#define KEYBOARDREPEATTIMERMINUTE	939
#define KEYBOARDREPEATTIMERSECOND	940

#define KEYBOARDPRESSSTARTBUTTON	941
#define KEYBOARDPRESSSTOPBUTTON		942
#define KEYBOARDPRESSHOTKEYBUTTON	943
#define KEYBOARDPRESSHOTKEY			944


// SETTINGS PAGE
#define LOADSCRIPTSBUTTON			945
#define SAVESCRIPTSBUTTON			946
#define INFOBUTTON					947
#define SETTINGSBUTTON				948

#define SETTINGSFRAME				949
#define THEMEGROUPBOX				950
#define THEMESLISTCOMBOBOX			951
#define MINIMIZEONTRAY				952
#define ALWAYSONTOP					953
#define DEBUGHOTKEYBUTTON			954
#define BACKTOMAINBUTTON			955


// OTHER ID'S
#define OPENTRAY					956
#define QUITTRAY					957
#define MINIMIZETRAY				958
#define MAXIMIZETRAY				WM_USER + 1
#define AUTOCLICKERTIMER			959
#define AUTOPRESSERTIMER			960
#define AUTOCLICKERCOUNTDOWN		961
#define AUTOPRESSERCOUNTDOWN		962
#define AUTOCLICKER_TICKTOCK		963
#define AUTOPRESSER_TICKTOCK		964





/* buttons.cpp */
extern HWND
activateMouseCheckBox,
mouseLmB,
mouseSingleOrDouble,
mouseRepeatInfinity,
mouseRepeatTimes,
mouseRepeatTimer,
mouseClickStart,
mouseClickStop,
mouseHotkeyButton,

activateKeyboardCheckBox,
keyboardSelectedKey,
keyboardRepeatInfinity,
keyboardRepeatTimes,
keyboardRepeatTimer,
keyboardPressStart,
keyboardPressStop,
keyboardHotkeyButton,

infoButton,
loadScriptsButton,
saveScriptsButton,
settingsButton,

themesList,
minimizeOnTray,
alwaysOnTop,
debugHotkeyButton,
backToMainButton,

tooltipWindow;

extern LRESULT isAlwaysOnTopChecked;

void LoadingButtons(HWND hWnd, HINSTANCE hInstance);



/* entries.cpp */
extern HWND
mouseClickTimer,
mouseClickType,
mouseClickRepeat,
mouseRepeatTimesEntry,
mouseRepeatTimesSpin,
mouseRepeatTimerHour,
mouseRepeatTimerMinute,
mouseRepeatTimerSecond,
mouseEnterHour,
mouseEnterMinute,
mouseEnterSecond,
mouseEnterMilliSecond,

keyboardPressTimer,
keyboardPressRepeat,
keyboardRepeatTimesEntry,
keyboardRepeatTimesSpin,
keyboardRepeatTimerHour,
keyboardRepeatTimerMinute,
keyboardRepeatTimerSecond,
keyboardEnterHour,
keyboardEnterMinute,
keyboardEnterSecond,
keyboardEnterMilliSecond,
keyboardSelectKey,

settingsFrame,
themeSelect;

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
#define HOTKEYAUTOCLICKER 1
#define HOTKEYAUTOPRESSER 2

#define SINGLE	1
#define DOUBLE	2
#define XTRA	16

extern OSVERSIONINFO winver;
extern UINT
mouseButton,
mouseHotkey,
mouseSpecialKey,
clickType,
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
int GetMouseClickType(HWND mouseClickStartTypeParam);
UINT GetKeyboardKey(HWND keyboardSelectedKey);
void StartAutoClicker(int clickType, int mouseButton);
void StartAutoPresser(UINT keyboardKey);



/* images.cpp */
void LoadingImages();
void GetImages(HDC hdc, int themeOption);



/* misc.cpp */
#define AUTOCLICKER 0
#define AUTOPRESSER 1

float DPIScale();
bool isWindowsNT();
void ActiveAppearance(HWND hWnd, int modType, bool isEnabled, int specParam);
void HotkeyButtonAppearance(HWND hotkeyButton, bool isEnabled);
void HotkeySelectionAppearance(HWND hWnd, int mouseActive, int keyboardActive, bool isEnabled);
void DebugAppearance(HWND hWnd, bool isEnabled);
void PopulateComboBox(HWND keyboardSelectedKey, HKL hkl);



/* pages.cpp */
#define MAINPAGE	 0
#define HIDE		 0
#define SETTINGSPAGE 1
#define SHOW		 1

void ShowPages(int page);



/* systemtray.cpp */
extern HMENU trayMenu;
extern LRESULT isTrayChecked;
void SystemTrayInit(HWND hWnd, HINSTANCE hInstance);
void MinimizeToTray();
void ShowTrayMenu(HWND hWnd, POINT pt, bool mouseActive, bool keyboardActive);
void RemoveTrayIcon();



/* texts.cpp */
void AutoClickerTexts(HDC hdc);
void KeyboardPresserTexts(HDC hdc);
void PageTexts(HDC hdc, int pageTexts);



/* themes.cpp */
#define THEMEDEFAULT	0
#define THEMEBURLYWOOD	1
#define THEMEGREY		2
#define THEMESOCCER		3
#define THEMEOCEANIC	4

extern int themeOption;
extern HBRUSH themeColor;
extern COLORREF lineColor1, lineColor2;

void DrawLine(HDC hdc, double x1, double y1, double x2, double y2, COLORREF color, int lineWidth);
void SelectThemeText(TCHAR themeText[]);
void SelectTheme(int themeOption);



/* timer.cpp */
#define TIMERAUTOCLICKER 1
#define TIMERAUTOPRESSER 2

void RepeatTimes(HWND hWnd, int modType);

extern int
mouseClickStartRepeatTimes,
mouseClickStartRepeatTimesLimit,
mouseClickStartRepeatCountdown,

keyboardPressRepeatTimes,
keyboardPressRepeatTimesLimit,
keyboardPressRepeatCountdown;

int GetRepeatTimer(HWND hWnd, int modType);
int UpdateCountdown(int modType);
void SetAppTimer(HWND hWnd, int selectMod);

extern bool isClickerTimerActive;
void SetAutoclickerTimer(HWND hWnd);

extern bool isPresserTimerActive;
void SetAutopresserTimer(HWND hWnd);