// Schemes.h
// Schemes Internal Header File
// By Joe Esposito


#pragma once



// Internal Functions
// -------------------

LOCAL LPESCHEME _CreateScheme ( UINT uSchemeType, UINT uSchemeUserType, LPVOID lpSchemeData, UINT nExtraSchemeData );
LOCAL BOOL _DestroyScheme ( LPESCHEME lpScheme );
LOCAL LONG _SetSchemeInfo ( LPESCHEME lpScheme, INT nIndex, LONG lValue );
LOCAL LONG _GetSchemeInfo ( LPESCHEME lpScheme, INT nIndex );



// Implementation File
// "Schemes.cpp"
