// MarqueeBoxProc.cpp
// MarqueeBox Procedure Implementation File
// By Joe Esposito


#pragma once



// Internal Variables
// -------------------

LOCAL LPMARQUEEBOXCLASSINFO m_MarqueeBoxInfo = NULL;



// Local Structs
// --------------

typedef struct tagMARQUEEBOXINFO
{
	COLORREF crBackcolor;		// Color of the background
	COLORREF crTextColor;		// Color of the text
	HFONT hFont;				// Font of text
} MARQUEEBOXINFO, *LPMARQUEEBOXINFO;



// MarqueeBox Window Procedure
// ----------------------------

LOCAL LRESULT CALLBACK _MarqueeBoxProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	LPMARQUEEBOXINFO lpbi;
	COLORREF crBackcolor; COLORREF crTextColor;
	LPSTR lpszTemp; INT iTemp;
	HBRUSH hbrTemp;
	DWORD dwStyle;
	HFONT hftTemp;
	RECT rt;
	
	if (!m_MarqueeBoxInfo) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	lpbi = (LPMARQUEEBOXINFO)GetWindowLong(hWnd, 0);


	switch (uMsg)
	{
		case WM_CREATE:
			
			// Create Local Info
			// ------------------

			// Create info
			if ((lpbi = new MARQUEEBOXINFO) == NULL) return -1;
			lpbi->crBackcolor = 0x8000000F;		// Set default color: button face
			lpbi->crTextColor = 0x80000008;		// Set default color: window text
			lpbi->hFont = NULL;					// Set default font: system font


			// Set window info
			SetWindowLong(hWnd, 0, (LONG)lpbi);
			break;

		// !!!!! Invalidate only non-border area
		case MBM_SETBACKCOLOR: if (!lpbi) return FALSE; lpbi->crBackcolor = (COLORREF)wParam;  if (LOWORD(lParam) != FALSE) { GetClientRect(hWnd, &rt); InvalidateRect(hWnd, &rt, TRUE); }  return TRUE;
		case MBM_SETTEXTCOLOR: if (!lpbi) return FALSE; lpbi->crTextColor = (COLORREF)wParam;  if (LOWORD(lParam) != FALSE) { GetClientRect(hWnd, &rt); InvalidateRect(hWnd, &rt, TRUE); }  return TRUE;

		// !!!!! Invalidate only non-border area
		case WM_SETFONT: if (!lpbi) return 0;  lpbi->hFont = (HFONT)wParam; if (LOWORD(lParam) != FALSE) { GetClientRect(hWnd, &rt); InvalidateRect(hWnd, &rt, TRUE); } return 0;
		case WM_GETFONT: if (!lpbi) return NULL;  return (LRESULT)lpbi->hFont;

		case WM_WINDOWPOSCHANGED:

			if ((((LPWINDOWPOS)lParam)->flags & SWP_NOSIZE) == 0)
			{
				// Resize Client
				// --------------

				// !!!!! Invalidate only non-border area
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, TRUE);
			}

			return 0;

		case WM_PAINT:

			// Setup painting
			// ---------------

			// Get window's update DC
			hDC = BeginPaint(hWnd, &ps);
			dwStyle = GetWindowLong(hWnd, GWL_STYLE);

			// Get 24-bit color from windows color
			if (((crBackcolor = lpbi->crBackcolor) & 0xFF000000) == 0x80000000) { crBackcolor = GetSysColor(crBackcolor & 0xFFFFFF); }
			if (((crTextColor = lpbi->crTextColor) & 0xFF000000) == 0x80000000) { crTextColor = GetSysColor(crTextColor & 0xFFFFFF); }


			// Set Up Drawing
			// ---------------

			// !!!!! Flicker-free effect

			// !!!!! 'rt' holds size of text
			GetClientRect(hWnd, &rt); rt.right = 280; rt.bottom = 20;
			// !!!!! Use client window with given borders
			if ((dwStyle & MBS_ALIGNCENTER) == MBS_ALIGNCENTER) { rt.top = ((ClientHeight(hWnd) - rt.bottom) / 2); rt.bottom += rt.top;  rt.left = ((ClientWidth(hWnd) - rt.right) / 2); rt.right += rt.left; }
			else if ((dwStyle & MBS_ALIGNBOTTOMRIGHT) == MBS_ALIGNBOTTOMRIGHT) { rt.top = (ClientHeight(hWnd) - rt.bottom); rt.bottom += rt.top;  rt.left = (ClientWidth(hWnd) - rt.right); rt.right += rt.left; }
			else { rt.top = 0; rt.left = 0; }

			// !!!!! Calculate the real text position [of scrolling] (left/top) depeding on VERTICAL bit in style
			if (dwStyle & MBS_MARQUEEVERT)
			{}
			else
			{}

			// Draw background
			// !!!!! Draw around the rect
			hbrTemp = CreateSolidBrush(crBackcolor);
			FillRect(hDC, &ps.rcPaint, hbrTemp);	// !!!!! Fill the background
			DeleteObject(hbrTemp);	// Delete the brush

			
			// Draw Text
			// ----------

			if ((iTemp = GetWindowTextLength(hWnd)) > 0)
			{
				// Setup drawing
				lpszTemp = new char [(iTemp + 1)]; GetWindowText(hWnd, lpszTemp, (iTemp + 1)); // Get string
				if (lpbi->hFont) hftTemp = (HFONT)SelectObject(hDC, (HFONT)lpbi->hFont);	// Get font
				SetBkColor(hDC, crBackcolor); SetTextColor(hDC, crTextColor);		// Get text format

				// Draw Text
				DrawText(hDC, lpszTemp, iTemp, &rt, 0);

				// Clean up
				if (lpbi->hFont) SelectObject(hDC, hftTemp);	// Restore original font
				delete [iTemp] lpszTemp;	// Delete temp string
			}


			// Clean up
			// ---------

			EndPaint(hWnd, &ps);		// End painting
			return 0;

		case WM_DESTROY:

			// Clean up
			// ---------

			// !!!!! DelectObject(lpbi->hbrBackground);

			delete lpbi; SetWindowLong(hWnd, 0, NULL);
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
