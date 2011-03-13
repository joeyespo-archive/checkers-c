// !!! ADD IN FINAL EXAMINATION COMMENTS
// !!! ADD VARIABLES SECTION OF HELP
// !!! CHECK FUNCTIONS
// !!! ADD !!! FUNCTIONS

// ****************************************************************
// Esposoft C++ Array Collection class (v1.1.01)
// Created by Joey Esposito
//
// eCollection is a class that allows
// resizable vectors; any class array
//
//
// Functions
// ----------
// itemcount ()           --  The number of items in eCollection
// item (index)           --  Returns the item
// resize (num, def_item) --  Resizes eCollection, and stores new items as <def_item>
// resize (num)           --  Resizes eCollection
// add (item)             --  Adds one index onto eCollection
// remove (index)         --  Removes an item by index number
// clear ()               --  Clears all eCollection items
// swap (index1, index2)  --  Swaps two items by index numbers
// find ( item )          --  Returns if that item is in the eCollection
//
//
// Warning
// --------
// For those who need an eCollection of Pointers to something:
//  Always initialize the pointers in the eCollection before using
//  or refering to them!
//
// A good way of intialization in resizing:
// Constructor eCollection(<size>, *<def_value>*);
//
//
// Options
// --------
// To use any of these options, declare them
// BEFORE including eCollection
//
// #define eCollection_templates
//   eCollection uses templates instead of Strings or eStrings
//
// #define def_eCollection_template <TNAME>
//   Sets the Default template to <TNAME>
//   Do NOT use References when setting the default Template name
//
//
// #define eCollection_no_ecollection_macro
//   Turns off the "ecollection" macro
//
// #define eCollection_no_Collection_macro
//   Turns off the "Collection" macro
//
// #define eCollection_no_collection_macro
//   Turns off the "collection" macro
//
//   This is in case you need the variables "collection", "Collection", or
//   "ecollection" reserved for any reason
//
//
// #define eCollection_no_eString
//   Makes sure eString is NOT used in eCollection [by default]
//
// #define eCollection_assert
//   This turns on the assert checking
// ****************************************************************


#pragma once



// Define Library
#define _Esposoft__eCollection_


// Include String Routines
#include <string.h>

// Include Assert (if user allows it)
#ifdef eCollection_assert
#include <assert.h>
#endif


// Define NULL
#ifndef NULL
 #define NULL = 0x0000
#else
 #if (NULL != 0)
   #error Definition already defined: NULL
 #endif
#endif


// Define -eCollection- Macros
// ----------------------------

// Check and define local definition
#ifdef eColl_use_eString
#error Definition already defined: eColl_use_eString
#endif

#ifndef eCollection_no_eString
 #ifdef _Esposoft__eString_
  #define eColl_use_eString
 #endif
#endif


// If user didn't define a default template,
// define eCollection default
#ifndef def_eCollection_template
 #ifdef eColl_use_eString
  #define def_eCollection_template	eString
 #else
  #define def_eCollection_template	char *
 #endif
#endif


// Check local eCollection definitions
#ifdef eColl
#error Definition already defined: eColl
#endif
#ifdef eColl_template
#error Definition already defined: eColl_template
#endif
#ifdef eColl_template_item
#error Definition already defined: eColl_template_item
#endif

// Define local eCollection definitions
// They vary, depending on the user's options
// This is to save maximum memory and best speed
#ifndef eCollection_no_templates
 #define eColl			eCollection<eCollection_item>
 #define eColl_template	template <class eCollection_item>
 #define eColl_template_item	eCollection_item
#else
 #ifdef eColl_use_eString
  #define eColl			eCollection
  #define eColl_template
  #define eColl_template_item	def_eCollection_template
 #else
  #define eColl			eCollection
  #define eColl_template
  #define eColl_template_item	def_eCollection_template
 #endif
#endif



// Define class eCollection
// -------------------------

