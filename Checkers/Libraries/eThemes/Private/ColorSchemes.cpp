// ColorSchemes.cpp
// Color Schemes Internal Implementation File
// By Joe Esposito


// When setting a color from a color object check if its a:
// - Theme object (get the color scheme object)
// - Color scheme object
// - CalcColor object
// - Color object

// NOTE: In these functions: lpsi has already been checked (and IS a local color info ocject)



// Local Functions
// ----------------

LOCAL VOID _GetColorSchemePercentBits ( LPDWORD lpColor, int nSize, int nPos, COLORREF crStart, COLORREF crEnd );



// Internal Functions
// -------------------

// Sets the internal colors, all at once
LOCAL BOOL _SetColorSchemeColors (LPCOLORSCHEMEINFO lpsi, LPSCHEMECOLORBASE lpcSource)
{
	union { LPCALCSCHEMECOLORS lpcsc; LPSCHEMECOLORSTRUCT lpcTemp; };
	LPSCHEMECOLORSTRUCT lpcDest;
	SCHEMECOLORSTRUCT cs;

	
	if (((LPSCHEMECOLORBASE)lpsi)->cbSize == sizeof(SCHEMECOLORSTRUCT)) lpcDest = (LPSCHEMECOLORSTRUCT)lpsi; else lpcDest = lpsi->lpsc;
	if (!lpcDest) return FALSE;

	// If setting color object to nothing
	if (lpcSource == NULL) {
		if (((LPSCHEMECOLORBASE)lpsi)->cbSize == sizeof(SCHEMECOLORSTRUCT)) _DeleteColorSchemeColors((LPSCHEMECOLORSTRUCT)lpsi); else _DestroyColorSchemeColors(lpsi);
		return FALSE;
	}

	if (lpcSource->cbSize == sizeof(CALCSCHEMECOLORS))		// Data is CALCSCHEMECOLORS
	{
		lpcsc = (LPCALCSCHEMECOLORS)lpcSource;
		ZeroMemory(&cs, sizeof(SCHEMECOLORSTRUCT));

		// Copy old colors
		if ((lpcDest) && (lpcDest->cbSize == sizeof(SCHEMECOLORSTRUCT))) memcpy(&cs, lpcDest, sizeof(SCHEMECOLORSTRUCT));
		cs.cbSize = sizeof(SCHEMECOLORSTRUCT);
		
		// Check percentages
		if (lpcsc->iHighlightPercent != CC_IGNORE) cs.hpenHighlight = CreatePen(PS_SOLID, 0, GETCUSTOMSCHEMECOLOR(lpcsc->crHighlight, lpcsc->iHighlightPercent));
		if (lpcsc->iLightPercent != CC_IGNORE) cs.hpenLight = CreatePen(PS_SOLID, 0,  GETCUSTOMSCHEMECOLOR(lpcsc->crLight, lpcsc->iLightPercent));
		if (lpcsc->iShadowPercent != CC_IGNORE) cs.hpenShadow = CreatePen(PS_SOLID, 0, GETCUSTOMSCHEMECOLOR(lpcsc->crShadow, lpcsc->iShadowPercent));
		if (lpcsc->iDkShadowPercent != CC_IGNORE) cs.hpenDkShadow = CreatePen(PS_SOLID, 0, GETCUSTOMSCHEMECOLOR(lpcsc->crDkShadow, lpcsc->iDkShadowPercent));
		if (lpcsc->iFacePercent != CC_IGNORE) cs.hbrBackground = CreateSolidBrush(GETCUSTOMSCHEMECOLOR(lpcsc->crFace, lpcsc->iFacePercent));
		if (lpcsc->iDefaultBorderPercent != CC_IGNORE) cs.hpenDefaultBorder = CreatePen(PS_SOLID, 0, GETCUSTOMSCHEMECOLOR(lpcsc->crDefaultBorder, lpcsc->iDefaultBorderPercent));
		if (lpcsc->iTextColorPercent != CC_IGNORE) cs.crTextColor = GETCUSTOMSCHEMECOLOR(lpcsc->crTextColor, lpcsc->iTextColorPercent);
		if (lpcsc->iDisabledColorPercent != CC_IGNORE) cs.crDisabledColor = GETCUSTOMSCHEMECOLOR(lpcsc->crDisabledColor, lpcsc->iDisabledColorPercent);
		if (lpcsc->iGhostedColorPercent != CC_IGNORE) cs.crGhostedColor = GETCUSTOMSCHEMECOLOR(lpcsc->crGhostedColor, lpcsc->iGhostedColorPercent);

		// Set the colors (indirectly)
		if (((LPSCHEMECOLORBASE)lpsi)->cbSize == sizeof(SCHEMECOLORSTRUCT)) _DeleteColorSchemeColors((LPSCHEMECOLORSTRUCT)lpsi); else _DestroyColorSchemeColors(lpsi);
		memcpy(lpcDest, &cs, sizeof(SCHEMECOLORSTRUCT));
	}
	else if (lpcSource->cbSize == sizeof(SCHEMECOLORSTRUCT))		// Data is SCHEMECOLORSTRUCT
	{ return _CopyColorSchemeColors(lpcDest, (LPSCHEMECOLORSTRUCT)lpcSource); }
	else if ((lpcTemp = _GetColorObject(lpcSource)) != NULL)
	{ return _CopyColorSchemeColors(lpcDest, lpcTemp); }

	return FALSE;
}



