// frmAbout.cpp - Checkers
// About Window Implementation File
// By Joey Esposito


#pragma once


// Header File:
#include "Main.h"



// Local Macros
// -------------

#define BG_GB_COLOR_TL			0x8888E0
#define BG_GB_COLOR_BL			0x404040
#define BG_GB_COLOR_TR			0x80000018
#define BG_GB_COLOR_BR			0x5050A0

#define ID_BTN_OK				0x1001



// Local Variables
// ----------------

LOCAL UINT nWindowCount = 0;
LOCAL HBITMAP hBackground = NULL;
LOCAL HICON hicoLogo = NULL;
LOCAL HWND hOK;



// Local Functions
// ----------------

LOCAL VOID EndAbout ( HWND hWnd );



// frmMain Window Procedure
// -------------------------

LRESULT CALLBACK frmAboutProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hDC2;
	PAINTSTRUCT ps;
	HBITMAP hbmTemp;
	HFONT hftTemp;
	RECT rt;

	switch (uMsg)
	{
		case WM_CREATE:

			// Window Startup Position
			// ------------------------

			((LPCREATESTRUCT)lParam)->cx = NCWidth(hWnd) + 344;
			((LPCREATESTRUCT)lParam)->cy = NCHeight(hWnd) + 178;

			GetWindowRect(GetDesktopWindow(), &rt);
			Reposition(hWnd, (((rt.right-rt.left)-((LPCREATESTRUCT)lParam)->cx) / 2), (((rt.bottom-rt.top) - ((LPCREATESTRUCT)lParam)->cy) / 2), ((LPCREATESTRUCT)lParam)->cx, ((LPCREATESTRUCT)lParam)->cy);

			
			// Initialize window
			// ------------------

			nWindowCount++;
			if (hicoLogo == NULL) hicoLogo = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));


			// Create Window
			// --------------

			hOK = CreateWindow("button", "OK", (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_NOTIFY | BS_DEFPUSHBUTTON), 258, 8, 73, 25, hWnd, (HMENU)ID_BTN_OK, hInstance, NULL);
			 SendMessage(hOK, WM_SETFONT, (WPARAM)hFont_Main, 0);
			
			if (hBackground == NULL) hBackground = CreateGradientBitmap(ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
			break;

		case WM_ACTIVATE:

			if ((LOWORD(wParam) != WA_INACTIVE) && (HIWORD(wParam) == FALSE))
			{ SetFocus(hOK); return 0; }
			
			break;

		case WM_PAINT:

			// Setup painting
			hDC = BeginPaint(hWnd, &ps);

			// Setup background
			hDC2 = CreateCompatibleDC(NULL);
			hbmTemp = (HBITMAP)SelectObject(hDC2, hBackground);
			SetBkMode(hDC, TRANSPARENT); hftTemp = (HFONT)GetCurrentObject(hDC, OBJ_FONT);


			// Paint background
			BitBlt(hDC, 0, 0, ClientWidth(hWnd), ClientHeight(hWnd), hDC2, 0, 0, SRCCOPY);

			// Draw statics
			rt.left = 8; rt.top = 8; rt.right = 44; rt.bottom = 44; DrawEdge(hDC, &rt, (BDR_SUNKENOUTER), BF_RECT);
			DrawIcon(hDC, 10, 10, hicoLogo);
			
			SelectObject(hDC, hFont_MainBold);
			rt.left = 52; rt.top = 10; rt.right = 232; rt.bottom = 50; DrawText(hDC, "Checkers", -1, &rt, 0);
			rt.left = 52; rt.top = 26; rt.right = 232; rt.bottom = 58; DrawText(hDC, "By Joe Esposito", -1, &rt, 0);


			// Clean up
			SelectObject(hDC, hftTemp);
			SelectObject(hDC2, hbmTemp); DeleteDC(hDC2);
			EndPaint(hWnd, &ps);
			return TRUE;
		
		case WM_SYSCOLORCHANGE:

			hDC = CreateCompatibleDC(NULL); hbmTemp = (HBITMAP)SelectObject(hDC, hBackground);
			DrawGradientRect(hDC, 0, 0, ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
			SelectObject(hDC, hbmTemp); DeleteDC(hDC);
			break;

		case WM_COMMAND:

			if (lParam != NULL)
			{
				// Control Notification
				// ---------------------

				switch (HIWORD(wParam))
				{
				case BN_CLICKED:				// Button Clicked
					switch (LOWORD(wParam)) {
					case ID_BTN_OK:				// OK button
						DestroyWindow(hWnd);
						break;
					}
				}
			}

			break;

		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:
			
			// End Modal Loop:
			if (((LPWINDOWPOS)lParam)->flags & SWP_HIDEWINDOW) EndAbout(hWnd);
			break;

		case WM_DESTROY:

			// Clean up
			// ---------

			if (--nWindowCount == 0) {
				DestroyIcon(hicoLogo); hicoLogo = NULL;
				DeleteObject(hBackground); hBackground = NULL;
			}

			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



// Public Functions
// -----------------

void DoAbout (HWND hOwner)
{
	HWND hWnd;
	hWnd = CreateWindowEx((WS_EX_DLGMODALFRAME | WS_EX_CONTROLPARENT | WS_EX_WINDOWEDGE), ID_ABOUTWND_CLASSNAME, "About Checkers", (WS_POPUPWINDOW | WS_DLGFRAME  | WS_OVERLAPPED | WS_CAPTION | WS_CLIPSIBLINGS), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hOwner, NULL, hInstance, NULL);
	DoModal(hWnd, hOwner);		// Modal loop
}



// Local Functions
// ----------------

VOID EndAbout (HWND hWnd)
{ EndModal(hWnd, 0); }
