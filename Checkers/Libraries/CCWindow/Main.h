// Main.h - CCWindow
// Entry Point Header File
// By Joe Esposito


#pragma once



// Include Libraries
// ------------------

#include <Windows.h>					// Windows base
#include <eThemes.h>					// Windows themes library



// Macro Declarations
// -------------------

#undef ECALL
#undef ESTDCALL


#ifdef CCWINDOW_INCLUDE

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



// Library Source Files
// ---------------------------------------------------------------------------------

// Public Sources
// ---------------

// Control Container Window functions
#include "Public\CCWindow.h"		// Control Container Window functions
#include "Public\CCFrame.h"			// Control Container Frame functions
#include "Public\CCClient.h"		// Control Container Client functions



// Internal Sources
// -----------------

// Control Container Window functions
#include "Private\CCWnd.h"			// Control Container Window declarations
#include "Private\CCFProc.h"		// Control Container Frame window procedure
#include "Private\CCCProc.h"		// Control Container Client window procedure

// ---------------------------------------------------------------------------------



#ifndef CCWINDOW_SOURCE

// Free macros
// ------------

#undef ECALL
#undef ESTDCALL

#endif


// Implementation File:
// "Main.cpp"
