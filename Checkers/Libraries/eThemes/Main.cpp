// Main.cpp
// Entry Point of Library
// By Joe Esposito


// !!!!! ToDo !!!!!
// ----------------------------------------------------------
// 
// - Buttons: -REMOVE- temp bitmap and bitblt onto the DC for no flicker
// - Add more items in DrawSchemeItem()
// - Finish DrawEdge()
// 
// ----------------------------------------------------------


#pragma once



// Include Header
// ---------------

#include "Main.h"



// Library Source Files
// ----------------------------------------------------------------------

// Public Sources
// ---------------

// Theme objects
#include "Public\eTheme.cpp"			// eTheme object
#include "Public\eScheme.cpp"			// eScheme object

// Scheme objects
#include "Public\eUserScheme.cpp"		// eUserScheme object
#include "Public\eColorScheme.cpp"		// eColorScheme object
#include "Public\ColorFunctions.cpp"	// eColorScheme functions



// Internal Sources
// -----------------

// Theme objects
#include "Private\Themes.cpp"			// Internal theme object
#include "Private\Schemes.cpp"			// Internal scheme object

// Scheme objects
#include "Private\UserSchemes.cpp"		// Internal user scheme object
#include "Private\ColorSchemes.cpp"		// Internal color scheme object

// ----------------------------------------------------------------------



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
#undef HETHEME
#undef HESCHEME
#undef HETHEMEOBJ
