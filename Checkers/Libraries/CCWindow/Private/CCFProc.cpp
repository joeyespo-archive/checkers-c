// CCFProc.cpp - CCWindow
// Control Container Frame Window Procedure Implementation File
// By Joe Esposito



// CCFrame Window Procedure
// -------------------------

LOCAL LRESULT CALLBACK _CCFrameProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	union { COLORREF cr; LPCCCITEM *lpacccitem; };
	union { HWND hwndTemp; UINT uTemp; DWORD dwTemp; BOOL bTemp; };
	
	LPCCFRAMEINFO lpcci;
	LRESULT lResult;
	RECT rt;
	HDC hDC;

	lpcci = (LPCCFRAMEINFO)GetWindowLong(hWnd, 0);


	switch (uMsg)
	{
		case WM_CREATE:

			// Initialize
			// -----------

			// Check extended styles
			if (((LPCREATESTRUCT)lParam)->dwExStyle & CCFRAME_DISABLED_WINDOWEXSTYLES)
			{ SetWindowLong(hWnd, GWL_EXSTYLE, (((LPCREATESTRUCT)lParam)->dwExStyle & ~CCFRAME_DISABLED_WINDOWEXSTYLES)); }
			// Check styles
			if (((LPCREATESTRUCT)lParam)->style & CCFRAME_DISABLED_WINDOWSTYLES)
			{ SetWindowLong(hWnd, GWL_STYLE, (((LPCREATESTRUCT)lParam)->style & ~CCFRAME_DISABLED_WINDOWSTYLES)); }



			// Set Local Info
			// ---------------

			// Create CCFrame info
			lpcci = new CCFRAMEINFO;
			lpcci->hScheme = NULL;
			lpcci->lpActiveCCClient = NULL;
			lpcci->uNumCCClients = 0;
			lpcci->lpaCCClients = NULL;
			lpcci->lpUserData = new DWORD; (*lpcci->lpUserData) = 0;

			// Window just created (no CCClient active); window is NOT currently a control parent
			if (((LPCREATESTRUCT)lParam)->style & WS_EX_CONTROLPARENT)
				SetWindowLong(hWnd, GWL_EXSTYLE, (GetWindowLong(hWnd, GWL_EXSTYLE) & ~WS_EX_CONTROLPARENT));
			
			// Set info
			SetWindowLong(hWnd, 0, (LONG)lpcci);
			break;


		case CCFM_CREATE:

			if (!lpcci) return FALSE;

			// Check to maintain unique id's
			if (lpcci->uNumCCClients > 0) {
				for (uTemp = 0; uTemp < lpcci->uNumCCClients; uTemp++)
				{ if (lpcci->lpaCCClients[uTemp]->uId == ((LPCCCLIENTCREATESTRUCT)lParam)->uId) { return TRUE; } }
			}

			// Resize CCClient window item array
			lpacccitem = lpcci->lpaCCClients;
			if ((lpcci->lpaCCClients = new LPCCCITEM [(++lpcci->uNumCCClients)]) == NULL) { lpcci->lpaCCClients = lpacccitem; lpcci->uNumCCClients--; return FALSE; }
			if (lpacccitem) memcpy(lpcci->lpaCCClients, lpacccitem, (sizeof(LPCCCITEM) * (lpcci->uNumCCClients-1)));

			// Set reserved info
			((LPCCCLIENTCREATESTRUCT)lParam)->lpReserved = hWnd;
			((LPCCCLIENTCREATESTRUCT)lParam)->dwStyle &= (CCCLIENT_ALLOWED_WINDOWSTYLES);
			((LPCCCLIENTCREATESTRUCT)lParam)->dwExStyle &= (CCCLIENT_ALLOWED_WINDOWEXSTYLES);

			// Set CCClient window item info
			if ((lpcci->lpaCCClients[(lpcci->uNumCCClients-1)] = new CCCITEM) == NULL) { delete [lpcci->uNumCCClients] lpcci->lpaCCClients; lpcci->uNumCCClients--; return FALSE; }
			lpcci->lpaCCClients[(lpcci->uNumCCClients-1)]->bDeleting = false;
			lpcci->lpaCCClients[(lpcci->uNumCCClients-1)]->uId = ((LPCCCLIENTCREATESTRUCT)lParam)->uId;
			
			// Create the window, and store the handle in the CCClient item
			if ((lpcci->lpaCCClients[(lpcci->uNumCCClients-1)]->hCCClientWnd = CreateWindowEx((WS_EX_CONTROLPARENT | ((LPCCCLIENTCREATESTRUCT)lParam)->dwExStyle), ID_CCCLIENT_CLASSNAME, NULL, (CCCLIENT_FORCED_WINDOWSTYLES | ((LPCCCLIENTCREATESTRUCT)lParam)->dwStyle), 0, 0, ((LPCCCLIENTCREATESTRUCT)lParam)->cx, ((LPCCCLIENTCREATESTRUCT)lParam)->cy, hWnd, (HMENU)0, ((LPCCCLIENTCREATESTRUCT)lParam)->hInstance, (LPVOID)lParam)) == NULL)
			{ delete lpcci->lpaCCClients[(lpcci->uNumCCClients-1)]; delete [lpcci->uNumCCClients] lpcci->lpaCCClients; lpcci->uNumCCClients--; return FALSE; }
			

			// Delete old pointer array
			delete [(lpcci->uNumCCClients-1)] lpacccitem;
			return TRUE;

		case CCFM_DESTROY:

			if (!lpcci) return FALSE;
			if (lpcci->uNumCCClients <= 0) return FALSE;

			// Look for specified window
			for (uTemp = 0; uTemp < lpcci->uNumCCClients; uTemp++)
			{
				if (wParam == NULL) { if (lpcci->lpaCCClients[uTemp]->uId != (UINT)lParam) continue; }
				else { if (lpcci->lpaCCClients[uTemp]->hCCClientWnd != (HWND)wParam) continue; }

				if ((--lpcci->uNumCCClients) == 0) {
					if (!DestroyWindow(lpcci->lpaCCClients[uTemp]->hCCClientWnd)) { lpcci->uNumCCClients++; return FALSE; };
					delete lpcci->lpaCCClients[0];
					delete [1] lpcci->lpaCCClients;
					lpcci->lpaCCClients = NULL;
					SendMessage(hWnd, CCFM_SETACTIVEWINDOW, 0, NULL);
					return TRUE;
				}


				// Resize, excluding the removed item
				// -----------------------------------

				// Recursion check
				if (lpcci->lpaCCClients[uTemp]->bDeleting) return TRUE;
				lpcci->lpaCCClients[uTemp]->bDeleting = true;

 				// Create new struct and destroy old window (with error checking)
				if ((lpacccitem = new LPCCCITEM [lpcci->uNumCCClients]) == NULL) { lpcci->uNumCCClients++; lpcci->lpaCCClients[uTemp]->bDeleting = false; return FALSE; }
				if (lpcci->lpaCCClients[uTemp]->hCCClientWnd == (HWND)SendMessage(hWnd, CCFM_GETACTIVEWINDOW, 0, 0)) SendMessage(hWnd, CCFM_SETACTIVEWINDOW, 0, NULL);
				if (!DestroyWindow(lpcci->lpaCCClients[uTemp]->hCCClientWnd)) { delete [lpcci->uNumCCClients] lpacccitem; lpcci->uNumCCClients++; lpcci->lpaCCClients[uTemp]->bDeleting = false; return FALSE; };
				if (uTemp > 0) memcpy(lpacccitem, lpcci->lpaCCClients, (sizeof(LPCCCITEM) * uTemp));
				if (uTemp < lpcci->uNumCCClients) memcpy((&(lpacccitem[uTemp])), (&(lpcci->lpaCCClients[uTemp+1])), (sizeof(LPCCCITEM) * (lpcci->uNumCCClients-uTemp)));
				
				delete lpcci->lpaCCClients[uTemp];	// Delete the structure (nothing else will be pointing to it, as of now)
				delete [(lpcci->uNumCCClients+1)] lpcci->lpaCCClients;	// Delete the old pointer list
				lpcci->lpaCCClients = lpacccitem;		// Copy new (updated) structure

				return TRUE;
			}
			
			return FALSE;

		
		case CCFM_GETACTIVEWINDOW:

			if (!lpcci) return NULL;
			if (!lpcci->lpActiveCCClient) return NULL;
			return (LRESULT)lpcci->lpActiveCCClient->hCCClientWnd;

		case CCFM_SETACTIVEWINDOW:

			if (!lpcci) return FALSE;

			if (lParam == NULL) { return _ActivateCCClientWindow(hWnd, lpcci, NULL); }

			// Check window
			if (lpcci->uNumCCClients > 0) {
				for (uTemp = 0; uTemp < lpcci->uNumCCClients; uTemp++) {
					if (lpcci->lpaCCClients[uTemp]->hCCClientWnd == (HWND)lParam)
					{ return _ActivateCCClientWindow( hWnd, lpcci, (lpcci->lpaCCClients[uTemp]) ); }
				}
			}
			
			_ActivateCCClientWindow(hWnd, lpcci, NULL);
			return FALSE;

		case CCFM_GETACTIVEWINDOWID:

			if (!lpcci) return 0;

			if (!lpcci->lpActiveCCClient) return 0;
			return (LRESULT)lpcci->lpActiveCCClient->uId;

		case CCFM_SETACTIVEWINDOWID:

			if (!lpcci) return FALSE;

			// Check window
			if (lpcci->uNumCCClients > 0) {
				for (uTemp = 0; uTemp < lpcci->uNumCCClients; uTemp++) {
					if ((lpcci->lpaCCClients[uTemp]->uId == (UINT)lParam) && (lpcci->lpaCCClients[uTemp]->hCCClientWnd != NULL))
					{ return _ActivateCCClientWindow( hWnd, lpcci, (lpcci->lpaCCClients[uTemp]) ); }
				}
			}
			
			_ActivateCCClientWindow(hWnd, lpcci, NULL);
			return FALSE;

		case CCFM_SETCOLORSCHEME:

			if (!lpcci) return FALSE;

			// Create local color scheme
			DestroyColorScheme(lpcci->hScheme);
			lpcci->hScheme = CreateColorScheme((LPSCHEMECOLORBASE)lParam, 0);
			return TRUE;

		case CCFM_GETCOLORSCHEME: if (!lpcci) return FALSE;  return (LRESULT)lpcci->hScheme;

		case CCFM_SETUSERDATA: if (!lpcci) return 0;  if (!lpcci->lpUserData) return 0;  dwTemp = (*lpcci->lpUserData); (*lpcci->lpUserData) = (DWORD)lParam; return (LRESULT)dwTemp;
		case CCFM_GETUSERDATA: if (!lpcci) return 0;  if (!lpcci->lpUserData) return 0;  return (LRESULT)(*lpcci->lpUserData);

		case CCFM_SETBKCOLOR: lResult = (BOOL)SetSchemeColor(lpcci->hScheme, CSI_BACKGROUND, (COLORREF)lParam); return lResult;
		case CCFM_GETBKCOLOR: return (LRESULT)GetSchemeColor(lpcci->hScheme, CSI_BACKGROUND);
		case CCFM_GETBKBRUSH: return (LRESULT)GetSchemeBkBrush(lpcci->hScheme);

		case DM_GETDEFID: return (MAKELONG(GetDlgCtrlID(GetFocus()), DC_HASDEFID));


		case WM_STYLECHANGING:

			if (wParam != GWL_EXSTYLE) {
				// Check styles
				if (((LPSTYLESTRUCT)lParam)->styleNew & CCFRAME_DISABLED_WINDOWSTYLES) ((LPSTYLESTRUCT)lParam)->styleNew = (((LPSTYLESTRUCT)lParam)->styleNew & ~CCFRAME_DISABLED_WINDOWSTYLES);
				break;
			}

			// Check for WS_EX_CONTROLPARENT
			hwndTemp = (HWND)SendMessage(hWnd, CCFM_GETACTIVEWINDOW, 0, 0);
			if (((((LPSTYLESTRUCT)lParam)->styleNew & WS_EX_CONTROLPARENT) == WS_EX_CONTROLPARENT) == (hwndTemp == NULL)) ((LPSTYLESTRUCT)lParam)->styleNew = ((((LPSTYLESTRUCT)lParam)->styleNew & ((hwndTemp == NULL)?(~WS_EX_CONTROLPARENT):(0xFFFFFFFF))) | ((hwndTemp == NULL)?(0):(WS_EX_CONTROLPARENT)));

			// Check extended styles
			if (((LPSTYLESTRUCT)lParam)->styleNew & CCFRAME_DISABLED_WINDOWEXSTYLES) ((LPSTYLESTRUCT)lParam)->styleNew = (((LPSTYLESTRUCT)lParam)->styleNew & ~CCFRAME_DISABLED_WINDOWEXSTYLES);
			break;

		case WM_STYLECHANGED:
			
			if (wParam != GWL_EXSTYLE) {
				// Check styles
				if (((LPSTYLESTRUCT)lParam)->styleNew & CCFRAME_DISABLED_WINDOWSTYLES)
				{ SetWindowLong(hWnd, GWL_STYLE, (((LPSTYLESTRUCT)lParam)->styleNew & ~CCFRAME_DISABLED_WINDOWSTYLES)); }
				break;
			}

			// Check for WS_EX_CONTROLPARENT
			hwndTemp = (HWND)SendMessage(hWnd, CCFM_GETACTIVEWINDOW, 0, 0);
			if (((((LPSTYLESTRUCT)lParam)->styleNew & WS_EX_CONTROLPARENT) == WS_EX_CONTROLPARENT) == (hwndTemp == NULL)) SetWindowLong(hWnd, GWL_EXSTYLE, ((((LPSTYLESTRUCT)lParam)->styleNew & ((hwndTemp == NULL)?(~WS_EX_CONTROLPARENT):(0xFFFFFFFF))) | ((hwndTemp == NULL)?(0):(WS_EX_CONTROLPARENT))));
	
			// Check extended styles
			if (((LPSTYLESTRUCT)lParam)->styleNew & CCFRAME_DISABLED_WINDOWEXSTYLES)
			{ SetWindowLong(hWnd, GWL_EXSTYLE, (((LPSTYLESTRUCT)lParam)->styleNew & ~CCFRAME_DISABLED_WINDOWEXSTYLES)); }
			break;

		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:

			// Send CC Client a resize update
			if (!lpcci) break;
			if (!lpcci->lpActiveCCClient) break;

			GetWindowRect(lpcci->lpActiveCCClient->hCCClientWnd, &rt);	// Get the window rect
			_RelocateCCCWnd(lpcci->lpActiveCCClient->hCCClientWnd, (rt.right - rt.left), (rt.bottom - rt.top), FALSE);
			UpdateWindow(hWnd);	// Update window
			break;

		case WM_NCPAINT:

			// Set up drawing
			hDC = GetWindowDC(hWnd); GetWindowRect(hWnd, &rt);
			
			// Set up frame coordinates
			rt.right -= rt.left; rt.left = 0; rt.bottom -= rt.top; rt.top = 0;

			// Draw border
			if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_CLIENTEDGE)
			{ DrawSchemeEdge(hDC, &rt, lpcci->hScheme, (EDGE_SUNKEN), (BF_RECT)); }
			else if (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_STATICEDGE)
			{ DrawSchemeEdge(hDC, &rt, lpcci->hScheme, (BDR_SUNKENINNER), (BF_RECT)); }
			else { DrawSchemeEdge(hDC, &rt, lpcci->hScheme, (EDGE_RAISED), (BF_RECT)); }

			// Clean up
			ReleaseDC(hWnd, hDC);
			return 0;

		case WM_ERASEBKGND:

			if (!lpcci) break;

			// Erase control background
			GetUpdateRect(hWnd, &rt, FALSE);
			FillRect((HDC)(wParam), &rt, GetSchemeBkBrush(lpcci->hScheme));
			return TRUE;

		case WM_DESTROY:

			// Clean up
			// ---------

			if (lpcci)
			{
				// Destroy each CCClient
				while (lpcci->uNumCCClients > 0)
				{ SendMessage(hWnd, CCFM_DESTROY, (WPARAM)lpcci->lpaCCClients[0]->hCCClientWnd, 0); }

				delete lpcci->lpUserData;				// Delete user data
				DestroyColorScheme(lpcci->hScheme);		// Destroy color scheme
				delete lpcci;							// Delete the local info
			}

			SetWindowLong(hWnd, 0, 0);					// Failsafe
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
