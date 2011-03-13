// eColorScheme.h
// Color Schemes Header File
// By Joe Esposito


#pragma once



// Color Scheme Indexes
// ---------------------

// Colors
#define CSI_USER					0				// Start of the user indexes
#define CSI_HIGHLIGHT				-1				// Color frame color
#define CSI_LIGHT					-2				// Color frame color
#define CSI_SHADOW					-3				// Color frame color
#define CSI_DKSHADOW				-4				// Color frame color
#define CSI_BACKGROUND				-5				// Background color
#define CSI_BORDER					-6				// Default border color
#define CSI_BTNTEXT					-7				// Button text color
#define CSI_DISABLEDTEXT			-8 				// Disabled text color
#define CSI_GHOSTEDTEXT				-9				// Ghost text color
// Flags
#define CSF_MUSTEXIST				0x00000001		// If the color doesnt exist, SetLastError(13)
#define CSF_NOSYSCOLOR				0x00000002		// If the color doesnt exist, do not return a system color


// CalcColor Options
#define CC_IGNORE					0x80000000		// Ignores the color in a CALCSCHEMECOLORS color

// Extra colors mask
#define CSM_IGNORE					0x00000000		// Dont change the mask
#define CSM_LONG					0x00000001		// Extra data is a LONG value (user data: only exception to passing a color to SetSchemeInfo.. can be any value)
#define CSM_COLORREF				0x00000002		// Extra data is a COLORREF
#define CSM_HBRUSH					0x00000003		// Extra data is a handle to a brush
#define CSM_HPEN					0x00000004		// Extra data is a handle to a pen



// Public Color Scheme Structs
// ----------------------------

typedef struct _SCHEMECOLORBASE
{
	UINT cbSize;									// Size of structure
} SCHEMECOLORBASE, *LPSCHEMECOLORBASE;

typedef struct _SCHEMECOLORSTRUCT : _SCHEMECOLORBASE
{
	HPEN hpenHighlight, hpenLight;					// Frame colors
	HPEN hpenShadow, hpenDkShadow;					// 
	HBRUSH hbrBackground;							// Background color
	HPEN hpenDefaultBorder;							// Default border
	COLORREF crTextColor;							// Text color
	COLORREF crDisabledColor, crGhostedColor;		// Disabled colors
} SCHEMECOLORSTRUCT, *LPSCHEMECOLORSTRUCT;


typedef struct _CALCSCHEMECOLORS : _SCHEMECOLORBASE
{
	// Color shading percentages  (0 = use COLORREF color; CC_IGNORE = dont change; else shade from crFace)
	int iFacePercent;								// Face (background) percentage
	int iHighlightPercent, iLightPercent;			// Frame color percentagess
	int iShadowPercent, iDkShadowPercent;			// 
	int iDefaultBorderPercent;						// Default border color percentage
	int iTextColorPercent;							// Text color percentage
	int iDisabledColorPercent, iGhostedColorPercent; // Disabled colors percentages

	COLORREF crFace;								// Face (background) color
	COLORREF crHighlight, crLight;					// Frame colors
	COLORREF crShadow, crDkShadow;					// 
	COLORREF crDefaultBorder;						// Default border color 
	COLORREF crTextColor;							// Text color
	COLORREF crDisabledColor, crGhostedColor;		// Disabled colors
} CALCSCHEMECOLORS, *LPCALCSCHEMECOLORS;



// Public Functions
// -----------------

ECALL HESCHEME ESTDCALL CreateColorScheme ( LPSCHEMECOLORBASE lpc, UINT uExtraInfoLength );
ECALL BOOL ESTDCALL DestroyColorScheme ( HESCHEME hScheme );
ECALL BOOL ESTDCALL SetSchemeColors ( HETHEMEOBJ hThemeObj, LPSCHEMECOLORBASE lpc );
ECALL BOOL ESTDCALL SetSchemeColor ( HETHEMEOBJ hThemeObj, INT nIndex, COLORREF crColor );
ECALL BOOL ESTDCALL SetColorSchemeInfo ( HETHEMEOBJ hThemeObj, INT nIndex, LONG lValue );
ECALL BOOL ESTDCALL SetColorSchemeInfoEx ( HETHEMEOBJ hThemeObj, INT nIndex, LONG lValue, DWORD dwMask );
ECALL COLORREF ESTDCALL GetSchemeColor ( HETHEMEOBJ hThemeObj, INT nIndex );
ECALL COLORREF ESTDCALL GetSchemeColorEx ( HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwFlags );
ECALL LONG ESTDCALL GetColorSchemeInfo ( HETHEMEOBJ hThemeObj, INT nIndex );
ECALL LONG ESTDCALL GetColorSchemeInfoEx ( HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask, DWORD dwFlags );
ECALL HBRUSH ESTDCALL GetSchemeBkBrush ( HETHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL SetColorSchemeMask ( HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwMask );
ECALL DWORD ESTDCALL GetColorSchemeMask ( HETHEMEOBJ hThemeObj, INT nIndex );
ECALL HGDIOBJ ESTDCALL GetSchemeColorObj ( HETHEMEOBJ hThemeObj, INT nIndex );
ECALL HGDIOBJ ESTDCALL GetSchemeColorObjEx ( HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask );
ECALL COLORREF ESTDCALL GetSchemeColorPercent ( COLORREF crColor, INT iPercent );
ECALL BOOL ESTDCALL DeleteSchemeColor ( HETHEMEOBJ hThemeObj, INT nIndex );
ECALL BOOL ESTDCALL DeleteSchemeColors ( HETHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL DeleteSchemeUserColors ( HETHEMEOBJ hThemeObj );

ECALL HESCHEME ESTDCALL CopyColorScheme ( HETHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL CopySchemeColors ( HETHEMEOBJ hThemeObjDest, HETHEMEOBJ hThemeObjSource );
ECALL BOOL ESTDCALL CopySchemeUserColors ( HETHEMEOBJ hThemeObjDest, HETHEMEOBJ hThemeObjSource );


// Implementation File
// "eColorScheme.cpp"