// Gets a single internal color
LOCAL BOOL _SetColorSchemeBaseColor (LPSCHEMECOLORSTRUCT lpc, INT nIndex, COLORREF crColor)
{
	if (lpc->cbSize != sizeof(SCHEMECOLORSTRUCT)) return FALSE;

	switch (nIndex) {
	case CSI_HIGHLIGHT: if (lpc->hpenHighlight) DeleteObject(lpc->hpenHighlight);  lpc->hpenHighlight = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_LIGHT: if (lpc->hpenLight) DeleteObject(lpc->hpenLight);  lpc->hpenLight = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_SHADOW: if (lpc->hpenShadow) DeleteObject(lpc->hpenShadow);  lpc->hpenShadow = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_DKSHADOW: if (lpc->hpenDkShadow) DeleteObject(lpc->hpenDkShadow);  lpc->hpenDkShadow = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_BACKGROUND: if (lpc->hbrBackground) DeleteObject(lpc->hbrBackground);  lpc->hbrBackground = CreateSolidBrush(crColor); return TRUE;
	case CSI_BORDER: if (lpc->hpenDefaultBorder) DeleteObject(lpc->hpenDefaultBorder);  lpc->hpenDefaultBorder = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_BTNTEXT: lpc->crTextColor = crColor; return TRUE;
	case CSI_DISABLEDTEXT: lpc->crDisabledColor = crColor; return TRUE;
	case CSI_GHOSTEDTEXT: lpc->crGhostedColor = crColor; return TRUE;
	}

	return FALSE;
}
// Sets a single internal color
LOCAL BOOL _SetColorSchemeInternalColor (LPCOLORSCHEMEINFO lpsi, INT nIndex, COLORREF crColor)
{
	if (!lpsi->lpsc) return FALSE;
	if (lpsi->lpsc->cbSize != sizeof(SCHEMECOLORSTRUCT)) return FALSE;

	switch (nIndex) {
	case CSI_HIGHLIGHT: if (lpsi->lpsc->hpenHighlight) DeleteObject(lpsi->lpsc->hpenHighlight);  lpsi->lpsc->hpenHighlight = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_LIGHT: if (lpsi->lpsc->hpenLight) DeleteObject(lpsi->lpsc->hpenLight);  lpsi->lpsc->hpenLight = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_SHADOW: if (lpsi->lpsc->hpenShadow) DeleteObject(lpsi->lpsc->hpenShadow);  lpsi->lpsc->hpenShadow = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_DKSHADOW: if (lpsi->lpsc->hpenDkShadow) DeleteObject(lpsi->lpsc->hpenDkShadow);  lpsi->lpsc->hpenDkShadow = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_BACKGROUND: if (lpsi->lpsc->hbrBackground) DeleteObject(lpsi->lpsc->hbrBackground);  lpsi->lpsc->hbrBackground = CreateSolidBrush(crColor); return TRUE;
	case CSI_BORDER: if (lpsi->lpsc->hpenDefaultBorder) DeleteObject(lpsi->lpsc->hpenDefaultBorder);  lpsi->lpsc->hpenDefaultBorder = CreatePen(PS_SOLID, 0, crColor); return TRUE;
	case CSI_BTNTEXT: lpsi->lpsc->crTextColor = crColor; return TRUE;
	case CSI_DISABLEDTEXT: lpsi->lpsc->crDisabledColor = crColor; return TRUE;
	case CSI_GHOSTEDTEXT: lpsi->lpsc->crGhostedColor = crColor; return TRUE;
	}

	return FALSE;
}



