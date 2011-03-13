// eColorSchemes.cpp
// Color Schemes Implementation File
// By Joe Esposito



// Color Schemes
// --------------

HESCHEME ESTDCALL CreateColorScheme (LPSCHEMECOLORBASE lpc, UINT uExtraInfoLength)
{
	LPESCHEME lpScheme;
	LPCOLORSCHEMEINFO lpsi;
	
	// Create color scheme info
	lpsi = new COLORSCHEMEINFO;
	
	lpsi->cbSize = sizeof(COLORSCHEMEINFO);
	lpsi->uUserCount = uExtraInfoLength;
	if ((lpsi->lpsc = new SCHEMECOLORSTRUCT) == NULL)
	{ delete lpsi; return NULL; } lpsi->lpsc->cbSize = sizeof(SCHEMECOLORSTRUCT);
	
	// Create scheme color mask
	if (uExtraInfoLength) {
		if ((lpsi->lpadwMask = new DWORD [uExtraInfoLength]) == NULL) {
			delete lpsi->lpsc; delete lpsi;
			return NULL;
		}
	} else
	{ lpsi->lpadwMask = NULL; }
	
	// Create the scheme
	if ((lpScheme = _CreateScheme(SCHEMES_COLORSCHEME, 0, (LPVOID)lpsi, uExtraInfoLength)) == NULL) {
		delete [uExtraInfoLength] lpsi->lpadwMask; _DestroyColorSchemeColors(lpsi); 
		delete lpsi->lpsc; delete lpsi;
		return NULL;
	} lpsi->lpScheme = lpScheme;

	// Create scheme colors
	_SetColorSchemeColors(lpsi, lpc);

	return (HESCHEME)lpScheme;
}

// Deletes scheme (and all of its local objects)
BOOL ESTDCALL DestroyColorScheme (HESCHEME hScheme)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if (!hScheme) return FALSE; if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) return FALSE;
	if (((LPESCHEME)hScheme)->uSchemeType != SCHEMES_COLORSCHEME) return FALSE;

	// Delete scheme data (colors, pens, and brushes)
	if ((lpsi = (LPCOLORSCHEMEINFO)((LPESCHEME)hScheme)->lpSchemeData) != NULL) {
		_DestroyColorSchemeColors(lpsi);
		delete lpsi->lpsc; delete lpsi;
	}

	return _DestroyScheme((LPESCHEME)hScheme);
}





// Sets only the internal colors
BOOL ESTDCALL SetSchemeColors (HETHEMEOBJ hThemeObj, LPSCHEMECOLORBASE lpc)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) return FALSE;
	return _SetColorSchemeColors(lpsi, (LPSCHEMECOLORSTRUCT)lpc);
}

// Sets the specified color
BOOL ESTDCALL SetSchemeColor (HETHEMEOBJ hThemeObj, INT nIndex, COLORREF crColor)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if (!hThemeObj) return FALSE;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetColorSchemeBaseColor((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex, 0);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) return FALSE;
	if (nIndex < 0) return _SetColorSchemeInternalColor(lpsi, nIndex, crColor);
	return _SetColorSchemeUserInfo(lpsi, nIndex, 0, (LONG)crColor);
}

// Sets the color scheme info [user color]
BOOL ESTDCALL SetColorSchemeInfo (HETHEMEOBJ hThemeObj, INT nIndex, LONG lValue)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) return FALSE;
	if (nIndex < 0) return FALSE;
	return _SetColorSchemeUserInfo(lpsi, nIndex, 0, lValue);
}

// Sets the color scheme info [user color] and, optionaly, its mask
BOOL ESTDCALL SetColorSchemeInfoEx (HETHEMEOBJ hThemeObj, INT nIndex, LONG lValue, DWORD dwMask)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) return FALSE;
	if (nIndex < 0) return FALSE;
	return _SetColorSchemeUserInfo(lpsi, nIndex, dwMask, lValue);
}

// Gets the specified color
COLORREF ESTDCALL GetSchemeColor (HETHEMEOBJ hThemeObj, INT nIndex)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if (!hThemeObj) return 0;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetColorSchemeBaseColor((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex, 0);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return _GetColorSchemeInternalColor(lpsi, nIndex, 0);
	return _GetColorSchemeUserInfo(lpsi, nIndex, CSM_IGNORE, 0);
}

// Gets the specified color (with flags)
COLORREF ESTDCALL GetSchemeColorEx (HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwFlags)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if (!hThemeObj) return 0;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetColorSchemeBaseColor((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex, dwFlags);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return _GetColorSchemeInternalColor(lpsi, nIndex, dwFlags);
	return _GetColorSchemeUserInfo(lpsi, nIndex, CSM_IGNORE, dwFlags);
}

// Gets the color scheme info [user color]
LONG ESTDCALL GetColorSchemeInfo (HETHEMEOBJ hThemeObj, INT nIndex)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return FALSE;
	return _GetColorSchemeUserInfo(lpsi, nIndex, CSM_IGNORE, 0);
}

// Gets the color scheme info [user color] (with flags)
LONG ESTDCALL GetColorSchemeInfoEx (HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask, DWORD dwFlags)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return FALSE;
	return _GetColorSchemeUserInfo(lpsi, nIndex, dwQueryMask, dwFlags);
}

