// eScheme.cpp
// Schemes Implementation File
// By Joe Esposito



// Public Functions
// -----------------

UINT ESTDCALL GetSchemeType (HESCHEME hScheme)
{
	if (!hScheme) { SetLastError(126); return NULL; } if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) { SetLastError(126); return NULL; }
	return ((LPESCHEME)hScheme)->uSchemeType;
}

UINT ESTDCALL GetSchemeInfoCount (HESCHEME hScheme)
{
	if (!hScheme) { SetLastError(126); return NULL; } if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) { SetLastError(126); return NULL; }
	return ((LPESCHEME)hScheme)->nExtraData;
}
