// eCheckers.cpp - eCheckers
// eCheckers Game Implementation File
// By Joey Esposito


// !!!!! ToDo !!!!!
// 
// - Type of game for settings:
//   - Tutorial (less strict rules)
//   - Normal game (normal rules)
//   - Tornament (Very strict rules)
// 
// - Jumps (multi-jumps)
// 

// 
//   N
// W x E   <-- Point of reference: N+forward = N, N+backward = S
//   S                             S+forward = S, S+backward = N
// 


#pragma once



// Local declarations, macros, and tables
// ---------------------------------------

// Declarations
LOCAL LPECKPIECE GetPieceFromId ( LPECKGAME lpckGame, DWORD dwId );
LOCAL UINT _DropPiece ( LPECKGAME lpckGame, INT row, INT col, UINT *lpuJumped, BOOL bQueryDrop );
LOCAL BOOL _SetWinner ( LPECKGAME lpckGame, BOOL bQueryWinner );
LOCAL INT _TurnPOV ( INT nStatus, INT nRotAngle );
LOCAL BOOL _DeletePiece ( LPECKPIECE lpckPiece );


// Macros
#define CKF_FORWARDN					0x00000000
#define CKF_FORWARDE					0x00000001
#define CKF_FORWARDS					0x00000002
#define CKF_FORWARDW					0x00000003
#define CKFM_POV						0x0000000F		// Point of view mask
#define	CKF_DIRFL						0x00000100
#define	CKF_DIRFR						0x00000200
#define	CKF_DIRBR						0x00000400
#define	CKF_DIRBL						0x00000800
#define CKFM_DIRECTION					0x0000FF00		// Allowed direction mask
#define CKF_PAWN						(CKF_DIRFL | CKF_DIRFR)
#define CKF_KING						(CKF_DIRFL | CKF_DIRFR | CKF_DIRBL | CKF_DIRBR)
#define CKFM_RANK						CKFM_DIRECTION	// Rank mask
#define CKF_PROMOTEOPP					0x00010000		// Piece receives a promotoin when reached the opposite side
#define CKFM_FLAGS						0x00000000		// Piece flags mask

// Max definitions
#define	GCKL_LAST						0x00000010
#define	CKG_HIGHEST						CKG_TOURNAMENT
#define CKGAME_PLAYING					CKGAME_UNAVAILABLE

// Game definitions
#define CK_BOARDWIDTH					8
#define CK_BOARDHEIGHT					8
#define CK_STARTPIECES					12
#define CK_STARTTEAMS					2
#define CK_MAXTEAMS						2


// Tables
static const DWORD _CkBoardSetup[CK_STARTTEAMS][CK_STARTPIECES] =	// [team][piece (id)] .. row = LOWORD(), col = HIWORD()
	{	{ 0x00020008, 0x00040008, 0x00060008, 0x00080008,  0x00010007, 0x00030007, 0x00050007, 0x00070007,  0x00020006, 0x00040006, 0x00060006, 0x00080006 },
		{ 0x00010001, 0x00030001, 0x00050001, 0x00070001,  0x00020002, 0x00040002, 0x00060002, 0x00080002,  0x00010003, 0x00030003, 0x00050003, 0x00070003 }	};
static const DWORD _CkBoardStatus[CK_STARTTEAMS][CK_STARTPIECES] =	// [team][piece (id)] .. piece status table
	{	{ 0x00010300, 0x00010300, 0x00010300, 0x00010300,  0x00010300, 0x00010300, 0x00010300, 0x00010300,  0x00010300, 0x00010300, 0x00010300, 0x00010300 },
		{ 0x00010302, 0x00010302, 0x00010302, 0x00010302,  0x00010302, 0x00010302, 0x00010302, 0x00010302,  0x00010302, 0x00010302, 0x00010302, 0x00010302 }	};



// Game Information Functions
// ---------------------------

// Creates a checkers game object
HECKGAME ESTDCALL CreateCkGame ()
{
	LPECKGAME lpckGame;
	
	if ((lpckGame = new ECKGAME) == NULL) return NULL;


	// Game non-play config
	lpckGame->lpckGame = NULL;	// Game was not yet set up

	// !!!!! Add game to game array

	return (HECKGAME)lpckGame;
}

