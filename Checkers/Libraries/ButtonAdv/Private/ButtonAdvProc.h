// ButtonAdvProc.h
// ButtonAdv Procedure Header File
// By Joe Esposito


#pragma once



// Internal Structs
// -----------------

typedef struct tagBUTTONADVCLASSINFO
{
	UINT uRegisterCount;				// How many times class is registered
	UINT uWindowIndex;					// Window index for local window variables
	WNDPROC lpButtonProc;				// Button window procedure
} BUTTONADVCLASSINFO, *LPBUTTONADVCLASSINFO;



// Internal Variables
// -------------------

extern LPBUTTONADVCLASSINFO m_ButtonAdvInfo;



// Internal Declarations
// ----------------------

LOCAL LRESULT CALLBACK _ButtonAdvProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "ButtonAdvProc.cpp"
