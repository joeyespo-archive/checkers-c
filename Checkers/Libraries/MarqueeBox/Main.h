// Main.h - MarqueeBox
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


#ifdef MARQUEEBOX_INCLUDE

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

#endif



// Library Files
// ----------------------------------------------------------------------

// Public Headers
// ---------------

// MarqueeBox functions
#include "Public\MarqueeBox.h"			// MarqueeBox functions



// Internal Sources
// -----------------

// MarqueeBox functions
#include "Private\MarqueeBoxProc.h"		// MarqueeBox procedure function

// ----------------------------------------------------------------------



// Implementation File:
// "Main.cpp"
