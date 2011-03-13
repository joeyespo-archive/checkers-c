// eCkWindow.h - eCheckers
// eCheckers Windows Graphics and Gameplay Header File
// By Joey Esposito


#pragma once



// Checkers Macros
// ----------------

// Checkers Board Styles
#define CKS_AUTOSIZE				0x00000001		// Auto sizes the window to the 
#define CKS_NOAUTOUPDATE			0x00000002		// Doesnt auto-update the window to the 

// Gameplay
#define CKGAME_UNAVAILABLE				0x0000		// Game result is not available (currently playing)
#define CKGAME_TEAMWINS					0x0001		// Team 'CKGAME_TEAMWINS+n' wins; n > 0, < 0xFFFF
#define CKGAME_TIE						0xFFFF		// Game result was a draw

// Ranks
#define CKR_PAWN						0x0001
#define CKR_KING						0x0002



// Checkers Board Messages
// ------------------------

#define WCKM_UPDATEBOARD			(WM_USER+0)		// Redraws the board (lParam (BOOL) = Update board: must be 0 .. needed only when internally resizing the board)
#define WCKM_STARTGAME				(WM_USER+1)		// Starts the game according to the current settings (lParam = Game type; Returns: TRUE = game started, FALSE = not started)
#define WCKM_STOPGAME				(WM_USER+2)		// Stops the game (lParam = (BOOL)bForcefull; Returns: TRUE = game ended, FALSE = not ended)
#define WCKM_PLAYING				(WM_USER+3)		// Returns whether or not the a game is playing
#define WCKM_STARTED				(WM_USER+4)		// Game was recently started (Returns: TRUE = Game is playing, or a winner has been decided; FALSE = game stopped: not playing)
#define WCKM_GAMERESULT				(WM_USER+5)		// Returns the game result
#define WCKM_SETSCHEMECOLOR			(WM_USER+6)		// Sets a single scheme color (wParam = color scheme index; lParam = color)
#define WCKM_GETSCHEMECOLOR			(WM_USER+7)		// Returns a scheme color (wParam = color scheme index)
#define WCKM_SETSCHEMECOLORS		(WM_USER+8)		// Sets the color scheme (lParam = color scheme to copy)
#define WCKM_GETSCHEMECOLORS		(WM_USER+9)		// Gets the current color scheme (lParam = color scheme to receive colors)
#define WCKM_SETSQUAREBORDERCOLOR	(WM_USER+10)	// Sets the square's border color (lParam =	color)
#define WCKM_GETSQUAREBORDERCOLOR	(WM_USER+11)	// Gets the square's border color (Returns the current color)
#define WCKM_SETBOARDCOLOR1			(WM_USER+12)	// Sets the first square's color (lParam =	color)
#define WCKM_GETBOARDCOLOR1			(WM_USER+13)	// Gets the first square's color (Returns the current color)
#define WCKM_SETBOARDCOLOR2			(WM_USER+14)	// Sets the second square's color (lParam =	color)
#define WCKM_GETBOARDCOLOR2			(WM_USER+15)	// Gets the second square's color (Returns the current color)
#define WCKM_SETBORDERSIZE			(WM_USER+16)	// Sets the border size (wParam = width; lParam = height)
#define WCKM_GETBORDERWIDTH			(WM_USER+17)	// Gets the border width (Returns the current width)
#define WCKM_GETBORDERHEIGHT		(WM_USER+18)	// Gets the border height (Returns the current height)
#define WCKM_SETQUARESIZE			(WM_USER+19)	// Sets the square size (wParam = width; lParam = height)
#define WCKM_GETSQUAREWIDTH			(WM_USER+20)	// Gets the square width (Returns the current width)
#define WCKM_GETSQUAREHEIGHT		(WM_USER+21)	// Gets the square height (Returns the current height)
#define WCKM_SETSQUAREBORDERSIZE	(WM_USER+22)	// Sets the square border size (wParam = width; lParam = height)
#define WCKM_GETSQUAREBORDERWIDTH	(WM_USER+23)	// Gets the square border width (Returns the current width)
#define WCKM_GETSQUAREBORDERHEIGHT	(WM_USER+24)	// Gets the square border height (Returns the current height)
#define WCKM_SETPIECEPIC			(WM_USER+25)	// Sets a pic (LOWORD(wParam) = team; HIWORD(wParam) = rank; lParam = HICON)
#define WCKM_GETPIECEPIC			(WM_USER+26)	// Returns a pic (LOWORD(wParam) = team; HIWORD(wParam) = rank; Returns: HICON)
#define WCKM_SETPIECECURSOR			(WM_USER+27)	// Sets a cursor (LOWORD(wParam) = team; HIWORD(wParam) = rank; lParam = HCURSOR)
#define WCKM_GETPIECECURSOR			(WM_USER+28)	// Returns a cursor (LOWORD(wParam) = team; HIWORD(wParam) = rank; Returns: HCURSOR)
#define WCKM_GETSIZE				(WM_USER+29)	// Gets the window size that fits the checkers board (lParam = LPRECT to retreive size)
#define WCKM_RESIZE					(WM_USER+30)	// Sizes the window to fit the checkers board
#define WCKM_GETHELDORIGIN			(WM_USER+31)	// Returns the held piece's original position (LOWORD() = row, HIWORD() = column;  (0, 0) = not holding)
#define WCKM_GETDROPPOSITION		(WM_USER+32)	// Returns the held piece's new	position (LOWORD() = row, HIWORD() = column;  (0, 0) = not dropping)
// !!!!! Game messages
//        - Pick up a particular piece by row/col



// Checkers Board Notifications
// -----------------------------

// Basic notifications
#define WCKN_DRAWFRAME				0x0000			// Sent when frame needs drawn (Return values: TRUE = frame was drawn; FALSE = frame was not drawn, draw frame)

// Game actions (return non-zero to cancel)
#define WCKN_QUERYSTARTGAME			0x0001			// Start game is ok or not (Return: 0 = continue with game start, non-zero = do not start game)
#define WCKN_STARTGAME				0x0002			// Game starting
#define WCKN_QUERYENDGAME			0x0003			// Decides whether or not to really end the game (Return: 0 = continue with game end, non-zero = do not end the game)
#define WCKN_ENDGAME				0x0004			// Game has ended
#define WCKN_PICKUPPIECE			0x0005			// Picking up a piece
#define WCKN_NOPICKUPPIECE			0x0006			// Tried picking up a piece from other team
#define WCKN_ILLEGALMOVE			0x0007			// Illegal move (ignored return value)
#define WCKN_MOVEPIECE				0x0008			// Move piece; DropPos is (0, 0) when no real moving is taken place
#define WCKN_JUMPPIECE				0x0009			// Move piece, with jump
#define WCKN_MULTIJUMPPIECE			0x000A			// Move piece, with multi-jump
#define WCKN_KINGED					0x000B			// Move piece, with king promotion



// Public Declarations
// --------------------

ECALL BOOL ESTDCALL RegisterCheckersBoard ( HINSTANCE hInstance );
ECALL BOOL ESTDCALL UnregisterCheckersBoard ( HINSTANCE hInstance );





// Implementation File:
// "eCkWindow.cpp"
