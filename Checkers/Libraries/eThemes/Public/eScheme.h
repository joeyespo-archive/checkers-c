// eScheme.h
// Schemes Header File
// By Joe Esposito


#pragma once



// Structures
// -----------

typedef struct _ESCHEME : _ETHEMEOBJ
{
	UINT uSchemeType;			// Type of scheme object (SCHEMES_x)
	UINT uSchemeUserType;		// Type of scheme object (if a user scheme)
	LPVOID lpSchemeData;		// Scheme data
	UINT nExtraData;			// Number of extra schemes
	LONG *lpExtraData;			// Pointer to extra data
} ESCHEME, *LPESCHEME;



// Public Functions
// -----------------

ECALL UINT ESTDCALL GetSchemeType ( HESCHEME hScheme );
ECALL UINT ESTDCALL GetSchemeInfoCount ( HESCHEME hScheme );



// Implementation File
// "eScheme.cpp"
