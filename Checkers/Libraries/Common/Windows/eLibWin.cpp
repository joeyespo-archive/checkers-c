// eLibWin.cpp
// Standard Windows Library Implementation File
// By Joey Esposito


#pragma once


// Header File:
#include "eLibWin.h"



// Include Sources
// ----------------

#include <eLib.cpp>



// Local Macros
// -------------

#define CDB_TEMPLATE_NUMSTATICBYTES		26



// Local Function Declarations
// ----------------------------

BOOL _eLibHookWindowCreate ();
BOOL _eLibUnhookWindowCreate ();
LRESULT CALLBACK _eLibCBTProc ( int nCode, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK _eLibButtonProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Local Variables
// ----------------

STATIC HHOOK m_hHookCbtFilter = NULL;



// Public Functions
// -----------------

void DoEvents (HWND hDialog, HWND hMDIClient, DOEVENTSPROC lpDoEventsProc)
{
	MSG msg;

	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (lpDoEventsProc != NULL)
			if (!lpDoEventsProc(msg)) continue;

		if (hMDIClient != NULL)
			if (TranslateMDISysAccel(hMDIClient, &msg)) continue;

		if (!IsDialogMessage(hDialog, &msg)) {		// Check for dialog messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			
		if (msg.message == WM_QUIT) { PostThreadMessage(GetCurrentThreadId(), WM_QUIT, msg.wParam, msg.lParam); break; }
	}
}

void ShowLastError ()
{ MsgBox(GetLastError(), "Error", (MB_OK | MB_ICONERROR)); }

void ShowLastErrorDescription ()
{
	LPSTR lpMsgBuf;
	FormatMessage( (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS), NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	MsgBox(lpMsgBuf, "Error", (MB_OK | MB_ICONERROR));
	LocalFree(lpMsgBuf);
}

void ShowLastErrorMessage ()
{ ShowLastErrorDescription(); }

eString GetLastErrorDescription ()
{ return GetErrorDescription(GetLastError()); }

eString GetLastErrorMessage ()
{ return GetLastErrorDescription(); }

eString GetErrorDescription (DWORD dwErrCode)
{
	eString str;
	LPVOID lpMsgBuf;

	FormatMessage( (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS), NULL, dwErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	str = (char *)lpMsgBuf;

	LocalFree(lpMsgBuf);

	return str;
}

eString GetErrorMessage (DWORD dwErrCode)
{ return GetErrorDescription (dwErrCode); }


eString GetClassName (HWND hWnd)
{
	char *s;
	eString szStr;
	int i = 1056;

	s = new char [i];

	GetClassName(hWnd, s, i);

	szStr = s;
	delete [] s;

	return szStr;
}

eString GetWindowText (const HWND hWnd)
{
	char *s;
	int n = GetWindowTextLength(hWnd);
	eString str;

	s = new char [(n + 1)];
	GetWindowText(hWnd, s, (n + 1));
	
	str = s;
	delete [] s;

	return str;
}



BOOL ModifyStyle (HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{ return _ModifyStyle(hWnd, GWL_STYLE, dwRemove, dwAdd, nFlags); }
BOOL ModifyStyleEx (HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{ return _ModifyStyle(hWnd, GWL_EXSTYLE, dwRemove, dwAdd, nFlags); }

// Change a window's style
BOOL _ModifyStyle (HWND hWnd, int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	DWORD dwStyle = GetWindowLong(hWnd, nStyleOffset);
	DWORD dwNewStyle = ((dwStyle & ~dwRemove) | dwAdd);
	
	if (dwStyle == dwNewStyle) return FALSE;

	SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
	if (nFlags != 0) {
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			((SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) | nFlags));
	}

	return TRUE;
}

BOOL HasStyle (HWND hWnd, DWORD dwStyle)
{ return (_HasStyle(hWnd, GWL_STYLE, dwStyle)); }
BOOL HasStyleEx (HWND hWnd, DWORD dwStyle)
{ return (_HasStyle(hWnd, GWL_EXSTYLE, dwStyle)); }

// Test a window's style
BOOL _HasStyle (HWND hWnd, int nStyleOffset, DWORD dwTest)
{ return ((GetWindowLong(hWnd, nStyleOffset) & dwTest) == dwTest); }


BOOL RefreshWindow (HWND hWnd, LPRECT lpRect, BOOL bErase)
{ InvalidateRect(hWnd, lpRect, bErase); UpdateWindow(hWnd); return TRUE; }

INT X (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.left); }
INT Y (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.top); }
INT Bottom (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.bottom); }
INT Right (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.right); }

