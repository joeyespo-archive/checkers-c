// eThemes.h
// eThemes Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(ETHEMES_INCLUDE)) && (!defined(ETHEMES_SOURCE)) && (!defined(ETHEMES_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:eThemesD.lib" )
#else
#pragma comment ( linker, "/defaultlib:eThemes.lib" )
#endif
#endif

#ifdef ETHEMES_INCLUDE
#include "eThemes\Main.h"
#endif
#ifdef ETHEMES_SOURCE
#define ETHEMES_INCLUDE
#include "eThemes\Main.cpp"
#endif



// Public Macro Definitions
// -------------------------

// Theme object types
#define THEMES_THEME					0x00000001
#define THEMES_SCHEME					0x00000002

// Scheme types
#define SCHEMES_USERSCHEME				0x00000001
#define SCHEMES_COLORSCHEME				0x00000002



// Flags and Styles
// -----------------

// Additional DrawEdge() [DrawEdgeAdv()] flags
#define BF_DEFAULT					0x00010000		// Default border



// Color Scheme Indexes
// ---------------------

// Colors
#define CSI_USER					 0				// Start of the user indexes
#define CSI_HIGHLIGHT				-1				// Color frame color
#define CSI_LIGHT					-2				// Color frame color
#define CSI_SHADOW					-3				// Color frame color
#define CSI_DKSHADOW				-4				// Color frame color
#define CSI_BACKGROUND				-5				// Background color
#define CSI_BORDER					-6				// Default border color
#define CSI_BTNTEXT					-7				// Button text color
#define CSI_DISABLEDTEXT			-8 				// Disabled text color
#define CSI_GHOSTEDTEXT				-9 				// Ghost text color
// Flags
#define CSF_MUSTEXIST				0x00000001		// If the color doesnt exist, SetLastError(13)
#define CSF_NOSYSCOLOR				0x00000002		// If the color doesnt exist, do not return a system color
#define CSF_STRUCTURE				0x00000004		// Returns a pointer to the color structure (Do not delete this structure)


// CalcColor Options
#define CC_IGNORE					0x80000000		// Ignores the color in a CALCSCHEMECOLORS color

// Extra colors mask
#define CSM_IGNORE					0x00000000		// Dont change the mask
#define CSM_LONG					0x00000001		// Extra data is a LONG value (user data: only exception to passing a color to SetSchemeInfo.. can be any value)
#define CSM_COLORREF				0x00000002		// Extra data is a COLORREF
#define CSM_HBRUSH					0x00000003		// Extra data is a handle to a brush
#define CSM_HPEN					0x00000004		// Extra data is a handle to a pen




#if ( (!defined(ETHEMES_INCLUDE)) && (!defined(ETHEMES_SOURCE)) && (!defined(_ETHEMES_)) )

#define _ETHEMES_

// Function Modifiers
// -------------------

// Handles declarers
#ifdef STRICT
#define DECLARE_ETHEMES_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name;
#define DECLARE_ETHEMES_HANDLE_BASE(name, base) struct name##__ : base { int unused; }; typedef struct name##__ *name;
#else
#define DECLARE_ETHEMES_HANDLE(name) typedef void *name;
#define DECLARE_ETHEMES_HANDLE_BASE(name, base) typedef void *name;
#endif

// Base theme object handle
DECLARE_ETHEMES_HANDLE(HTHEMEOBJ);

// Theme object handles
DECLARE_ETHEMES_HANDLE_BASE(HTHEME, HTHEMEOBJ__);
DECLARE_ETHEMES_HANDLE_BASE(HSCHEME, HTHEMEOBJ__);

#undef DECLARE_ETHEMES_HANDLE
#undef DECLARE_ETHEMES_HANDLE_BASE


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Color Scheme Structs
// ----------------------------

typedef struct tagSCHEMECOLORBASE
{
	UINT cbSize;									// Size of structure
} SCHEMECOLORBASE, *LPSCHEMECOLORBASE;

typedef struct tagSCHEMECOLORSTRUCT : tagSCHEMECOLORBASE
{
	HPEN hpenHighlight, hpenLight;					// Frame colors
	HPEN hpenShadow, hpenDkShadow;					// 
	HBRUSH hbrBackground;							// Background color
	HPEN hpenDefaultBorder;							// Default border
	HPEN hpenFocusRect;								// Focus rect color
	COLORREF crTextColor;							// Text color
	COLORREF crDisabledColor, crGhostedColor;		// Disabled colors
} SCHEMECOLORSTRUCT, *LPSCHEMECOLORSTRUCT;


typedef struct tagCALCSCHEMECOLORS : tagSCHEMECOLORBASE
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

// Theme object functions
ECALL HTHEME ESTDCALL CreateTheme ( UINT nExtraSchemes );
ECALL BOOL ESTDCALL DestroyTheme ( HTHEME hTheme );
ECALL HSCHEME ESTDCALL SelectScheme ( HTHEME hTheme, HSCHEME hScheme );
ECALL HSCHEME ESTDCALL GetCurrentScheme ( HTHEMEOBJ hThemeObj, UINT nSchemeType );
ECALL HSCHEME ESTDCALL SetUserScheme ( HTHEME hTheme, HSCHEME hScheme, INT nIndex );
ECALL UINT ESTDCALL GetThemeSchemeCount ( HTHEME hTheme );
ECALL UINT ESTDCALL GetThemeObjType ( HTHEMEOBJ hThemeObj );