// Gets a single internal color
LOCAL COLORREF _GetColorSchemeBaseColor (LPSCHEMECOLORSTRUCT lpc, INT nIndex, DWORD dwFlags)
{
	switch (nIndex) {
	case CSI_HIGHLIGHT: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetPenColor(lpc->hpenHighlight);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DHILIGHT); return 0;
	case CSI_LIGHT: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetPenColor(lpc->hpenLight);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DLIGHT); return 0;
	case CSI_SHADOW: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetPenColor(lpc->hpenShadow);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DSHADOW); return 0;
	case CSI_DKSHADOW: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetPenColor(lpc->hpenDkShadow);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DDKSHADOW); return 0;
	case CSI_BACKGROUND: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetBrushColor(lpc->hbrBackground);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNFACE); return 0;
	case CSI_BORDER: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return GetPenColor(lpc->hpenDefaultBorder);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DDKSHADOW); return 0;
	case CSI_BTNTEXT: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return lpc->crTextColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNTEXT); return 0;
	case CSI_DISABLEDTEXT: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return lpc->crDisabledColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNSHADOW); return 0;
	case CSI_GHOSTEDTEXT: if (lpc->cbSize == sizeof(SCHEMECOLORSTRUCT)) return lpc->crGhostedColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNHILIGHT); return 0;
	} if (dwFlags & CSF_MUSTEXIST) SetLastError(13); return 0;
}
// Gets a single internal color
LOCAL COLORREF _GetColorSchemeInternalColor (LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwFlags)
{
	if (nIndex >= 0) { if (dwFlags & CSF_MUSTEXIST) SetLastError(13);  return 0; }

	switch (nIndex) {
	case CSI_HIGHLIGHT: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetPenColor(lpsi->lpsc->hpenHighlight);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DHILIGHT); return 0;
	case CSI_LIGHT: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetPenColor(lpsi->lpsc->hpenLight);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DLIGHT); return 0;
	case CSI_SHADOW: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetPenColor(lpsi->lpsc->hpenShadow);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DSHADOW); return 0;
	case CSI_DKSHADOW: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetPenColor(lpsi->lpsc->hpenDkShadow);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DDKSHADOW); return 0;
	case CSI_BACKGROUND: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetBrushColor(lpsi->lpsc->hbrBackground);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNFACE); return 0;
	case CSI_BORDER: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return GetPenColor(lpsi->lpsc->hpenDefaultBorder);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_3DDKSHADOW); return 0;
	case CSI_BTNTEXT: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return lpsi->lpsc->crTextColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNTEXT); return 0;
	case CSI_DISABLEDTEXT: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return lpsi->lpsc->crDisabledColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNSHADOW); return 0;
	case CSI_GHOSTEDTEXT: if ((lpsi->lpsc) && (lpsi->lpsc->cbSize == sizeof(SCHEMECOLORSTRUCT))) return lpsi->lpsc->crGhostedColor;  if (dwFlags & CSF_MUSTEXIST) SetLastError(13); if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_BTNHILIGHT); return 0;
	} if (dwFlags & CSF_MUSTEXIST) SetLastError(13); return 0;
}