INT Top (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.top); }
INT Left (HWND hWnd)
{ RECT rt; if (!GetWindowRect(hWnd, &rt)) return 0; MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2); return (rt.left); }
INT Width (HWND hWnd)
{ RECT rt; GetWindowRect(hWnd, &rt); return (rt.right - rt.left); }
INT Height (HWND hWnd)
{ RECT rt; GetWindowRect(hWnd, &rt); return (rt.bottom - rt.top); }

INT ClientTop (HWND hWnd)
{ RECT rt; if (!GetClientRect(hWnd, &rt)) return 0; return (rt.top); }
INT ClientLeft (HWND hWnd)
{ RECT rt; if (!GetClientRect(hWnd, &rt)) return 0; return (rt.left); }
INT ClientBottom (HWND hWnd)
{ RECT rt; if (!GetClientRect(hWnd, &rt)) return 0; return (rt.bottom); }
INT ClientRight (HWND hWnd)
{ RECT rt; if (!GetClientRect(hWnd, &rt)) return 0; return (rt.right); }
	
INT ClientX (HWND hWnd) { RECT rt; GetClientRect(hWnd, &rt); return (rt.left); }
INT ClientY (HWND hWnd) { RECT rt; GetClientRect(hWnd, &rt); return (rt.top); }
INT ClientWidth (HWND hWnd) { RECT rt; GetClientRect(hWnd, &rt); return (rt.right - rt.left); }
INT ClientHeight (HWND hWnd) { RECT rt; GetClientRect(hWnd, &rt); return (rt.bottom - rt.top); }

INT NCWidth (HWND hWnd) { return (Width(hWnd) - ClientWidth(hWnd)); }
INT NCHeight (HWND hWnd) { return (Height(hWnd) - ClientHeight(hWnd)); }

