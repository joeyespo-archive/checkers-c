// MarqueeBoxProc.h - MarqueeBox
// MarqueeBox Procedure Header File
// By Joe Esposito


#pragma once



// Internal Structs
// -----------------

typedef struct tagMARQUEEBOXCLASSINFO
{
	UINT uRegisterCount;				// How many times class is registered
	WNDPROC lpButtonProc;				// Button window procedure
} MARQUEEBOXCLASSINFO, *LPMARQUEEBOXCLASSINFO;



// Internal Variables
// -------------------

extern LPMARQUEEBOXCLASSINFO m_MarqueeBoxInfo;



// Internal Declarations
// ----------------------

LOCAL LRESULT CALLBACK _MarqueeBoxProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "MarqueeBoxProc.cpp"
