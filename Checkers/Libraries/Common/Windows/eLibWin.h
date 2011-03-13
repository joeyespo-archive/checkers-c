// eLibWin.h
// Esposito Standard Windows Library Header File
// By Joey Esposito


#pragma once



// Include Libraries
// ------------------

#include <eLib.h>
#include <eString.h>

#include <Windows.h>



// Extended Macros
// ----------------

#define BN_MOUSEENTER		0x1001
#define BN_MOUSEEXIT		0x1002



// Basic typedef's
// ----------------

typedef BOOL (CALLBACK *DOEVENTSPROC)(MSG);
typedef unsigned int	uint;



// Resource Macros
// ----------------

#define ResIcon(rIcon)		LoadIcon(hInstance, MAKEINTRESOURCE(rIcon))
#define ResMenu(rMenu)		LoadMenu(hInstance, MAKEINTRESOURCE(rMenu))
#define ResBitmap(rBitmap)	LoadImage(hInstance, MAKEINTRESOURCE(rBitmap), IMAGE_BITMAP, 0, 0, LR_SHARED)
#define ResAccel(rAccel)	LoadAccelerators(hInstance, MAKEINTRESOURCE(rAccel))
#define ResAccelTable		ResAccel
#define ResCursor(rCursor)	LoadCursor(NULL, MAKEINTRESOURCE(rCursor))
#define SysCursor(CursorID)	LoadCursor(NULL, CursorID)
#define SysDefCursor()		LoadCursor(NULL, IDC_ARROW)
#define LoadResBitmap(rBitmap, nStyle)	LoadImage(hInstance, MAKEINTRESOURCE(rBitmap), IMAGE_BITMAP, 0, 0, nStyle)



// Common Window Styles
// ---------------------

#define WS_FIXEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN)
#define WS_SIZABLEWINDOW (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)



// Public Declarations
// --------------------

// Messages:
void DoEvents ( HWND hDialog = NULL, DOEVENTSPROC lpDoEventsProc = NULL );


// Error Messages:
extern void ShowLastError ();
extern void ShowLastErrorDescription ();
extern eString GetLastErrorDescription ();
extern eString GetErrorDescription ( DWORD dwErrCode );

// Displays a MessageBox:
_inline int MsgBox ( const char *lpText = "", const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ((lpText == NULL) ? ("") : (lpText)), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }

_inline int MsgBox ( const bool bValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ((bValue) ? ("True") : ("False")), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const int nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const __int64 nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const unsigned int nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const unsigned __int64 nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const double nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const long nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const unsigned long nValue, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, ToStr(nValue), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }
_inline int MsgBox ( const void *bAddress, const LPCSTR lpCaption = NULL, const UINT uType = MB_OK, const HWND hWnd = 0 )
{ return MessageBox(hWnd, (eString(ToStr((unsigned long)bAddress,16))), ((lpCaption == NULL) ? ("") : (lpCaption)), uType); }


// Create an undefined bitmap
HBITMAP _CreateBitmap ( INT cx, INT cy );


// Create a RECT pointer
_inline LPRECT CreateRect(LONG left, LONG top, LONG right, LONG bottom)
{ LPRECT lprt = new RECT;  lprt->left = left; lprt->top = top; lprt->right = right; lprt->bottom = bottom;  return lprt; }


extern eString GetWindowText ( HWND hWnd );
extern eString GetClassName ( HWND hWnd );


extern BOOL ModifyStyle ( HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags );
extern BOOL ModifyStyleEx ( HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags );

extern BOOL _ModifyStyle ( HWND hWnd, int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags );

extern BOOL HasStyle ( HWND hWnd,DWORD dwStyle );
extern BOOL HasStyleEx ( HWND hWnd, DWORD dwStyle );

extern BOOL _HasStyle ( HWND hWnd, int nStyleOffset, DWORD dwTest );

extern BOOL RefreshWindow ( HWND hWnd, LPRECT lpRect = NULL, BOOL bErase = TRUE );

extern INT X ( HWND hWnd );
extern INT Y ( HWND hWnd );
extern INT Bottom ( HWND hWnd );
extern INT Right ( HWND hWnd );

extern INT Top ( HWND hWnd );
extern INT Left ( HWND hWnd );
extern INT Height ( HWND hWnd );
extern INT Width ( HWND hWnd );

extern INT ClientTop ( HWND hWnd );
extern INT ClientLeft ( HWND hWnd );
extern INT ClientBottom ( HWND hWnd );
extern INT ClientRight ( HWND hWnd );
	
extern INT ClientX ( HWND hWnd );
extern INT ClientY ( HWND hWnd );
extern INT ClientHeight ( HWND hWnd );
extern INT ClientWidth ( HWND hWnd );

extern INT NCWidth ( HWND hWnd );
extern INT NCHeight ( HWND hWnd );

extern BOOL Resize ( HWND hWnd, INT cx, INT cy, UINT uFlags = 0 );
extern BOOL Move ( HWND hWnd, INT x, INT y, UINT uFlags = 0 );
extern BOOL Reposition ( HWND hWnd, INT x, INT y, INT cx, INT cy, UINT uFlags = 0 );
extern BOOL Height ( HWND hWnd, INT cy, UINT uFlags = 0 );
extern BOOL Width ( HWND hWnd, INT cx, UINT uFlags = 0 );
extern BOOL Left ( HWND hWnd, INT x, UINT uFlags = 0 );
extern BOOL Top ( HWND hWnd, INT y, UINT uFlags = 0 );
	
extern BOOL X ( HWND hWnd, INT x, UINT uFlags = 0 );
extern BOOL Y ( HWND hWnd, INT y, UINT uFlags = 0 );
extern BOOL Bottom ( HWND hWnd, INT y, UINT uFlags = 0 );
extern BOOL Right ( HWND hWnd, INT x, UINT uFlags = 0 );

extern RECT GetRect ( HWND hWnd );

//BOOL IsModule ( HMODULE hModule );



// Dialog Boxes
// -------------

extern INT CreateDialogBox ( DWORD dwStyleEx, LPCSTR lpszClassName, LPCSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent, LPSTR lpszMenu, DWORD dwHelpId, HINSTANCE hInstance, DLGPROC lpDialogProc, LPARAM lParam, bool bModalDialog );



// Subclassing
// ------------

extern HWND CreateButton ( LPCTSTR lpWindowText, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, DWORD dwControlID, HINSTANCE hInstance );
extern HWND CreateButtonEx ( DWORD dwStyleEx, LPCTSTR lpWindowText, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, DWORD dwControlID, HINSTANCE hInstance );



// Implinentation File:
// "eLibWin.cpp"
