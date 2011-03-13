// CCWnd.h - CCWindow
// Control Container Private Header File
// By Joe Esposito



// Internal Structure Declarations
// --------------------------------

// CCFrame structs
struct tagCCFRAMEINFO; typedef tagCCFRAMEINFO CCFRAMEINFO, *LPCCFRAMEINFO;	// CCFrame window info
struct tagCCCITEM; typedef tagCCCITEM CCCITEM, *LPCCCITEM;		// CCClient item data

// CCClient structs
struct tagCCCLIENTINFO; typedef tagCCCLIENTINFO CCCLIENTINFO, *LPCCCLIENTINFO;	// CCClient window info



// Internal Declarations
// ----------------------

LOCAL BOOL _ActivateCCClientWindow ( HWND hCCWnd, LPCCFRAMEINFO lpcci, LPCCCITEM lpcccitem );
LOCAL BOOL _RelocateCCCWnd ( HWND hCCCWnd, INT cx, INT cy, BOOL bShow );



// Implementation File:
// "CCWnd.cpp"