BOOL Resize (HWND hWnd, INT cx, INT cy, UINT uFlags) { return SetWindowPos(hWnd, NULL, 0, 0, cx, cy, ((SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Move (HWND hWnd, INT x, INT y, UINT uFlags) { return SetWindowPos(hWnd, NULL, x, y, 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Reposition (HWND hWnd, INT x, INT y, INT cx, INT cy, UINT uFlags) { return SetWindowPos(hWnd, NULL, x, y, cx, cy, ((SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Width (HWND hWnd, INT cx, UINT uFlags) { return SetWindowPos(hWnd, NULL, 0, 0, cx, Height(hWnd), ((SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Height (HWND hWnd, INT cy, UINT uFlags) { return SetWindowPos(hWnd, NULL, 0, 0, Width(hWnd), cy, ((SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Left (HWND hWnd, INT x, UINT uFlags) { return SetWindowPos(hWnd, NULL, x, Y(hWnd), 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Top (HWND hWnd, INT y, UINT uFlags) { return SetWindowPos(hWnd, NULL, X(hWnd), y, 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
	
BOOL X (HWND hWnd, INT x, UINT uFlags)
{ return SetWindowPos(hWnd, NULL, x, Y(hWnd), 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Y (HWND hWnd, INT y, UINT uFlags)
{ return SetWindowPos(hWnd, NULL, X(hWnd), y, 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Bottom (HWND hWnd, INT y, UINT uFlags)
{ return SetWindowPos(hWnd, NULL, X(hWnd), (y - Top(hWnd)), 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }
BOOL Right (HWND hWnd, INT x, UINT uFlags)
{ return SetWindowPos(hWnd, NULL, (x - Left(hWnd)), Y(hWnd), 0, 0, ((SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER) | uFlags)); }

RECT GetRect (HWND hWnd)
{
	RECT rt;
	
	GetWindowRect(hWnd, &rt);
	MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rt, 2);
	
	return rt;
}

// Create an undefined bitmap
HBITMAP _CreateBitmap (INT cx, INT cy)
{
	HDC hDC;
	BITMAPINFO bmi;
	HBITMAP hbmpBitmap;
	

	// Create DC
	hDC = CreateCompatibleDC(NULL);

	// Bitmap header
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = -14; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;
	
	// Create the bitmap
	hbmpBitmap = CreateDIBSection(hDC, &bmi, (DIB_RGB_COLORS), NULL, NULL, NULL);

	// Clean up
	DeleteDC(hDC);

	return hbmpBitmap;
}

/*BOOL IsModule (HMODULE hModule)
{
	const DWORD cb = 256;

	HMODULE *lphModules;
	DWORD nNeeded = (cb * sizeof(HMODULE));

	lphModules = new HMODULE [(cb)];
	EnumProcessModules(GetCurrentProcess(), lphModules, cb, &nNeeded);

	nNeeded /= sizeof(HMODULE);
	
	for (UINT i = 0; i < nNeeded; i++)
		if (lphModules[i] == hModule) {
			delete [cb] lphModules;
			return TRUE;
		}

	delete [cb] lphModules;
	return FALSE;
}
*/



// Dialogs
// --------

// Result is value passed to EndDialog() if modal dialog; it is an HWND if non-modal
INT CreateDialogBox (DWORD dwStyleEx, LPCSTR lpszClassName, LPCSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent, LPSTR lpszMenu, DWORD dwHelpId, HINSTANCE hInstance, DLGPROC lpDialogProc, LPARAM lParam, bool bModalDialog)
{
	INT nResult;
	LPWSTR lpszwMenu = NULL; INT nMenuCount;
	LPWSTR lpszwClassName = NULL; INT nClassNameCount;
	LPWSTR lpszwWindowName = NULL; INT nWindowNameCount;
	LPSTR lpTemplate; INT nBytes;
	LPWSTR lpTemplateString;

	// Number of bytes in the static section of the struct
	nBytes = (CDB_TEMPLATE_NUMSTATICBYTES);
	
	
	// Menu setup
	if (lpszMenu == NULL) {
		nMenuCount = 0;			// String menu size (no menu name)
		nBytes += 2;			// Increase by 2: 0x0000 value (word)
	} else if (LOWORD(lpszMenu) == 0xFFFF) {
		nMenuCount = 0;			// String menu size (no menu name)
		nBytes += 4;			// Increase by 4: 0xFFFF value (word) + ordinal (word) = (dword)
	} else {
		// Get required unicode wide-character count (plus 1 wchar for NULL-termination)
		nBytes += (sizeof(WCHAR) * ((nMenuCount = MultiByteToWideChar(CP_ACP, (0), lpszMenu, sizeof(lpszMenu), NULL, 0)) + 1));
	}

	// Class name setup
	if (lpszClassName == NULL) {
		nClassNameCount = 0;	// String size (no string)
		nBytes += 2;			// Increase by 2: 0x0000 value (word)
	} else if (LOWORD(lpszClassName) == 0xFFFF) {
		nClassNameCount = 0;	// String size (no string)
		nBytes += 4;			// Increase by 4: 0xFFFF value (word) + ordinal (word) = (dword)
	} else {
		// Get required unicode wide-character count (plus 1 wchar for NULL-termination)
		nBytes += (sizeof(WCHAR) * ((nClassNameCount = MultiByteToWideChar(CP_ACP, (0), lpszClassName, strlen(lpszClassName), NULL, 0)) + 1));
	}

	// Window name setup
	if (lpszWindowName == NULL) {
		nWindowNameCount = 0;	// String size (no string)
		nBytes += 2;			// Increase by 2: 0x0000 value (word)
	} else if (LOWORD(lpszWindowName) == 0xFFFF) {
		nWindowNameCount = 0;	// String size (no string)
		nBytes += 4;			// Increase by 4: 0xFFFF value (word) + ordinal (word) = (dword)
	} else {
		// Get required unicode wide-character count (plus 1 wchar for NULL-termination)
		nBytes += (sizeof(WCHAR) * ((nWindowNameCount = MultiByteToWideChar(CP_ACP, (0), lpszWindowName, strlen(lpszWindowName), NULL, 0)) + 1));
	}

	// Align on a DWORD boundary
	nBytes += (nBytes % sizeof(DWORD));

	
	// !!!!!
	if (dwStyle & DS_SETFONT) return NULL;


	// Reserve template memory
	if ((lpTemplate = new char [nBytes]) == NULL) return NULL;


	// Add variables to template
	*(LPWORD)(lpTemplate)		= 1;			// Version (word)
	*(LPWORD)(lpTemplate+2)		= 0xFFFF;		// Signature (word)
	*(LPDWORD)(lpTemplate+4)	= dwHelpId;		// Help ID (dword)
	*(LPDWORD)(lpTemplate+8)	= dwStyleEx;	// ExStyle (dword)
	*(LPDWORD)(lpTemplate+12)	= dwStyle;		// ExStyle (dword)
	*(LPWORD)(lpTemplate+16)	= 0;			// Items in dialog box (word)
	*(LPWORD)(lpTemplate+18)	= x;			// x (word:short)
	*(LPWORD)(lpTemplate+20)	= y;			// y (word:short)
	*(LPWORD)(lpTemplate+22)	= nWidth;		// cx (word:short)
	*(LPWORD)(lpTemplate+24)	= nHeight;		// cy (word:short)


	// Add strings to menu
	lpTemplateString = (LPWSTR)(lpTemplate + CDB_TEMPLATE_NUMSTATICBYTES);

	// Add menu to template
	if (nMenuCount == 0) {
		if (lpszMenu == NULL) { *(lpTemplateString) = 0x0000; lpTemplateString += 1; }
		else if (LOWORD(lpszMenu) == 0xFFFF) { *(lpTemplateString) = 0xFFFF; *(lpTemplateString+1) = HIWORD(lpszMenu); lpTemplateString += 2; }
	} else {
		MultiByteToWideChar(CP_ACP, (0), lpszMenu, strlen(lpszMenu), lpTemplateString, nMenuCount);
		lpTemplateString[nMenuCount] = NULL;
		lpTemplateString += (nMenuCount + 1);
	}

	// Add class name to template
	if (nClassNameCount == 0) {
		if (lpszClassName == NULL) { *(lpTemplateString) = 0x0000; lpTemplateString += 1; }
		else if (LOWORD(lpszClassName) == 0xFFFF) { *(lpTemplateString) = 0xFFFF; *(lpTemplateString+1) = HIWORD(lpszClassName); lpTemplateString += 2; }
	} else {
		MultiByteToWideChar(CP_ACP, (0), lpszClassName, strlen(lpszClassName), lpTemplateString, nClassNameCount);
		lpTemplateString[nClassNameCount] = NULL;
		lpTemplateString += (nClassNameCount + 1);
	}

	// Add class name to template
	if (nWindowNameCount == 0) {
		if (lpszWindowName == NULL) { *(lpTemplateString) = 0x0000; lpTemplateString += 1; }
		else if (LOWORD(lpszWindowName) == 0xFFFF) { *(lpTemplateString) = 0xFFFF; *(lpTemplateString+1) = HIWORD(lpszWindowName); lpTemplateString += 2; }
	} else {
		MultiByteToWideChar(CP_ACP, (0), lpszWindowName, strlen(lpszWindowName), lpTemplateString, nWindowNameCount);
		lpTemplateString[nWindowNameCount] = NULL;
		lpTemplateString += (nWindowNameCount + 1);
	}

	
	// !!!!! DS_SETFONT
	// !!!!! DWORD scale


	if (bModalDialog) { nResult = DialogBoxIndirectParam(hInstance, (LPCDLGTEMPLATE)lpTemplate, hwndParent, lpDialogProc, lParam); }
	else { nResult = (INT)CreateDialogIndirectParam(hInstance, (LPCDLGTEMPLATE)lpTemplate, hwndParent, lpDialogProc, lParam); }

	//delete [nBytes] lpTemplate;
	
	return nResult;
}



// Window Subclassing
// -------------------

// General:
BOOL _eLibHookWindowCreate ()
{
	if (m_hHookCbtFilter != NULL) return FALSE;
	if ((m_hHookCbtFilter = SetWindowsHookEx(WH_CBT, _eLibCBTProc, NULL, GetCurrentThreadId())) == NULL) return NULL;
	return TRUE;
}
BOOL _eLibUnhookWindowCreate ()
{
	if (m_hHookCbtFilter != NULL) {
		UnhookWindowsHookEx(m_hHookCbtFilter);
		m_hHookCbtFilter = NULL;
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK _eLibCBTProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	LPCREATESTRUCT lpcs;
	HHOOK m_hChainHookCbtFilter = m_hHookCbtFilter;

	if (nCode == HCBT_CREATEWND)
	{
		lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
		
		SetWindowLong((HWND)wParam, GWL_WNDPROC, ((long)lpcs->lpCreateParams) );
		lpcs->lpCreateParams = NULL;

		UnhookWindowsHookEx(m_hHookCbtFilter);
		m_hHookCbtFilter = NULL;
	}

	return CallNextHookEx(m_hChainHookCbtFilter, nCode, wParam, lParam);
}



// Buttons:
HWND CreateButton (LPCTSTR lpWindowText, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, DWORD dwControlID, HINSTANCE hInstance)
{ return CreateButtonEx((WS_EX_NOPARENTNOTIFY), lpWindowText, dwStyle, x, y, nWidth, nHeight, hWndParent, dwControlID, hInstance); }

HWND CreateButtonEx (DWORD dwStyleEx, LPCTSTR lpWindowText, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, DWORD dwControlID, HINSTANCE hInstance)
{
	HWND hWnd;

	if (_eLibHookWindowCreate() == FALSE) return NULL;
	hWnd = CreateWindowEx((dwStyleEx), "button", lpWindowText, dwStyle, x, y, nWidth, nHeight, hWndParent, (HMENU)dwControlID, hInstance, (LPVOID)(_eLibButtonProc));
	if (_eLibUnhookWindowCreate() == FALSE) { DestroyWindow(hWnd); return NULL; }

	return hWnd;
}

LRESULT CALLBACK _eLibButtonProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret;
	WNDCLASSEX wcex;
	STATIC WNDPROC lpfnWndProc = NULL;
	POINT pt;
	RECT rt;
	
	if (lpfnWndProc == NULL) {  GetClassInfoEx(NULL, "button", &wcex);  lpfnWndProc = wcex.lpfnWndProc; }


	switch (uMsg)
	{
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:

			if (!(GetWindowLong(hWnd, GWL_STYLE) & BS_NOTIFY)) break;	// Send only if user wants notifications

			if (((wParam & MK_LBUTTON) != MK_LBUTTON) && ((wParam & MK_MBUTTON) != MK_MBUTTON) && ((wParam & MK_RBUTTON) != MK_RBUTTON)) {
				GetWindowRect(hWnd, &rt);
				pt.x = LOWORD(lParam); pt.y = HIWORD(lParam); ClientToScreen(hWnd, &pt);
			
				if (((pt.x >= rt.left) && (pt.x <= rt.right)) && ((pt.y >= rt.top) && (pt.y <= rt.bottom))) {
					if (GetCapture() == NULL)
					{ SetCapture(hWnd); SendMessage(GetParent(hWnd), WM_COMMAND, (WPARAM)MAKELONG(GetWindowLong(hWnd, GWL_ID), BN_MOUSEENTER), (LPARAM)hWnd); }
				} else
				{ ReleaseCapture(); }
			}

			break;

		case WM_ERASEBKGND:
			
			if (HasStyle(hWnd, BS_OWNERDRAW)) return TRUE;
			break;

		case WM_CAPTURECHANGED:

			if (GetCapture() != hWnd) SendMessage(GetParent(hWnd), WM_COMMAND, (WPARAM)MAKELONG(GetWindowLong(hWnd, GWL_ID), BN_MOUSEEXIT), (LPARAM)hWnd);
			break;

		case WM_GETDLGCODE:

			ret = CallWindowProc(lpfnWndProc, hWnd, uMsg, wParam, lParam);
			
			if (lParam != NULL) {
				if (((LPMSG)lParam)->message == WM_CHAR) ret |= DLGC_WANTCHARS;
				if ((((LPMSG)lParam)->message == WM_KEYDOWN) || (((LPMSG)lParam)->message == WM_KILLFOCUS) || (((LPMSG)lParam)->message == WM_ACTIVATE))
					if (SendMessage(hWnd, BM_GETSTATE, NULL, NULL) & BST_PUSHED)
					{ return (CallWindowProc(lpfnWndProc, hWnd, uMsg, wParam, lParam) | DLGC_WANTMESSAGE); }
			}

			return ret;
	}

	return CallWindowProc(lpfnWndProc, hWnd, uMsg, wParam, lParam);
}
