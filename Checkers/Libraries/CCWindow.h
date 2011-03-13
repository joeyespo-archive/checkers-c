// ButtonAdv.h
// ButtonAdv Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(CCWINDOW_INCLUDE)) && (!defined(CCWINDOW_SOURCE)) && (!defined(CCWINDOW_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:CCWindowD.lib" )
#else
#pragma comment ( linker, "/defaultlib:CCWindow.lib" )
#endif
#endif

#ifdef CCWINDOW_INCLUDE
#include "CCWindow\Main.h"
#endif
#ifdef CCWINDOW_SOURCE
#define CCWINDOW_INCLUDE
#include "CCWindow\Main.cpp"
#endif



// Using CCWindow
// -----------------------------------------------------------------------------------------
// 
// Window Rules:
// 
//
// CCFrame window procedure rules
// ----------------------------------------------------------------
// 
// - Invalid window styles
//   - All window styles are valid
// 
// - Invalid extended window styles
//   - WS_EX_LEFTSCROLLBAR
//   - WS_EX_RIGHTSCROLLBAR
// 
// NOTE: The styles listed will have no effect on the window.
//       All other extended window styles are valid.
// 
// ----------------------------------------------------------------
//
//
// CCClient window procedure rules
// ----------------------------------------------------------------
// 
// - WM_CREATE: lpCreateParams of the CREATESTRUCT is a pointer 
//              to the CCCLIENTCREATESTRUCT structure passed to
//              the CCFrame when creating the CCClient window.
// 
// - You MUST pass all unhandled messages to DefCCClientProc(),
//   instead of the DefWindowProc() function.
// 
// - You can access the CCFrame's color scheme for
//   color correlation.
// 
// - Available window styles
//   - WS_DISABLED
//   - WS_BORDER
//   - WS_DLGFRAME
//   - WS_THICKFRAME
// 
//  NOTE: No other window style will have any effect on the window
// 
// - Available extended window styles
//   - WS_EX_DLGMODALFRAME
//   - WS_EX_ACCEPTFILES
//   - WS_EX_TRANSPARENT
//   - WS_EX_WINDOWEDGE
//   - WS_EX_CLIENTEDGE
//   - WS_EX_CONTEXTHELP
//   - WS_EX_RIGHT
//   - WS_EX_RTLREADING
//   - WS_EX_LEFTSCROLLBAR
//   - WS_EX_RIGHTSCROLLBAR
//   - WS_EX_CONTROLPARENT
//   - WS_EX_STATICEDGE
//  
//  NOTE: No other extended window style will have any effect on the window
// 
// ----------------------------------------------------------------
// 
// -----------------------------------------------------------------------------------------



// Library Declarations
// -----------------------------------------------------------------------------------------

#if ( (!defined(CCWINDOW_INCLUDE)) && (!defined(CCWINDOW_SOURCE)) && (!defined(_CCWINDOW_)) )

#define _CCWINDOW_


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Macros
// --------------

// Classes
#define ID_CCFRAME_CLASSNAME		"ccframe"
#define ID_CCCLIENT_CLASSNAME		"ccclient"



// CCFrame Styles
// ---------------

#define CCFS_NORMAL					0x00000000		// Normal mode
#define CCFS_VSCROLLBAR				0x00000001		// Verticle scroll bar
#define CCFS_HSCROLLBAR				0x00000002		// Horizontal scroll bar
#define CCFS_NOHIDESCROLLBAR		0x00000004		// Scroll bars are always visible



// CCFrame Messages
// -----------------

