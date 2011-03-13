// EspoLib.cpp
// Espo Standard Routines Implementation File
// By Joey Esposito

#pragma once



// Include Header
// ---------------

#include "eLib.h"



// Class Initialization
// ---------------------

bool eLib::BaseHex = false;
bool eLib::UCaseHex = true;
bool eLib::FullHex = true;
uint eLib::MaxStrLen = 64;



// String Routines
// ----------------

char *FillString (unsigned int uNumber, char ch)
{
	char *str;

	str = new char [(uNumber + 1)];
	
	str[uNumber] = 0;
	strnset(str, ch, uNumber);

	return str;
}

char *AddStr (char *str1, char *str2)
{
	char *temp;
	unsigned int Str1Len = strlen(str1);
	unsigned int Str2Len = strlen(str2);
	unsigned int StrLen = (Str1Len + Str2Len);

	if ((Str1Len == 0) && (Str2Len == 0))
		return new char [0];

	temp = new char [(StrLen + 1)];

	strncpy(temp, str1, Str1Len);
	strncpy(&temp[Str1Len], str2, Str2Len);
	temp[StrLen] = 0;

	return temp;
}

char *Mid(const char *str, const unsigned int start, const unsigned int length)
{
	unsigned int len = length;
	unsigned int sPos = start;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos < 0) return "";
	if (sPos >= strlen(str)) return "";
	if (len == 0) len = strlen(str);
	if (len > strlen(str)) len = strlen(str);
	
	if ((sPos + len) > strlen(str))
		len = (strlen(str) - sPos);

	char *newstr = new char [len];
	strncpy(newstr, (&(str[sPos])), len);
	newstr[len] = 0;

	return newstr;
}


// Compares a 2 strings, the length is the length of the shortest string
bool ComparePartial (const char *str1, const char *str2)
{
	bool ReturnValue = false;

	_asm
	{
		mov  EBX,str1		; Get address of String 1
		mov  EDX,str2		; Get address of String 2

		mov  ReturnValue,0	; ReturnValue is false until proven otherwise

	cLoop:
		mov  AL,byte ptr [EBX]	; Get next character into AH (str1)
		mov  AH,byte ptr [EDX]	; Get next character into AH (str2)
		
		TEST AL,AL			; Is zero?
		jz   cMatch			; If so, it is a match

		TEST AH,AH			; Is zero?
		jz   cMatch			; If so, it is a match

		cmp  AL,AH			; Compare the two bytes
		jne  cDone			; If not equal, then end, ReturnValue being false

		inc  EBX			; Point to next character (str1)
		inc  EDX			; Point to next character (str2)
		jmp  cLoop			;   Otherwise, loop

	cMatch:
		mov  ReturnValue,1	; Return true

	cDone:
	}

	return ReturnValue;
}



// File Routines
// --------------

// Returns the FileName only
char *GetFileNameOnly(const char *lpszFileName)
{
	char *lpszNewStr;
	unsigned int i, n, l;

	l = strlen(lpszFileName);

	for (i = (l - 1); i > 0; i--)
	{
		if (lpszFileName[i] == char(92))
		{
			n = (l - (i + 1));

			lpszNewStr = new char [(n + 1)];
			strncpy(lpszNewStr, (&(lpszFileName[(i + 1)])), n);
			lpszNewStr[n] = 0;

			return lpszNewStr;
		}
	}

	lpszNewStr = new char [(l + 1)];
	strncpy(lpszNewStr, lpszFileName, l);
	lpszNewStr[l] = 0;

	return lpszNewStr;
}


// String/Number Conversion Routines
// ----------------------------------

#ifdef eLib__eString
eString FullHex (eString szHex, unsigned int nDigits)
{
	char *lpszNewStr;
	eString szNewStr;

	lpszNewStr = szHex;
	lpszNewStr = FullHex(lpszNewStr);

	szNewStr = lpszNewStr;
	delete lpszNewStr;

	return szNewStr;
}
#endif