// Returns the background brush handle
HBRUSH ESTDCALL GetSchemeBkBrush (HETHEMEOBJ hThemeObj)
{
	LPSCHEMECOLORSTRUCT lpcs;

	if (!hThemeObj) return (HBRUSH)(COLOR_BTNFACE+1);
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) {  if (!((LPSCHEMECOLORSTRUCT)hThemeObj)->hbrBackground) return (HBRUSH)(COLOR_BTNFACE+1);  return (HBRUSH)_GetSchemeColorObj((LPSCHEMECOLORSTRUCT)hThemeObj, CSI_BACKGROUND, CSM_IGNORE);  }
	if ((lpcs = _GetColorObject((LPETHEMEOBJ)hThemeObj)) == NULL) return (HBRUSH)(COLOR_BTNFACE+1);
	if (!lpcs->hbrBackground) return (HBRUSH)(COLOR_BTNFACE+1);  return lpcs->hbrBackground;
}

// Sets a color's object mask
BOOL ESTDCALL SetColorSchemeMask (HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwMask)
{
	LPCOLORSCHEMEINFO lpsi;
	
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return FALSE;
	return _SetColorSchemeUserMask(lpsi, nIndex, dwMask);
}

// Returns a color's object mask
DWORD ESTDCALL GetColorSchemeMask (HETHEMEOBJ hThemeObj, INT nIndex)
{
	LPCOLORSCHEMEINFO lpsi;

	if (!hThemeObj) return 0;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetColorSchemeMask(nIndex);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) return _GetColorSchemeMask(nIndex);
	return _GetColorSchemeUserMask(lpsi, nIndex);
}


// Returns the color's GDI object
HGDIOBJ ESTDCALL GetSchemeColorObj (HETHEMEOBJ hThemeObj, INT nIndex)
{
	LPCOLORSCHEMEINFO lpsi;

	if (!hThemeObj) return NULL;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetSchemeColorObj((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex, CSM_IGNORE);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) { if (!lpsi->lpsc) return NULL;  return _GetSchemeColorObj(lpsi->lpsc, nIndex, CSM_IGNORE); }
	return _GetSchemeUserColorObj(lpsi, nIndex, CSM_IGNORE);
}
// Returns the color's GDI object (according to its mask)
HGDIOBJ ESTDCALL GetSchemeColorObjEx (HETHEMEOBJ hThemeObj, INT nIndex, DWORD dwQueryMask)
{
	LPCOLORSCHEMEINFO lpsi;

	if (!hThemeObj) return NULL;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _GetSchemeColorObj((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex, dwQueryMask);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) { if (!lpsi->lpsc) return NULL;  return _GetSchemeColorObj(lpsi->lpsc, nIndex, dwQueryMask); }
	return _GetSchemeUserColorObj(lpsi, nIndex, dwQueryMask);
}



// Returns a new color, with its color percent
COLORREF ESTDCALL GetSchemeColorPercent (COLORREF crColor, INT iPercent)
{ return GETCUSTOMSCHEMECOLOR(crColor, iPercent); }



// Deletes a color object
BOOL ESTDCALL DeleteSchemeColor (HETHEMEOBJ hThemeObj, INT nIndex)
{
	LPCOLORSCHEMEINFO lpsi;

	if (!hThemeObj) return FALSE;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _DeleteSchemeColor((LPSCHEMECOLORSTRUCT)hThemeObj, nIndex);
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	if (nIndex < 0) { if (!lpsi->lpsc) return FALSE;  return _DeleteSchemeColor(lpsi->lpsc, nIndex); }
	return _DeleteSchemeUserColor(lpsi, nIndex);
}

// Deletes all internal color objects
BOOL ESTDCALL DeleteSchemeColors (HETHEMEOBJ hThemeObj)
{
	LPSCHEMECOLORSTRUCT lpcs;

	if (!hThemeObj) return FALSE;
	if (((LPSCHEMECOLORBASE)hThemeObj)->cbSize == sizeof(SCHEMECOLORSTRUCT)) return _DeleteColorSchemeColors((LPSCHEMECOLORSTRUCT)hThemeObj);
	if ((lpcs = _GetColorObject((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	return _DeleteColorSchemeColors(lpcs);
}

// Deletes all user color objects
BOOL ESTDCALL DeleteSchemeUserColors (HETHEMEOBJ hThemeObj)
{
	LPCOLORSCHEMEINFO lpsi;

	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) { SetLastError(126); return 0; }
	return _DeleteColorSchemeUserColors(lpsi);
}



// Copies a color scheme
ECALL HESCHEME ESTDCALL CopyColorScheme (HETHEMEOBJ hThemeObj)
{
	LPCOLORSCHEMEINFO lpsi;
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObj)) == NULL) return NULL;
	return (HESCHEME)_CopyColorScheme(lpsi);
}
// Copies internal colors
ECALL BOOL ESTDCALL CopySchemeColors (HETHEMEOBJ hThemeObjDest, HETHEMEOBJ hThemeObjSource)
{
	LPCOLORSCHEMEINFO lpsi, lpsi2;
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObjDest)) == NULL) return NULL;
	if ((lpsi2 = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObjSource)) == NULL) return NULL;
	return _CopySchemeColors(lpsi, lpsi2);
}
// Copies user colors
ECALL BOOL ESTDCALL CopySchemeUserColors (HETHEMEOBJ hThemeObjDest, HETHEMEOBJ hThemeObjSource)
{
	LPCOLORSCHEMEINFO lpsi, lpsi2;
	if ((lpsi = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObjDest)) == NULL) return NULL;
	if ((lpsi2 = _GetSchemeColorInfoStruct((LPETHEMEOBJ)hThemeObjSource)) == NULL) return NULL;
	return _CopySchemeUserColors(lpsi, lpsi2);
}