// Sent to the CCClient window to get or set info
#define CCFM_CREATE					(WM_USER+3)		// Creates a client window (wParam = NULL; lParam = LPCCCREATESTRUCT)
#define CCFM_DESTROY				(WM_USER+4)		// Destroys a client window (wParam = hwndChild; lParam = CCClient ID, only if wParam is NULL)
#define CCFM_SETACTIVEWINDOW		(WM_USER+5)		// Sets the active CCClient window (lParam: CCClient hWnd)
#define CCFM_GETACTIVEWINDOW		(WM_USER+6)		// Returns current activated CCClient window (Returns: hWnd of activated CCClient window)
#define CCFM_SETACTIVEWINDOWID		(WM_USER+7)		// Selects a created CCClient window to be active (lParam = CCClient ID)
#define CCFM_GETACTIVEWINDOWID		(WM_USER+8)		// Returns current activated CCClient window (Returns: ID of activated CCClient window)
#define CCFM_SETCOLORSCHEME			(WM_USER+9)		// Sets the custom window colors (lParam: handle to theme object structure) * NOTE: change does NOT redraw the window; to do so just call: InvalidateRect(hCCFrameWnd, NULL, FALSE); UpdateWindow(hCCFrameWnd);
#define CCFM_GETCOLORSCHEME			(WM_USER+10)	// Gets the custom window colors (Returns: handle to theme object structure)
#define CCFM_SETBKCOLOR				(WM_USER+11)	// Sets the custom bg color (lParam: (COLORREF)crNewColor)  * NOTE: change does NOT redraw the window; to do so just call: InvalidateRect(hCCFrameWnd, NULL, FALSE); UpdateWindow(hCCFrameWnd);
#define CCFM_GETBKCOLOR				(WM_USER+12)	// Gets the custom bg color (Returns: (COLORREF)crBackcolor)
#define CCFM_GETBKBRUSH				(WM_USER+13)	// Gets the custom bg brush (Returns: (HBRUSH)hbrBackcolor)
#define CCFM_SETUSERDATA			(WM_USER+14)	// Sets the user data (lParam = (LPVOID)lpUserData)
#define CCFM_GETUSERDATA			(WM_USER+15)	// Gets the user data (Returns: (LPVOID)lpUserData)



// Public CCClient Structs
// ------------------------

typedef struct tagCCCLIENTCREATESTRUCT
{
    int cx;								// Initial width
    int cy;								// Initial height
	UINT uId;							// CCClient identifier
	DWORD dwStyle;						// CCClient window stlyes
	DWORD dwExStyle;					// CCClient extended window stlyes
	WNDPROC lpWndProc;					// Window procedure
	HINSTANCE hInstance;				// Application instance handle
	LPVOID lpReserved;					// Reserved for internal use
    LPARAM lParam;						// User data to be passed to WM_CREATE
} CCCLIENTCREATESTRUCT, *LPCCCLIENTCREATESTRUCT;



// CCClient Styles
// ----------------

#define CCCS_ALIGNTOPLEFT			0x00000000		// Align top, left corner
#define CCCS_ALIGNBOTTOMLEFT		0x00000001		// Align bottom, left corner
#define CCCS_ALIGNTOPRIGHT			0x00000002		// Align top, right corner
#define CCCS_ALIGNBOTTOMRIGHT		0x00000003		// Align bottom, right corner
#define CCCS_ALIGNTOP				0x00000004		// Align top side
#define CCCS_ALIGNBOTTOM			0x00000005		// Align bottom side
#define CCCS_ALIGNLEFT				0x00000006		// Align left side
#define CCCS_ALIGNRIGHT				0x00000007		// Align right side
#define CCCS_ALIGNCENTER			0x00000008		// Align center
#define CCCS_ALIGNUSER				0x00000009		// Allows the user to control alignment
#define CCCS_ALIGNMASK				0x0000000F		// Mask of window alignment



// CCClient Messages
// ------------------

// Sent to the CCClient window to set or get info
#define CCCM_GETCCFRAME				(WM_USER+2)		// Returns the control container frame window (Returns: (HWND)hWndCCFrame)
#define CCCM_GETCOLORSCHEME			(WM_USER+3)		// Returns the CCFrame's ColorScheme (Returns: (HSCHEME)hScheme)
#define CCCM_GETBKCOLOR				(WM_USER+4)		// Returns the CCFrame's background color (Returns: (COLORREF)crBackground)
#define CCCM_GETBKBRUSH				(WM_USER+5)		// Returns the CCFrame's background brush (Returns: (HBRUSH)hbrBackground)
#define CCCM_GETCCFUSERDATA			(WM_USER+6)		// Gets the CCFrame's user data (Returns: (LPVOID)lpUserData)
#define CCCM_SETUSERDATA			(WM_USER+7)		// Sets the user data, and returns the old value (lParam = (LPVOID)lpUserData; Returns: (LPVOID)lpUserData)
#define CCCM_GETUSERDATA			(WM_USER+8)		// Gets the user data (Returns: (LPVOID)lpUserData)

// Handled by user in CCClient subclassed procedure
#define CCCM_GETUSERDATA			(WM_USER+10)	// Tells user to re-align the window (CCFrame has resized)



// Public Declarations
// --------------------

// Registering classes
BOOL WINAPI RegisterCCWindow ( HINSTANCE hInstance );
BOOL WINAPI UnregisterCCWindow ( HINSTANCE hInstance );

// Default CCClient window procedure
LRESULT CALLBACK DefCCClientProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// Called instead of DefWindowProc() in a CCClient window procedure


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL

// -----------------------------------------------------------------------------------------