// Scheme object functions
ECALL UINT ESTDCALL GetSchemeType ( HSCHEME hScheme );
ECALL UINT ESTDCALL GetSchemeInfoCount ( HSCHEME hScheme );

// UserScheme object functions
ECALL HSCHEME ESTDCALL CreateUserScheme ( LPVOID lpSchemeData, UINT uSchemeUserType, UINT nExtraSchemeData );
ECALL BOOL ESTDCALL DestroyUserScheme ( HSCHEME lpScheme, UINT uSchemeUserType );
ECALL LONG ESTDCALL SetUserSchemeInfo ( HSCHEME lpScheme, INT nIndex, LONG lValue );
ECALL LONG ESTDCALL GetUserSchemeInfo ( HSCHEME lpScheme, INT nIndex );

// ColorScheme object functions
ECALL HSCHEME ESTDCALL CreateColorScheme ( LPSCHEMECOLORBASE lpc, UINT uExtraInfoLength );
ECALL BOOL ESTDCALL DestroyColorScheme ( HSCHEME hScheme );
ECALL BOOL ESTDCALL SetSchemeColors ( HTHEMEOBJ hThemeObj, LPSCHEMECOLORBASE lpc );
ECALL BOOL ESTDCALL SetSchemeColor ( HTHEMEOBJ hThemeObj, INT nIndex, COLORREF crColor );
ECALL BOOL ESTDCALL SetColorSchemeInfo ( HTHEMEOBJ hThemeObj, INT nIndex, LONG lValue );
ECALL BOOL ESTDCALL SetColorSchemeInfoEx ( HTHEMEOBJ hThemeObj, INT nIndex, LONG lValue, DWORD dwMask );
ECALL COLORREF ESTDCALL GetSchemeColor ( HTHEMEOBJ hThemeObj, INT nIndex );
ECALL COLORREF ESTDCALL GetSchemeColorEx ( HTHEMEOBJ hThemeObj, INT nIndex, DWORD dwFlags );
ECALL LONG ESTDCALL GetColorSchemeInfo ( HTHEMEOBJ hThemeObj, INT nIndex );
ECALL LONG ESTDCALL GetColorSchemeInfoEx ( HTHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask, DWORD dwFlags );
ECALL HBRUSH ESTDCALL GetSchemeBkBrush ( HTHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL SetColorSchemeMask ( HTHEMEOBJ hThemeObj, INT nIndex, DWORD dwMask );
ECALL DWORD ESTDCALL GetColorSchemeMask ( HTHEMEOBJ hThemeObj, INT nIndex );
ECALL HGDIOBJ ESTDCALL GetSchemeColorObj ( HTHEMEOBJ hThemeObj, INT nIndex );
ECALL HGDIOBJ ESTDCALL GetSchemeColorObjEx ( HTHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask );
ECALL COLORREF ESTDCALL GetSchemeColorPercent ( COLORREF crColor, INT iPercent );
ECALL BOOL ESTDCALL DeleteSchemeColor ( HTHEMEOBJ hThemeObj, INT nIndex );
ECALL BOOL ESTDCALL DeleteSchemeColors ( HTHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL DeleteSchemeUserColors ( HTHEMEOBJ hThemeObj );

ECALL HSCHEME ESTDCALL CopyColorScheme ( HTHEMEOBJ hThemeObj );
ECALL BOOL ESTDCALL CopySchemeColors ( HTHEMEOBJ hThemeObjDest, HTHEMEOBJ hThemeObjSource );
ECALL BOOL ESTDCALL CopySchemeUserColors ( HTHEMEOBJ hThemeObjDest, HTHEMEOBJ hThemeObjSource );

// Drawing functions
ECALL BOOL ESTDCALL SchemeLineTo ( HDC hDC, HTHEMEOBJ hThemeObj, INT nColorIndex, INT x, INT y );
ECALL BOOL ESTDCALL DrawSchemeLine ( HDC hDC, HTHEMEOBJ hThemeObj, INT nColorIndex, INT x1, INT y1, INT x2, INT y2, LPPOINT lpPoint );
ECALL BOOL ESTDCALL DrawSchemeEdge ( HDC hDC, LPRECT lprt, HTHEMEOBJ hThemeObj, UINT uEdge, UINT uFlags );
ECALL BOOL ESTDCALL DrawSchemeButton ( HDC hDC, LPRECT lprt, LPRECT lpFocusRect, HTHEMEOBJ hThemeObj, UINT uState, LPSTR lpszWindowText, BOOL bNoFlicker );
ECALL BOOL ESTDCALL DrawSchemeItem ( LPDRAWITEMSTRUCT lpds, UINT uStateExtra, LPRECT lpFocusRect, HTHEMEOBJ hThemeObj, LPVOID lpData, BOOL bNoFlicker );


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
