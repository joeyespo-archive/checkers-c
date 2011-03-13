// ButtonAdv.h
// ButtonAdv Library Header File
// By Joe Esposito


#pragma once



// Public Macros
// --------------

// Class ID
#define ID_BUTTONADV_CLASSNAME		"buttonadv"

// !!!!! Window Styles
// !!!!! #define own styles

// Window Messages
#define BN_MOUSEENTER		0x1001
#define BN_MOUSEEXIT		0x1002



// Public Declarations
// --------------------

// Registering functions:
BOOL WINAPI RegisterButtonAdv ( HINSTANCE hInstance );
BOOL WINAPI UnregisterButtonAdv ( HINSTANCE hInstance );

// Default window procedure
WNDPROC WINAPI DefButtonAdvProc ();



// Implementation File:
// "ButtonAdv.cpp"
