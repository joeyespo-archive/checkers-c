// ****************************************************************
// Esposoft C++ Array Collection class IMPLEMENTATION (v1.0.01)
// Created by Joey Esposito
//
// eCollection is a class that allows
// resizable vectors; any class array
// ****************************************************************


#pragma once



// Include Header
// ---------------

#include "Main.h"



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



// Define class eCollection Functions
// -----------------------------------

// Constructor/Destructor
// -----------------------

eColl_template
eColl::eCollection () : fn_free(free)
{
	m_Size = 0;
	m_ItemList = NULL;
}
eColl_template
eColl::eCollection (const eCollection &Coll) : fn_free(free)
{
	m_Size = Coll.m_Size;
	m_ItemList = new eColl_template_item * [m_Size];

	for (unsigned int i = 0; i < m_Size; i++)
		m_ItemList[i] = new eColl_template_item(*Coll.m_ItemList[i]);
}
/*eColl_template
eColl::eCollection (const unsigned int Size) : fn_free(free)
{
	m_Size = Size;
	m_ItemList = new eColl_template_item [m_Size];
}*/
eColl_template
eColl::eCollection (const unsigned int Size, eColl_template_item def_item) : fn_free(free)
{
	m_Size = Size;
	m_ItemList = new eColl_template_item * [m_Size];

	for (unsigned int i = 0; i < m_Size; i++)
	{ m_ItemList[i] = new eColl_template_item(def_item); }
}
eColl_template
eColl::eCollection (const eColl_template_item *Items, unsigned int Count ) : fn_free(free)
{
	m_Size = Count;
	m_ItemList = new eColl_template_item * [m_Size];

	for (unsigned int i = 0; i < m_Size; i++)
  { m_ItemList[i] = new eColl_template_item(Items[i]); }
}
eColl_template
eColl::eCollection (eColl_template_item DefItem) : fn_free(free)
{
	m_Size = 1;
	m_ItemList = new eColl_template_item * [1];

	m_ItemList[0] = new eColl_template_item(DefItem);
}
eColl_template
eColl::~eCollection ()
{ Clear(); }


// Overloaded Operators
// ---------------------

// Character Accessors with Index Checking
// (Retrieves a spacific item from eCollection)
eColl_template
eColl_template_item &eColl::operator [] (const unsigned int Offset)
{
	if ((Offset < 0) || (Offset >= m_Size) || (m_ItemList == NULL))
	{
		#ifdef cerr
		cerr<<"Index out of bounds (eCollection::operator []): "<<Offset<<endl;
		#endif
		#ifdef eCollection_assert
		assert(!((Offset < 0) || (Offset >= m_Size) || (m_ItemList == NULL)));
		#endif
	}

	return (*m_ItemList[Offset]);
}

// Assignment Operators
// ---------------------

eColl_template
const eColl &eColl::operator = (const eColl &coll)
{
	if (&coll == this)
		return *this;

	Clear();
	
	m_Size = coll.m_Size;
	m_ItemList = new eColl_template_item * [m_Size];
	
	for (unsigned int i = 0; i < m_Size; i++)
		m_ItemList[i] = new eColl_template_item(*coll.m_ItemList[i]);
	
	return *this;
}
eColl_template
const eColl &eColl::operator += (eColl_template_item value)
{
	unsigned int i;

	eColl_template_item **newItem;
	newItem = new eColl_template_item * [(m_Size + 1)];

	for (i = 0; i < m_Size; i++)
		newItem[i] = eColl_template_item(*m_ItemList[i]);
	
	newItem[i = m_Size] = new eColl_template_item(value);


	Clear();

	m_Size = (i + 1);
	m_ItemList = newItem;

	return *this;
}
eColl_template
const eColl &eColl::operator += (eColl &coll)
{
	unsigned int i;

	eColl_template_item **newItem;
	newItem = new eColl_template_item * [(m_Size + coll.m_Size)];

	for (i = 0; i < m_Size; i++)
		newItem[i] = eColl_template_item(*m_ItemList[i]);

	for (i = 0; i < coll.m_Size; i++)
		newItem[(i + m_Size)] = new eColl_template_item(*coll.m_ItemList[i]);
  
  i = m_Size;

  Clear();

  m_Size = (i + coll.m_Size);
	m_ItemList = newItem;

	return *this;
}

eColl_template
const eColl operator + (const eColl &coll1, const eColl &coll2)
{ return (eColl(coll1) += coll2); }