typedef void (* ECOLLECTION_FREEPROC)(void *);

eColl_template
class eCollection
{
public:
	// Constructor/Destructor
	// -----------------------
	eCollection ();		// Default Constructor
	eCollection ( const eCollection &Coll );	// Copy Constructor
//	eCollection ( const unsigned int Size );		// Presized Constructor
	eCollection ( const unsigned int Size, eColl_template_item def_item );
	eCollection ( const eColl_template_item *Items, unsigned int Count );
	eCollection ( eColl_template_item def_item );	// One sized constructor
	~eCollection ();							// Destructor


	// Overloaded Operators
	// ---------------------

	// Character Accessors with Index Checking
	eColl_template_item &operator [] ( const unsigned int Offset );	// Retrieves a spacific item from eCollection
		

	// Assignment Operators
	// ---------------------

	const eCollection &operator = ( const eCollection & );	// Copies an eCollection with another
	const eCollection &operator += ( eCollection & );  // Adds an item to eCollection
	const eCollection &operator += ( eColl_template_item  );  // Adds an item to eCollection
	friend const eCollection operator + ( const eCollection &, const eCollection & );   // Adds an eCollection to eCollection
	const bool operator == ( const eColl_template_item & );  // Returns if an item appears in an eCollection
	const bool operator == ( const eCollection & );  // Returns if an item appears in an eCollection
	

	
	// Added Functions
	// -----------------

	unsigned int Count () const;	// Returns the number of items
	void AddList ( const eColl_template_item *value, const unsigned int count );

	// General Accessors
	eColl_template_item &Item ( const unsigned int ItemNum );	// Used to retrieve a spacific item


	// Resize Modifiers
	// -----------------

	// General Resizers
	// (Resizes to user's new size)
	const eCollection &Resize ( const unsigned int NewSize );		// Resizes to user's new size
	const eCollection &Resize ( const unsigned int NewSize, eColl_template_item DefItem );	// Resizes to user's new size

	// Additional Resizers
	const eCollection &Add ();	// Resizes by one
	const eCollection &Add ( eColl_template_item Item, bool bNoRepeats = false );	// Resizes the list by one to a spacific item
	const eCollection &Add ( const eColl_template_item *Items, unsigned int Count, bool NoRepeats );
	eColl_template_item Remove ( const unsigned int Index );	// Removes an item by it's index number
	void RemoveItems ( eColl_template_item Item );	// Removes all items that match the parameter
	void Clear ();		// Clears all items
	

	// Swap
	const eCollection &Swap ( const unsigned int Index1, const unsigned int Index2 );	// Switches all Variables and values between an eCollection

	
	// In-Class Functions
	// -------------------

	friend const eCollection operator + (const eCollection &Coll, const eColl_template_item Value);

private:
	unsigned int m_Size;	// The number of Items
	eColl_template_item **m_ItemList;	// The actual list of pointers to items
  ECOLLECTION_FREEPROC fn_free; // The free function to be called
};

//const eCollection operator + ( const eCollection &coll, const eColl_template_item addValue );


// Free local Variables
#ifdef eColl
 #undef eColl
#endif
#ifdef eColl_template
 #undef eColl_template
#endif
#ifdef eColl_template_item
 #undef eColl_template_item
#endif

#ifdef eColl_use_eString
 #undef eColl_use_eString
#endif


// Define eCollection Shortcut Macros
#ifndef eCollection_no_ecollection_macro
 #ifndef ecollection
  #define ecollection		eCollection		// Converts ecollection to eCollection
 #endif
#endif

#ifndef eCollection_no_Collection_macro
 #ifndef Collection
  #define Collection		eCollection		// Converts collection to eCollection
 #endif
#endif

#ifndef eCollection_no_collection_macro
 #ifndef collection
  #define collection		eCollection		// Converts collection to eCollection
 #endif
#endif


// Implementation File:
// "eCollection.cpp"
