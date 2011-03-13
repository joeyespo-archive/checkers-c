// ColorFunctions.cpp
// Color Functions Internal Implementation File
// By Joe Esposito



// Draws a line using a scheme color
BOOL ESTDCALL SchemeLineTo (HDC hDC, HETHEMEOBJ hThemeObj, INT nColorIndex, INT x, INT y)
{
	BOOL bResult;

	HPEN hpenTemp = (HPEN)SelectObject(hDC, GetSchemeColorObjEx(hThemeObj, nColorIndex, CSM_HPEN));
	bResult = LineTo(hDC, x, y);
	SelectObject(hDC, hpenTemp);
	
	return bResult;
}

// Draws a line using a scheme color
BOOL ESTDCALL DrawSchemeLine (HDC hDC, HETHEMEOBJ hThemeObj, INT nColorIndex, INT x1, INT y1, INT x2, INT y2, LPPOINT lpPoint)
{
	BOOL bResult;

	HPEN hpenTemp = (HPEN)SelectObject(hDC, GetSchemeColorObjEx(hThemeObj, nColorIndex, CSM_HPEN));
	if (!MoveToEx(hDC, x1, y1, lpPoint)) { SelectObject(hDC, hpenTemp); return FALSE; }
	bResult = LineTo(hDC, x2, y2);
	SelectObject(hDC, hpenTemp);

	return bResult;
}

