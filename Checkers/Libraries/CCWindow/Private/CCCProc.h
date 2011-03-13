// CCCProc.h - CCWindow
// Control Container Client Window Procedure Header File
// By Joe Esposito



// Internal Macros
// ----------------

#define CCCLIENT_CCWINDOW_STYLEMASK		(0x0000FFFF)
#define CCCLIENT_ALLOWED_WINDOWSTYLES	(WS_DISABLED | WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | CCCLIENT_CCWINDOW_STYLEMASK)
#define CCCLIENT_ALLOWED_WINDOWEXSTYLES	(WS_EX_DLGMODALFRAME | WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_CONTEXTHELP | WS_EX_RIGHT | WS_EX_RTLREADING | WS_EX_LEFTSCROLLBAR | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT | WS_EX_STATICEDGE)
#define CCCLIENT_FORCED_WINDOWSTYLES	(WS_CHILD | WS_GROUP | WS_CLIPCHILDREN)



// Internal Structures
// --------------------

// CCClient window info
typedef struct tagCCCLIENTINFO
{
	HWND hCCFrameWnd;					// CCFrame window
	WNDPROC lpWndProc;					// Window Procedure
	LPDWORD lpUserData;					// Pointer to dword-aligned user data local to the CCClient
} CCCLIENTINFO, *LPCCCLIENTINFO;



// Internal Declarations
// ----------------------

LOCAL LRESULT CALLBACK _CCClientProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "CCCProc.cpp"
