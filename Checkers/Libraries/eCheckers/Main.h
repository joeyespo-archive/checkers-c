// Main.h
// Entry Point Header File
// By Joe Esposito


#pragma once



// Include Libraries
// ------------------

#include <math.h>



// Macro Declarations
// -------------------

#undef ECALL
#undef ESTDCALL


#ifdef ECHECKERS_INCLUDE

// Handles
#ifdef STRICT
struct HCKGAME__ { int unused; }; typedef struct HCKGAME__ *HCKGAME;
#else
typedef void *HCKGAME;
#endif

// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		

// Define struct handles
#define HECKGAME			HCKGAME


#else	// If compiling as a library


// Define function modifiers and structs
#define ECALL			extern "C"
#define ESTDCALL		__stdcall

// Define structs
#define HECKGAME		LPECKGAME

#endif



// Library Files
// ----------------------------------------------------------------------

// Public Headers
// ---------------

// Checkers core
#include "eCkGame.h"					// Checkers functions

// ----------------------------------------------------------------------



// Implementation File:
// "Main.cpp"
