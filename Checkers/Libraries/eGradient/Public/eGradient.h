// eGradient.h
// eGradient Library Header File
// By Joe Esposito


#pragma once



// Public Declarations
// --------------------

// Bitmap functions:
ECALL HBITMAP ESTDCALL CreateGradientBitmap ( int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );
ECALL HBITMAP ESTDCALL CreateGradientHorizBitmap ( int cx, COLORREF crStart, COLORREF crEnd );
ECALL HBITMAP ESTDCALL CreateGradientVertBitmap ( int cy, COLORREF crStart, COLORREF crEnd );

// Drawing functions:
ECALL BOOL ESTDCALL DrawGradientRect ( HDC hDC, int x, int y, int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );
ECALL BOOL ESTDCALL DrawGradientHoriz ( HDC hDC, int x, int y, int cx, COLORREF cStart, COLORREF cEnd );
ECALL BOOL ESTDCALL DrawGradientVert ( HDC hDC, int x, int y, int cy, COLORREF cStart, COLORREF cEnd );
//ECALL BOOL ESTDCALL DrawGradientLine ( HDC hDC, int x1, int y1, int x2, int y2, COLORREF cStart, COLORREF cEnd );
//ECALL BOOL ESTDCALL DrawGradientTriangle ( HDC hDC );

// Color calculation functions:
ECALL COLORREF ESTDCALL GetGradientPixel ( int cLen, int nPos, COLORREF cStart, COLORREF cEnd );
ECALL COLORREF ESTDCALL GetGradientRectPixel ( int cx, int cy, int x, int y, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight );
//ECALL COLORREF ESTDCALL GetGradientTrianglePixel ( HDC hDC );


// Implementation File:
// "eGradient.cpp"