char *FullHex (char *lpHex, unsigned int nDigits)
{
	bool HexHeader;
	unsigned int i = strlen(lpHex);
	char *nNewHex;

	if ((lpHex[0] == '0') && (UCase(lpHex[1]) == 'X')) HexHeader = true;

	if (i < (nDigits + ((HexHeader)?(2):(0))))
	{
		nNewHex = new char [(((HexHeader) ? (2) : (0)) + (nDigits + 1))];
		strncpy((&(nNewHex[((((HexHeader) ? (2) : (0)) + nDigits) - i)])), lpHex, i);
		strnset(nNewHex, '0', ((nDigits + 1) - (i - 1)));
		
		if (HexHeader) { nNewHex[0] = '0'; nNewHex[1] = 'x'; };
		nNewHex[(((HexHeader) ? (2) : (0)) + (nDigits))] = 0;
	} 
	else if (i > (nDigits + ((HexHeader)?(2):(0))))
	{
		nNewHex = new char [(((HexHeader) ? (2) : (0)) + (nDigits + 1))];
		strncpy((&(nNewHex[((((HexHeader) ? (2) : (0)) + nDigits) - i)])), lpHex, nDigits);
		
		if (HexHeader) { nNewHex[0] = '0'; nNewHex[1] = 'x'; };
		nNewHex[(((HexHeader) ? (2) : (0)) + (nDigits))] = 0;
	}
	else
	{
		nNewHex = new char [(((HexHeader) ? (2) : (0)) + (i + 1))];
		strncpy((&(nNewHex[((HexHeader) ? (2) : (0))])), lpHex, i);

		if (HexHeader) { nNewHex[0] = '0'; nNewHex[1] = 'x'; };
		nNewHex[(((HexHeader) ? (2) : (0)) + (i))] = 0;
	}

	return nNewHex;
}

char UCase (char ch)
{
	char *ptch = &ch;

	_asm
	{
		mov  EDX,ptch				; Get address into DX

		mov  AL,[EDX]				; Get character into AL

		cmp  AL,97					; Compare AL with character 97 ('a')
		jl   cDone					; If AL is less then 97, skip & jump to get next character

		cmp  AL,122					; Compare AL with character 122 ('z')
		jg   cDone					; Or if AL is greater then 122, skip & jump to get next character

		sub  AL,32					; Subtract AL by 32:  97 - 32 = character 65 ('A'), as for all characters from 'a' to 'z'
		
		mov  [EDX],AL				; Set new character

	cDone:
	}

	return ch;
}
char *UCase (char *szString)
{
	unsigned int len;

	len = strlen(szString);

	_asm
	{
		mov  ECX,len				; Get Length into CX
		jcxz cDone					; End if length is 0

		mov  EDX,szString			; Get starting address into DX

	cLoop:
		mov  AL,[EDX]				; Get next character into AL
		cmp  AL,97					; Compare AL with character 97 ('a')
		jl   cNext					; If AL is less then 97, skip & jump to get next character

		cmp  AL,122					; Compare AL with character 122 ('z')
		jg   cNext					; Or if AL is greater then 122, skip & jump to get next character

		sub  AL,32					; Subtract AL by 32:  97 - 32 = character 65 ('A'), as for all characters from 'a' to 'z'
		mov  [EDX],AL				; Put new character into String

	cNext:
		inc  EDX					; Point to next character in old String
		dec  ECX					; Decrease CX by 1
		
		jcxz cDone					; If CX is 0, exit
		jmp  cLoop					;   Otherwise, continue loop

	cDone:
	}

	return szString;
}


char LCase (char ch)
{
	char *ptch = &ch;

	_asm
	{
		mov  EDX,ptch				; Get address into DX

		mov  AL,[EDX]				; Get character into AL

		cmp  AL,65					; Compare AL with character 65 ('A')
		jl   cDone					; If AL is less then 65, skip & jump to get next character

		cmp  AL,90					; Compare AL with character 90 ('Z')
		jg   cDone					; Or if AL is greater then 90, skip & jump to get next character

		add  AL,32					; Add AL by 32:  97 + 32 = character 97 ('a'), as for all characters from 'A' to 'Z'

		mov  [EDX],AL				; Set new character

	cDone:
	}

	return ch;
}
char *LCase (char *szString)
{
	unsigned int len;

	len = strlen(szString);

	_asm
	{
		mov  ECX,len				; Get Length into CX
		jcxz cDone					; End if length is 0

		mov  EDX,szString			; Get starting address into DX

	cLoop:
		mov  AL,[EDX]				; Get next character into AL
		cmp  AL,65					; Compare AL with character 65 ('A')
		jl   cNext					; If AL is less then 65, skip & jump to get next character

		cmp  AL,90					; Compare AL with character 90 ('Z')
		jg   cNext					; Or if AL is greater then 90, skip & jump to get next character

		add  AL,32					; Add AL by 32:  97 + 32 = character 97 ('a'), as for all characters from 'A' to 'Z'
		mov  [EDX],AL				; Put new character into String

	cNext:
		inc  EDX					; Point to next character in old String
		dec  ECX					; Decrease CX by 1
		
		jcxz cDone					; If CX is 0, exit
		jmp  cLoop					;   Otherwise, continue loop

	cDone:
	}

	return szString;
}