// Sets a single user color [info]
LOCAL BOOL _SetColorSchemeUserInfo (LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask, COLORREF crColor)
{
	DWORD m_dwMask;
	if (nIndex > lpsi->uUserCount) return FALSE;

	// Test mask
	m_dwMask = lpsi->lpadwMask[nIndex];
	if (dwMask != CSM_IGNORE) { if ((m_dwMask != CSM_IGNORE) && (dwMask != m_dwMask)) return FALSE;  m_dwMask = dwMask; }

	_DeleteSchemeUserColor(lpsi, nIndex);
	lpsi->lpadwMask[nIndex] = m_dwMask;
	
	switch (m_dwMask) {
	case CSM_LONG: lpsi->lpScheme->lpExtraData[nIndex] = (LONG)crColor; return TRUE;
	case CSM_COLORREF: lpsi->lpScheme->lpExtraData[nIndex] = (LONG)crColor; return TRUE;
	case CSM_HBRUSH: if (lpsi->lpScheme->lpExtraData[nIndex]) DeleteObject((HBRUSH)lpsi->lpScheme->lpExtraData[nIndex]);  lpsi->lpScheme->lpExtraData[nIndex] = (LONG)CreateSolidBrush(crColor); return TRUE;
	case CSM_HPEN: if (lpsi->lpScheme->lpExtraData[nIndex]) DeleteObject((HPEN)lpsi->lpScheme->lpExtraData[nIndex]);  lpsi->lpScheme->lpExtraData[nIndex] = (LONG)CreatePen(PS_SOLID, 0, crColor); return TRUE;
	}

	return FALSE;
}
// Gets a single user color [info]
LOCAL LONG _GetColorSchemeUserInfo (LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask, DWORD dwFlags)
{
	if (nIndex > lpsi->uUserCount) { if (dwFlags & CSF_MUSTEXIST) SetLastError(13); return FALSE; }
	
	// Test mask
	if (dwMask != CSM_IGNORE)
	{
		if (dwMask != lpsi->lpadwMask[nIndex])
		{ if (dwFlags & CSF_MUSTEXIST) SetLastError(13);  return FALSE; }
	}

	switch (lpsi->lpadwMask[nIndex]) {
	case CSM_LONG: return (COLORREF)lpsi->lpScheme->lpExtraData[nIndex];
	case CSM_COLORREF: return (COLORREF)lpsi->lpScheme->lpExtraData[nIndex];
	case CSM_HBRUSH: if (lpsi->lpScheme->lpExtraData[nIndex]) return GetBrushColor((HBRUSH)lpsi->lpScheme->lpExtraData[nIndex]);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13);  if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_WINDOW);  return 0;
	case CSM_HPEN: if (lpsi->lpScheme->lpExtraData[nIndex]) return GetPenColor((HPEN)lpsi->lpScheme->lpExtraData[nIndex]);  if (dwFlags & CSF_MUSTEXIST) SetLastError(13);  if (!(dwFlags & CSF_NOSYSCOLOR)) return GetSysColor(COLOR_WINDOWTEXT);  return 0;
	}

	return FALSE;
}



// Sets the user color's object mask
LOCAL BOOL _SetColorSchemeUserMask (LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask)
{
	if (nIndex >= lpsi->uUserCount) return FALSE;
	if (dwMask == CSM_IGNORE) return FALSE;
	lpsi->lpadwMask[nIndex] = dwMask; return TRUE;
}



// Returns the internal color's object mask
LOCAL DWORD _GetColorSchemeMask (INT nIndex)
{
	switch (nIndex) {
	case CSI_HIGHLIGHT: return CSM_HPEN;
	case CSI_LIGHT: return CSM_HPEN;
	case CSI_SHADOW: return CSM_HPEN;
	case CSI_DKSHADOW: return CSM_HPEN;
	case CSI_BACKGROUND: return CSM_HBRUSH;
	case CSI_BORDER: return CSM_HPEN;
	case CSI_BTNTEXT: return CSM_COLORREF;
	case CSI_DISABLEDTEXT: return CSM_COLORREF;
	case CSI_GHOSTEDTEXT: return CSM_COLORREF;
	} return CSM_IGNORE;
}
// Returns the user color's object mask
LOCAL DWORD _GetColorSchemeUserMask (LPCOLORSCHEMEINFO lpsi, INT nIndex)
{
	if (nIndex >= lpsi->uUserCount) return FALSE;
	return lpsi->lpadwMask[nIndex];
}



// Returns pointer to the color info associated with the specified object
LOCAL LPCOLORSCHEMEINFO _GetSchemeColorInfoStruct (LPVOID lpv)
{
	LPESCHEME lpScheme;

	if (!lpv) return NULL;


	if ((lpScheme = (LPESCHEME)GetCurrentScheme((HETHEMEOBJ)lpv, SCHEMES_COLORSCHEME)) == NULL) return NULL;
	if (lpScheme->uSchemeType != SCHEMES_COLORSCHEME) return NULL;
	if ( !((LPCOLORSCHEMEINFO)lpScheme->lpSchemeData) ) return NULL;

	return ((LPCOLORSCHEMEINFO)lpScheme->lpSchemeData);
}