eColl_template
const bool eColl::operator == (const eColl_template_item &value)
{
	unsigned int i;
	
	for (i = 0; i < m_Size; i++)
		if ((*m_ItemList[i]) == value)
			return true;

	return false;
}

eColl_template
const bool eColl::operator == (const eCollection &coll)
{
	unsigned int i;

	if (&coll == this)
		return true;
	
	if (!(m_Size == coll.m_Size))
		return false;

	for (i = 0; i < m_Size; i++)
		if (!((*m_ItemList[i]) == (*coll.m_ItemList[i])))
			return false;

	return true;
}


// Added Functions
// -----------------

eColl_template
unsigned int eColl::Count () const
{ return m_Size; }

eColl_template
void eColl::AddList (const eColl_template_item *value, const unsigned int count)
{
	unsigned int i, t;
	unsigned int NewLen = (m_Size + count);
	eColl_template_item **NewList;

	NewList = new eColl_template_item * [NewLen];

	for (i = 0; i < m_Size; i++)
		NewList[i] = new eColl_template_item(*m_ItemList[i]);
	
  t = m_Size;
  
  Clear();
	
  for (i = 0; i < count; i++)
		NewList[(i + t)] = new eColl_template_item(value[i]);
	
	m_Size = NewLen;
	m_ItemList = NewList;
}


// General Accessors
// (Used to retrieve a certain item)
eColl_template
eColl_template_item &eColl::Item (const unsigned int ItemNum)
{
	if ((ItemNum < 0) || (ItemNum >= m_Size) || (m_ItemList == NULL))
	{
		#ifdef cerr
		cerr<<"Index out of bounds (eCollection::Item): "<<ItemNum<<endl;
		#endif
		#ifdef eCollection_assert
		assert(!((ItemNum < 0) || (ItemNum >= m_Size) || (m_ItemList == NULL)));
		#endif
	}

	return (*m_ItemList[ItemNum]);
}


// Resize Modifiers
// -----------------

// (Directly Resizes the Item List)
eColl_template
const eColl &eColl::Resize (const unsigned int NewSize)
{
	if (NewSize == m_Size)
		return *this;

	if (NewSize == 0)		// Resize to 0
	{ Clear(); }
	else					// Resize to any number greater than 0
	{
		if (m_Size == 0)	// Resize, from size 0
		{
      m_Size = NewSize;
			fn_free = free;
			
      m_ItemList = new eColl_template_item * [m_Size];
		}
		else		// Resize to any number, from any number
		{
			unsigned int i;
			eColl_template_item **eColl_new = new eColl_template_item * [NewSize];

			if (NewSize < m_Size)
				m_Size = NewSize;

			for (i = 0; i < m_Size; i++)
				eColl_new[i] = new eColl_template_item(*m_ItemList[i]);
			
			Clear();
			
      m_ItemList = eColl_new;
			m_Size = NewSize;
		}
	}

	return *this;
}
eColl_template
const eColl &eColl::Resize (const unsigned int NewSize, eColl_template_item DefItem)
{
	if (NewSize == m_Size)
		return *this;

	if (NewSize == 0)		// Resize to 0
  { Clear(); }
	else					// Resize to any number greater than 0
	{
		if (m_Size == 0)	// Resize, from size 0
		{
      m_Size = NewSize;
			fn_free = free;
			
      m_ItemList = new eColl_template_item * [m_Size];
			
			for (unsigned int i = 0; i < m_Size; i++)
				m_ItemList[i] = new eColl_template_item(DefItem);
		}
		else		// Resize to any number, from any number
		{
			unsigned int i, t;
			eColl_template_item **eColl_new = new eColl_template_item * [NewSize];
			
			if (NewSize < m_Size)
				m_Size = NewSize;

			for (i = 0; i < m_Size; i++)
				eColl_new[i] = eColl_template_item(*m_ItemList[i]);
      
      t = m_Size;
			
      Clear();
      
			m_ItemList = eColl_new;
			
			if (NewSize > t)
			{
				for (i = m_Size; i < NewSize; i++)
					m_ItemList[i] = new eColl_template_item(DefItem);
			}
			
			m_Size = NewSize;
		}
	}

	return *this;
}

