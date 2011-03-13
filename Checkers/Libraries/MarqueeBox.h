// MarqueeBox.h
// MarqueeBox Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(MARQUEEBOX_INCLUDE)) && (!defined(MARQUEEBOX_SOURCE)) && (!defined(MARQUEEBOX_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:MarqueeBoxD.lib" )
#else
#pragma comment ( linker, "/defaultlib:MarqueeBox.lib" )
#endif
#endif

#ifdef MARQUEEBOX_INCLUDE
#include "MarqueeBox\Main.h"
#endif
#ifdef MARQUEEBOX_SOURCE
#define MARQUEEBOX_INCLUDE
#include "MarqueeBox\Main.cpp"
#endif



#if ( (!defined(MARQUEEBOX_INCLUDE)) && (!defined(MARQUEEBOX_SOURCE)) && (!defined(_MARQUEEBOX_)) )

#define _MARQUEEBOX_


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Macros
// --------------

// Class ID
#define ID_MARQUEEBOX_CLASSNAME		"marqueebox"

// Window Messages
#define BN_MOUSEENTER		0x1001
#define BN_MOUSEEXIT		0x1002



// Public Declarations
// --------------------

// Registering functions:
BOOL WINAPI RegisterMarqueeBox ( HINSTANCE hInstance );
BOOL WINAPI UnregisterMarqueeBox ( HINSTANCE hInstance );


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
