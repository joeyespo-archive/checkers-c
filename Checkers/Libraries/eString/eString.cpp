// ****************************************************************
// Esposoft C++ String class IMPLEMENTATION (v2.5.08)
// Created by Joey Esposito
//
// eString is a class that allows resizable strings
//
// Do not load this file in your project
// ****************************************************************


#pragma once



// Include Header
// ---------------

#include "eString.h"



// Constructor/Destructor
// -----------------------

eString::eString () : fn_free(free)
{
	eStr_Len = 0;
	eStr_Str = new char [1];
	eStr_Str[0] = 0;
}
eString::eString (const eString &str) : fn_free(free)
{
	if (&str == NULL)
	{
		eStr_Len = 0;
		eStr_Str = new char [1];
		eStr_Str[0] = 0;
		return;
	}

	eStr_Len = str.eStr_Len;
	eStr_Str = new char [(eStr_Len + 1)];

	strncpy(eStr_Str, str.eStr_Str, eStr_Len);
	eStr_Str[eStr_Len] = 0;
}
eString::eString (const char *ch) : fn_free(free)
{
  if (ch == NULL)
	{
		eStr_Len = 0;
		eStr_Str = new char [1];
		eStr_Str[0] = 0;
		return;
	}

	
  eStr_Len = strlen(ch);
	eStr_Str = new char [(eStr_Len + 1)];

	strncpy(eStr_Str, ch, eStr_Len);
	eStr_Str[eStr_Len] = 0;
}
eString::eString (const int ch) : fn_free(free)
{
	union
	{	int i;
		char ch;
	} GetCh;

	GetCh.i = ch;

	eStr_Len = 1;
	eStr_Str = new char [((GetCh.ch == 0) ? (1) : (2))];
	eStr_Str[0] = GetCh.ch;
	if (GetCh.ch != 0) eStr_Str[1] = 0;
}
eString::~eString()
{
	fn_free(eStr_Str); eStr_Str = NULL;
	eStr_Len = 0;
}


// Assignment
// -----------

eString::operator char * () const
{
	char *szStr;
	
	szStr = new char [(eStr_Len + 1)];
	strncpy(szStr, eStr_Str, eStr_Len);
	szStr[eStr_Len] = 0;

	return szStr;
}

// Add to Self
const eString &eString::operator += (const eString &str)
{
	char *tempstr = new char [(eStr_Len + 1)];
	strncpy(tempstr, eStr_Str, eStr_Len);
	tempstr[eStr_Len] = 0;

	eStr_Len += str.eStr_Len;

	fn_free(eStr_Str); fn_free = free;
	eStr_Str = new char [(eStr_Len + 1)];

	strncpy(eStr_Str, tempstr, strlen(tempstr));
	strncpy((&(eStr_Str[strlen(tempstr)])), str.eStr_Str, str.eStr_Len);
	eStr_Str[eStr_Len] = 0;

	delete [] tempstr; tempstr = NULL;
	
  return *this;
}
const eString &eString::operator += (const char *ch)
{
	char *tempstr = new char [(eStr_Len + 1)];
	strncpy(tempstr, eStr_Str, eStr_Len);
	tempstr[eStr_Len] = 0;

	eStr_Len += strlen(ch);

	fn_free(eStr_Str); fn_free = free;
	eStr_Str = new char [(eStr_Len + 1)];

	strncpy(eStr_Str, tempstr, strlen(tempstr));
	strncpy((&(eStr_Str[strlen(tempstr)])), ch, strlen(ch));
	eStr_Str[eStr_Len] = 0;

	delete [] tempstr; tempstr = NULL;
	return *this;
}
const eString &eString::operator += (const int ch)
{
	if (ch == 0) return *this;

	char *tempstr = new char [(eStr_Len + 1)];
	strncpy(tempstr, eStr_Str, eStr_Len);
	tempstr[eStr_Len] = 0;

	eStr_Len += 1;

	fn_free(eStr_Str); fn_free = free;
	eStr_Str = new char [(eStr_Len + 1)];

	strncpy(eStr_Str, tempstr, strlen(tempstr));
	eStr_Str[strlen(tempstr)] = ch;
	eStr_Str[eStr_Len] = 0;

	delete [] tempstr; tempstr = NULL;
	return *this;
}