// Add Modifier
// (Resizes to add another item)
eColl_template
const eColl &eColl::Add ()
{
	unsigned int i;
	eColl_template_item **eColl_new = new eColl_template_item * [(m_Size + 1)];

	for (i = 0; i < m_Size; i++)
		eColl_new[i] = eColl_template_item(*m_ItemList[i]);
  
  i = m_Size;

	Clear();
	
  m_ItemList = eColl_new;

	m_Size = (i + 1);

	return *this;
}
eColl_template
const eColl &eColl::Add (eColl_template_item Item, bool NoRepeats)
{
	unsigned int i, t, nc = 1;
	bool _add = true;

//	if (NoRepeats)
//		for (i = 0; i < m_Size; i++)
//		{ if (m_ItemList[i] == Item) { nc = 0; _add = false; i = m_Size; } }
			
	eColl_template_item **eColl_new = new eColl_template_item * [(m_Size + nc)];

	for (i = 0; i < m_Size; i++)
		eColl_new[i] = new eColl_template_item(*m_ItemList[i]);
  
  eColl_new[(t = m_Size)] = new eColl_template_item(Item);

	Clear();
	
  m_ItemList = eColl_new;
	m_Size = (t + nc);

	return *this;
}
eColl_template
const eColl &eColl::Add (const eColl_template_item *Items, unsigned int Count, bool NoRepeats)
{
	unsigned int i, i2, t;	bool _add;
	unsigned int c = Count;
	unsigned int nc = m_Size;

	eColl_template_item **eColl_new = new eColl_template_item * [(m_Size + c)];

	for (i = 0; i < m_Size; i++)
		eColl_new[i] = eColl_template_item(*m_ItemList[i]);

	for (i = m_Size; i < (m_Size + c); i++)
	{
		_add = true;
		if (NoRepeats)
			for (i2 = 0; i2 < i; i2++)
			{ if (eColl_new[i2] == Items[(i - m_Size)]) { _add = false; i2 = i; } }

		if (_add)
		{ eColl_new[nc++] = Items[(i - m_Size)]; }
	}

	t = m_Size;
  nc -= m_Size;

	Clear();
	
  m_Size = (t + nc);
	
  m_ItemList = eColl_new;

	return *this;
}

// Remove Modifier
// (Resizes to remove an item)
eColl_template
eColl_template_item eColl::Remove (const unsigned int Index)
{
  unsigned int i, t;
	
  if ((Index < 0) || (Index >= m_Size) || (m_ItemList == NULL))
	{
		#ifdef eCollection_assert
		assert(!((Index < 0) || (Index >= m_Size) || (m_ItemList == NULL)));
		#endif

		return (*m_ItemList[Index]);
	}


	eColl_template_item Removed(*m_ItemList[Index]);
  fn_free(m_ItemList[Index]);

	if ((--m_Size) == 0)
	{
		fn_free(m_ItemList);
		m_ItemList = NULL;
		return Removed;
	}

	eColl_template_item **eColl_new = new eColl_template_item * [m_Size];

	for (i = 0; i < Index; i++)
		eColl_new[i] = eColl_template_item(*m_ItemList[i]);

	for (i = (Index + 1); i <= m_Size; i++)
		eColl_new[(i - 1)] = m_ItemList[i];
  
  t = m_Size;
	
  Clear();
	
  m_ItemList = eColl_new;
  m_Size = t;

	return Removed;
}

eColl_template
void eColl::RemoveItems (eColl_template_item Item)
{
	for (int i = 0; i < m_Size; i++)
	{
		if (m_ItemList[i] == Item)
    { Remove(i); i--; }
	}
}


// Clear Modifier
// (Clears every item)
eColl_template
void eColl::Clear ()
{
	if (m_Size > 0)
  {
    for (unsigned int i = 0; i < m_Size; i++)
    { fn_free(m_ItemList[i]); }
    fn_free(m_ItemList);
  }
  
  m_Size = 0;
	m_ItemList = NULL;
  fn_free = free;
}

// Swap
// (Switches all Variables and values between an eCollection)
eColl_template
const eColl &eColl::Swap (const unsigned int Index1, const unsigned int Index2)
{
	eColl_template_item temp;

	temp = m_ItemList[Index1];
	m_ItemList[Index1] = m_ItemList[Index2];
	m_ItemList[Index2] = temp;
	
  return *this;
}


eColl_template
const eColl operator + (const eColl &Coll, const eColl_template_item Value)
{
	eColl Result(Coll);
  Result += Value;

	return Result;
}



// Free Variables
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