#ifdef eLib__eString
eString UCase (eString szString)
{
	char *lpszString;
	eString szResult;
	
	lpszString = szString;

	UCase(lpszString);

	szResult = lpszString;
	delete lpszString;

	return szResult;
}

eString LCase (eString szString)
{
	char *lpszString;
	eString szResult;
	
	lpszString = szString;

	LCase(lpszString);

	szResult = lpszString;
	delete lpszString;

	return szResult;
}
#endif

char *ToStr (const bool b)
{
	char *ch = new char [5];
	ch = ((b) ? ("True") : ("False"));

	return ch;
}
char *ToStr (const int num, const int nRadixBase)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_itoa(num, temp, nRadixBase));

	if ((nRadixBase == 16) && (eLib::FullHex)) gStr = FullHex(temp);

	if (gStr == NULL) {
		gStr = new char [(i + 1)];
		strncpy(gStr, temp, i);
		gStr[i] = 0;
	}
	
	delete temp;

	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const __int64 num, const int nRadixBase)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_i64toa(num, temp, nRadixBase));

	if ((nRadixBase == 16) && (eLib::FullHex)) gStr = FullHex(temp);

	if (gStr == NULL) {
		gStr = new char [(i + 1)];
		strncpy(gStr, temp, i);
		gStr[i] = 0;
	}

	delete temp;

	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const unsigned int num, const int nRadixBase)
{ return ToStr( ((__int64)num), nRadixBase ); }
char *ToStr (const unsigned __int64 num, const int nRadixBase)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_ui64toa(num, temp, nRadixBase));

	if ((nRadixBase == 16) && (eLib::FullHex)) gStr = FullHex(temp);

	if (gStr == NULL) {
		gStr = new char [(i + 1)];
		strncpy(gStr, temp, i);
		gStr[i] = 0;
	}

	delete temp;

	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const double num, const int NumDigits)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_gcvt(num, NumDigits, temp));

	gStr = new char [(i + 1)];
	strncpy(gStr, temp, i);
	gStr[i] = 0;

	delete temp;

	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const long num, const int nRadixBase)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_ltoa(num, temp, nRadixBase));

	if ((nRadixBase == 16) && (eLib::FullHex)) gStr = FullHex(temp);

	if (gStr == NULL) {
		gStr = new char [(i + 1)];
		strncpy(gStr, temp, i);
		gStr[i] = 0;
	}

	delete temp;

	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const unsigned long num, const int nRadixBase)
{
	char *gStr = NULL, *temp = 0;
	unsigned int i;

	temp = new char [eLib::MaxStrLen + 1];
	i = strlen(_ultoa(num, temp, nRadixBase));

	if ((nRadixBase == 16) && (eLib::FullHex)) gStr = FullHex(temp);
	
	if (gStr == NULL) {
		gStr = new char [(i + 1)];
		strncpy(gStr, temp, i);
		gStr[i] = 0;
	}

	delete temp;

	
	if (eLib::UCaseHex) UCase(gStr+2);
	return gStr;
}
char *ToStr (const void *pAddr)
{
	unsigned __int32 lAddr;
	__asm
	{
		mov  EAX,pAddr
		mov  lAddr,EAX
	}

	return ToStr((unsigned long)lAddr, 16);
}

char *Trim (const char *lpStr)
{
	char *lpResult;
	unsigned int i;
	unsigned int FirstPos, SecondPos;
	unsigned int StrLength = strlen(lpStr);

	if (StrLength == 0)
	{
		if (lpStr == NULL)
			return NULL;

		lpResult = new char [1];
		lpResult[0] = NULL;
		return lpResult;
	}

	FirstPos = StrLength;
	for (i = 0; (i < StrLength); i++)
		if ((lpStr[i] != 32) && (lpStr[i] != 9))
		{ FirstPos = i; break; }

	SecondPos = StrLength;
	for (i = (StrLength - 1); (i >= 0); i--)
		if ((lpStr[i] != 32) && (lpStr[i] != 9))
		{ SecondPos = i; break; }

	i = ((SecondPos - FirstPos) + 1);
	lpResult = new char [(i + 1)];
	
	strncpy(lpResult, &lpStr[FirstPos], i);
	lpResult[i] = NULL;

	return lpResult;
}


