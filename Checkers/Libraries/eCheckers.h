// eCheckersLib.h - eCheckers
// eCheckers Game Library Header File
// By Joey Esposito



// Library Macros
// ---------------

#if ( (!defined(ECHECKERS_INCLUDE)) && (!defined(ECHECKERS_SOURCE)) && (!defined(ECHECKERS_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( linker, "/defaultlib:eCheckersD.lib" )
#else
#pragma comment ( linker, "/defaultlib:eCheckers.lib" )
#endif
#endif

#ifdef ECHECKERS_INCLUDE
#include "eCheckers\Main.h"
#endif
#ifdef ECHECKERS_SOURCE
#define ECHECKERS_INCLUDE
#include "eCheckers\Main.cpp"
#endif





// Game Macros
// ------------

// Gameplay
#define CKGAME_UNAVAILABLE				0x0000		// Game result is not available (currently playing)
#define CKGAME_TEAMWINS					0x0001		// Team 'CKGAME_TEAMWINS+n' wins; n > 0, < 0xFFFF
#define CKGAME_TIE						0xFFFF		// Game result was a draw

// Game initialization
#define CKINIT_STARTGAME				0x01		// Starts the game immediately





#if ( (!defined(ECHECKERS_INCLUDE)) && (!defined(ECHECKERS_SOURCE)) && (!defined(_ECHECKERS_)) )

#define _ECHECKERS_


// Function Modifiers
// -------------------

// Handles declarers
#ifdef STRICT
#define DECLARE_CKHANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name;
#else
#define DECLARE_CKHANDLE(name) typedef void *name;
#endif

// Base theme object handle
DECLARE_CKHANDLE(HCKGAME);

#undef DECLARE_CKHANDLE


// Define function modifiers
#define ECALL			extern "C"
#define ESTDCALL		__stdcall



// Public Declarations
// --------------------

ECALL HCKGAME ESTDCALL CreateCkGame ();
ECALL BOOL ESTDCALL InitCkGameInfo ( HCKGAME lpckGame, LPCKRULES lpckRules );
ECALL BOOL ESTDCALL ClearCkGameInfo ( HCKGAME lpckGame );
ECALL BOOL ESTDCALL StartCkGame ( HCKGAME lpckGame );
ECALL BOOL ESTDCALL StopCkGame ( HCKGAME lpckGame );
ECALL BOOL ESTDCALL DestroyCkGame ( HCKGAME lpckGame );
ECALL LRESULT ESTDCALL SendCkMessage ( HCKGAME lpckGame, UINT uMsg, LPARAM lParam, WPARAM wParam );


#endif



// Free macros
// ------------

#undef ECALL
#undef ESTDCALL
