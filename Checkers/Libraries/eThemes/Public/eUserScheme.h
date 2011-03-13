// eUserScheme.h
// User Schemes Header File
// By Joe Esposito


#pragma once



// Public Functions
// -----------------

ECALL HESCHEME ESTDCALL CreateUserScheme ( LPVOID lpSchemeData, UINT uSchemeUserType, UINT nExtraSchemeData );
ECALL BOOL ESTDCALL DestroyUserScheme ( HESCHEME lpScheme, UINT uSchemeUserType );
ECALL LONG ESTDCALL SetUserSchemeInfo ( HESCHEME lpScheme, INT nIndex, LONG lValue );
ECALL LONG ESTDCALL GetUserSchemeInfo ( HESCHEME lpScheme, INT nIndex );



// Implementation File
// "eUserScheme.cpp"
