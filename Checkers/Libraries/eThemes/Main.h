// Main.h
// Entry Point Header File
// By Joe Esposito


#pragma once



// Include Libraries
// ------------------

#include <Windows.h>					// Windows Base



// Macro Declarations
// -------------------

#undef ECALL
#undef ESTDCALL


#ifdef ETHEMES_INCLUDE

// Handles
#ifdef STRICT
struct HTHEMEOBJ__ { int unused; }; typedef struct HTHEMEOBJ__ *HTHEMEOBJ;
struct HTHEME__ : HTHEMEOBJ__ { int unused; }; typedef struct HTHEME__ *HTHEME;
struct HSCHEME__ : HTHEMEOBJ__ { int unused; }; typedef struct HSCHEME__ *HSCHEME;
#else
typedef void *HTHEMEOBJ;
typedef void *HTHEME;
typedef void *HSCHEME;
#endif

// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		

// Function Modifiers
#ifndef STATIC
#define STATIC			static
#endif
#ifndef LOCAL
#define LOCAL			STATIC
#endif

// Define struct handles
#define HETHEME			HTHEME
#define HESCHEME		HSCHEME
#define HETHEMEOBJ		HTHEMEOBJ


#else	// If compiling as a library


// Define function modifiers and structs
#define ECALL			extern "C"
#define ESTDCALL		__stdcall

// Function Modifiers
#ifndef STATIC
#define STATIC			static
#endif
#ifndef LOCAL
#define LOCAL			STATIC
#endif

// Define structs
#define HETHEME			LPETHEME
#define HESCHEME		LPESCHEME
#define HETHEMEOBJ		LPETHEMEOBJ

#endif



// Library Files
// ----------------------------------------------------------------------

// Public Headers
// ---------------

// Theme objects
#include "Public\eTheme.h"				// eTheme object
#include "Public\eScheme.h"				// eScheme object

// Scheme objects
#include "Public\eUserScheme.h"			// eUserScheme object
#include "Public\eColorScheme.h"		// eColorScheme object
#include "Public\ColorFunctions.h"		// eColorScheme functions



// Internal Headers
// -----------------

// Theme objects
#include "Private\Themes.h"				// Internal theme object
#include "Private\Schemes.h"			// Internal scheme object

// Scheme objects
#include "Private\UserSchemes.h"		// Internal user scheme object
#include "Private\ColorSchemes.h"		// Internal color scheme object

// ----------------------------------------------------------------------



// Implementation File:
// "Main.cpp"
