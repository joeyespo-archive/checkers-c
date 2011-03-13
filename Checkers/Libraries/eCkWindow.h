// eWinCheckers.h - eCheckers
// eCheckers Windows Graphics and Gameplay [Redirection] Header File
// By Joey Esposito



// Redirect to library
// --------------------

// Import Library
// ---------------

#if ( (!defined(ECKWINDOW_INCLUDE)) && (!defined(ECKWINDOW_SOURCE)) && (!defined(ECKWINDOW_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:eCkWindowD.lib" )
#else
#pragma comment ( linker, "/defaultlib:eCkWindow.lib" )
#endif
#endif

#ifdef ECKWINDOW_INCLUDE
#include "eCkWindow\Main.h"
#endif
#ifdef ECKWINDOW_SOURCE
#define ECKWINDOW_INCLUDE
#include "eCkWindow\Main.cpp"
#endif



#if ( (!defined(ECKWINDOW_INCLUDE)) && (!defined(ECKWINDOW_SOURCE)) && (!defined(_ECKWINDOW_)) )

#define _ECKWINDOW_



// Checkers Board Styles
// ----------------------

#define CKS_AUTOSIZE				0x00000001		// Auto sizes the window to the 
#define CKS_NOAUTOUPDATE			0x00000002		// Doesnt auto-update the window to the 



// Checkers Board Messages
// ------------------------

#define WCKM_UPDATEBOARD			(WM_USER+0)		// Redraws the board (lParam (BOOL) = Update board: must be 0 .. needed only when internally resizing the board)
#define WCKM_SETSCHEMECOLOR			(WM_USER+1)		// Sets a single scheme color (wParam = color scheme index; lParam = color)
#define WCKM_GETSCHEMECOLOR			(WM_USER+2)		// Returns a scheme color (wParam = color scheme index)
#define WCKM_SETSCHEMECOLORS		(WM_USER+3)		// Sets the color scheme (lParam = color scheme to copy)
#define WCKM_GETSCHEMECOLORS		(WM_USER+4)		// Gets the current color scheme (lParam = color scheme to receive colors)
#define WCKM_SETSQUAREBORDERCOLOR	(WM_USER+5)		// Sets the square's border color (lParam =	color)
#define WCKM_GETSQUAREBORDERCOLOR	(WM_USER+6)		// Gets the square's border color (Returns the current color)
#define WCKM_SETBOARDCOLOR1			(WM_USER+7)		// Sets the first square's color (lParam =	color)
#define WCKM_GETBOARDCOLOR1			(WM_USER+8)		// Gets the first square's color (Returns the current color)
#define WCKM_SETBOARDCOLOR2			(WM_USER+9)		// Sets the second square's color (lParam =	color)
#define WCKM_GETBOARDCOLOR2			(WM_USER+10)	// Gets the second square's color (Returns the current color)
#define WCKM_SETBORDERSIZE			(WM_USER+11)	// Sets the border size (wParam = width; lParam = height)
#define WCKM_GETBORDERWIDTH			(WM_USER+12)	// Gets the border width (Returns the current width)
#define WCKM_GETBORDERHEIGHT		(WM_USER+13)	// Gets the border height (Returns the current height)
#define WCKM_SETQUARESIZE			(WM_USER+14)	// Sets the square size (wParam = width; lParam = height)
#define WCKM_GETSQUAREWIDTH			(WM_USER+15)	// Gets the square width (Returns the current width)
#define WCKM_GETSQUAREHEIGHT		(WM_USER+16)	// Gets the square height (Returns the current height)
#define WCKM_SETSQUAREBORDERSIZE	(WM_USER+17)	// Sets the square border size (wParam = width; lParam = height)
#define WCKM_GETSQUAREBORDERWIDTH	(WM_USER+18)	// Gets the square border width (Returns the current width)
#define WCKM_GETSQUAREBORDERHEIGHT	(WM_USER+19)	// Gets the square border height (Returns the current height)
#define WCKM_SETPLAYER1ICON			(WM_USER+20)	// Sets player 1 icon (lParam = HICON)
#define WCKM_GETPLAYER1ICON			(WM_USER+21)	// Returns the player 1 icon (HICON)
#define WCKM_SETPLAYER2ICON			(WM_USER+22)	// Sets player 2 icon (lParam = HICON)
#define WCKM_GETPLAYER2ICON			(WM_USER+23)	// Returns the player 2 icon (HICON)
#define WCKM_GETSIZE				(WM_USER+24)	// Gets the window size that fits the checkers board (lParam = LPRECT to retreive size)
#define WCKM_RESIZE					(WM_USER+25)	// Sizes the window to fit the checkers board



// Checkers Board Notifications
// -----------------------------

#define WCKN_DRAWFRAME				0x0001			// Sent when frame needs drawn (Return values: TRUE = frame was drawn; FALSE = frame was not drawn, draw frame)



// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall


// Public Declarations
// --------------------

ECALL BOOL ESTDCALL RegisterCheckersBoard ( HINSTANCE hInstance );
ECALL BOOL ESTDCALL UnregisterCheckersBoard ( HINSTANCE hInstance );


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
