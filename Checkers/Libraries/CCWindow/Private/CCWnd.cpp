// CCWnd.cpp - CCWindow
// Control Container Private Implementation File
// By Joe Esposito



// Internal Functions
// -------------------

// Activates a CCClient window
LOCAL BOOL _ActivateCCClientWindow (HWND hCCFWnd, LPCCFRAMEINFO lpcci, LPCCCITEM lpcccitem)
{
	HWND hwndTemp;
	RECT rt;

	// Quick check
	if (lpcccitem) if (!IsWindowEnabled(lpcccitem->hCCClientWnd)) return FALSE;

	
	// Temperarily store old window (for hiding), and set new active window
	hwndTemp = ((lpcci->lpActiveCCClient)?(lpcci->lpActiveCCClient->hCCClientWnd):(NULL));
	lpcci->lpActiveCCClient = lpcccitem;

	// Hide old window
	if (hwndTemp) ShowWindow(hwndTemp, SW_HIDE);
	
	// Check and update WS_EX_CONTROLPARENT style, depending on if a CCClient is activated
	if (((GetWindowLong(hCCFWnd, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) == WS_EX_CONTROLPARENT) == (lpcccitem == NULL)) SetWindowLong(hCCFWnd, GWL_EXSTYLE, ((GetWindowLong(hCCFWnd, GWL_EXSTYLE) & ((lpcccitem == NULL)?(~WS_EX_CONTROLPARENT):(0xFFFFFFFF))) | ((lpcccitem == NULL)?(0):(WS_EX_CONTROLPARENT))) );
	
	// Activate and relocate new window
	if (lpcccitem) {
		GetWindowRect(lpcccitem->hCCClientWnd, &rt);
		_RelocateCCCWnd(lpcccitem->hCCClientWnd, (rt.right-rt.left), (rt.bottom-rt.top), TRUE);
		//!!!!! ShowWindow(lpcccitem->hCCClientWnd, SW_SHOW);
		//SetWindowLong(lpcccitem->hCCClientWnd, GWL_STYLE, (GetWindowLong(lpcccitem->hCCClientWnd, GWL_STYLE) | WS_VISIBLE));
	}

	return TRUE;
}


// Relocates window
LOCAL BOOL _RelocateCCCWnd (HWND hCCCWnd, INT cx, INT cy, BOOL bShow)
{
	HWND hwndTemp;
	INT x, y;
	RECT rt;

	if (!hCCCWnd) return FALSE;


	// Initialize
	hwndTemp = GetParent(hCCCWnd);


	// Calculate new position
	// -----------------------

	GetClientRect((HWND)SendMessage(hCCCWnd, CCCM_GETCCFRAME, 0, 0), &rt);

	switch ((GetWindowLong(hCCCWnd, GWL_STYLE) & CCCS_ALIGNMASK)) {
	case CCCS_ALIGNBOTTOMLEFT: x = 0; y = ((rt.bottom-rt.top) - cy); break;
	case CCCS_ALIGNTOPRIGHT: x = ((rt.right-rt.left) - cx); y = 0; break;
	case CCCS_ALIGNBOTTOMRIGHT: x = ((rt.right-rt.left) - cx); y = ((rt.bottom-rt.top) - cy); break;
	case CCCS_ALIGNTOP: x = (((rt.right-rt.left) - cx) / 2); y = 0; break;
	case CCCS_ALIGNBOTTOM: x = (((rt.right-rt.left) - cx) / 2); y = ((rt.bottom-rt.top) - cy); break;
	case CCCS_ALIGNLEFT: x = 0; y = (((rt.bottom-rt.top) - cy) / 2); break;
	case CCCS_ALIGNRIGHT: x = ((rt.right-rt.left) - cx); y = (((rt.bottom-rt.top) - cy) / 2); break;
	case CCCS_ALIGNCENTER: x = (((rt.right-rt.left) - cx) / 2); y = (((rt.bottom-rt.top) - cy) / 2); break;
	default: x = 0; y = 0; break;
	}


	// Check to see if relocation is really needed
	GetWindowRect(hCCCWnd, &rt); MapWindowPoints(NULL, GetParent(hCCCWnd), (LPPOINT)&rt, 2);
	if (((rt.left == x) && (rt.top == y)) && (((rt.right-rt.left) == cx) && ((rt.bottom-rt.top) == cy)))
	{ if (bShow) ShowWindow(hCCCWnd, SW_SHOW); return FALSE; }

	// Reposition window
	if (!SetWindowPos(hCCCWnd, NULL, x, y, cx, cy, (SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER))) { return FALSE; }

	// Show window
	if (bShow) ShowWindow(hCCCWnd, SW_SHOW);
	return TRUE;
}
