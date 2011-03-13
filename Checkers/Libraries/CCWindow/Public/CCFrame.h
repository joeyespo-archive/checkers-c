// CCFrame.h - CCWindow
// Control Container Frame Header File
// By Joe Esposito


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


#pragma once



// Public Macros
// --------------

// Classes
#define ID_CCFRAME_CLASSNAME		"ccframe"



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



// Implementation File:
// "CCFrame.cpp"
