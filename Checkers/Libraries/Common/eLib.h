// eLib.h
// Espo Standard Routines Header File
// By Joey Esposito

// Pre-Defines:
//
//   #define eLib__No_eString		// Prohibits eString Declarations
//


#pragma once



// Includes
// ---------

#include <stdlib.h>
#include <string.h>



// Basic Macros
// -------------

#ifndef STATIC
#define STATIC			static
#endif
#ifndef LOCAL
#define LOCAL			STATIC
#endif

#define UNION			union
#define VIRTUAL			virtual
#define FRIEND			friend
#define INLINE			__forceinline
#define LOCALTHREAD		__declspec ( thread )
#define EXTERN			extern
#define STDCALL			__stdcall
#define DLLEXPORT		__declspec ( dllexport ) STDCALL
#define DLLIMPORT		__declspec ( dllimport ) STDCALL
#define SWITCH(data)	switch((LONG)data)
#define CASE(data)		case((LONG)data)
#define DEFAULT			default
#define BREAK			break
#define CREATECHECK(value)	if (!value) return -1;



// Global Typedefs
// ----------------

typedef unsigned int		word;
typedef unsigned long		dword;
typedef unsigned int		uint;



// Options
// --------

#undef eLib__eString

#ifndef eLib__No_eString
#ifdef _Esposoft__eString_
#define eLib__eString
#endif
#endif



// Classes
// --------

class eLib
{
public:

	static bool BaseHex;	// Use Hex as base number system
	static bool UCaseHex;	// UCase all hex values
	static bool FullHex;	// Display full Hexadecimal digits
	static uint MaxStrLen;	// Maximum string Len
};



// Declarations
// -------------

// String Routines:
char *FillString ( unsigned int uNumber, char ch );
char *AddStr ( char *, char * );
char *Mid ( const char *str, const unsigned int start = 1, const unsigned int length = 0 );
bool ComparePartial ( const char *str1, const char *str2 );	// Compares a 2 strings, the length is the length of the shortest string

// File Routines:
char *GetFileNameOnly ( const char *FileName );	// Returns only the FileName in a File

// String/Number Conversions:
char *FullHex ( char *lpHex, unsigned int nDigits = 8 );
char UCase ( char ch );				// Get Upper-Cased format of a Character
char *UCase ( char *szStringToCase );	// Get Upper-Cased format of a String
char LCase ( char ch );				// Get Lower-Cased format of a Character
char *LCase ( char *szStringToCase );	// Get Lower-Cased format of a String

#ifdef eLib__eString
eString FullHex ( eString lpHex, unsigned int nDigits = 8 );	// Get Upper-Cased format of a String
eString UCase ( eString szStringToCase );	// Get Upper-Cased format of a String
eString LCase ( eString szStringToCase );	// Get Lower-Cased format of a String
#endif

char *Trim ( const char *lpStr );

char *ToStr ( const bool b );			// Boolean
char *ToStr ( const int num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );		// Signed Integer
char *ToStr ( const __int64 num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );		// Signed 64 Integer
char *ToStr ( const unsigned int num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );		// Signed 64 Integer
char *ToStr ( const unsigned __int64 num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );	// Signed Integer
char *ToStr ( const double num, const int NumDigits = 12 );	// Signed Double
char *ToStr ( const long num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );	// Signed Long
char *ToStr ( const unsigned long num, const int nRadixBase = ((eLib::BaseHex) ? (16) : (10)) );	// Unsigned Long
char *ToStr ( const void *pAddr );	// Pointer Address

bool ToBool ( const char *string );
bool ToBool ( const int num );
bool ToBool ( const __int64 num );
bool ToBool ( const unsigned __int64 num );
bool ToBool ( const double num );
bool ToBool ( const long num );
bool ToBool ( const unsigned long num );

int ToInt ( const bool value );
int ToInt ( const char *string );
int ToInt ( const __int64 num );
int ToInt ( const unsigned __int64 num );
int ToInt ( const double num );
int ToInt ( const long num );
int ToInt ( const unsigned long num );

long ToVal ( const bool value );
long ToVal ( const char *string, int base = 0 );
long ToVal ( const int num );
long ToVal ( const __int64 num );
long ToVal ( const unsigned __int64 num );
long ToVal ( const double num );
long ToVal ( const unsigned long num );

__int64 ToInt64 ( const bool value );
__int64 ToInt64 ( const char *string );
__int64 ToInt64 ( const int num );
__int64 ToInt64 ( const unsigned __int64 num );
__int64 ToInt64 ( const double num );
__int64 ToInt64 ( const long num );
__int64 ToInt64 ( const unsigned long num );

unsigned __int64 ToUInt64 ( const bool value );
unsigned __int64 ToUInt64 ( const char *string );
unsigned __int64 ToUInt64 ( const int num );
unsigned __int64 ToUInt64 ( const __int64 num );
unsigned __int64 ToUInt64 ( const double num );
unsigned __int64 ToUInt64 ( const long num );
unsigned __int64 ToUInt64 ( const unsigned long num );

double ToDouble ( const bool value );
double ToDouble ( const char *string );
double ToDouble ( const int num );
double ToDouble ( const __int64 num );
double ToDouble ( const unsigned __int64 num );
double ToDouble ( const long num );
double ToDouble ( const unsigned long num );

long ToLong ( const bool value );
long ToLong ( const char *string, int base = 10 );
long ToLong ( const int num );
long ToLong ( const __int64 num );
long ToLong ( const unsigned __int64 num );
long ToLong ( const double num );
long ToLong ( const unsigned long num );

unsigned long ToULong ( const bool value );
unsigned long ToULong ( const char *string, int base = 10 );
unsigned long ToULong ( const int num );
unsigned long ToULong ( const __int64 num );
unsigned long ToULong ( const unsigned __int64 num );
unsigned long ToULong ( const double num );
unsigned long ToULong ( const long num );



// Macro Functions
// ----------------

#define strlen(s)	((s == 0) ? (0) : (strlen(s)))

inline char *ToHex ( const int num ) { return ToStr(num, 16); };
inline char *ToHex ( const __int64 num ) { return ToStr(num, 16); };
inline char *ToHex ( const unsigned __int64 num ) { return ToStr(num, 16); };
inline char *ToHex ( const long num ) { return ToStr(num, 16); };
inline char *ToHex ( const unsigned long num ) { return ToStr(num, 16); };
inline char *ToHex ( const void *pAddr ) { return ToStr(pAddr); };

__forceinline void ZeroMem ( const void *lpAddr, const unsigned int nBytes ) {
	_asm
	{
		xor  ax,ax					; Zero AX
		mov  edi,lpAddr				; Store Address in DI
		mov	 ecx,nBytes				; Copy length into CX (Count Register)
		rep stos byte ptr [edi]		; Store CX number of bytes (AL) in [EDI]
	}
}
__forceinline void SetMem64 ( const void *lpAddr, const unsigned long dwData, const unsigned int nLength ) {
	_asm
	{
		mov  eax,dwData				; Data to store
		mov  edi,lpAddr				; Store Address in DI
		mov	 ecx,nLength			; Copy length into CX (Count Register)
		
		SetMem:
		mov  dword ptr [edi],eax	; Store data
		add  edi,4					; Point to next DWORD
		LOOP SetMem
	}
}

template <class T> __forceinline void swap ( const T &x, const T &y ) { T temp = x; x = y; y = temp; }


// Implementation File:
// "eLib.cpp"
