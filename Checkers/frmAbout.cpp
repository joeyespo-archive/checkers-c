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



// frmMain Window Procedure
// -------------------------

LRESULT CALLBACK frmAboutProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hDC2;
	PAINTSTRUCT ps;
	HBITMAP hbmTemp;
	HFONT hftTemp;
	HWND hwndTemp;
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

			if ((nWindowCount++) == 0)	// Increase window count by 1
			{
				// Initialize shared data
				hBackground = CreateGradientBitmap(ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
				hicoLogo = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
			}


			// Create Window
			// --------------

			hwndTemp = CreateButton("OK", (WS_CHILD | WS_GROUP | WS_TABSTOP | WS_VISIBLE), 258, 8, 73, 25, hWnd, ID_BTN_OK, hInstance);
			 SendMessage(hwndTemp, WM_SETFONT, (WPARAM)hFont_Main, 0);
			
			break;

		case WM_ACTIVATE:

			if ((LOWORD(wParam) != WA_INACTIVE) && (HIWORD(wParam) == FALSE))
			{ SetFocus(GetDlgItem(hWnd, ID_BTN_OK)); SendMessage(hWnd, DM_SETDEFID, ID_BTN_OK, NULL); return 0; }
			
			break;

		case DM_GETDEFID:
			
			return (MAKELONG(ID_BTN_OK, DC_HASDEFID));

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

			// Redraw background
			hDC = CreateCompatibleDC(NULL); hbmTemp = (HBITMAP)SelectObject(hDC, hBackground);
			DrawGradientRect(hDC, 0, 0, ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
			SelectObject(hDC, hbmTemp); DeleteDC(hDC);
			break;

		case WM_COMMAND:

			if (lParam != NULL)
			{
				// Control Notification
				// ---------------------

				switch (LOWORD(wParam)) {
				case (ID_BTN_OK | BN_CLICKED):			// OK button
					
					switch (HIWORD(wParam)) {
					case BN_CLICKED:
					
						SendMessage(hWnd, WM_CLOSE, 0, 0);
						return 0;
					}
				}
			}

			break;

		case WM_CLOSE:
			
			// End the dialog
			EndDialog(hWnd, 0);
			return 0;

		case WM_DESTROY:

			// Clean up
			// ---------

			// Failsafe
			EndDialog(hWnd, 0);

			// Clean up shared data
			if (--nWindowCount == 0) {
				DestroyIcon(hicoLogo); hicoLogo = NULL;
				DeleteObject(hBackground); hBackground = NULL;
			}

			break;
	}

	return DefDlgProc(hWnd, uMsg, wParam, lParam);
}



// Public Functions
// -----------------

void DoAbout (HWND hParent)
{ CreateDialogBox((WS_EX_CONTROLPARENT | WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE), ID_ABOUTWND_CLASSNAME, "About Checkers", (WS_VISIBLE | WS_POPUPWINDOW | WS_DLGFRAME | WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | DS_NOIDLEMSG | DS_SETFOREGROUND), CW_USEDEFAULT, CW_USEDEFAULT, 344, 178, hParent, NULL, 0, hInstance, NULL, NULL, true); }