const eString &eString::operator = (const eString &str)
{
	if (&str == this)
		return *this;

	eStr_Len = str.eStr_Len;
	
	fn_free(eStr_Str); fn_free = free;
	eStr_Str = new char[(eStr_Len + 1)];
	
	strncpy(eStr_Str, str.eStr_Str, eStr_Len);
	eStr_Str[eStr_Len] = 0;
	
	return *this;
}
const eString &eString::operator = (const char *ch)
{
	if (ch == NULL)
	{
		eStr_Len = 0;
    eStr_Str = new char [1];
		eStr_Str[0] = 0;
    fn_free = free;

		return *this;
	}

	if (ch == this->eStr_Str)
		return *this;

	eStr_Len = strlen(ch);

	fn_free(eStr_Str); fn_free = free;
	eStr_Str = new char [(eStr_Len + 1)];
	
	strncpy(eStr_Str, ch, eStr_Len);
	eStr_Str[eStr_Len] = 0;

	return *this;
}
const eString &eString::operator = (const int ch)
{
	union
	{	int i;
		char ch;
	} GetCh;

	GetCh.i = ch;

	fn_free(eStr_Str);
  fn_free = free;

	eStr_Len = ((GetCh.ch == 0) ? (0) : (1));
	eStr_Str = new char [((GetCh.ch == 0) ? (1) : (2))];
	eStr_Str[0] = GetCh.ch;
	if (GetCh.ch != 0) eStr_Str[1] = 0;

	return *this;
}

// Friends
// --------

// eString Addition
const eString operator + (const eString &base, const eString &str)
{
	eString sResult;
	sResult.eStr_Len = (base.eStr_Len + str.eStr_Len);

	sResult.fn_free(sResult.eStr_Str);
	sResult.eStr_Str = new char [(sResult.eStr_Len + 1)];

	strncpy(sResult.eStr_Str, base.eStr_Str, base.eStr_Len);
	strncpy((&(sResult.eStr_Str[base.eStr_Len])), str.eStr_Str, str.eStr_Len);

	sResult.eStr_Str[sResult.eStr_Len] = 0;

	return sResult;
}
const eString operator + (const eString &base, const char ch [])
{
	eString sResult;
	
	sResult.eStr_Len = (base.eStr_Len + strlen(ch));

	sResult.fn_free(sResult.eStr_Str);
	sResult.eStr_Str = new char [(sResult.eStr_Len + 1)];	

	strncpy(sResult.eStr_Str, base.eStr_Str, base.eStr_Len);
	strncpy((&(sResult.eStr_Str[base.eStr_Len])), ch, strlen(ch));
	
	sResult.eStr_Str[sResult.eStr_Len] = 0;

	return sResult;
}
const eString operator + (const eString &base, const char &ch)
{
	eString sResult;
	sResult.eStr_Len = (base.eStr_Len + 1);

	sResult.fn_free(sResult.eStr_Str);
	sResult.eStr_Str = new char [(sResult.eStr_Len + 1)];

	strncpy(sResult.eStr_Str, base.eStr_Str, base.eStr_Len);
	
	sResult.eStr_Str[base.eStr_Len] = ch;
	sResult.eStr_Str[sResult.eStr_Len] = 0;

	return sResult;
}



// General Accessors
// ------------------

eString eString::Mid(const unsigned int start, const unsigned int length) const
{
	unsigned int len = length;
	unsigned int sPos = start;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos < 0) return "";
	if (sPos >= eStr_Len) return "";
	if (len == 0) len = eStr_Len;
	if (len > eStr_Len) len = eStr_Len;
	
	if ((sPos + len) > eStr_Len)
		len = (eStr_Len - sPos);

	eString sResult;
	sResult.eStr_Len = len;
	sResult.eStr_Str = new char [(len + 1)];
	strncpy(sResult.eStr_Str, (&(eStr_Str[sPos])), len);
	sResult[len] = 0;

	return sResult;
}


