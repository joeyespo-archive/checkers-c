// Main.h - Checkers
// Entry Point Header of Application
// By Joe Esposito


#pragma once



// Libraries
// ----------

#include <Windows.h>
#include <eLibWin.h>
#include <eModal.h>
#include <eThemes.h>
#include <eGradient.h>
#include <RichEdit.h>
#include <mmSystem.h>
#include <Time.h>	// !!!!! Use time functions for gameplay timer

#define ECKWINDOW_INCLUDE	// !!!!!
#include <eCkWindow.h>

#include "Res\Resource.h"



// Application Window Classes
// ---------------------------

#define ID_MAINWND_CLASSNAME	"_espo@@CheckersMain"
#define ID_ABOUTWND_CLASSNAME	"_espo@@CheckersAbout"
#define ID_GAMEWND_CLASSNAME	"_espo@@CheckersGame"



// Global Structs
// ---------------

// Application Options
typedef struct _APPOPTIONS
{
	unsigned long bShowQuitConfirm : 1;
	unsigned long bStartLastPosition : 1;
	int lastX;
	int lastY;
	COLORREF crSquare1;
	COLORREF crSquare2;
} APPOPTIONS, *LPAPPOPTIONS;



// Global Variables
// -----------------

extern HINSTANCE hInstance;				// Application's current hInstance

extern HWND hDialogWnd;					// Current [focused] dialog window

extern HFONT hFont_Main;				// Main Font (Normal)
extern HFONT hFont_MainBold;			// Main Font (Bold)

extern APPOPTIONS oOptions;				// Application Options



// Global Declarations
// --------------------

INT AppFailed ( char *lpszError = NULL );		// If loading fails
void LoadAppOptions ( LPAPPOPTIONS lpOptions );	// Load application options



// Include Headers
// ----------------

#include "frmMain.h"
#include "frmAbout.h"
#include "frmGame.h"



// Implementation File:
// "Main.cpp"
