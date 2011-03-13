// CCCProc.cpp - CCWindow
// Control Container Client Window Procedure Implementation File
// By Joe Esposito



// CCClient Window Procedure
// --------------------------

LOCAL LRESULT CALLBACK _CCClientProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	union { LPVOID lpvTemp; LRESULT lResult; HSCHEME htmpScheme; };

	LPCCCLIENTINFO lpccci;
	INT cx, cy;
	RECT rt;
	HDC hDC;

	lpccci = (LPCCCLIENTINFO)GetWindowLong(hWnd, 0);

	switch (uMsg)
	{
		case WM_CREATE:

			// Initialize
			// -----------

			// Get createion parameters
			if ((lpvTemp = ((LPCREATESTRUCT)lParam)->lpCreateParams) == NULL) return -1;


			// Check extended styles
			if (((LPCREATESTRUCT)lParam)->dwExStyle & ~CCCLIENT_ALLOWED_WINDOWEXSTYLES)
			{ SetWindowLong(hWnd, GWL_EXSTYLE, (((LPCREATESTRUCT)lParam)->dwExStyle & CCCLIENT_ALLOWED_WINDOWEXSTYLES)); }
			// Check styles
			if (((LPCREATESTRUCT)lParam)->style & ~CCCLIENT_ALLOWED_WINDOWSTYLES)
			{ SetWindowLong(hWnd, GWL_STYLE, (((LPCREATESTRUCT)lParam)->style & CCCLIENT_ALLOWED_WINDOWSTYLES)); }
			

			
			// Set Local Info
			// ---------------

			// Create local info
			if ((lpccci = new CCCLIENTINFO) == NULL) return -1;
			
			// Set info pointer
			SetWindowLong(hWnd, 0, (LONG)lpccci);

			
			// Set local info
			if ((lpccci->hCCFrameWnd = (HWND)((LPCCCLIENTCREATESTRUCT)lpvTemp)->lpReserved) == NULL) { delete lpccci; return -1; }
			lpccci->lpWndProc = ((LPCCCLIENTCREATESTRUCT)lpvTemp)->lpWndProc;
			lpccci->lpUserData = new DWORD; (*lpccci->lpUserData) = 0;

			// Failsafe
			if (lpccci->lpWndProc == NULL) lpccci->lpWndProc = DefCCClientProc;
			if (lpccci->lpWndProc == DefWindowProc) lpccci->lpWndProc = DefCCClientProc;


			// Reset reserved info
			((LPCCCLIENTCREATESTRUCT)lpvTemp)->lpReserved = NULL;
			
			break;
		

		case CCCM_GETCCFRAME:

			// Return the CCFrame window
			return (LRESULT)lpccci->hCCFrameWnd;

		case CCCM_GETCOLORSCHEME:
		
			// Return the CCFrame's ColorScheme
			return (LRESULT)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETCOLORSCHEME, 0, 0);

		case CCCM_GETBKCOLOR:
		
			// Return the CCFrame's background color
			return (LRESULT)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETBKCOLOR, 0, 0);

		case CCCM_GETBKBRUSH:

			// Return the CCFrame's background brush
			return (LRESULT)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETBKBRUSH, 0, 0);

		case CCCM_GETCCFUSERDATA: return (LRESULT)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETUSERDATA, 0, 0);
		case CCCM_SETUSERDATA: if (!lpccci) return 0;  if (!lpccci->lpUserData) return 0;  (*lpccci->lpUserData) = (DWORD)lParam; return TRUE;
		case CCCM_GETUSERDATA: if (!lpccci) return 0;  if (!lpccci->lpUserData) return 0;  lResult = (LRESULT)(*lpccci->lpUserData); (*lpccci->lpUserData) = (DWORD)lParam; return lResult;


		case WM_STYLECHANGING:

			// Check extended styles
			if (wParam == GWL_EXSTYLE)
			{ ((LPSTYLESTRUCT)lParam)->styleNew &= CCCLIENT_ALLOWED_WINDOWEXSTYLES; break; }
			
			// Check styles
			((LPSTYLESTRUCT)lParam)->styleNew = ((((LPSTYLESTRUCT)lParam)->styleNew & CCCLIENT_ALLOWED_WINDOWSTYLES) | CCCLIENT_FORCED_WINDOWSTYLES);
			break;

		case WM_STYLECHANGED:

			// Check extended styles
			if (wParam == GWL_EXSTYLE) {
				if (((LPSTYLESTRUCT)lParam)->styleNew & ~CCCLIENT_ALLOWED_WINDOWEXSTYLES)
				{ SetWindowLong(hWnd, GWL_EXSTYLE, (((LPSTYLESTRUCT)lParam)->styleNew & CCCLIENT_ALLOWED_WINDOWEXSTYLES)); }
			}

			// Check styles
			if (((LPSTYLESTRUCT)lParam)->styleNew & ~(CCCLIENT_ALLOWED_WINDOWSTYLES | CCCLIENT_FORCED_WINDOWSTYLES))
			{ SetWindowLong(hWnd, GWL_STYLE, ((((LPSTYLESTRUCT)lParam)->styleNew & CCCLIENT_ALLOWED_WINDOWSTYLES) | CCCLIENT_FORCED_WINDOWSTYLES)); }
			break;

		case WM_WINDOWPOSCHANGING:
		
			// Test hide window
			if (((LPWINDOWPOS)lParam)->flags & SWP_HIDEWINDOW) {
				if (hWnd == (HWND)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETACTIVEWINDOW, 0, 0)) {
					// Active window; do not hide
					if (GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE) { ((LPWINDOWPOS)lParam)->flags &= ~SWP_HIDEWINDOW; } 	// Simply do not hide
					else { ((LPWINDOWPOS)lParam)->flags |= SWP_SHOWWINDOW; }		// Currently hidden; Show the window
				} else {
					// Not active window, continue hide
					if (!(GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)) { ((LPWINDOWPOS)lParam)->flags &= ~SWP_HIDEWINDOW; }	// Already hidden; do not re-hide
				}
			} // Test show window
			if (((LPWINDOWPOS)lParam)->flags & SWP_SHOWWINDOW) {
				if (hWnd == (HWND)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETACTIVEWINDOW, 0, 0)) {
					// Active window; continue show
					if ((GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)) { ((LPWINDOWPOS)lParam)->flags &= ~SWP_SHOWWINDOW; }	// Already shown; do not re-show
				} else {
					// Not active window, do not show
					if ((GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)) { ((LPWINDOWPOS)lParam)->flags |= SWP_HIDEWINDOW; }		// Currently shown; Hide the window
					else { ((LPWINDOWPOS)lParam)->flags &= ~SWP_SHOWWINDOW; }	// Simply do not hide the window
				}
			}
			
			// Do not reposition window
			if (((LPWINDOWPOS)lParam)->flags & SWP_NOREPOSITION)
			{ ((LPWINDOWPOS)lParam)->flags &= ~SWP_NOREPOSITION; ((LPWINDOWPOS)lParam)->hwndInsertAfter = NULL; }
			break;

		case WM_WINDOWPOSCHANGED:
			
			// Test hide window
			if (((LPWINDOWPOS)lParam)->flags & SWP_HIDEWINDOW) {
				// If active window, re-show window
				if (hWnd == (HWND)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETACTIVEWINDOW, 0, 0))
				{ ShowWindow(hWnd, SW_SHOW); }
			} // Test show window
			if (((LPWINDOWPOS)lParam)->flags & SWP_SHOWWINDOW) {
				// If not active window, re-hide window
				if (hWnd != (HWND)SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_GETACTIVEWINDOW, 0, 0))
				{ ShowWindow(hWnd, SW_HIDE); }
			}


			// Resize/reposition correctly, according to CCFrame settings
			if (!( (((LPWINDOWPOS)lParam)->flags & SWP_NOMOVE) && (((LPWINDOWPOS)lParam)->flags & SWP_NOSIZE) ))
			{
				// Get size
				if (((LPWINDOWPOS)lParam)->flags & SWP_NOSIZE)
				{ GetWindowRect(hWnd, &rt); cx = (rt.right-rt.left); cy = (rt.bottom-rt.top); }
				else { cx =  ((LPWINDOWPOS)lParam)->cx; cy =  ((LPWINDOWPOS)lParam)->cy; }
			
				// Relocate CC Client window
				_RelocateCCCWnd(hWnd, cx, cy, FALSE);
				break;
			}

			break;

		case WM_NCPAINT:

			// Set up drawing
			hDC = GetWindowDC(hWnd);
			GetWindowRect(hWnd, &rt);
			htmpScheme = (HSCHEME)SendMessage(hWnd, CCCM_GETCOLORSCHEME, NULL, NULL);
			

			// !!!!! SystemParametersInfo() -- SPI_GETBORDER
			// Set up frame coordinates
			rt.right -= rt.left; rt.left = 0; rt.bottom -= rt.top; rt.top = 0;

			// Draw border
			if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_CLIENTEDGE)
			{ DrawSchemeEdge(hDC, &rt, htmpScheme, (EDGE_SUNKEN), (BF_RECT)); }
			else if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_STATICEDGE)
			{ DrawSchemeEdge(hDC, &rt, htmpScheme, (BDR_SUNKENINNER), (BF_RECT)); }
			else if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_WINDOWEDGE)
			{ DrawSchemeEdge(hDC, &rt, htmpScheme, (EDGE_RAISED), (BF_RECT)); }

			if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_BORDER)
			{ DrawSchemeEdge(hDC, &rt, htmpScheme, (BDR_RAISEDOUTER), (BF_RECT | BF_FLAT)); }

			// Clean up
			ReleaseDC(hWnd, hDC);
			return 0;

		case WM_DESTROY:

			// Clean up
			// ---------

			// Notify CC, allow it to delete
			SendMessage((HWND)SendMessage(hWnd, CCCM_GETCCFRAME, 0, 0), CCFM_DESTROY, 0, (LPARAM)hWnd);
			

			// Forward to user procedure
			if (lpccci) { lResult = CallWindowProc(lpccci->lpWndProc, hWnd, uMsg, wParam, lParam); }
			else { lResult = DefCCClientProc(hWnd, uMsg, wParam, lParam); }


			// Clean up
			// ---------

			if (lpccci) {
				delete lpccci->lpUserData;			// Delete user data
				delete lpccci;						// Delete the local info
			}

			// Failsafe
			SetWindowLong(hWnd, 0, 0);

			return lResult;
	}

	if ((lpccci) && (lpccci->lpWndProc)) return CallWindowProc(lpccci->lpWndProc, hWnd, uMsg, wParam, lParam);
	return DefCCClientProc(hWnd, uMsg, wParam, lParam);
}



// Default CCClient Window Procedure
// ----------------------------------

LRESULT CALLBACK DefCCClientProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPCCCLIENTINFO lpccci;
	RECT rt;

	lpccci = (LPCCCLIENTINFO)GetWindowLong(hWnd, 0);

	
	switch (uMsg)
	{
		case WM_ERASEBKGND:

			GetClientRect(hWnd, &rt);
			FillRect((HDC)wParam, &rt, (HBRUSH)SendMessage(hWnd, CCCM_GETBKBRUSH, 0, 0));
			return TRUE;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