unsigned int eString::Find(const eString &str, const unsigned int start, const unsigned int length) const
{
	unsigned int len = length;
	unsigned int sPos = start;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos > (eStr_Len - str.eStr_Len)) return 0;
	if (sPos < 0) return 0;
	if (len < 0) return 0;
	if ((len == 0)||(len > (eStr_Len - str.eStr_Len))) len = (eStr_Len - str.eStr_Len);
	if (str.eStr_Len > length) return 0;

	if (&str == this) return 0;
	if (str.eStr_Len == 0) return 0;
	
	// Search for Occurence
	len = ((eStr_Len - str.eStr_Len) - ((eStr_Len - str.eStr_Len) - len));
	
	for(unsigned int i = sPos; i <= len; i++)
		if (strncmp((&(eStr_Str[i])), str.eStr_Str, str.eStr_Len) == 0)
			return (i + 1);

	return 0;
}
unsigned int eString::Find(const char ch [], const unsigned int start, const unsigned int length) const
{
	unsigned int len = length;
	unsigned int sPos = start;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos > (eStr_Len - strlen(ch))) return 0;
	if (sPos < 0) return 0;
	if (len < 0) return 0;
	if ((len == 0)||(len > (eStr_Len - strlen(ch)))) len = (eStr_Len - strlen(ch));
	if (strlen(ch) == 0) return 0;
	if (strlen(ch) > length) return 0;
	
	// Search for Occurence
	unsigned int lenCh = strlen(ch);
	len = ((eStr_Len - lenCh) - ((eStr_Len - lenCh) - len));
	
	for(unsigned int i = sPos; i <= len; i++)
		if (strncmp((&(eStr_Str[i])), ch, lenCh) == 0)
			return (i + 1);

	return 0;
}
unsigned int eString::Find(const char &ch, const unsigned int start, const unsigned int length) const
{
	unsigned int len = length;
	unsigned int sPos = start;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos > (eStr_Len - 1)) return 0;
	if (sPos < 0) return 0;
	if (len < 0) return 0;
	if ((len == 0)||(len > (eStr_Len - 1))) len = (eStr_Len - 1);
		
	// Search for Occurence
	len = (eStr_Len - (eStr_Len - len));
	for(unsigned int i = sPos; i < len; i++)
		if (eStr_Str[i] == ch)
			return (i + 1);

	return 0;
}

eString Mid(const eString &str, const unsigned int start, const unsigned int length)
{
	unsigned int len = length;
	unsigned int sPos = start;
	
	char *lpszResult;

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos < 0) return "";
	if (sPos >= str.eStr_Len) return "";
	if (len == 0) len = str.eStr_Len;
	if (len > str.eStr_Len) len = str.eStr_Len;
	
	if ((sPos + len) > str.eStr_Len)
		len = (str.eStr_Len - sPos);

	lpszResult = new char [(len + 1)];
	strncpy(lpszResult, (&(str.eStr_Str[sPos])), len);
	lpszResult[len] = 0;

	eString sResult(lpszResult);
	delete [] lpszResult;

	return sResult;
}

unsigned int Find(const char *str, const char *tofind, unsigned int start, unsigned int length)
{
	unsigned int len = length;
	unsigned int sPos = start;

	unsigned int lenToFind = strlen(tofind);
	unsigned int lenStr = strlen(str);

	// Error Checking
	if (sPos > 0) sPos--;
	if (sPos > (lenStr - lenToFind)) return 0;
	if (sPos < 0) return 0;
	if (len < 0) return 0;
	if ((len == 0)||(len > (lenStr - lenToFind))) len = (lenStr - lenToFind);
	if (lenToFind > length) return 0;
	
	if (lenToFind == 0) return 0;
	
	// Search for Occurence
	len = ((lenStr - lenToFind) - ((lenStr - lenToFind) - len));
	
	for(unsigned int i = sPos; i <= len; i++)
		if (strncmp((&(str[i])), tofind, lenToFind) == 0)
			return (i + 1);

	return 0;
}


eString Trim (char *szTrimString)
{
	char *sResult;
	unsigned int i;
	unsigned int FirstPos, SecondPos;
	unsigned int StrLength = strlen(szTrimString);

	if (StrLength == 0)
		return szTrimString;

	FirstPos = StrLength;
	for (i = 0; (i < StrLength); i++)
		if ((szTrimString[i] != 32) && (szTrimString[i] != 9))
		{ FirstPos = i; break; }

	SecondPos = StrLength;
	for (i = (StrLength - 1); (i >= 0); i--)
		if ((szTrimString[i] != 32) && (szTrimString[i] != 9))
		{ SecondPos = i; break; }

	i = ((SecondPos - FirstPos) + 1);
	sResult = new char [(i + 1)];
	
	strncpy(sResult, &szTrimString[FirstPos], i);
	sResult[i] = 0;

	return sResult;
}
