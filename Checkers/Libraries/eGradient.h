// eGradient.h
// eGradient Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(EGRADIENT_INCLUDE)) && (!defined(EGRADIENT_SOURCE)) && (!defined(EGRADIENT_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( lib, "eGradientD.lib" )
#else
#pragma comment ( lib, "eGradient.lib" )
#endif
#endif

#ifdef EGRADIENT_INCLUDE
#include "eGradient\Main.h"
#endif
#ifdef EGRADIENT_SOURCE
#define EGRADIENT_INCLUDE
#include "eGradient\Main.cpp"
#endif



#if ( (!defined(EGRADIENT_INCLUDE)) && (!defined(EGRADIENT_SOURCE)) && (!defined(_EGRADIENT_)) )

#define _EGRADIENT_


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Functions
// -----------------

// Bitmap functions:
ECALL HBITMAP ESTDCALL CreateGradientBitmap ( int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );
ECALL HBITMAP ESTDCALL CreateGradientHorizBitmap ( int cx, COLORREF crStart, COLORREF crEnd );
ECALL HBITMAP ESTDCALL CreateGradientVertBitmap ( int cy, COLORREF crStart, COLORREF crEnd );

// Drawing functions:
ECALL BOOL ESTDCALL DrawGradientRect ( HDC hDC, int x, int y, int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );
ECALL BOOL ESTDCALL DrawGradientHoriz ( HDC hDC, int x, int y, int cx, COLORREF cStart, COLORREF cEnd );
ECALL BOOL ESTDCALL DrawGradientVert ( HDC hDC, int x, int y, int cy, COLORREF cStart, COLORREF cEnd );

// Color calculation functions:
ECALL COLORREF ESTDCALL GetGradientPixel ( int cLen, int nPos, COLORREF cStart, COLORREF cEnd );
ECALL COLORREF ESTDCALL GetGradientRectPixel ( int cx, int cy, int x, int y, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
