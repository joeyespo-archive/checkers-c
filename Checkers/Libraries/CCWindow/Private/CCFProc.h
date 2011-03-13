// CCFProc.h - CCWindow
// Control Container Frame Window Procedure Header File
// By Joe Esposito



// Internal Macros
// ----------------

#define CCFRAME_CCWINDOW_STYLEMASK		(0x0000FFFF)
#define CCFRAME_DISABLED_WINDOWSTYLES	(0)
#define CCFRAME_DISABLED_WINDOWEXSTYLES	(WS_EX_LEFTSCROLLBAR | WS_EX_RIGHTSCROLLBAR)



// Internal Structures
// --------------------

// CCFrame window info
typedef struct tagCCFRAMEINFO
{
	HSCHEME hScheme;					// The current scheme
	LPCCCITEM lpActiveCCClient;			// Activated CCClient window item
	UINT nEmptyBorder;					// Pixels between the client and the frame
	UINT uNumCCClients;					// Number of total CCClients
	LPCCCITEM *lpaCCClients;			// Array of pointers to CCClient window items
	LPDWORD lpUserData;					// Pointer to dword-aligned user data for shared information between CCClient windows
} CCFRAMEINFO, *LPCCFRAMEINFO;

// CCClient window item
typedef struct tagCCCITEM
{
	UINT uId;							// Id of window
	HWND hCCClientWnd;					// CCClient window
	bool bDeleting;						// Window is being deleted
} CCCITEM, *LPCCCITEM;



// Internal Declarations
// ----------------------

LOCAL LRESULT CALLBACK _CCFrameProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "CCFProc.cpp"
