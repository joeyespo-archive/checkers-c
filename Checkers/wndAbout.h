// wndAbout.h - Checkers
// About Window Header File
// By Joey Esposito


#pragma once



// Public Structs
// ---------------

typedef struct tagABOUTWNDINFO
{
  HICON hicoLogo;          // Logo icon
  HBITMAP hBackground;      // Background bitmap
} ABOUTWNDINFO, *LPABOUTWNDINFO;



// Public Declarations
// --------------------

void DoAbout ( HWND hOwner );      // Shows the About Window
LRESULT CALLBACK wndAboutProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "wndAbout.cpp"