// Destroys a checkers game object
BOOL ESTDCALL DestroyCkGame (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) { delete ((LPECKGAME)hckGame); return TRUE; }
	
	// Stop game first
	if (((LPECKGAME)hckGame)->lpckGame->lpGameResult)
		StopCkGame((HECKGAME)hckGame);

	// Destroy game info
	ClearCkGameInfo((HECKGAME)hckGame);

	// Delete game
	delete ((LPECKGAME)hckGame);

	return TRUE;	// Success
}

BOOL ESTDCALL IsCkGame (HECKGAME hckGame)
{
	// !!!!! Check game array
	if (!(LPECKGAME)hckGame) return FALSE;
	return TRUE;
}

// Initializes the game and rules
BOOL ESTDCALL InitCkGameInfo (HECKGAME hckGame, LPCKRULES lpckRules)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (((LPECKGAME)hckGame)->lpckGame) {
		if ((((LPECKGAME)hckGame)->lpckGame->lpGameResult) && (*((LPECKGAME)hckGame)->lpckGame->lpGameResult == CKGAME_PLAYING)) return FALSE;
		delete ((LPECKGAME)hckGame)->lpckGame;		// Overwrite old data, if exists
	}

	
	// Create game info
	if ((((LPECKGAME)hckGame)->lpckGame = new ECKGAMEPLAY) == NULL) return FALSE;

	
	// Initialize rules
	((LPECKGAME)hckGame)->lpckGame->ckRules.nRules = 0;
	
	// Set custom rules
	if (lpckRules)
	{
		((LPECKGAME)hckGame)->lpckGame->ckRules.bP2First = lpckRules->bP2First1;
		((LPECKGAME)hckGame)->lpckGame->ckRules.bIgnoreMustJump = lpckRules->bIgnoreMustJump;
	}
	

	// Set game data
	((LPECKGAME)hckGame)->lpckGame->uGameType = CKG_NOGAME;	// No game type
	((LPECKGAME)hckGame)->lpckGame->lpGameResult = NULL;	// Result unavailable
	((LPECKGAME)hckGame)->lpckGame->uTurn = 0;				// Not playing just yet
	((LPECKGAME)hckGame)->lpckGame->lpHolding = NULL;		// Not holding anything


	// Teams
	((LPECKGAME)hckGame)->lpckGame->nTeams = CK_STARTTEAMS;	// Start with maximum teams
	((LPECKGAME)hckGame)->lpckGame->lpackTeams = NULL;		// Initialized teams when game starts

	return TRUE;
}

// Clears the game and resets the rules
BOOL ESTDCALL ClearCkGameInfo (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return TRUE;
	if ((((LPECKGAME)hckGame)->lpckGame->lpGameResult) && (*((LPECKGAME)hckGame)->lpckGame->lpGameResult == CKGAME_PLAYING)) return FALSE;

	// Clean up
	if (((LPECKGAME)hckGame)->lpckGame->lpGameResult) delete ((LPECKGAME)hckGame)->lpckGame->lpGameResult;
	delete ((LPECKGAME)hckGame)->lpckGame;

	return TRUE;
}

