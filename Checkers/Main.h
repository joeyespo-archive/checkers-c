// Main.h
// Entry Point Header File
// By Joe Esposito


#pragma once



// Include Libraries
// ------------------

// General headers
#include <Time.h>  // !!!!! Use time functions for gameplay timer

// Windows headers
#include <Windows.h>
#include <mmSystem.h>
#include <RichEdit.h>
#include <eLibWin.h>
#include <eThemes.h>
#include <eGradient.h>

// Checkers headers
#define ECKWINDOW_INCLUDE  // !!!!!
#include <eCkWindow.h>

// Resource header
#include "Res\Resource.h"



// Application Window Classes
// ---------------------------

#define ID_MAINWND_CLASSNAME    "_espo@@CheckersMain"
#define ID_GAMEWND_CLASSNAME    "_espo@@CheckersGame"
#define ID_ABOUTWND_CLASSNAME   "_espo@@CheckersAbout"



// Global Macros
// --------------

#define SAFE_DESTROYICON(icon)  if (icon) { DeleteObject(icon); icon = NULL; }
#define SAFE_DELETEOBJ(obj)     if (obj) { DeleteObject(obj); obj = NULL; }



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



// Globals
// --------

// Instance variables
extern HINSTANCE hInstance;            // Application's current hInstance

// Application Variables
extern HWND hDialogWnd;              // Current [focused] dialog window
extern HFONT hFont_Main;            // Main Font (Normal)
extern HFONT hFont_MainBold;          // Main Font (Bold)
extern APPOPTIONS oOptions;            // Application Options



// Global Declarations
// --------------------

// Application initialization functions
INT Init ( HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd );  // Initializes application
INT Terminate ();  // Terminates application
INT AppFailed ( char *lpszError = NULL );    // Called when loading fails
BOOL LoadAppOptions ( LPAPPOPTIONS lpOptions );  // Loads application options



// Include Headers
// ----------------

// Windows
#include "wndMain.h"        // Main window header
#include "wndGame.h"        // Main window header
#include "wndAbout.h"       // About window header



// Implementation File:
// "Main.cpp"
