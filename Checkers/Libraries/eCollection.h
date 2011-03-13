// eCollection.h
// Public eCollection Library Entry Point
// By Joe Esposito


#pragma once



// Link Libraries
// ---------------

#ifndef _ESPO_NOLIB_ECOLLECTION
# ifndef _DEBUG
#  pragma comment ( lib, "eCollection.lib" )        // eCollection library
# else
#  pragma comment ( lib, "eCollectionD.lib" )       // eCollection library [debug version]
# endif
#endif



// Library Options Macros
// -----------------------

#define eCollection_templates     // !!!!! ??
#define eCollection_no_eString
#define eCollection_assert



// Include Library Headers
// ------------------------

#ifndef _ESPO_ECOLLECTION_SOURCE
# include ".\eCollection\eCollection.h"
#else
# include ".\eCollection\eCollection.cpp"
#endif