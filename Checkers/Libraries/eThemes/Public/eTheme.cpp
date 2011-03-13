// eTheme.h
// eTheme Implementation File
// By Joe Esposito



// Public Functions
// -----------------

// Creates a theme
HETHEME ESTDCALL CreateTheme (UINT nExtraSchemes)
{
	LPETHEME lpTheme;

	if ((lpTheme = new ETHEME) == NULL) return NULL;
	
	lpTheme->uType = THEMES_THEME;
	lpTheme->nExtraSchemes = nExtraSchemes;
	
	if ((lpTheme->lpaSchemes = new LPESCHEME [(THEME_INTERNAL_NUMSCHEMES)]) == NULL) {
		delete lpTheme;
		return NULL;
	}

	if ((lpTheme->lpaUserSchemes = new LPESCHEME [(nExtraSchemes)]) == NULL) {
		delete lpTheme->lpaSchemes; delete lpTheme;
		return NULL;
	}

	ZeroMemory(lpTheme->lpaSchemes, (THEME_INTERNAL_SCHEMESSIZE));
	ZeroMemory(lpTheme->lpaUserSchemes, (nExtraSchemes * sizeof(LPESCHEME)));

	return (HETHEME)lpTheme;
}

// Destroys the theme (not any schemes)
BOOL ESTDCALL DestroyTheme (HETHEME hTheme)
{
	if (!hTheme) return FALSE; if (((LPETHEME)hTheme)->uType != THEMES_THEME) { SetLastError(126); return FALSE; }

	((LPETHEME)hTheme)->uType = 0;
	if (((LPETHEME)hTheme)->lpaUserSchemes) delete [(((LPETHEME)hTheme)->nExtraSchemes)] ((LPETHEME)hTheme)->lpaUserSchemes;
	if (((LPETHEME)hTheme)->lpaSchemes) delete [(THEME_INTERNAL_NUMSCHEMES)] ((LPETHEME)hTheme)->lpaSchemes;

	delete ((LPETHEME)hTheme);

	return TRUE;
}


HESCHEME ESTDCALL SelectScheme (HETHEME hTheme, HESCHEME hScheme)
{
	LPESCHEME lpSchemeTemp;
	if (!hTheme) { SetLastError(126); return NULL; }; if (((LPETHEME)hTheme)->uType != THEMES_THEME) { SetLastError(126); return NULL; }
	if (!hScheme) { SetLastError(126); return NULL; }


	if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) { SetLastError(126); return NULL; }
	switch (((LPESCHEME)hScheme)->uSchemeType) {		// Compare id's
		case SCHEMES_COLORSCHEME:
			
			// Set the new color scheme, and return the previous
			lpSchemeTemp = ((LPETHEME)hTheme)->lpaSchemes[GS_COLORSCHEME];
			((LPETHEME)hTheme)->lpaSchemes[GS_COLORSCHEME] = ((LPESCHEME)hScheme);
			return (HESCHEME)lpSchemeTemp;
	
	} SetLastError(126); return NULL;
}

HESCHEME ESTDCALL GetCurrentScheme (HETHEMEOBJ hThemeObj, UINT nSchemeType)
{
	if (!hThemeObj) { SetLastError(126); return NULL; }
	
	switch (((LPETHEMEOBJ)hThemeObj)->uType) {
	case THEMES_THEME:

		// Object is a theme.. get the scheme
		switch (nSchemeType) {
		case SCHEMES_COLORSCHEME: return (HESCHEME)((LPETHEME)hThemeObj)->lpaSchemes[GS_COLORSCHEME];
		} SetLastError(126); return NULL;

	case THEMES_SCHEME:

		// Object is a scheme.. check it and return object
		switch (nSchemeType) {
		case SCHEMES_COLORSCHEME: if (((LPESCHEME)hThemeObj)->uSchemeType != SCHEMES_COLORSCHEME) { SetLastError(126); return NULL; }  return (HESCHEME)hThemeObj;
		} SetLastError(126); return NULL;

	} SetLastError(126); return NULL;
}

HESCHEME ESTDCALL SetExtraScheme (HETHEME hTheme, HESCHEME hScheme, UINT nIndex)
{
	LPESCHEME m_lpScheme;

	if (!hTheme) return NULL; if (((LPETHEME)hTheme)->uType != THEMES_THEME) { SetLastError(126); return NULL; }
	
	
	m_lpScheme = ((LPETHEME)hTheme)->lpaSchemes[nIndex];
	((LPETHEME)hTheme)->lpaSchemes[nIndex] = ((LPESCHEME)hScheme);

	return (HESCHEME)m_lpScheme;
}

LPESCHEME ESTDCALL GetExtraScheme (HETHEME hTheme, UINT nIndex)
{
	if (!hTheme) { SetLastError(126); return NULL; } if (((LPETHEME)hTheme)->uType != THEMES_THEME) { SetLastError(126); return NULL; }
	return ((LPETHEME)hTheme)->lpaSchemes[nIndex];
}

UINT ESTDCALL GetThemeSchemeCount (HETHEME hTheme)
{
	if (!hTheme) { SetLastError(126); return 0; } if (((LPETHEME)hTheme)->uType != THEMES_THEME) { SetLastError(126); return 0; }
	return ((LPETHEME)hTheme)->nExtraSchemes;
}

UINT ESTDCALL GetThemeObjType (HETHEMEOBJ hThemeObj)
{
	if (!hThemeObj) { SetLastError(126); return 0; }
	return ((LPETHEMEOBJ)hThemeObj)->uType;
}
