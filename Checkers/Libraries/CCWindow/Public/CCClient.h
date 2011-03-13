// CCClient.h - CCWindow
// Control Container Client Header File
// By Joe Esposito

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


#pragma once



// Public Macros
// --------------

// Classes
#define ID_CCCLIENT_CLASSNAME		"ccclient"



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
#define CCCS_ALIGNMASK				0x0000000F		// Mask of window alignment
#define CCCS_ALIGNUSER				0x00000010		// Allows the user to control CCClient alignment (sends CCCM_GETUSERDATA mesage to CCClient window when CCFrame is resized)



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
#define CCCM_ALIGNWINDOW			(WM_USER+10)	// Tells user to re-align the window; sent when CCFrame has resized (WPARAM = NULL; LPARAM = NULL; RETURN VALUE = Return 0 if handled)



// Public Declarations
// --------------------

// Default CCClient window procedure
LRESULT CALLBACK DefCCClientProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// Called instead of DefWindowProc() in a CCClient window procedure



// Implementation File:
// "CCClient.cpp"
