// eUserScheme.cpp
// User Schemes Implementation File
// By Joe Esposito



// Public Functions
// -----------------

HESCHEME ESTDCALL CreateUserScheme (LPVOID lpSchemeData, UINT uSchemeUserType, UINT nExtraSchemeData)
{ return (HESCHEME)_CreateScheme(SCHEMES_USERSCHEME, uSchemeUserType, lpSchemeData, nExtraSchemeData); }

BOOL ESTDCALL DestroyUserScheme (HESCHEME hScheme, UINT uSchemeUserType)
{
	if (!hScheme) return FALSE; if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) return NULL;
	if (((LPESCHEME)hScheme)->uSchemeType != SCHEMES_USERSCHEME) return FALSE;
	if ((uSchemeUserType != 0) && (((LPESCHEME)hScheme)->uSchemeUserType != uSchemeUserType)) return FALSE;
	
	return _DestroyScheme((LPESCHEME)hScheme);
}

LONG ESTDCALL SetUserSchemeInfo (HESCHEME hScheme, INT nIndex, LONG lValue)
{
	if (!hScheme) return FALSE; if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) { SetLastError(126); return NULL; }
	if (((LPESCHEME)hScheme)->uSchemeType != SCHEMES_USERSCHEME) { SetLastError(126); return NULL; }

	return _SetSchemeInfo((LPESCHEME)hScheme, nIndex, lValue);
}

LONG ESTDCALL GetUserSchemeInfo (HESCHEME hScheme, INT nIndex)
{
	if (!hScheme) return FALSE; if (((LPESCHEME)hScheme)->uType != THEMES_SCHEME) { SetLastError(126); return NULL; }
	if (((LPESCHEME)hScheme)->uSchemeType != SCHEMES_USERSCHEME) { SetLastError(126); return NULL; }

	return _GetSchemeInfo((LPESCHEME)hScheme, nIndex);
}