// Returns pointer to the color struct associated with the specified object
LOCAL LPSCHEMECOLORSTRUCT _GetColorObject (LPVOID lpv)
{
	LPCOLORSCHEMEINFO lpci;
	
	if (((LPSCHEMECOLORBASE)lpv)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return (LPSCHEMECOLORSTRUCT)lpv;
	if ((lpci = _GetSchemeColorInfoStruct(lpv)) == NULL) return NULL;
	if (lpci->cbSize != sizeof(COLORSCHEMEINFO)) return NULL;
	if (!lpci->lpsc) return NULL;
	if (lpci->lpsc->cbSize != sizeof(SCHEMECOLORSTRUCT)) return NULL;
	
	return lpci->lpsc;
}


// Returns the internal color's GDI object
LOCAL HGDIOBJ _GetSchemeColorObj (LPSCHEMECOLORSTRUCT lpc, INT nIndex, DWORD dwMask)
{
	if ((dwMask != CSM_IGNORE) && (dwMask != _GetColorSchemeMask(nIndex))) return NULL;

	switch (nIndex) {
	case CSI_HIGHLIGHT: return (HGDIOBJ)lpc->hpenHighlight;
	case CSI_LIGHT: return (HGDIOBJ)lpc->hpenLight;
	case CSI_SHADOW: return (HGDIOBJ)lpc->hpenShadow;
	case CSI_DKSHADOW: return (HGDIOBJ)lpc->hpenDkShadow;
	case CSI_BACKGROUND: return (HGDIOBJ)lpc->hbrBackground;
	case CSI_BORDER: return (HGDIOBJ)lpc->hpenDefaultBorder;
	case CSI_BTNTEXT: return (HGDIOBJ)lpc->crTextColor;
	case CSI_DISABLEDTEXT: return (HGDIOBJ)lpc->crDisabledColor;
	case CSI_GHOSTEDTEXT: return (HGDIOBJ)lpc->crGhostedColor;
	} return NULL;
}
// Returns the user color's GDI object
LOCAL HGDIOBJ _GetSchemeUserColorObj (LPCOLORSCHEMEINFO lpsi, INT nIndex, DWORD dwMask)
{
	if (nIndex >= lpsi->uUserCount) return NULL;
	if ((dwMask != CSM_IGNORE) && (dwMask != lpsi->lpadwMask[nIndex])) return NULL;

	switch (lpsi->lpadwMask[nIndex]) {
	case CSM_LONG: case CSM_COLORREF: return (HGDIOBJ)lpsi->lpScheme->lpExtraData[nIndex];
	case CSM_HBRUSH: case CSM_HPEN: return (HGDIOBJ)lpsi->lpScheme->lpExtraData[nIndex];
	} return NULL;
}


// Returns a color, in between 2 colors
LOCAL COLORREF _GetColorSchemePercent (INT iMax, INT nValue, COLORREF crStart, COLORREF crEnd)
{
	COLORREF crResult;

	if ((iMax <= 0) || (iMax > 0xFFFF)) return 0;
	if ((nValue < 0) || (nValue >= iMax)) return 0;

	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }

	_GetColorSchemePercentBits ((LPDWORD)&crResult, iMax, nValue, crStart, crEnd);

	return crResult;
}


// Deletes a single internal color object
LOCAL BOOL _DeleteSchemeColor (LPSCHEMECOLORSTRUCT lpc, INT nIndex)
{
	switch (nIndex) {
	case CSI_HIGHLIGHT: DeleteObject(lpc->hpenHighlight); lpc->hpenHighlight = 0; return TRUE;
	case CSI_LIGHT: DeleteObject(lpc->hpenLight); lpc->hpenLight = 0; return TRUE;
	case CSI_SHADOW: DeleteObject(lpc->hpenShadow); lpc->hpenShadow = 0; return TRUE;
	case CSI_DKSHADOW: DeleteObject(lpc->hpenDkShadow); lpc->hpenDkShadow = 0; return TRUE;
	case CSI_BACKGROUND: DeleteObject(lpc->hbrBackground); lpc->hbrBackground = 0; return TRUE;
	case CSI_BORDER: DeleteObject(lpc->hpenDefaultBorder); lpc->hpenDefaultBorder = 0; return TRUE;
	case CSI_BTNTEXT: lpc->crTextColor = 0; return TRUE;
	case CSI_DISABLEDTEXT: lpc->crDisabledColor = 0; return TRUE;
	case CSI_GHOSTEDTEXT: lpc->crGhostedColor = 0; return TRUE;
	} return FALSE;
}
// Deletes a single user color object
LOCAL BOOL _DeleteSchemeUserColor (LPCOLORSCHEMEINFO lpsi, INT nIndex)
{
	if (nIndex >= lpsi->uUserCount) return FALSE;
	switch (lpsi->lpadwMask[nIndex]) {
	case CSM_LONG: case CSM_COLORREF: lpsi->lpadwMask[nIndex] = CSM_IGNORE; lpsi->lpScheme->lpExtraData[nIndex] = 0; break;
	case CSM_HBRUSH: if (lpsi->lpScheme->lpExtraData[nIndex]) DeleteObject((HBRUSH)lpsi->lpScheme->lpExtraData[nIndex]); lpsi->lpadwMask[nIndex] = CSM_IGNORE; lpsi->lpScheme->lpExtraData[nIndex] = 0; break;
	case CSM_HPEN: if (lpsi->lpScheme->lpExtraData[nIndex]) DeleteObject((HPEN)lpsi->lpScheme->lpExtraData[nIndex]); lpsi->lpadwMask[nIndex] = CSM_IGNORE; lpsi->lpScheme->lpExtraData[nIndex] = 0; break;
	default: lpsi->lpadwMask[nIndex] = CSM_IGNORE; lpsi->lpScheme->lpExtraData[nIndex] = 0; return FALSE;
	} return TRUE;
}


