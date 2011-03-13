// Main.cpp - CCWindow
// Entry Point of Library
// By Joe Esposito

// !!!!! ToDo !!!!!
// 
// - CCFrame window messages
//   - Getting window handles (CCFM_GETCCCLIENT: wParam = hWnd (or ID, if CCFG_BYID was specified) for reference.. CCFG_SELF=0 [returns passed client], CCFG_FIRST, CCFG_LAST, CCFG_NEXT, CCFG_PREVIOUS, CCFG_BYID [passed an ID], CCFG_GETID [returns an ID])
// 
// - CCFrame
//   - Redrawing when changing active CCClient
//     - Erase only where the old window existed, and where the new window
//       now does not occupy.
//   - Scroll bars (using ColorSchemes)
// 
// !!!!!!!!!!!!!!!!


#pragma once



// Include Header
// ---------------

#include "Main.h"



// Library Source Files
// ---------------------------------------------------------------------------------

// Public Sources
// ---------------

// Control Container Window functions
#include "Public\CCWindow.cpp"		// Control Container Window functions
#include "Public\CCFrame.cpp"		// Control Container Frame functions
#include "Public\CCClient.cpp"		// Control Container Client functions



// Internal Sources
// -----------------

// Control Container Window functions
#include "Private\CCWnd.cpp"		// Control Container Window declarations
#include "Private\CCFProc.cpp"		// Control Container Frame window procedure
#include "Private\CCCProc.cpp"		// Control Container Client window procedure

// ---------------------------------------------------------------------------------



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
