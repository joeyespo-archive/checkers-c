// ButtonAdv.h
// ButtonAdv Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(BUTTONADV_INCLUDE)) && (!defined(BUTTONADV_SOURCE)) && (!defined(BUTTONADV_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:ButtonAdvD.lib" )
#else
#pragma comment ( linker, "/defaultlib:ButtonAdv.lib" )
#endif
#endif

#ifdef BUTTONADV_INCLUDE
#include "ButtonAdv\Main.h"
#endif
#ifdef BUTTONADV_SOURCE
#define BUTTONADV_INCLUDE
#include "ButtonAdv\Main.cpp"
#endif



#if ( (!defined(BUTTONADV_INCLUDE)) && (!defined(BUTTONADV_SOURCE)) && (!defined(_BUTTONADV_)) )

#define _BUTTONADV_


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Macros
// --------------

// Class ID
#define ID_BUTTONADV_CLASSNAME		"buttonadv"

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


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