// Starts the game (must already be initialized)
BOOL ESTDCALL StartCkGame (HECKGAME hckGame, UINT uGameType)
{
	LPECKPIECE *lpackPieces;
	LPECKPIECE lpckPiece;
	INT t, ct, i; UINT n;
	DWORD dwId;

	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if ((((LPECKGAME)hckGame)->lpckGame->lpGameResult) && (*((LPECKGAME)hckGame)->lpckGame->lpGameResult == CKGAME_PLAYING)) return FALSE;
	if ((uGameType <= CKG_NOGAME) || (uGameType > CKG_HIGHEST)) return FALSE;


	// Game status
	if ((((LPECKGAME)hckGame)->lpckGame->lpGameResult = new UINT) == NULL) return FALSE;
	(*((LPECKGAME)hckGame)->lpckGame->lpGameResult) = CKGAME_PLAYING;

	// Setup game data
	((LPECKGAME)hckGame)->lpckGame->uGameType = uGameType;		// Set game type
	((LPECKGAME)hckGame)->lpckGame->uTurn = ((((LPECKGAME)hckGame)->lpckGame->ckRules.bP2First)?(2):(1));
	((LPECKGAME)hckGame)->lpckGame->lpHolding = NULL;			// Not holding any pieces yet

	
	// Set up teams and pieces
	// ------------------------

	// Initialize gameboard
	for (i = 0; i < CK_BOARDWIDTH; i++) for (t = 0; t < CK_BOARDHEIGHT; t++)
	{ ((LPECKGAME)hckGame)->lpckGame->lpaPieces[i][t] = NULL; }

	// Create team array
	if ( (ct = ((LPECKGAME)hckGame)->lpckGame->nTeams) > CK_MAXTEAMS ) return FALSE;
	((LPECKGAME)hckGame)->lpckGame->lpackTeams = new LPECKPLAYER [(ct)];
	
	for (t = 0; t < ct; t++)
	{	
		// Create the team
		if ((((LPECKGAME)hckGame)->lpckGame->lpackTeams[t] = new ECKPLAYER) == NULL) goto BadCkStart;
		
		// Create the pieces
		((LPECKGAME)hckGame)->lpckGame->lpackTeams[t]->nPieces = 0;
		if ((lpackPieces = (((LPECKGAME)hckGame)->lpckGame->lpackTeams[t]->lpaPieces = new LPECKPIECE [12])) == NULL) goto BadCkStart;

		// Initialize pieces
		for (i = 0, dwId = 0; i < CK_STARTPIECES; i++, dwId++)
		{
			if ((lpackPieces[i] = new ECKPIECE) == NULL) goto BadCkStart;
			((LPECKGAME)hckGame)->lpckGame->lpackTeams[t]->nPieces++;
			
			lpckPiece = lpackPieces[i];
			lpckPiece->lpGame = ((LPECKGAME)hckGame);
		
			lpckPiece->dwId = (dwId-1); 
			lpckPiece->uTeam = (t+1);
			lpckPiece->dwStatus = ((_CkBoardStatus[t][dwId] & (~CKFM_DIRECTION)) | 1);
			lpckPiece->row = HIWORD(_CkBoardSetup[t][dwId]);
			lpckPiece->col = LOWORD(_CkBoardSetup[t][dwId]);

			((LPECKGAME)hckGame)->lpckGame->lpaPieces[(lpckPiece->row-1)][(lpckPiece->col-1)] = lpckPiece;
		}
	} return TRUE;


BadCkStart:

	delete ((LPECKGAME)hckGame)->lpckGame->lpGameResult;
	
	for (i = 0; i < ct; i++)
	{
		if (((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->lpaPieces) {
			for (n = 0; n < ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->nPieces; n++)
			{ delete ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->lpaPieces[n]; }
			delete [((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->nPieces] ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->lpaPieces;
		}
		delete ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i];
	} delete [ct] ((LPECKGAME)hckGame)->lpckGame->lpackTeams; ((LPECKGAME)hckGame)->lpckGame->lpackTeams = NULL;

	return FALSE;
}

// Stops the game
BOOL ESTDCALL StopCkGame (HECKGAME hckGame)
{
	int i, ct;

	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;

	// Delete players
	ct = ((LPECKGAME)hckGame)->lpckGame->nTeams;
	for (i = 0; i < ct; i++)
	{
		if (((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->lpaPieces) delete [((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->nPieces] ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i]->lpaPieces;
		delete ((LPECKGAME)hckGame)->lpckGame->lpackTeams[i];
	} delete [ct] ((LPECKGAME)hckGame)->lpckGame->lpackTeams; ((LPECKGAME)hckGame)->lpckGame->lpackTeams = NULL;

	delete ((LPECKGAME)hckGame)->lpckGame->lpGameResult;	// Not playing
	((LPECKGAME)hckGame)->lpckGame->lpGameResult = NULL;

	return TRUE;	// Success
}





// Game Control Functions
// -----------------------

// Returns if the game was started or not (game can either be playing, or a winner was decided, for this to be true)
BOOL ESTDCALL StartedCkGame (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;

	return TRUE;
}

// Returns if the game is playing or not
BOOL ESTDCALL IsPlayingCkGame (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;
	if ((*((LPECKGAME)hckGame)->lpckGame->lpGameResult) != CKGAME_PLAYING) return FALSE;

	return TRUE;
}

// Returns the game result
UINT ESTDCALL GetCkGameResult (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;

	return (*((LPECKGAME)hckGame)->lpckGame->lpGameResult);
}

// Returns the game type
UINT ESTDCALL GetCkGameType (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;

	return ((LPECKGAME)hckGame)->lpckGame->uGameType;
}

// Returns if the piece exists on the board at a given pos
BOOL ESTDCALL IsCkPeice (HECKGAME hckGame, INT row, INT column)
{
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;

	
	// Get the piece and return its id
	return (((LPECKGAME)hckGame)->lpckGame->lpaPieces[(row-1)][(column-1)] != NULL);
}
// Returns if the piece exists, given its id
BOOL ESTDCALL IsCkPeiceId (HECKGAME hckGame, DWORD dwId)
{
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;

	
	// Get the piece and return its id
	return (GetPieceFromId((LPECKGAME)hckGame, dwId) != NULL);
}

// Returns the piece's id of the piece on the specified board position
DWORD ESTDCALL GetCkPeiceId (HECKGAME hckGame, INT row, INT column)
{
	LPECKPIECE lpckPiece;
	
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return FALSE;

	
	// Get the piece and return its id
	if ((lpckPiece = ((LPECKGAME)hckGame)->lpckGame->lpaPieces[(row-1)][(column-1)]) == NULL) return 0;
	return lpckPiece->dwId;
}


// Returns the team number whose piece is on the specified board position
DWORD ESTDCALL GetCkPieceTeam (HECKGAME hckGame, INT row, INT column)
{
	LPECKPIECE lpckPiece;
	
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return FALSE;


	// Get the piece and return its team
	if ((lpckPiece = ((LPECKGAME)hckGame)->lpckGame->lpaPieces[(row-1)][(column-1)]) == NULL) return 0;
	return lpckPiece->uTeam;
}
// Returns the piece's player team whose piece's id matches the specified id
DWORD ESTDCALL GetCkPieceIdTeam (HECKGAME hckGame, DWORD dwId)
{
	LPECKPIECE lpckPiece;

	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;


	// Get the piece and return its team
	if ((lpckPiece = GetPieceFromId((LPECKGAME)hckGame, dwId)) == NULL) return 0;
	return lpckPiece->uTeam;
}

// Returns the position of a piece by its id
LONG ESTDCALL GetCkPiecePos (HECKGAME hckGame, DWORD dwId)
{
	LPECKPIECE lpckPiece;

	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;


	// Get the piece and return its team
	if ((lpckPiece = GetPieceFromId((LPECKGAME)hckGame, dwId)) == NULL) return 0;
	return MAKELONG(lpckPiece->row, lpckPiece->col);
}


// Returns the rank of the piece on the specified board position
UINT ESTDCALL GetCkPieceRank (HECKGAME hckGame, INT row, INT column)
{
	LPECKPIECE lpckPiece;
	
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return FALSE;


	// Get the piece and return its team
	if ((lpckPiece = ((LPECKGAME)hckGame)->lpckGame->lpaPieces[(row-1)][(column-1)]) == NULL) return 0;
	return (  ((lpckPiece->dwStatus & CKF_KING) == CKF_KING)?(CKR_KING):( (((lpckPiece->dwStatus & CKF_PAWN) == CKF_PAWN)?(CKR_PAWN):(0)) )  );
}
// Returns the piece's rank whose piece's id matches the specified id
UINT ESTDCALL GetCkPieceIdRank (HECKGAME hckGame, DWORD dwId)
{
	LPECKPIECE lpckPiece;

	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;


	// Get the piece and return its team
	if ((lpckPiece = GetPieceFromId((LPECKGAME)hckGame, dwId)) == NULL) return 0;
	return (  ((lpckPiece->dwStatus & CKF_KING) == CKF_KING)?(CKR_KING):( (((lpckPiece->dwStatus & CKF_PAWN) == CKF_PAWN)?(CKR_PAWN):(0)) )  );
}

// Picks up the piece on the specified board position
UINT ESTDCALL PickUpCkPiece (HECKGAME hckGame, INT row, INT column)
{
	LPECKPIECE lpckPiece;
	
	if (!IsCkGame(hckGame)) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return CK_ERROR;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return CK_ERROR;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return CK_NOPICKUP;

	// Get the piece
	if ((lpckPiece = ((LPECKGAME)hckGame)->lpckGame->lpaPieces[(row-1)][(column-1)]) == NULL) return CK_NOPICKUP;
	if (((LPECKGAME)hckGame)->lpckGame->uTurn != lpckPiece->uTeam) return CK_WRONGTEAM;

	((LPECKGAME)hckGame)->lpckGame->lpHolding = lpckPiece;
	return CK_PICKEDUP;
}
// Picks up the piece whose piece's id matches the specified id, if allowed
BOOL ESTDCALL PickUpCkPieceId (HECKGAME hckGame, DWORD dwId)
{
	LPECKPIECE lpckPiece;

	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return FALSE;

	// Get the piece
	if ((lpckPiece = GetPieceFromId((LPECKGAME)hckGame, dwId)) == NULL) return FALSE;
	((LPECKGAME)hckGame)->lpckGame->lpHolding = lpckPiece;
	return TRUE;
}

// Returns the original position of the piece currently being held
LONG ESTDCALL GetCkHeldPiecePos (HECKGAME hckGame)
{
	LPECKPIECE lpckPiece;

	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return 0;


	// Get the piece and return its position
	if ((lpckPiece = ((LPECKGAME)hckGame)->lpckGame->lpHolding) == NULL) return 0;
	return MAKELONG(lpckPiece->row, lpckPiece->col);
}

// Returns if a piece is currently being held of not
BOOL ESTDCALL IsCkHeldPiece (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return FALSE;

	
	// Check holding pointer
	return (((LPECKGAME)hckGame)->lpckGame->lpHolding != NULL);
}
BOOL ESTDCALL IsCkHeldPiecePos (HECKGAME hckGame, INT row, INT column)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return FALSE;

	
	// Check holding pointer
	if (((LPECKGAME)hckGame)->lpckGame->lpHolding) return ( (((LPECKGAME)hckGame)->lpckGame->lpHolding->row == row) && (((LPECKGAME)hckGame)->lpckGame->lpHolding->col == column) );
	return FALSE;
}
DWORD ESTDCALL IsCkHeldPieceId (HECKGAME hckGame, DWORD dwId)
{
	if (!IsCkGame(hckGame)) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame) return FALSE;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return FALSE;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return FALSE;

	
	// Check holding pointer
	if (((LPECKGAME)hckGame)->lpckGame->lpHolding) return (((LPECKGAME)hckGame)->lpckGame->lpHolding->dwId == dwId);
	return FALSE;
}

// Returns the piece being held's id [0 if nothing being held]
DWORD ESTDCALL GetCkHeldPieceId (HECKGAME hckGame)
{
	if (!IsCkGame(hckGame)) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame) return 0;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return 0;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return 0;

	
	// Check holding pointer
	if (((LPECKGAME)hckGame)->lpckGame->lpHolding) return ((LPECKGAME)hckGame)->lpckGame->lpHolding->dwId;
	return 0;
}

// Drops the piece that is currently being held (returns TRUE -only- if moved)
UINT ESTDCALL DropCkPiece (HECKGAME hckGame, INT row, INT column, UINT *lpuJumped)
{
	UINT uResult;

	if (!IsCkGame(hckGame)) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return CK_ERROR;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return CK_ERROR;
	if ( ((row < 0) || (row > CK_BOARDHEIGHT)) || ((column < 0) || (column > CK_BOARDWIDTH)) ) return (CK_ILLEGALMOVE | CK_BADMOVE);


	// Move piece
	if ((((uResult = _DropPiece((LPECKGAME)hckGame, row, column, lpuJumped, FALSE)) & CKM_MOVE) == CK_ILLEGALMOVE) || (uResult == CK_ERROR))
	{ ((LPECKGAME)hckGame)->lpckGame->lpHolding = NULL; return FALSE; }

	// Update game settings
	if ((++((LPECKGAME)hckGame)->lpckGame->uTurn) > CK_MAXTEAMS) ((LPECKGAME)hckGame)->lpckGame->uTurn = 1;
	((LPECKGAME)hckGame)->lpckGame->lpHolding = NULL;

	return uResult;
}

// Returns whether or not the move is valid
UINT ESTDCALL IsValidCkDrop (HECKGAME hckGame, INT row, INT column)
{
	if (!IsCkGame(hckGame)) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return CK_ERROR;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return CK_ERROR;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return (CK_ILLEGALMOVE | CK_BADMOVE);

	return ((_DropPiece((LPECKGAME)hckGame, row, column, NULL, TRUE) & CKM_MOVE) != 0);
}

// Returns whether the move's status, when dropped
UINT ESTDCALL GetCkDropStatus (HECKGAME hckGame, INT row, INT column)
{
	if (!IsCkGame(hckGame)) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame) return CK_ERROR;
	if (!((LPECKGAME)hckGame)->lpckGame->lpGameResult) return CK_ERROR;
	if (*((LPECKGAME)hckGame)->lpckGame->lpGameResult != CKGAME_PLAYING) return CK_ERROR;
	if ( ((row <= 0) || (row > CK_BOARDHEIGHT)) || ((column <= 0) || (column > CK_BOARDWIDTH)) ) return (CK_ILLEGALMOVE | CK_BADMOVE);

	return _DropPiece((LPECKGAME)hckGame, row, column, NULL, TRUE);
}



// Local Functions
// ----------------

// Returns the piece the matches the given ID
LOCAL LPECKPIECE GetPieceFromId (LPECKGAME lpckGame, DWORD dwId)
{
	UINT i; INT t, ct;
	LPECKPLAYER lpckPlayer;

	ct = lpckGame->lpckGame->nTeams;
	for (t = 0; t < ct; t++) {
		lpckPlayer = lpckGame->lpckGame->lpackTeams[t];
		
		for (i = 0; i < lpckPlayer->nPieces; i++)
		{ if (lpckPlayer->lpaPieces[i]->dwId == dwId) return (lpckPlayer->lpaPieces[i]); }
	}

	return NULL;
}

// Returns the action taken (or would have been taken)
LOCAL UINT _DropPiece (LPECKGAME lpckGame, INT row, INT col, UINT *lpuJumped, BOOL bQueryDrop)
{
	LPECKPIECE lpckOriginalPiece;
	LPECKPIECE lpckPieceTemp;
	UINT uJumped;
	UINT uDirRef;
	UINT uStatus;
	UINT uResult;
	INT maxRow, maxCol;		// Maximum width and height (-1 = none)

	// Failsafe
	if ((lpckOriginalPiece = lpckGame->lpckGame->lpHolding) == NULL) return (CK_ILLEGALMOVE | CK_BADMOVE);
	if ((lpckOriginalPiece->row == row) && (lpckOriginalPiece->col == col)) return (CK_ILLEGALMOVE | CK_BADMOVE);
	if ((row == 0) || (col == 0)) return (CK_ILLEGALMOVE | CK_BADMOVE);
	if (lpckGame->lpckGame->lpaPieces[(row-1)][(col-1)]) return (CK_ILLEGALMOVE | CK_BADMOVE);


	// Initialize data
	uStatus = (lpckOriginalPiece->dwStatus);
	
	if ((uStatus & CKFM_POV) == CKF_FORWARDN) { maxRow = 1; maxCol = 0; }
	else if ((uStatus & CKFM_POV) == CKF_FORWARDS) { maxRow = CK_BOARDHEIGHT; maxCol = 0; }
	else if ((uStatus & CKFM_POV) == CKF_FORWARDE) { maxRow = 0; maxCol = 1; }
	else if ((uStatus & CKFM_POV) == CKF_FORWARDW) { maxRow = 0; maxCol = CK_BOARDWIDTH; }
	else { maxRow = -1; maxCol = -1; }

	uResult = 0;
	uJumped = 0;
	
	uDirRef = _TurnPOV(uStatus, (uStatus & CKFM_POV));

	// !!!!! Test for an available jump for 'must jump' option; return (CK_MUSTJUMP)

	// Test single move
	if (((lpckOriginalPiece->row-1) == row) && ((lpckOriginalPiece->col-1) == col))
	{ if (!(uDirRef & CKF_DIRFL)) return (CK_ILLEGALMOVE | CK_BADMOVE); }
	else if (((lpckOriginalPiece->row-1) == row) && ((lpckOriginalPiece->col+1) == col)) // NW
	{ if (!(uDirRef & CKF_DIRFR)) return (CK_ILLEGALMOVE | CK_BADMOVE); }
	else if (((lpckOriginalPiece->row+1) == row) && ((lpckOriginalPiece->col-1) == col)) // SE
	{ if (!(uDirRef & CKF_DIRBL)) return (CK_ILLEGALMOVE | CK_BADMOVE); }
	else if (((lpckOriginalPiece->row+1) == row) && ((lpckOriginalPiece->col+1) == col)) // SW
	{ if (!(uDirRef & CKF_DIRBR)) return (CK_ILLEGALMOVE | CK_BADMOVE); }

	// Test single jump
	
	else if (((lpckOriginalPiece->row-2) == row) && ((lpckOriginalPiece->col-2) == col))
	{
		if (!(uDirRef & CKF_DIRFL)) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if ((lpckPieceTemp = lpckGame->lpckGame->lpaPieces[(lpckOriginalPiece->row-2)][(lpckOriginalPiece->col-2)]) == NULL) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (lpckPieceTemp->uTeam == lpckOriginalPiece->uTeam) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (!bQueryDrop) { if (!_DeletePiece(lpckPieceTemp)) return (CK_ERROR); }
		uJumped += 1;
	}
	else if (((lpckOriginalPiece->row-2) == row) && ((lpckOriginalPiece->col+2) == col)) // NW
	{
		if (!(uDirRef & CKF_DIRFR)) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if ((lpckPieceTemp = lpckGame->lpckGame->lpaPieces[(lpckOriginalPiece->row-2)][(lpckOriginalPiece->col)]) == NULL) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (lpckPieceTemp->uTeam == lpckOriginalPiece->uTeam) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (!bQueryDrop) { if (!_DeletePiece(lpckPieceTemp)) return (CK_ERROR); }
		uJumped += 1;
	}
	else if (((lpckOriginalPiece->row+2) == row) && ((lpckOriginalPiece->col-2) == col)) // SE
	{
		if (!(uDirRef & CKF_DIRBL)) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if ((lpckPieceTemp = lpckGame->lpckGame->lpaPieces[(lpckOriginalPiece->row)][(lpckOriginalPiece->col-2)]) == NULL) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (lpckPieceTemp->uTeam == lpckOriginalPiece->uTeam) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (!bQueryDrop) { if (!_DeletePiece(lpckPieceTemp)) return (CK_ERROR); }
		uJumped += 1;
	}
	else if (((lpckOriginalPiece->row+2) == row) && ((lpckOriginalPiece->col+2) == col)) // SW
	{
		if (!(uDirRef & CKF_DIRBR)) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if ((lpckPieceTemp = lpckGame->lpckGame->lpaPieces[(lpckOriginalPiece->row)][(lpckOriginalPiece->col)]) == NULL) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (lpckPieceTemp->uTeam == lpckOriginalPiece->uTeam) return (CK_ILLEGALMOVE | CK_BADMOVE);
		if (!bQueryDrop) { if (!_DeletePiece(lpckPieceTemp)) return (CK_ERROR); }
		uJumped += 1;
	}

	// !!!!! (multi-jumping)

	else
	{ return (CK_ILLEGALMOVE | CK_BADMOVE); }

	
	if (lpuJumped) *lpuJumped = uJumped;

	
	// Promotion at opposite side
	if (uStatus & CKF_PROMOTEOPP) {
		// Check to see if piece is at opposite side of board
		if ((((row == maxRow) || (maxRow == 0)) && ((col == maxCol) || (maxCol == 0))) && ((maxRow != 0) || (maxCol != 0)))
		{
			// King piece, if not already kinged
			if ((uStatus & CKF_KING) != CKF_KING) {
				if (!bQueryDrop) {
					uStatus |= (CKF_KING);			// Promote
					uStatus &= (~CKF_PROMOTEOPP);	// No more promotions for the king piece
				} uResult |= CK_KINGED;				// Kinged
			}
		}
	}

	
	// Set new data
	if (!bQueryDrop)
	{
		lpckOriginalPiece->dwStatus = uStatus;
		lpckGame->lpckGame->lpaPieces[(lpckOriginalPiece->row-1)][(lpckOriginalPiece->col-1)] = NULL;
		lpckOriginalPiece->row = row; lpckOriginalPiece->col = col;
		lpckGame->lpckGame->lpaPieces[(row-1)][(col-1)] = lpckOriginalPiece;
	}

	
	// Calculate the move result
	uResult |= ((uJumped)?( ((uJumped > 1)?(CK_MULTIJUMP):(CK_JUMP)) ):(CK_MOVE));
	if (_SetWinner(lpckGame, FALSE)) uResult |= (CK_ENDGAME);


	// Return move type
	return uResult;
}

// Sets the winner (FALSE = no winner)
LOCAL BOOL _SetWinner (LPECKGAME lpckGame, BOOL bQueryWinner)
{
	int i, n;
	UINT uResult;

	for (i = 0, n = 0; i < lpckGame->lpckGame->nTeams; i++)
	{
		if (lpckGame->lpckGame->lpackTeams[i]->nPieces != 0) {
			if (n != 0) return FALSE;	// More than 1 team is left	// !!!!! Check for available moves for each piece: if no moves are available for a team, that team loses
			n = (i+1);
		}
	}

	if (n == 0)
	{ uResult = CKGAME_TIE; }						// Draw
	else { uResult = (CKGAME_TEAMWINS+(n-1)); }		// Winner found

	// End the game
	if (!bQueryWinner)
	{
		// Failsafe
		if (!lpckGame->lpckGame->lpGameResult) return FALSE;
		if (*lpckGame->lpckGame->lpGameResult != CKGAME_PLAYING) return FALSE;
		
		// Set result
		(*lpckGame->lpckGame->lpGameResult) = uResult;
	}

	return TRUE;
}

LOCAL INT _TurnPOV (INT nStatus, INT nRotAngle)
{
	INT nResult;
	
	if (nRotAngle < 0) { nRotAngle = abs(nRotAngle) % 4; nRotAngle = (4 - nRotAngle); if (nRotAngle == 4) nRotAngle = 0; }
	if (nRotAngle >= 4) nRotAngle %= 4;

	if (nRotAngle == 0) return (nStatus & CKFM_DIRECTION);


	__asm
	{
		mov  eax,[nStatus]			; Get the pov and direction in AX
		mov  ecx,[nRotAngle]		; Get the direction in CX

		mov  edx,CKFM_DIRECTION		; Get mask
		
		and  eax,edx				; Get only the allowed direction(s)
		mov  al,ah					; Put pattern into lower byte
		xor  ah,ah					; Clear high byte of AX


		and  ecx,CKFM_POV			; Get the piece's position
		shl  ax,cl					; Move bits to new direction position
		mov  ah,al					; AH holds bits for computing
		and  al,0Fh					; AL holds only the working bits

		shr  ah,1					; Set carry bits as starting bits
		shr  ah,1					; 
		shr  ah,1					; 
		shr  ah,1					; 

		or   ah,al					; Combine to form new pattern
		xor  al,al					; Clear AL


		mov  [nResult],eax			; Store new directions
	};

	return nResult;
}

// Deletes a checkers piece from the board
LOCAL BOOL _DeletePiece (LPECKPIECE lpckPiece)
{
	UINT i; INT t, ct;
	LPECKGAME lpckGame;
	LPECKPLAYER lpckPlayer;
	LPECKPIECE *lpackPiecesTemp;

	if (!lpckPiece) return FALSE;
	if ((lpckGame = lpckPiece->lpGame) == NULL) return FALSE;


	// Clear board piece
	lpckGame->lpckGame->lpaPieces[(lpckPiece->row-1)][(lpckPiece->col-1)] = NULL;

	// Drop the piece if being held, before deleting
	if (lpckGame->lpckGame->lpHolding == lpckPiece) lpckGame->lpckGame->lpHolding = NULL;


	// Delete the piece from player list
	ct = lpckGame->lpckGame->nTeams;
	for (t = 0; t < ct; t++) {
		lpckPlayer = lpckGame->lpckGame->lpackTeams[t];
		
		for (i = 0; i < lpckPlayer->nPieces; i++) {
			if (lpckPlayer->lpaPieces[i] == lpckPiece)
			{
				lpackPiecesTemp = lpckPlayer->lpaPieces;
				lpckPlayer->lpaPieces = NULL;

				if ((--lpckPlayer->nPieces) > 0)
				{
					// Copy pieces
					if ((lpckPlayer->lpaPieces = new LPECKPIECE [lpckPlayer->nPieces]) == NULL) { delete [(lpckPlayer->nPieces+1)] lpackPiecesTemp; lpckPlayer->nPieces = 0; return FALSE; }
					if (i > 0) memcpy(((lpckPlayer->lpaPieces)), lpackPiecesTemp, (sizeof(LPECKPIECE)*i));
					if (i < lpckPlayer->nPieces) memcpy((&(lpckPlayer->lpaPieces[(i)])), (&(lpackPiecesTemp[(i+1)])), (sizeof(LPECKPIECE)*(lpckPlayer->nPieces-i)));
				}

				// Delete old
				delete [(lpckPlayer->nPieces+1)] lpackPiecesTemp;
				
				// Delete the piece
				delete lpckPiece;
			}
		}
	}

	return TRUE;
}
