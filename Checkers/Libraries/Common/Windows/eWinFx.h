// eWinFx.h
// Windows Basic FX Header File
// By Joe Esposito


#pragma once



// Public Declarations
// --------------------

HWND FindWindowAdv ( LPSTR lpClass, LPSTR lpTitle, DWORD dwProcessId );
BOOL EnumWindowsAdv ( LPSTR lpClass, LPSTR lpTitle, DWORD dwProcessId, WNDENUMPROC lpEnumFunc, LPARAM lParam );



// Implementation File:
// "eWinFx.cpp"
