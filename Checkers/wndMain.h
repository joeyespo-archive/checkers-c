// wndMain.h - Checkers
// Main Window Header File
// By Joe Esposito


#pragma once



// Public Structs
// ---------------

typedef struct tagMAINWNDINFO
{
  HBITMAP hBackground;      // Background bitmap
  HICON hicoLogo;          // Logo icon
  
  // Button icons
  HICON hico1Player, hico2Player, hicoOnline;
  HICON hico1Player_Over, hico2Player_Over, hicoOnline_Over;
} MAINWNDINFO, *LPMAINWNDINFO;



// Public Declarations
// --------------------

HWND CreateMainWindow ();
LRESULT CALLBACK wndMainProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "wndMain.cpp"
