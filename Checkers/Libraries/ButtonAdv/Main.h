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


#ifdef BUTTONADV_INCLUDE

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

// ButtonAdv functions
#include "Public\ButtonAdv.h"			// ButtonAdv functions



// Internal Sources
// -----------------

// ButtonAdv functions
#include "Private\ButtonAdvProc.h"		// ButtonAdv procedure function

// ----------------------------------------------------------------------



// Implementation File:
// "Main.cpp"