// Destroys all internal color objects
LOCAL BOOL _DeleteColorSchemeColors (LPSCHEMECOLORSTRUCT lpc)
{
	// Delete internal color objects
	if (lpc)
	{
		if (lpc->cbSize != sizeof(SCHEMECOLORSTRUCT)) return FALSE;

		DeleteObject(lpc->hpenLight); lpc->hpenLight = NULL; DeleteObject(lpc->hpenHighlight); lpc->hpenHighlight = NULL;
		DeleteObject(lpc->hpenShadow); lpc->hpenShadow = NULL; DeleteObject(lpc->hpenDkShadow); lpc->hpenDkShadow = NULL;
		DeleteObject(lpc->hbrBackground); lpc->hbrBackground = NULL;
		DeleteObject(lpc->hpenDefaultBorder); lpc->hpenDefaultBorder = NULL;
		lpc->crTextColor = lpc->crDisabledColor = lpc->crGhostedColor = 0;
		
		return TRUE;
	}

	return FALSE;
}
// Destroys all user color objects
LOCAL BOOL _DeleteColorSchemeUserColors (LPCOLORSCHEMEINFO lpsi)
{
	// Delete user color objects
	if (lpsi->lpsc)
	{
		for (int i = 0; i < lpsi->uUserCount; i++)
		{ _DeleteSchemeUserColor(lpsi, i); }
		
		return TRUE;
	}

	return FALSE;
}
// Destroys all color objects
LOCAL BOOL _DestroyColorSchemeColors (LPCOLORSCHEMEINFO lpsi)
{
	if (lpsi->lpsc) _DeleteColorSchemeColors(lpsi->lpsc);
	_DeleteColorSchemeUserColors(lpsi);
	
	return TRUE;
}



// Copies a color scheme
LOCAL LPESCHEME _CopyColorScheme (LPCOLORSCHEMEINFO lpsi)
{ return (LPESCHEME)CreateColorScheme((LPSCHEMECOLORBASE)lpsi, lpsi->uUserCount); }

// Copies internal colors from a color struct
LOCAL BOOL _CopyColorSchemeColors (LPSCHEMECOLORSTRUCT lpcDest, LPSCHEMECOLORSTRUCT lpcSource)
{
	int i, max = -((int)(sizeof(SCHEMECOLORSTRUCT) / sizeof(LPVOID)));
	
	for (i = -1; i >= max; i--)
	{ _SetColorSchemeBaseColor(lpcDest, i, _GetColorSchemeBaseColor(lpcSource, i, 0)); }

	return TRUE;
}

// Copies internal colors
LOCAL BOOL _CopySchemeColors (LPCOLORSCHEMEINFO lpDest, LPCOLORSCHEMEINFO lpSource)
{
	int i, max = -((int)(sizeof(SCHEMECOLORSTRUCT) / sizeof(LPVOID)));
	
	for (i = -1; i >= max; i--)
	{ _SetColorSchemeInternalColor(lpDest, i, _GetColorSchemeInternalColor(lpSource, i, 0)); }
	return TRUE;
}

