// ButtonAdvProc.cpp
// ButtonAdv Procedure Implementation File
// By Joe Esposito


#pragma once



// Internal Variables
// -------------------

LOCAL LPBUTTONADVCLASSINFO m_ButtonAdvInfo = NULL;



// Local Structs
// --------------

typedef struct tagBUTTONADVINFO
{
	WNDPROC lpForwardProc;				// Windows procedure to forward to
	POINTS ptTemp;						// Temp point variable (for BN_MOUSEMOVE)
} BUTTONADVINFO, *LPBUTTONADVINFO;



// ButtonAdv Window Procedure
// ---------------------------

LOCAL LRESULT CALLBACK _ButtonAdvProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPBUTTONADVINFO lpbi;
	WNDPROC wndprocTemp;
	LRESULT lResult;
	POINT pt;
	RECT rt;
	
	if (!m_ButtonAdvInfo) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	lpbi = (LPBUTTONADVINFO)GetWindowLong(hWnd, m_ButtonAdvInfo->uWindowIndex);


	switch (uMsg)
	{
		case WM_CREATE:
			
			// Create Local Info
			// ------------------

			// Create info
			if ((lpbi = new BUTTONADVINFO) == NULL) return -1;
			
			// Set info
			lpbi->lpForwardProc = m_ButtonAdvInfo->lpButtonProc;
			lpbi->ptTemp.x = 0; lpbi->ptTemp.y = 0;

			// Set window info
			SetWindowLong(hWnd, m_ButtonAdvInfo->uWindowIndex, (LONG)lpbi);
			break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:

			if (!(GetWindowLong(hWnd, GWL_STYLE) & BS_NOTIFY)) break;	// Send only if user wants notifications

			if (((wParam & MK_LBUTTON) != MK_LBUTTON) && ((wParam & MK_MBUTTON) != MK_MBUTTON) && ((wParam & MK_RBUTTON) != MK_RBUTTON)) {
				GetWindowRect(hWnd, &rt);
				pt.x = LOWORD(lParam); pt.y = HIWORD(lParam); ClientToScreen(hWnd, &pt);
			  
				if (((pt.x >= rt.left) && (pt.x <= rt.right)) && ((pt.y >= rt.top) && (pt.y <= rt.bottom))) {
					if (GetCapture() == NULL)
					{ SetCapture(hWnd); SendMessage(GetParent(hWnd), WM_COMMAND, (WPARAM)MAKELONG(GetWindowLong(hWnd, GWL_ID), BN_MOUSEENTER), (LPARAM)hWnd); }
				} else
				{ ReleaseCapture(); }
			}

			break;

		case WM_ERASEBKGND:
			
			if (GetWindowLong(hWnd, GWL_STYLE) & BS_OWNERDRAW) return TRUE;
			break;

		case WM_CAPTURECHANGED:

			if (GetCapture() != hWnd) SendMessage(GetParent(hWnd), WM_COMMAND, (WPARAM)MAKELONG(GetWindowLong(hWnd, GWL_ID), BN_MOUSEEXIT), (LPARAM)hWnd);
			break;

		case WM_GETDLGCODE:

			if (!lpbi) return CallWindowProc(m_ButtonAdvInfo->lpButtonProc, hWnd, uMsg, wParam, lParam);

			lResult = CallWindowProc(lpbi->lpForwardProc, hWnd, uMsg, wParam, lParam);
			
			if (lParam != NULL) {
				if (((LPMSG)lParam)->message == WM_CHAR) lResult |= DLGC_WANTCHARS;
				if ((((LPMSG)lParam)->message == WM_KEYDOWN) || (((LPMSG)lParam)->message == WM_KILLFOCUS) || (((LPMSG)lParam)->message == WM_ACTIVATE))
					if (SendMessage(hWnd, BM_GETSTATE, NULL, NULL) & BST_PUSHED)
					{ return (CallWindowProc(lpbi->lpForwardProc, hWnd, uMsg, wParam, lParam) | DLGC_WANTMESSAGE); }
			}

			return lResult;

		case WM_DESTROY:

			if (!lpbi) return CallWindowProc(m_ButtonAdvInfo->lpButtonProc, hWnd, uMsg, wParam, lParam);
			
			wndprocTemp = lpbi->lpForwardProc;
			delete lpbi; SetWindowLong(hWnd, m_ButtonAdvInfo->uWindowIndex, NULL);
			
			return CallWindowProc(wndprocTemp, hWnd, uMsg, wParam, lParam);
	}

	if (!lpbi) return CallWindowProc(m_ButtonAdvInfo->lpButtonProc, hWnd, uMsg, wParam, lParam);
	return CallWindowProc(lpbi->lpForwardProc, hWnd, uMsg, wParam, lParam);
}
