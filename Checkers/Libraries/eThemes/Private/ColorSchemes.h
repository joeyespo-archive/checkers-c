// ColorSchemes.h
// Color Schemes Internal Header File
// By Joe Esposito


#pragma once



// Macro Definitions
// ------------------

#define DRAWLINE(hDC, hPen, X, Y, DrawCondition)	if (DrawCondition) { SelectObject(hDC, hPen); LineTo(hDC, X, Y); } else { MoveToEx(hDC, X, Y, NULL); }
#define GETCUSTOMSCHEMECOLOR(color, percentage) ((percentage == 0)?(color):( _GetColorSchemePercent(100, ((abs(percentage) > 100)?(100):(abs(percentage))), color, ((percentage < 0)?(0x000000):(0xFFFFFF)) ) ))



// Internal Inlines
// -----------------

__forceinline COLORREF GetPenColor(HPEN hPen) { LOGPEN lp; GetObject(hPen, sizeof(LOGPEN), &lp); return lp.lopnColor; }
__forceinline COLORREF GetBrushColor(HBRUSH hBrush) { LOGBRUSH lb; GetObject(hBrush, sizeof(LOGBRUSH), &lb); return lb.lbColor; }



// Internal Structs
// -----------------

typedef struct _COLORSCHEMEINFO
{
	UINT cbSize;									// Color info size
	INT uUserCount;									// Number of user values
	LPDWORD lpadwMask;								// DWORD array that defines the extra mask
	LPSCHEMECOLORSTRUCT lpsc;						// Actual color info
	LPESCHEME lpScheme;								// Owner scheme
} COLORSCHEMEINFO, *LPCOLORSCHEMEINFO;




// Internal Declarations
// ----------------------

LOCAL BOOL _SetColorSchemeColors ( LPCOLORSCHEMEINFO lpsi, LPSCHEMECOLORBASE lpcSource );
LOCAL BOOL _SetColorSchemeBaseColor ( LPSCHEMECOLORSTRUCT lpc, INT nIndex, COLORREF crColor );
LOCAL BOOL _SetColorSchemeInternalColor ( LPCOLORSCHEMEINFO lpsi, INT nIndex, COLORREF crColor );
LOCAL COLORREF _GetColorSchemeBaseColor ( LPSCHEMECOLORSTRUCT lpc, INT nIndex, DWORD dwFlags );
LOCAL COLORREF _GetColorSchemeInternalColor ( LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwFlags );
LOCAL BOOL _SetColorSchemeUserInfo ( LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask, COLORREF crColor );
LOCAL LONG _GetColorSchemeUserInfo ( LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask, DWORD dwFlags );
LOCAL BOOL _SetColorSchemeUserMask ( LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask );
LOCAL DWORD _GetColorSchemeMask ( INT nIndex );
LOCAL DWORD _GetColorSchemeUserMask ( LPCOLORSCHEMEINFO lpsi, INT nIndex );
LOCAL LPCOLORSCHEMEINFO _GetSchemeColorInfoStruct ( LPVOID lpv );
LOCAL LPSCHEMECOLORSTRUCT _GetColorObject ( LPVOID lpv );
LOCAL HGDIOBJ _GetSchemeColorObj ( LPSCHEMECOLORSTRUCT lpc, INT nIndex, DWORD dwMask );
LOCAL HGDIOBJ _GetSchemeUserColorObj ( LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask );
LOCAL COLORREF _GetColorSchemePercent ( INT iMax, INT nValue, COLORREF crStart, COLORREF crEnd );
LOCAL BOOL _DeleteSchemeColor ( LPSCHEMECOLORSTRUCT lpc, INT nIndex );
LOCAL BOOL _DeleteSchemeUserColor ( LPCOLORSCHEMEINFO lpsi, INT nIndex );
LOCAL BOOL _DeleteColorSchemeColors ( LPSCHEMECOLORSTRUCT lpc );
LOCAL BOOL _DeleteColorSchemeUserColors ( LPCOLORSCHEMEINFO lpsi );
LOCAL BOOL _DestroyColorSchemeColors ( LPCOLORSCHEMEINFO lpsi );

LOCAL LPESCHEME _CopyColorScheme ( LPCOLORSCHEMEINFO lpsi );
LOCAL BOOL _CopyColorSchemeColors ( LPSCHEMECOLORSTRUCT lpcDest, LPSCHEMECOLORSTRUCT lpcSource );
LOCAL BOOL _CopySchemeColors ( LPCOLORSCHEMEINFO lpDest, LPCOLORSCHEMEINFO lpSource );
LOCAL BOOL _CopySchemeUserColors ( LPCOLORSCHEMEINFO lpDest, LPCOLORSCHEMEINFO lpSource );



// Implementation File
// "ColorSchemes.cpp"
