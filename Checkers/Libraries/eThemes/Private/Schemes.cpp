// Schemes.cpp
// Schemes Internal Implementation File
// By Joe Esposito



// Internal Functions
// -------------------

LPESCHEME _CreateScheme (UINT uSchemeType, UINT uSchemeUserType, LPVOID lpSchemeData, UINT nExtraSchemeData)
{
	LPESCHEME lpScheme;

	if (uSchemeType == 0) return NULL;
	if ((uSchemeType == SCHEMES_USERSCHEME) && (uSchemeUserType == 0)) return NULL;
	if (nExtraSchemeData == 0xFFFFFFFF) return NULL;


	if ((lpScheme = new ESCHEME) == NULL) return NULL;

	lpScheme->uType = THEMES_SCHEME;			// Object is a scheme
	lpScheme->uSchemeType = uSchemeType;		// Scheme object
	lpScheme->uSchemeUserType = ((uSchemeType == SCHEMES_USERSCHEME)?(uSchemeUserType):(0));
	lpScheme->lpSchemeData = lpSchemeData;		// Set scheme data

	// User data
	lpScheme->nExtraData = nExtraSchemeData;	// Extra data associated with object
	lpScheme->lpExtraData = new LONG [nExtraSchemeData];	// Create extra data

	return lpScheme;
}

BOOL _DestroyScheme (LPESCHEME lpScheme)
{
	// Delete extra data
	if (lpScheme->lpExtraData) delete [lpScheme->nExtraData] lpScheme->lpExtraData;
	
	lpScheme->uType = 0;
	delete lpScheme;

	return TRUE;
}

LONG _SetSchemeInfo (LPESCHEME lpScheme, INT nIndex, LONG lValue)
{
	LONG lOldValue;

	lOldValue = lpScheme->lpExtraData[nIndex];
	lpScheme->lpExtraData[nIndex] = lValue;

	return lOldValue;
}

LONG _GetSchemeInfo (LPESCHEME lpScheme, INT nIndex)
{ return lpScheme->lpExtraData[nIndex]; }
