// MarqueeBox.h - MarqueeBox
// MarqueeBox Library Header File
// By Joe Esposito


#pragma once



// Public Macros
// --------------

// Class ID
#define ID_MARQUEEBOX_CLASSNAME		"marqueebox"

// Window Styles
#define MBS_SIMPLE					0x00000000		// Simple MarqueeBox .. use window text/font
#define MBS_MARQUEEHORIZ			0x00000000		// Marquee is horizontal
#define MBS_MARQUEEVERT				0x00000001		// Marquee is vertical
#define MBS_FLICKERFREE				0x00000010		// MarqueeBox is drawn off screen, then moved onto the screen for a flicker-free effect
#define MBS_ALIGNTOPLEFT			0x00000000		// Text is aligned at either the top (Horiz) or left (Vert)
#define MBS_ALIGNBOTTOMRIGHT		0x00000100		// Text is aligned at either the top (Horiz) or left (Vert)
#define MBS_ALIGNCENTER				0x00000200		// Text is aligned at the center

// Window Messages
#define MBM_SETBACKCOLOR			(WM_USER+2)		// Sets backcolor (WPARAM = color; LPARAM = MAKELPARAM(fRedraw, 0)) Returns: [TRUE = OK; FALSE = Error]
#define MBM_SETTEXTCOLOR			(WM_USER+3)		// Sets textcolor (WPARAM = color; LPARAM = MAKELPARAM(fRedraw, 0)) Returns: [TRUE = OK; FALSE = Error]

// Window Messages
//#define MBN_MOUSEENTER			0x1001
//#define MBN_MOUSEEXIT				0x1002



// Public Declarations
// --------------------

// Registering functions:
BOOL WINAPI RegisterMarqueeBox ( HINSTANCE hInstance );
BOOL WINAPI UnregisterMarqueeBox ( HINSTANCE hInstance );



// Implementation File:
// "MarqueeBox.cpp"
