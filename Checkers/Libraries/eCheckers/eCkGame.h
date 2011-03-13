// eCheckers.h - eCheckers
// eCheckers Game Header File
// By Joey Esposito


#pragma once



// Checkers Macros
// ----------------

// Game types
#define CKG_NOGAME						0x0000		// Game not started, or doesnt exist
#define CKG_TUTORIAL					0x0001		// Tutorial game (Settings are changable; Game stoppable: forcefully or not; Allows for human players to be able to view valid moves)
#define CKG_NORMAL						0x0002		// Normal game (Settings are changable; Game stoppable: forcefully or not)
#define CKG_ADVANCED					0x0003		// Advanced game (Settings are not changable; Game stoppable: forcefully or not)
#define CKG_TOURNAMENT					0x0004		// Tournament game (Settings are not changable; Game stoppable only by force)


// Gameplay
#define CKGAME_UNAVAILABLE				0x0000		// Game result is not available (currently playing)
#define CKGAME_TEAMWINS					0x0001		// Team 'CKGAME_TEAMWINS+n' wins; n > 0, < 0xFFFF
#define CKGAME_TIE						0xFFFF		// Game result was a draw


// Ranks
#define CKR_PAWN						0x0001
#define CKR_KING						0x0002


// PickUpCkPiece()
// ---------------
#define CK_ERROR						0x0000
#define CK_NOPICKUP						0x0001
#define CK_WRONGTEAM					0x0002
#define CK_PICKEDUP						0x0003


// DropCkPiece()
// --------------
// Move error
#define CK_ERROR						0x0000		// Game error (word = 0)

// Move types
#define CK_ILLEGALMOVE					0x0000		// Illegal move (check status for reason)
#define CK_MOVE							0x0001		// Single move
#define CK_JUMP							0x0002		// Single jump
#define CK_MULTIJUMP					0x0003		// Multi jump

// Move status (moved)								// _** OK MOVE **_
#define CK_KINGED						0x0100		// Kinged (piece was moved to opposite side)
#define CK_ENDGAME						0x0200		// Game was ended: only one team remains
// Move status (illegal move)						// _** CK_ILLEGALMOVE **_
#define CK_BADMOVE						0x0100		// Illegal move (bit always on with CK_ILLEGALMOVE)
#define CK_MUSTJUMP						0x0200		// Couldnt move because of an open jump

// Move masks
#define CKM_MOVE						0x00FF		// Move result
#define CKM_STATUS						0x0F00		// Move status



// Constants
// ----------

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif



// Struct Declarations
// --------------------

struct _ECKGAME; typedef _ECKGAME ECKGAME, *LPECKGAME;
struct _ECKCONFIG; typedef _ECKCONFIG ECKCONFIG, *LPECKCONFIG;
struct _ECKGAMEPLAY; typedef _ECKGAMEPLAY ECKGAMEPLAY, *LPECKGAMEPLAY;
struct _ECKRULES; typedef _ECKRULES ECKRULES, *LPECKRULES;
struct _ECKPLAYER; typedef _ECKPLAYER ECKPLAYER, *LPECKPLAYER;
struct _ECKPIECE; typedef _ECKPIECE ECKPIECE, *LPECKPIECE;



// Local typedefs
// ---------------

typedef unsigned long       DWORD;
typedef unsigned int		UINT;
typedef long				LONG;
typedef int					INT;
typedef int					BOOL;
typedef LONG				CKRESULT;



// Public Structs
// ---------------

typedef struct _CKRULES
{
	bool bP2First1;			// Player 2 has first move !!!!! look in rule book for who goes first etc
	bool bIgnoreMustJump;	// If you can ignore the 'must jump' rule
} CKRULES, *LPCKRULES;



// Internal Structs
// -----------------

// Player structure
typedef struct _ECKPIECE
{
	LPECKGAME lpGame;						// Pointer to the owner game
	DWORD dwId;								// Piece ID
	UINT uTeam;								// Team number
	INT row;								// Current row
	INT col;								// Current column
	DWORD dwStatus;							// Piece status (rank, etc)
} ECKPIECE, *LPECKPIECE;

// Player structure
typedef struct _ECKPLAYER
{
	UINT nPieces;							// Number of pieces
	LPECKPIECE *lpaPieces;					// Pointer to an array of player piece pointers
} ECKPLAYER, *LPECKPLAYER;

// Game rules structure
typedef struct _ECKRULES
{
	union {
		unsigned char bP2First : 1;			// Player 2 has first move !!!!! look in rule book for who goes first etc
		unsigned char bIgnoreMustJump : 1;	// If you can ignore the 'must jump' rule
		
		unsigned char nRules;				// Rules [bits]
	};
} ECKRULES, *LPECKRULES;

// GamePlay structure
typedef struct _ECKGAMEPLAY
{
	UINT uGameType;							// Game type
	ECKRULES ckRules;						// [Additional] game rules
	INT nTeams;								// Number of teams
	LPECKPLAYER *lpackTeams;				// Teams [players]
	LPECKPIECE lpaPieces[8][8];				// An array of pointers to pieces set on the board
	UINT uTurn;								// 0 - Not playing; 1 - p1's turn; 2 - p2's turn
	LPECKPIECE lpHolding;					// Piece being held; NULL - Nothing held
	LPUINT lpGameResult;					// Game result
} ECKGAMEPLAY, *LPECKGAMEPLAY;

// Game structure
typedef struct _ECKGAME
{
	LPECKGAMEPLAY lpckGame;					// Gameplay information (after game was set up)
} ECKGAME, *LPECKGAME;



// Public Declarations
// --------------------

ECALL HECKGAME ESTDCALL CreateCkGame ();
ECALL BOOL ESTDCALL DestroyCkGame ( HECKGAME lpckGame );
ECALL BOOL ESTDCALL IsCkGame ( HECKGAME lpckGame );
ECALL BOOL ESTDCALL InitCkGameInfo ( HECKGAME lpckGame, LPCKRULES lpckRules );
ECALL BOOL ESTDCALL ClearCkGameInfo ( HECKGAME lpckGame );
ECALL BOOL ESTDCALL StartCkGame ( HECKGAME lpckGame );
ECALL BOOL ESTDCALL StopCkGame ( HECKGAME lpckGame );
ECALL DWORD ESTDCALL GetCkPeiceId ( HECKGAME lpckGame, INT row, INT column ); // Returns the player whose piece is on the specified board position



// Implementation File:
// "eCheckers.cpp"
