// Main.h
// Entry Point Header File
// By Joe Esposito


#pragma once



// Include Libraries
// ------------------

#include <Windows.h>					// Windows Header
#include <eThemes.h>					// eThemes [color schemes]

// !!!!! Checkers Core
#define ECHECKERS_INCLUDE
#include <eCheckers.h>



// Macro Declarations
// -------------------

#undef ECALL
#undef ESTDCALL


#ifdef ECKWINDOW_INCLUDE

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

// Checkers main
#include "eCkWindow.h"					// Checkers functions

// ----------------------------------------------------------------------



// Implementation File:
// "Main.cpp"