bool ToBool ( const char *string ) { char *t = _strdup(string); bool b = (strncmp(UCase(Trim(t)), "TRUE", strlen(t)) == 0); delete [] t; return b; };
bool ToBool ( const int num )	{ return (num != 0); };
bool ToBool ( const __int64 num )	{ return (num != 0); };
bool ToBool ( const unsigned __int64 num )	{ return (num != 0); };
bool ToBool ( const double num )	{ return (num != 0); };
bool ToBool ( const long num )	{ return (num != 0); };
bool ToBool ( const unsigned long num )	{ return (num != 0); };

int ToInt ( const bool value )	{ return ((value) ? (1) : (0)); };
int ToInt ( const char *string ) { return atoi(string); };
int ToInt ( const __int64 num )	{ return (int)num; };
int ToInt ( const unsigned __int64 num )	{ return (int)num; };
int ToInt ( const double num )	{ return (int)num; };
int ToInt ( const long num )	{ return (int)num; };
int ToInt ( const unsigned long num )	{ return (int)num; };

long ToVal ( const bool value )	{ return ((value) ? (1) : (0)); };
long ToVal ( const char *string, int base ) { base = ( (strncmp(Mid(string, 1, 2), "0x", 2) == 0) ? (16) : (10)); return strtol(string, 0, base); };
long ToVal ( const int num )	{ return (long)num; };
long ToVal ( const __int64 num )	{ return (long)num; };
long ToVal ( const unsigned __int64 num )	{ return (long)num; };
long ToVal ( const double num )	{ return (long)num; };
long ToVal ( const unsigned long num )	{ return (long)num; };

__int64 ToInt64 ( const bool value )	{ return ((value) ? (1) : (0)); };
__int64 ToInt64 ( const char *string ) { return _atoi64(string); };
__int64 ToInt64 ( const int num )	{ return (__int64)num; };
__int64 ToInt64 ( const unsigned __int64 num )	{ return (__int64)num; };
__int64 ToInt64 ( const double num )	{ return (__int64)num; };
__int64 ToInt64 ( const long num )	{ return (__int64)num; };
__int64 ToInt64 ( const unsigned long num )	{ return (__int64)num; };

unsigned __int64 ToUInt64 ( const bool value )	{ return ((value) ? (1) : (0)); };
unsigned __int64 ToUInt64 ( const char *string ) { return (unsigned __int64)_atoi64(string); };
unsigned __int64 ToUInt64 ( const int num )	{ return (unsigned __int64)num; };
unsigned __int64 ToUInt64 ( const __int64 num )	{ return (unsigned __int64)num; };
unsigned __int64 ToUInt64 ( const double num )	{ return (unsigned __int64)num; };
unsigned __int64 ToUInt64 ( const long num )	{ return (unsigned __int64)num; };
unsigned __int64 ToUInt64 ( const unsigned long num )	{ return (unsigned __int64)num; };

double ToDouble ( const bool value )	{ return ((value) ? (1) : (0)); };
double ToDouble ( const char *string ) { return strtod(string, 0); };
double ToDouble ( const int num )	{ return (double)num; };
double ToDouble ( const __int64 num )	{ return (double)num; };
double ToDouble ( const unsigned __int64 num )	{ return (double)((signed __int64)num); };
double ToDouble ( const long num )	{ return (double)num; };
double ToDouble ( const unsigned long num )	{ return (double)num; };

long ToLong ( const bool value )	{ return ((value) ? (1) : (0)); };
long ToLong ( const char *string, int base ) { return strtol(string, 0, base); };
long ToLong ( const int num )	{ return (long)num; };
long ToLong ( const __int64 num )	{ return (long)num; };
long ToLong ( const unsigned __int64 num )	{ return (long)num; };
long ToLong ( const double num )	{ return (long)num; };
long ToLong ( const unsigned long num )	{ return (long)num; };

unsigned long ToULong ( const bool value )	{ return ((value) ? (1) : (0)); };
unsigned long ToULong ( const char *string, int base ) { return (unsigned long)strtol(string, 0 , base); };
unsigned long ToULong ( const int num )	{ return (unsigned long)num; };
unsigned long ToULong ( const __int64 num )	{ return (unsigned long)num; };
unsigned long ToULong ( const unsigned __int64 num )	{ return (unsigned long)num; };
unsigned long ToULong ( const double num )	{ return (unsigned long)num; };
unsigned long ToULong ( const long num )	{ return (unsigned long)num; };
