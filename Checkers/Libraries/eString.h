// eString.h
// Public eString Library Entry Point
// By Joe Esposito


#pragma once



// Link Libraries
// ---------------

#ifndef _ESPO_NOLIB_ESTRING
# ifndef _DEBUG
#  pragma comment ( lib, "eString.lib" )            // eString library
# else
#  pragma comment ( lib, "eStringD.lib" )           // eString library [debug version]
# endif
#endif



// Library Options Macros
// -----------------------

#define eString_assert



// Include Library Headers
// ------------------------

#include ".\eString\eString.h"
