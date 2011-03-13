// eTheme.h
// eTheme Header File
// By Joe Esposito


#pragma once



// Public Macro Definitions
// -------------------------

// Theme object types
#define THEMES_THEME					0x00000001
#define THEMES_SCHEME					0x00000002

// Scheme types
#define SCHEMES_USERSCHEME				0x00000001
#define SCHEMES_COLORSCHEME				0x00000002



// Structure Declarations
// -----------------------

struct _ETHEMEOBJ; typedef _ETHEMEOBJ ETHEMEOBJ, *LPETHEMEOBJ;
struct _ETHEME; typedef _ETHEME ETHEME, *LPETHEME;
struct _ESCHEME; typedef _ESCHEME ESCHEME, *LPESCHEME;
struct _ECOLORSCHEME; typedef _ECOLORSCHEME ECOLORSCHEME, *LPECOLORSCHEME;



// Structures
// -----------

// Base theme object
typedef struct _ETHEMEOBJ
{
	UINT uType;					// Type of theme object (THEMES_THEME)
} ETHEMEOBJ, *LPETHEMEOBJ;

// Theme object
typedef struct _ETHEME : _ETHEMEOBJ
{
	UINT nExtraSchemes;			// Number of extra schemes
	ESCHEME **lpaSchemes;		// Pointer to scheme list
	ESCHEME **lpaUserSchemes;	// Pointer to user scheme list
} ETHEME, *LPETHEME;



// Public Functions
// -----------------

ECALL HETHEME ESTDCALL CreateTheme ( UINT nExtraSchemes );
ECALL BOOL ESTDCALL DestroyTheme ( HETHEME hTheme );
ECALL HESCHEME ESTDCALL SelectScheme ( HETHEME hTheme, HESCHEME hScheme );
ECALL HESCHEME ESTDCALL GetCurrentScheme ( HETHEMEOBJ hThemeObj, UINT nSchemeType );
ECALL HESCHEME ESTDCALL SetUserScheme ( HETHEME hTheme, HESCHEME hScheme, INT nIndex );
ECALL UINT ESTDCALL GetThemeSchemeCount ( HETHEME hTheme );
ECALL UINT ESTDCALL GetThemeObjType ( HETHEMEOBJ hThemeObj );



// Implementation File
// "eTheme.cpp"
