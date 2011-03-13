// Gradient.h
// Gradient Functions Header File
// By Joe Esposito


#pragma once



// Internal Declarations
// ----------------------

LOCAL VOID _GradientBoxBits ( LPDWORD lpBits, int nWidth, int nHeight, COLORREF crTopLeft, COLORREF crBottomLeft, COLORREF crTopRight, COLORREF crBottomRight );
LOCAL VOID _GradientBits ( LPDWORD lpBits, int nSize, COLORREF crStart, COLORREF crEnd );
LOCAL VOID _GradientFillBits ( LPDWORD lpBits, int nSize, COLORREF cColor );
LOCAL VOID _GetGradientBits ( LPDWORD lpColor, int nSize, int nPos, COLORREF crStart, COLORREF crEnd );


// Implementation File:
// "eGradient.cpp"