// Draws a windows edge using scheme colors
BOOL ESTDCALL DrawSchemeEdge (HDC hDC, LPRECT lprt, HETHEMEOBJ hThemeObj, UINT uEdge, UINT uFlags)
{
	LPSCHEMECOLORSTRUCT lpcs = NULL;
	HBRUSH hbrBackground = NULL;
	HPEN m_hpenLight = NULL, hpenLight, m_hpenHighlight = NULL, hpenHighlight;
	HPEN m_hpenShadow = NULL, hpenShadow, m_hpenDkShadow = NULL, hpenDkShadow;
	HPEN m_hpenDefaultBorder = NULL, hpenDefaultBorder = NULL;
	HPEN hpenTemp;
	LONG X, Y, nHeight, nWidth;
	RECT rt;

	// Check first
	if (lprt == NULL) return FALSE;
	if (hThemeObj) lpcs = _GetColorObject((LPETHEMEOBJ)hThemeObj);


	// Initialize data
	// ----------------

	// Set up pens and brushes
	if (lpcs)
	{
		hbrBackground = lpcs->hbrBackground;
		m_hpenDefaultBorder = hpenDefaultBorder = lpcs->hpenDefaultBorder;
		m_hpenLight = hpenLight = lpcs->hpenLight; m_hpenHighlight = hpenHighlight = lpcs->hpenHighlight;
		m_hpenShadow = hpenShadow = lpcs->hpenShadow; m_hpenDkShadow = hpenDkShadow = lpcs->hpenDkShadow;
	}
	if (!hbrBackground) hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
	if (!m_hpenLight) hpenLight = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));
	if (!m_hpenHighlight) hpenHighlight = CreatePen(PS_SOLID, 0, GetSysColor( ((uFlags & BF_MONO)?(COLOR_WINDOW):(COLOR_3DHILIGHT)) ));
	if (!m_hpenShadow) hpenShadow = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW));
	if (!m_hpenDkShadow) hpenDkShadow = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW));
	
	// Set up coordinates
	X = lprt->left; Y = lprt->top;
	nWidth = (lprt->right - lprt->left); nHeight = (lprt->bottom - lprt->top);
	
	// Set up device context
	hpenTemp = (HPEN)GetCurrentObject(hDC, OBJ_PEN);


	// Drawing
	// --------

	// Draw edge		!!!!! if BF_<BORDER>, then draw correctly
	if (uFlags & BF_DEFAULT)
	{
		MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
		DRAWLINE(hDC, hpenDefaultBorder, (X), (Y), (uFlags & BF_TOP));
		DRAWLINE(hDC, hpenDefaultBorder, (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
		DRAWLINE(hDC, hpenDefaultBorder, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
		DRAWLINE(hDC, hpenDefaultBorder, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
		X++; Y++; nHeight -= 2; nWidth -= 2;
	}

	if (uFlags & BF_MONO)
	{
		if (uEdge & (BDR_SUNKENOUTER | BDR_RAISEDOUTER)) {
			MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
			DRAWLINE(hDC, hpenDkShadow, (X), (Y), (uFlags & BF_TOP));
			DRAWLINE(hDC, hpenDkShadow, (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
			DRAWLINE(hDC, hpenDkShadow, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
			DRAWLINE(hDC, hpenDkShadow, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			X++; Y++; nHeight -= 2; nWidth -= 2;
		}
		if (uEdge & (BDR_SUNKENINNER | BDR_RAISEDINNER)) {
			MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
			DRAWLINE(hDC, hpenHighlight, (X), (Y), (uFlags & BF_TOP));
			DRAWLINE(hDC, hpenHighlight, (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
			DRAWLINE(hDC, hpenHighlight, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
			DRAWLINE(hDC, hpenHighlight, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			X++; Y++; nHeight -= 2; nWidth -= 2;
		}
	}else if (uFlags & BF_FLAT)
	{
		if (uEdge & (BDR_SUNKENOUTER | BDR_RAISEDOUTER)) {
			MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
			DRAWLINE(hDC, hpenShadow, (X), (Y), (uFlags & BF_TOP));
			DRAWLINE(hDC, hpenShadow, (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
			DRAWLINE(hDC, hpenShadow, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
			DRAWLINE(hDC, hpenShadow, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			X++; Y++; nHeight -= 2; nWidth -= 2;
		}
		if (uEdge & (BDR_SUNKENINNER | BDR_RAISEDINNER)) {
			MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
			DRAWLINE(hDC, hpenLight, (X), (Y), (uFlags & BF_TOP));
			DRAWLINE(hDC, hpenLight, (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
			DRAWLINE(hDC, hpenLight, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
			DRAWLINE(hDC, hpenLight, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			X++; Y++; nHeight -= 2; nWidth -= 2;
		}
	}else
	{
		if (uEdge & (BDR_SUNKENOUTER | BDR_RAISEDOUTER)) {
			if (uEdge & BDR_SUNKENOUTER) {
				MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenDkShadow):(hpenShadow)), (X), (Y), (uFlags & BF_TOP));
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenDkShadow):(hpenShadow)), (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
				DRAWLINE(hDC, hpenHighlight, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
				DRAWLINE(hDC, hpenHighlight, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			}
			if (uEdge & BDR_RAISEDOUTER) {
				MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenHighlight):(hpenLight)), (X), (Y), (uFlags & BF_TOP));
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenHighlight):(hpenLight)), (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
				DRAWLINE(hDC, hpenDkShadow, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
				DRAWLINE(hDC, hpenDkShadow, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			} X++; Y++; nHeight -= 2; nWidth -= 2;
		}
		if (uEdge & (BDR_SUNKENINNER | BDR_RAISEDINNER)) {
			if (uEdge & BDR_SUNKENINNER) {
				MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenShadow):(hpenDkShadow)), (X), (Y), (uFlags & BF_TOP));
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenShadow):(hpenDkShadow)), (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
				DRAWLINE(hDC, hpenLight, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
				DRAWLINE(hDC, hpenLight, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			}
			if (uEdge & BDR_RAISEDINNER) {
				MoveToEx(hDC, (X+(nWidth-2)), Y, NULL);
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenLight):(hpenHighlight)), (X), (Y), (uFlags & BF_TOP));
				DRAWLINE(hDC, ((uFlags & BF_SOFT)?(hpenLight):(hpenHighlight)), (X), (Y+(nHeight-1)), (uFlags & BF_LEFT));
				DRAWLINE(hDC, hpenShadow, (X+(nWidth-1)), (Y+(nHeight-1)), (uFlags & BF_BOTTOM));
				DRAWLINE(hDC, hpenShadow, (X+(nWidth-1)), (Y-1), (uFlags & BF_RIGHT));
			} X++; Y++; nHeight -= 2; nWidth -= 2;
		}
	}

	// Fill middle
	if (uFlags & BF_MIDDLE) {
		rt.left = X; rt.right = (X + nWidth);
		rt.top = Y; rt.bottom = (Y + nHeight);
		FillRect(hDC, &rt, hbrBackground);
	}

	// Adjust client rect
	if (uFlags & BF_ADJUST) {
		lprt->left = X; lprt->right = (X + nWidth);
		lprt->top = Y; lprt->bottom = (Y + nHeight);
	}
	

	// Termination
	// ------------

	// Clean up
	SelectObject(hDC, hpenTemp);

	// Delete local pens (if <m_nn> is NULL, then <nn> was created locally)
	if (!m_hpenLight) DeleteObject(hpenLight);
	if (!m_hpenHighlight) DeleteObject(hpenHighlight);
	if (!m_hpenShadow) DeleteObject(hpenShadow);
	if (!m_hpenDkShadow) DeleteObject(hpenDkShadow);
	if (!m_hpenDefaultBorder) DeleteObject(hpenDefaultBorder);

	// Return OK
	return TRUE;
}

// Draws an item using scheme colors
BOOL ESTDCALL DrawSchemeItem (LPDRAWITEMSTRUCT lpds, UINT uStateExtra, LPRECT lpFocusRect, HETHEMEOBJ hThemeObj, LPVOID lpData, BOOL bNoFlicker)
{
	char *m_Str;
	int n;

	switch (lpds->CtlType) {
	case ODT_BUTTON:

		// Draw a button
		// --------------

		// Get the window's text
		if (!lpData) {
			n = (GetWindowTextLength(lpds->hwndItem) + 1);
			if ((m_Str = new char [n]) == NULL) return FALSE;
			GetWindowText(lpds->hwndItem, m_Str, n);
		}

		DrawSchemeButton(lpds->hDC, &lpds->rcItem, lpFocusRect, hThemeObj, (lpds->itemState | uStateExtra), (LPSTR)((lpData)?(lpData):(m_Str)), bNoFlicker);

		// Clean up
		if (m_Str) delete [n] m_Str;

		// Success
		return TRUE;
	};

	return FALSE;
}


// Draws a button using scheme colors
// !!!!! Draw on memory bitmap, then copy
BOOL ESTDCALL DrawSchemeButton (HDC hDC, LPRECT lprt, LPRECT lpFocusRect, HETHEMEOBJ hThemeObj, UINT uState, LPSTR lpszWindowText, BOOL bNoFlicker)
{
	RECT rt;
	HDC hdcBitmap;
	BITMAPINFO bmi;
	HBITMAP hbmpBitmap, hbmpTemp;
	LONG X, Y, nHeight, nWidth;
	COLORREF crTemp;
	HFONT hfntTemp;
	bool bDefault;
	int i;

	// Check first
	if (!lprt) return FALSE;


	
	// Initialize locals
	// ------------------

	// Set up coordinates
	X = rt.left = lprt->left; rt.right = lprt->right;
	Y = rt.top = lprt->top; rt.bottom = lprt->bottom;
	nHeight = (rt.bottom-rt.top); nWidth = (rt.right-rt.left);

	// Locals
	bDefault = ((uState & ODS_DEFAULT) || (uState & ODS_FOCUS));



	// Create Bitmap
	// --------------

	if (bNoFlicker)
	{
		// Bitmap header
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = nWidth; bmi.bmiHeader.biHeight = -nHeight; bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;

		// Create the bitmap
		hdcBitmap = CreateCompatibleDC(NULL);
		hbmpBitmap = CreateDIBSection(hdcBitmap, &bmi, DIB_RGB_COLORS, NULL, NULL, NULL);
		hbmpTemp = (HBITMAP)SelectObject(hdcBitmap, hbmpBitmap);
	} else { hdcBitmap = hDC; }


	
	// Drawing
	// --------

	// Background
	FillRect(hdcBitmap, lprt, GetSchemeBkBrush(hThemeObj));



	// Draw Text		// !!!!! Draw disabled button (DFCS_INACTIVE)
	// ----------

	// Set up position
	if (uState & ODS_SELECTED) { rt.left += 2; rt.top += 2; }
	
	// Initialize text drawing
	i = SetBkMode(hdcBitmap, TRANSPARENT); crTemp = SetTextColor(hdcBitmap, GetSchemeColor(hThemeObj, CSI_BTNTEXT));
	if (bNoFlicker) hfntTemp = (HFONT)SelectObject(hdcBitmap, GetCurrentObject(hDC, OBJ_FONT));

	// Draw the text
	DrawText(hdcBitmap, lpszWindowText, -1, &rt, (DT_SINGLELINE | DT_CENTER | DT_VCENTER));
	
	// Restore original
	SetBkMode(hdcBitmap, i); SetTextColor(hdcBitmap, crTemp);
	if (bNoFlicker) SelectObject(hdcBitmap, hfntTemp);

	// Postion back to original
	if (uState & ODS_SELECTED) { rt.left -= 2; rt.top -= 2; }



	// Draw frame
	// -----------

	DrawSchemeEdge(hdcBitmap, lprt, hThemeObj, ((uState & ODS_SELECTED)?(BDR_RAISEDOUTER):(EDGE_RAISED)), (BF_RECT | ((uState & ODS_SELECTED)?(BF_FLAT):( (uState & DFCS_FLAT)?(BF_FLAT):( (uState & DFCS_MONO)?(BF_MONO):(BF_SOFT) ) )) | ((bDefault)?(BF_DEFAULT):(NULL)) ));

	// Draw focus rect
	if ((lpFocusRect) && (uState & ODS_FOCUS))
	{
		// Set up rectangle
		rt.left += lpFocusRect->left; rt.right -= lpFocusRect->right;
		rt.top += lpFocusRect->top; rt.bottom -= lpFocusRect->bottom;

		// Draw frame rect, then restore
		crTemp = SetTextColor(hdcBitmap, 0);
		DrawFocusRect(hdcBitmap, &rt);
		SetTextColor(hdcBitmap, crTemp);
	}

	// Draw on actual window
	if (bNoFlicker) BitBlt(hDC, X, Y, nWidth, nHeight, hdcBitmap, 0, 0, SRCCOPY);



	// Clean up
	// ---------

	if (bNoFlicker)
	{
		// Restore original objects
		SelectObject(hdcBitmap, hbmpTemp);		// Bitmap
		
		// Delete objects
		DeleteDC(hdcBitmap);					// Delete the bitmap DC
		DeleteObject(hbmpBitmap);				// Delete the bitmap
	}


	return TRUE;
}