// Copies user colors
LOCAL BOOL _CopySchemeUserColors (LPCOLORSCHEMEINFO lpDest, LPCOLORSCHEMEINFO lpSource)
{
	int max = ((lpDest->uUserCount < lpSource->uUserCount)?(lpDest->uUserCount):(lpSource->uUserCount));
	int i;

	for (i = 0; i < max; i++)
	{ _SetColorSchemeUserInfo(lpDest, i, lpDest->lpadwMask[i], _GetColorSchemeUserInfo(lpSource, i, CSM_IGNORE, 0)); }

	return TRUE;
}




LOCAL VOID _GetColorSchemePercentBits (LPDWORD lpColor, int nSize, int nPos, COLORREF crStart, COLORREF crEnd)
{
	__asm {

		PUSH ES					; Store extra segment
		PUSH EDI				; Store data offset


		; Step 1: gradient the left side
		; -------------------------------

		; Set up basic registers
		mov  ecx,nSize			; Get height
		AND  ecx,0FFFFh			; Use only first word
		mov  esi,lpColor		; Get bits pointer
		inc  esi				; Point to reversed beginning byte
		inc  esi


		; Store gradient settings for RGB values		
		xor  eax,eax			; Zero AX
		PUSH ax					; AH = 0h  -  No more settings
		
		mov  ax,0FFFFh			; AH = 0FFFFh

		; Store gradient
		mov  ebx,crStart		; Get starting color value
		mov  edx,crEnd			; Get end color value

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH ax					; AX = FFFFh  -  Setting OK


GB_GRADIENT_LOOP:

		; Check gradient settings
		POP  ax					; Get settings header
		TEST ax,ax				; Is setting OK?
		jz   GB_END				;  ..no more settings

		; Get gradient settings
		POP  bx					; Get setting: starting color value
		POP  dx					; Get setting: ending color value

		xor  eax,eax			; Clear EAX
		
		; Decide which loop to enter
		cmp  bl,dl				; Compare
		je   GB_GRADIENT_EQUAL	; Jump if (bl == dl)
		ja   GB_GRADIENT_ABOVE	; Jump if (bl > dl)


		; Set up loop
		mov  al,dl				; AL holds ending color
		sub  al,bl				; Get difference (al - bl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder: original numerator (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator

		
		
		; Get the color
		mov  edi,eax			; Store AX (denominator) for a moment
		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index
		AND  eax,0FFFFh			; Use only first word

		mul  bh					; Get actual position by the step value ()
		add  bl,al				; Add with starting color to get the desired color

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK1	; Jump if no fraction check is required

		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index (ax is now [will be] the numerator)

		mul  dx					; Get total increase numerator (original * desired position)
		add  ax,dx				; Increase numerator (desired numerator + current [original])

		cmp  ax,di				; Compare numerator to denominator
		jb   GB_GRADIENT_OK1	; Jump if (ax < di) -- not a whole number
		
		div  di					; Get increase value (numerator / denominator)
		add  bl,al				; Add numerator to color value

		GB_GRADIENT_OK1:
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)
		jmp GB_GRADIENT_LOOP	; Do next color value


GB_GRADIENT_LOOP2:

		; Get the color
		mov  edi,eax			; Store AX (denominator) for a moment
		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index
		AND  eax,0FFFFh			; Use only first word

		mul  bh					; Get actual position by the step value ()
		sub  bl,al				; Add with starting color to get the desired color

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK2	; Jump if no fraction check is required

		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index (ax is now [will be] the numerator)

		mul  dx					; Get total increase numerator (original * desired position)
		add  ax,dx				; Increase numerator (desired numerator + current [original])

		cmp  ax,di				; Compare numerator to denominator
		jb   GB_GRADIENT_OK2	; Jump if (ax < di) -- not a whole number
		
		div  di					; Get increase value (numerator / denominator)
		sub  bl,al				; Add numerator to color value

		GB_GRADIENT_OK2:
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)
		jmp GB_GRADIENT_LOOP	; Do next color value


GB_GRADIENT_ABOVE:

		; Set up loop
		mov  al,bl				; AL holds starting color
		sub  al,dl				; Get difference (al - dl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder: original numerator (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator

		jmp GB_GRADIENT_LOOP2	; Begin loop


GB_GRADIENT_EQUAL:				; Special case: starting and ending colors are equal		

		; Update color value
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)

		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again

GB_END:

		POP  EDI				; Restore data offset
		POP  ES					; Restore extra segment

	}
}
