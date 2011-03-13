// eColorFunctions.h
// Color Functions Header File
// By Joe Esposito


#pragma once



// Flags and Styles
// -----------------

// Additional DrawSchemeEdge() flags
#define BF_DEFAULT					0x00010000		// Default border



// Public Functions
// -----------------

// Drawing functions
ECALL BOOL ESTDCALL SchemeLineTo ( HDC hDC, HETHEMEOBJ hThemeObj, INT nColorIndex, INT x, INT y );
ECALL BOOL ESTDCALL DrawSchemeLine ( HDC hDC, HETHEMEOBJ hThemeObj, INT nColorIndex, INT x1, INT y1, INT x2, INT y2, LPPOINT lpPoint );
ECALL BOOL ESTDCALL DrawSchemeEdge ( HDC hDC, LPRECT lprt, HETHEMEOBJ hThemeObj, UINT uEdge, UINT uFlags );
ECALL BOOL ESTDCALL DrawSchemeButton ( HDC hDC, LPRECT lprt, LPRECT lpFocusRect, HETHEMEOBJ hThemeObj, UINT uState, LPSTR lpszWindowText, BOOL bNoFlicker );
ECALL BOOL ESTDCALL DrawSchemeItem ( LPDRAWITEMSTRUCT lpds, UINT uStateExtra, LPRECT lpFocusRect, HETHEMEOBJ hThemeObj, LPVOID lpData, BOOL bNoFlicker );



// Implementation File
// "eColorFunctions.cpp"
