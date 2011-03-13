// ****************************************************************
// Esposoft C++ String class (v2.5.08)
// Created by Joey Esposito
//
// eString is a class that allows resizable strings
//
// NOTE: If you need an eString to equal 0 (NULL), you must use "char(0)"
// instead of "0", because the overload functions might think
// "0" is used for a Character Pointer Address
//
// Examples:
// eString s (char(0));
// s = char(0);
//
//
// Options
// --------
// To use any of these options, declare them
// BEFORE including eString
//
// #define EspoLib__Max_String_Length	<StringLength>
//
// #define no_estring_macro
//   Turns off the "estring" shortcut macro
//
// #define no_String_macro
//   Turns off the "String" shortcut macro
//    BEFORE the include of eString
//
// #define no_string_macro
//   Turns off the "string" shortcut macro
//    BEFORE the include of eString
//
//   This is in case you need the variables "string" or
//   "estring" reserved for any reason
//
//
// #define eString_no_assert
//   This turns off the assert checking
// ****************************************************************


#pragma once



// Define Library
#define _Esposoft__eString_


// Include String Routines
#include <string.h>
#include <stdlib.h>

// Include Assert (if user allows it)
#ifndef eString_no_assert
#include <assert.h>
#endif

#ifndef NULL
 #define NULL = 0x0000
#else
 #if (NULL != 0)
   #error "Already defined: NULL"
 #endif
#endif


#ifndef EspoLib__Max_String_Length
#define EspoLib__Max_String_Length		255
#endif


typedef void (* ESTRING_FREEPROC)(void *);



class eString
{
public:

	// Constructor/Destructor
	// -----------------------
	eString ();							// Defualt Constructor
	eString ( const eString &str );		// Copy Constructor
	eString ( const char *ch );			// String Constructor
	eString ( const signed int ch );	// Character Constructor (by Integer)
	~eString ();						// eString Destructor


	// Assignment
	// -----------

	// Add to Self
	// (Adds a String to the current eString)
	const eString &operator += ( const eString &str );	// Adds a String to the current eString
	const eString &operator += ( const char *ch );	// Adds a String to the current eString
	const eString &operator += ( const signed int ch );		// Adds a String to the current eString

	// Copy Assignment
	// (Changes current eString to equal another String)
	const eString &operator = ( const eString &str );
	const eString &operator = ( const char *ch );
	const eString &operator = ( const signed int ch );

	// Compare Operators
	// (Compare an eString with another String)
	const bool operator == ( const char *ch )  { return (strcmp(eStr_Str, ch) == 0); };	// Compare an eString with another String
	const bool operator == ( const eString &Str )  { return (strcmp(eStr_Str, Str.eStr_Str) == 0); };	// Compare an eString with another String


	// char * Operator
	operator char * () const;	// Returns C-Style String
	

	// General Accessors
	// ------------------

	int Length () const { return eStr_Len; };	// Returns Length of String
	char * Str () const { return this->operator char * (); };								// Returns a copy of the C-Style String
	
	eString Mid ( const unsigned int start = 1, const unsigned int length = 0 ) const;	// Retrieves partial eString in C-Style format

	// Find Functions
	// (Helps find a section of current eString;  Returns 0 if it is not in current eString)
	unsigned int Find ( const eString &str, unsigned int start = 1, unsigned int length = 0 ) const;	// Occurence of eString
	unsigned int Find ( const char ch [], unsigned int start = 1, unsigned int length = 0 ) const;		// Occurence of String
	unsigned int Find ( const char &ch, unsigned int start = 1, unsigned int length = 0 ) const;		// Occurence of Character


	// Friends
	// --------

	// Addition Operators
	// (Adds a String and an eString together, and vise versa)
	friend const eString operator + ( const eString &base, const eString &str );
	friend const eString operator + ( const eString &base, const char ch [] );
	friend const eString operator + ( const eString &base, const char &ch );

	// Subtraction Operators
	// (Subtracts EVERY Occurence of a String in the current eString)
	friend const eString operator - ( const eString &base, const eString &str );
	friend const eString operator - ( const eString &base, const char ch [] );
	friend const eString operator - ( const eString &base, const char &ch );


	// Friend Mid Functions
	// (Used to get a section of a String)
	friend eString Mid ( const eString &str, const unsigned int start = 1, const unsigned int length = 0 );
	friend eString Trim ( char *TrimString );	// Removes extreme whitespaces

	friend unsigned int Find ( const char *str, const char *tofind, unsigned int start = 1, unsigned int length = 0 );	// Occurence String

private:
	char *eStr_Str;				// Actual String
	unsigned int eStr_Len;  // String's Length
  ESTRING_FREEPROC fn_free; // The free function to be called
};



// Define eString Shortcut Macros
#ifndef no_estring_macro
 typedef eString  eString;  // Converts estring to eString
#endif

#ifndef no_String_macro
 typedef eString  String;   // Converts string to eString
#endif

#ifndef no_string_macro
 typedef eString  string;   // Converts string to eString
#endif


// Implementation File
// "eString.cpp"
