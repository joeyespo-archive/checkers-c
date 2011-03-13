// eCkWindow.cpp - eCheckers
// eCheckers Windows Graphics and Gameplay Implementation File
// By Joey Esposito


// !!!!! ToDo !!!!!
// 
// - Game control
// - Use DrawPicture() instead of DrawIcon() for images (also: use [convert to] bitmaps)
// - Custom gameboard bitmap
// - Custom square bitmaps (if gameboard bitmap not used)
// 


#pragma once


// Header File:
#include "eCkWindow.h"



// Local macros, structs, variables, and declarations
// ---------------------------------------------------

// Class name
#define ID_CHECKERSBOARD_CLASSNAME		"eckwindow"

// User color scheme indexes
#define CKC_SQUAREBORDERCOLOR			0
#define CKC_BOARDCOLOR1					1
#define CKC_BOARDCOLOR2					2

// Default piece sizes
#define CKSIZE_WIDTH					30
#define CKSIZE_HEIGHT					30

// Piece status
#define CKP_RANKS						2
#define CKP_TEAMS						2


// Structs
typedef struct tagCKBITMAPINFO
{
	HICON hicoaPieces[CKP_RANKS][CKP_TEAMS];	// Piece icons
	HCURSOR hcuraPieces[CKP_RANKS][CKP_TEAMS];	// Piece cursors
	//!!!!! HBITMAP hbmpaPieces[CKP_RANKS][CKP_TEAMS][2];	// Piece status bitmaps and masks
	//!!!!! HBITMAP hbmpGameBoard;	// Gameboard bitmap
	INT nSquareWidth;				// Width of a single square
	INT nSquareHeight;				// Height of a single square
	INT nSquareBorderWidth;			// Width of the square border
	INT nSquareBorderHeight;		// Height of the square border
} CKBITMAPINFO, *LPCKBITMAPINFO;

typedef struct tagCKBOARDINFO
{
	HCKGAME hckGame;				// Current checkers game
	HBITMAP hbmpBoard;				// Board bitmap
	HSCHEME hColorScheme;			// Color scheme of board
	CKBITMAPINFO ckBitmapInfo;		// Bitmap representation info
	WORD DropRow, DropCol;			// Drop row and column
	INT nBoardWidth;				// Width of the board bitmap
	INT nBoardHeight;				// Width of the board bitmap
	INT nBorderWidth;				// Width of the square border
	INT nBorderHeight;				// Height of the square border
	INT x;							// The x point of the board on the window
	INT y;							// The y point of the board on the window
	bool bNoAutoUpdate;				// Auto-updates picture or not
	bool bAutoSize;					// Autosize window
	//bool bScrollBars;				// Scrollbars when the window is too small
} CKBOARDINFO, *LPCKBOARDINFO;


// Declarations
LOCAL LRESULT CALLBACK eCheckersBoardProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
LOCAL HBITMAP CreateCkBitmap ( LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme, INT *lpnWidth, INT *lpnHeight );
LOCAL BOOL DrawCkBoard ( HDC hDC, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme );
LOCAL BOOL DrawCkPiece ( HDC hDC, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, INT x, INT y );
LOCAL BOOL DrawCkSquare ( HBITMAP hbmpBoard, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme, INT x, INT y );


// Variables
LOCAL HCURSOR hcurNormal = NULL;



// Public Functions
// -----------------

// Register checkers board window
BOOL ESTDCALL RegisterCheckersBoard (HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	// SCECC
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = ID_CHECKERSBOARD_CLASSNAME;
	wcex.hInstance = hInstance;
	wcex.style = (0);
	wcex.hIcon = NULL; wcex.hIconSm = NULL;
	wcex.hCursor = (HCURSOR)LoadCursor(NULL, (LPSTR)IDC_ARROW);
	wcex.lpfnWndProc = (WNDPROC)eCheckersBoardProc;
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 4;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	
	return (RegisterClassEx(&wcex) != NULL);
}
// Unregister checkers board window
BOOL ESTDCALL UnregisterCheckersBoard (HINSTANCE hInstance)
{ return UnregisterClass(ID_CHECKERSBOARD_CLASSNAME, hInstance); }



// Window Procedure
// -----------------

// Checkers board window procedure
LOCAL LRESULT CALLBACK eCheckersBoardProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	union { HDC hdcTemp; HPEN hpenTemp; HCURSOR hcurTemp; LPRECT lprt; };
	union { HBRUSH hbrTemp; LONG lTemp; LRESULT lResult; };
	
	INT x, y;
	UINT t1, t2;
	INT nWidth, nHeight;
	HBITMAP hbmpTemp;
	LPCKBOARDINFO lpcki;
	PAINTSTRUCT ps;
	RECT rt;
	HDC hDC;


	// Get window local data
	lpcki = (LPCKBOARDINFO)GetWindowLong(hWnd, 0);

	switch (uMsg)
	{
		case WM_CREATE:
			
			// Create info struct
			if ((lpcki = new CKBOARDINFO) == NULL) return -1;
			if (!hcurNormal) hcurNormal = (HCURSOR)GetClassLong(hWnd, GCL_HCURSOR);


			// Set window locals
			lpcki->hckGame = NULL;
			lpcki->hbmpBoard = NULL;
			lpcki->hColorScheme = CreateColorScheme(NULL, 3);
			lpcki->DropRow = 0; lpcki->DropCol = 0;
		 	lpcki->nBoardWidth = NULL; lpcki->nBoardHeight = NULL;
			lpcki->nBorderWidth = 6; lpcki->nBorderHeight = 4;
			for (x = 0; x < CKP_RANKS; x++) { for (y = 0; y < CKP_TEAMS; y++) lpcki->ckBitmapInfo.hicoaPieces[x][y] = NULL; }
			for (x = 0; x < CKP_RANKS; x++) { for (y = 0; y < CKP_TEAMS; y++) lpcki->ckBitmapInfo.hcuraPieces[x][y] = NULL; }
			lpcki->ckBitmapInfo.nSquareWidth = 34; lpcki->ckBitmapInfo.nSquareHeight = 32;
			lpcki->ckBitmapInfo.nSquareBorderWidth = 1; lpcki->ckBitmapInfo.nSquareBorderHeight = 1;
			lpcki->x = 0; lpcki->y = 0;
			lpcki->bAutoSize = ((((LPCREATESTRUCT)lParam)->style & CKS_AUTOSIZE) == CKS_AUTOSIZE);
			lpcki->bNoAutoUpdate = ((((LPCREATESTRUCT)lParam)->style & CKS_NOAUTOUPDATE) == CKS_NOAUTOUPDATE);
			SetWindowLong(hWnd, 0, (LONG)lpcki);	// Store info in window


			// Set color scheme masks
			SetColorSchemeInfoEx(lpcki->hColorScheme, CKC_SQUAREBORDERCOLOR, 0x000000, CSM_HBRUSH);
			SetColorSchemeInfoEx(lpcki->hColorScheme, CKC_BOARDCOLOR1, 0x404040, CSM_HBRUSH);
			SetColorSchemeInfoEx(lpcki->hColorScheme, CKC_BOARDCOLOR2, 0xF0F0F0, CSM_HBRUSH);
			

			// Create game object
			lpcki->hckGame = CreateCkGame();
			InitCkGameInfo(lpcki->hckGame, NULL);
			

			// Resize window
			if (((LPCREATESTRUCT)lParam)->style & CKS_AUTOSIZE) SendMessage(hWnd, WCKM_RESIZE, 0, 0);
			SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);	// Create board bitmap, if no resizing was done [and redraw]
			break;
		

		case WCKM_UPDATEBOARD:
			
			// Redraw bitmap
			if ((!lpcki->hbmpBoard) || (lParam))
			{ if (lpcki->hbmpBoard) DeleteObject(lpcki->hbmpBoard);  lpcki->hbmpBoard = CreateCkBitmap((&(lpcki->ckBitmapInfo)), lpcki->hckGame, lpcki->hColorScheme, (&(lpcki->nBoardWidth)), (&(lpcki->nBoardHeight))); }
			else
			{
				// Set up drawing
				hdcTemp = CreateCompatibleDC(NULL);
				hbmpTemp = (HBITMAP)SelectObject(hdcTemp, lpcki->hbmpBoard);
				
				// Draw board onto bitmap
				DrawCkBoard(hdcTemp, (&(lpcki->ckBitmapInfo)), lpcki->hckGame, lpcki->hColorScheme);
				
				// Clean up
				SelectObject(hdcTemp, hbmpTemp); DeleteDC(hdcTemp);
				InvalidateRect(hWnd, NULL, TRUE);
			}

			return 0;

		case WCKM_STARTGAME:
			
			if (IsPlayingCkGame(lpcki->hckGame)) return FALSE;

			// Make sure game is ok to start
			if (SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_QUERYSTARTGAME), (LPARAM)hWnd)) return FALSE;
			
			// Start the game
			if (StartCkGame(lpcki->hckGame, lParam)) {
				// Send gamestart message
				SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_STARTGAME), (LPARAM)hWnd);
		
				// Redraw board and window
				SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
				return TRUE;	// Game started ok
			}

			return FALSE;		// Game did not start

		case WCKM_STOPGAME:

			if (!StartedCkGame(lpcki->hckGame)) return FALSE;
			
			// Make sure game is ok to stopped
			if (SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_QUERYENDGAME), (LPARAM)hWnd)) return FALSE;
			
			// Stop the game	// !!!!! Forcefull stop (lParam)
			if (StopCkGame(lpcki->hckGame)) {
				// Send gameend message
				SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_ENDGAME), (LPARAM)hWnd);

				// Redraw board and window
				SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
				return TRUE;	// Game stopped ok
			}

			return FALSE;		// Game did not stopped

		case WCKM_PLAYING: return IsPlayingCkGame(lpcki->hckGame);
		case WCKM_STARTED: return StartedCkGame(lpcki->hckGame);
		case WCKM_GAMERESULT: return (LRESULT)GetCkGameResult(lpcki->hckGame);

		case WCKM_SETSCHEMECOLOR:		// Sets a scheme color
			
			// Security check
			if ((INT)wParam >= 0) { if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE); return FALSE; }
			
			// Set the color and update board (if ok)
			lResult = (LRESULT)SetSchemeColor(lpcki->hColorScheme, (INT)wParam, (COLORREF)lParam);
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
			
			return lResult;		// Return result

		case WCKM_GETSCHEMECOLOR:		// Gets a scheme color

			// Security check
			if ((INT)wParam >= 0) return 0x000000;
			return (LRESULT)GetSchemeColor(lpcki->hColorScheme, (UINT)wParam);	// Get color

		case WCKM_SETSCHEMECOLORS:		// Sets all basic scheme colors
			
			// Copy the passed scheme and update board (if ok)
			lResult = (LRESULT)CopySchemeColors(lpcki->hColorScheme, (HTHEMEOBJ)lParam);
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);

			return lResult;		// Return result

		case WCKM_GETSCHEMECOLORS:		// Gets a copy of the current scheme
			
			return CopySchemeColors((HTHEMEOBJ)lParam, lpcki->hColorScheme);

		case WCKM_SETSQUAREBORDERCOLOR:	// Sets the square's border color
			
			// Set the color and update board (if ok)
			lResult = (LRESULT)SetSchemeColor(lpcki->hColorScheme, CKC_SQUAREBORDERCOLOR, (COLORREF)lParam);
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
			return lResult;		// Return result

		case WCKM_GETSQUAREBORDERCOLOR:	// Gets the square's border color
			
			return (LRESULT)GetSchemeColor(lpcki->hColorScheme, CKC_SQUAREBORDERCOLOR);

		case WCKM_SETBOARDCOLOR1:		// Sets the first board square color
			
			// Set the color and update board (if ok)
			lResult = (LRESULT)SetSchemeColor(lpcki->hColorScheme, CKC_BOARDCOLOR1, (COLORREF)lParam);
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
			return lResult;		// Return result

		case WCKM_GETBOARDCOLOR1:		// Gets the first board square color
			
			return (LRESULT)GetSchemeColor(lpcki->hColorScheme, WCKM_GETBOARDCOLOR1);

		case WCKM_SETBOARDCOLOR2:		// Sets the second board square color
			
			// Set the color and update board (if ok)
			lResult = (LRESULT)SetSchemeColor(lpcki->hColorScheme, CKC_BOARDCOLOR2, (COLORREF)lParam);
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
			return lResult;		// Return result

		case WCKM_GETBOARDCOLOR2:		// Gets the second board square color
			
			return (LRESULT)GetSchemeColor(lpcki->hColorScheme, WCKM_GETBOARDCOLOR2);

		case WCKM_SETBORDERSIZE:		// Sets the board's border size
			
			// Set the size and resize board (if ok)
			lpcki->nBorderWidth = (INT)wParam; lpcki->nBorderHeight = (INT)lParam;
			if ((lpcki->bAutoSize) && (!lpcki->bNoAutoUpdate)) SendMessage(hWnd, WCKM_RESIZE, 0, 0);
			return 0;

		case WCKM_GETBORDERWIDTH: return (LRESULT)lpcki->nBorderWidth;
		case WCKM_GETBORDERHEIGHT: return (LRESULT)lpcki->nBorderHeight;
		
		case WCKM_SETQUARESIZE:			// Sets the board's square size
			
			// Set the size and resize board (if ok)
			lpcki->ckBitmapInfo.nSquareWidth = (INT)wParam; lpcki->ckBitmapInfo.nSquareHeight = (INT)lParam;
			if ((lpcki->bAutoSize) && (!lpcki->bNoAutoUpdate)) SendMessage(hWnd, WCKM_RESIZE, 0, 0);
			return 0;

		case WCKM_GETSQUAREWIDTH: return (LRESULT)lpcki->ckBitmapInfo.nSquareWidth;
		case WCKM_GETSQUAREHEIGHT: return (LRESULT)lpcki->ckBitmapInfo.nSquareHeight;

		case WCKM_SETSQUAREBORDERSIZE:	// Sets the square's border size
			
			// Set the size and resize board (if ok)
			lpcki->ckBitmapInfo.nSquareBorderWidth = (INT)wParam;
			lpcki->ckBitmapInfo.nSquareBorderHeight = (INT)lParam;
			if ((lpcki->bAutoSize) && (!lpcki->bNoAutoUpdate)) SendMessage(hWnd, WCKM_RESIZE, 0, 0);
			return 0;

		case WCKM_GETSQUAREBORDERWIDTH: return (LRESULT)lpcki->ckBitmapInfo.nSquareBorderWidth;
		case WCKM_GETSQUAREBORDERHEIGHT: return (LRESULT)lpcki->ckBitmapInfo.nSquareBorderHeight;
		
		case WCKM_SETPIECEPIC:			// Sets the specified piece status's icon
			
			if (((t1 = LOWORD(wParam)) <= 0) || (t1 > CKP_TEAMS)) return FALSE;
			if (((t2 = HIWORD(wParam)) <= 0) || (t2 > CKP_RANKS)) return FALSE;

			lpcki->ckBitmapInfo.hicoaPieces[(t1-1)][(t2-1)] = (HICON)lParam;
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, FALSE);
			return TRUE;
		
		case WCKM_GETPIECEPIC:			// Gets the specified piece status's icon
		
			if (((t1 = LOWORD(wParam)) <= 0) || (t1 > CKP_TEAMS)) return NULL;
			if (((t2 = HIWORD(wParam)) <= 0) || (t2 > CKP_RANKS)) return NULL;

			return (LRESULT)lpcki->ckBitmapInfo.hicoaPieces[(t1-1)][(t2-1)];
		
		case WCKM_SETPIECECURSOR:		// Sets the specified piece status's cursor
			
			if (((t1 = LOWORD(wParam)) <= 0) || (t1 > CKP_TEAMS)) return FALSE;
			if (((t2 = HIWORD(wParam)) <= 0) || (t2 > CKP_RANKS)) return FALSE;

			lpcki->ckBitmapInfo.hcuraPieces[(t1-1)][(t2-1)] = (HCURSOR)lParam;
			
			if (lTemp = GetCkHeldPiecePos(lpcki->hckGame)) {
				x = HIWORD(lTemp); y = LOWORD(lTemp);
	
				// Set the cursor
				hcurTemp = lpcki->ckBitmapInfo.hcuraPieces[(GetCkPieceRank(lpcki->hckGame, y, x)-1)][(GetCkPieceTeam(lpcki->hckGame, y, x)-1)];
				SetClassLong(hWnd, GCL_HCURSOR, (LONG)hcurTemp);
				SetCursor(hcurTemp);	// !!!!! 'Drag' a regioned window for the piece?
			}

			return TRUE;
		
		case WCKM_GETPIECECURSOR:		// Gets the specified piece status's cursor
		
			if (((t1 = LOWORD(wParam)) <= 0) || (t1 > CKP_TEAMS)) return NULL;
			if (((t2 = HIWORD(wParam)) <= 0) || (t2 > CKP_RANKS)) return NULL;

			return (LRESULT)lpcki->ckBitmapInfo.hcuraPieces[(t1-1)][(t2-1)];

		case WCKM_GETSIZE:

			// Security check
			if (lParam == NULL) return FALSE;
			
			// Calculate size
			rt.left = 0; rt.top = 0;
			rt.right = ((((lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth) * 8) + lpcki->ckBitmapInfo.nSquareBorderWidth) + (lpcki->nBorderWidth * 2));
			rt.bottom = ((((lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight) * 8) + lpcki->ckBitmapInfo.nSquareBorderHeight) + (lpcki->nBorderHeight * 2));
			AdjustWindowRectEx(&rt, GetWindowLong(hWnd, GWL_STYLE), FALSE, GetWindowLong(hWnd, GWL_EXSTYLE));

			memcpy((LPRECT)lParam, &rt, sizeof(RECT));
			return TRUE;

		case WCKM_RESIZE:
			
			// Calculate size
			rt.left = 0; rt.top = 0;
			rt.right = ((((lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth) * 8) + lpcki->ckBitmapInfo.nSquareBorderWidth) + (lpcki->nBorderWidth * 2));
			rt.bottom = ((((lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight) * 8) + lpcki->ckBitmapInfo.nSquareBorderHeight) + (lpcki->nBorderHeight * 2));
			AdjustWindowRectEx(&rt, GetWindowLong(hWnd, GWL_STYLE), FALSE, GetWindowLong(hWnd, GWL_EXSTYLE));
			
			// Set size
			SetWindowPos(hWnd, NULL, 0, 0, (rt.right - rt.left), (rt.bottom - rt.top), (SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER));

			// Update board (if ok)
			if (!lpcki->bNoAutoUpdate) SendMessage(hWnd, WCKM_UPDATEBOARD, 0, TRUE);
			return 0;
		
		case WCKM_GETHELDORIGIN: return GetCkHeldPiecePos(lpcki->hckGame);
		case WCKM_GETDROPPOSITION: return MAKELONG(lpcki->DropRow, lpcki->DropCol);
		

		case WM_STYLECHANGED:
			
			lpcki->bAutoSize = ((((((LPSTYLESTRUCT)lParam)->styleNew) & CKS_AUTOSIZE) == CKS_AUTOSIZE) != FALSE);
			lpcki->bNoAutoUpdate = ((((((LPSTYLESTRUCT)lParam)->styleNew) & CKS_NOAUTOUPDATE) == CKS_NOAUTOUPDATE) != FALSE);

			// Update if changed, if not previously updated
			if ( (((((LPSTYLESTRUCT)lParam)->styleOld & CKS_AUTOSIZE) == 0) && ((((LPSTYLESTRUCT)lParam)->styleNew & CKS_AUTOSIZE) == CKS_AUTOSIZE)) ||
				(((((LPSTYLESTRUCT)lParam)->styleOld & CKS_NOAUTOUPDATE) == CKS_NOAUTOUPDATE) && ((((LPSTYLESTRUCT)lParam)->styleNew & CKS_NOAUTOUPDATE) == 0)) )
				SendMessage(hWnd, WCKM_UPDATEBOARD, 0, TRUE);

			break;

		case WM_WINDOWPOSCHANGED:
			
			return TRUE;		// Dont send WM_SIZE or WM_MOVE


		case WM_NCPAINT:

			// Allow owner to draw frame
			if (SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_DRAWFRAME), (LPARAM)hWnd) == 0) return 0;
			
			// Set up drawing
			hDC = GetWindowDC(hWnd); GetWindowRect(hWnd, &rt);
			

			// Set up frame coordinates
			rt.right -= rt.left; rt.left = 0; rt.bottom -= rt.top; rt.top = 0;
			nWidth = (rt.right-rt.left); nHeight = (rt.bottom-rt.top);

			if ((GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE)
			{ DrawSchemeEdge(hDC, &rt, lpcki->hColorScheme, (EDGE_SUNKEN), (BF_RECT)); }
			else if ((GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_STATICEDGE) == WS_EX_STATICEDGE)
			{ DrawSchemeEdge(hDC, &rt, lpcki->hColorScheme, (BDR_SUNKENINNER), (BF_RECT)); }
			else { DrawSchemeEdge(hDC, &rt, lpcki->hColorScheme, (EDGE_RAISED), (BF_RECT)); }


			// Clean up
			ReleaseDC(hWnd, hDC);
			return 0;

		case WM_ERASEBKGND: return TRUE;		// No drawing here

		case WM_PAINT:
			
			// Setup painting
			hDC = BeginPaint(hWnd, &ps);

			// Create board bitmap DC
			hdcTemp = CreateCompatibleDC(NULL);
			hbmpTemp = (HBITMAP)SelectObject(hdcTemp, lpcki->hbmpBoard);


			// Draw background
			hbrTemp = GetSchemeBkBrush(lpcki->hColorScheme);
			GetClientRect(hWnd, &rt); nWidth = rt.right; nHeight = rt.bottom;
			x = (lpcki->nBorderWidth+lpcki->x);
			y = (lpcki->nBorderHeight+lpcki->y);
			
			if (x > 0) {
				rt.right = x;
				FillRect(hDC, &rt, hbrTemp);
				rt.left = rt.right; rt.right = nWidth;
			} if (y > 0) {
				rt.bottom = y;
				FillRect(hDC, &rt, hbrTemp);
				rt.bottom = nHeight;
			} if ((x+lpcki->nBoardWidth) < nWidth) {
				rt.left = (x+lpcki->nBoardWidth);
				FillRect(hDC, &rt, hbrTemp);
				rt.right = rt.left; rt.left = 0;
			} if ((y+lpcki->nBoardHeight) < nHeight) {
				rt.top = (y+lpcki->nBoardHeight);
				FillRect(hDC, &rt, hbrTemp);
			}

			
			// Draw board
			BitBlt(hDC, x, y, lpcki->nBoardWidth, lpcki->nBoardHeight, hdcTemp, 0, 0, SRCCOPY);


			// Clean up
			SelectObject(hdcTemp, hbmpTemp); DeleteDC(hdcTemp);		// Delete board DC
			EndPaint(hWnd, &ps);		// End painting
			return TRUE;

		case WM_LBUTTONDOWN:

			// Bounds check
			if ((LOWORD(lParam) < (lpcki->nBorderWidth+lpcki->x)) || (HIWORD(lParam) < (lpcki->nBorderHeight+lpcki->y))) break;
			if ((LOWORD(lParam) > ((lpcki->nBorderWidth+lpcki->x)+((lpcki->ckBitmapInfo.nSquareWidth+lpcki->ckBitmapInfo.nSquareBorderWidth)*8))) || (HIWORD(lParam) > ((lpcki->nBorderHeight+lpcki->y)+((lpcki->ckBitmapInfo.nSquareHeight+lpcki->ckBitmapInfo.nSquareBorderHeight)*8)))) break;

			// Get square position
			if ((x = ((LOWORD(lParam) - (lpcki->nBorderWidth+lpcki->x)) / (lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth)) ) > 7) x = 7;
			if ((y = ((HIWORD(lParam) - (lpcki->nBorderHeight+lpcki->y)) / (lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight)) ) > 7) y = 7;
			x++; y++;	// Board position

			
			// Restore the cursor, if still holding
			if (IsCkHeldPiece(lpcki->hckGame)) SendMessage(hWnd, WM_LBUTTONUP, wParam, lParam);

			// Pick up piece, if available
			if (((t1 = PickUpCkPiece(lpcki->hckGame, y, x)) == CK_NOPICKUP) || (t1 == CK_ERROR)) break;
			if (t1 == CK_WRONGTEAM) { SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_NOPICKUPPIECE), (LPARAM)hWnd); break; }
			
			// Send 'pick up' action message, and drop again if returned -1
			if (SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_PICKUPPIECE), (LPARAM)hWnd))
			{ DropCkPiece(lpcki->hckGame, 0, 0, NULL); break; }


			// !!!!! Set mouse as bitmap (convert bitmap to cursor), unless cursor is specified
			SetCapture(hWnd);
			if (t2 = GetCkPieceRank(lpcki->hckGame, y, x))
			{ hcurTemp = lpcki->ckBitmapInfo.hcuraPieces[(t2-1)][(GetCkPieceTeam(lpcki->hckGame, y, x)-1)]; }
			else { DropCkPiece(lpcki->hckGame, 0, 0, NULL); break; }
			x--; y--;	// Index position

			
			// Redraw new square
			DrawCkSquare(lpcki->hbmpBoard, &lpcki->ckBitmapInfo, lpcki->hckGame, lpcki->hColorScheme, x, y);

			// Paint new square
			GetClientRect(hWnd, &rt);
			rt.left += ((lpcki->nBorderWidth+lpcki->x) + ((x * (lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth)) + lpcki->ckBitmapInfo.nSquareBorderWidth)); rt.right = (rt.left + lpcki->ckBitmapInfo.nSquareWidth);
			rt.top += ((lpcki->nBorderHeight+lpcki->y) + ((y * (lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight)) + lpcki->ckBitmapInfo.nSquareBorderHeight)); rt.bottom = (rt.top + lpcki->ckBitmapInfo.nSquareHeight);
 			
			// Set the cursor
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)hcurTemp);
			SetCursor(hcurTemp);	// !!!!! 'Drag' a window region for the piece?

			// Paint window
			InvalidateRect(hWnd, &rt, FALSE); UpdateWindow(hWnd);
			break;

		case WM_LBUTTONUP:
			
			if (GetCapture() == hWnd) ReleaseCapture();
			if (!IsCkHeldPiece(lpcki->hckGame)) break;
			
			
			// Move the piece
			// ---------------

			// Bounds check
			if (( (LOWORD(lParam) >= (lpcki->nBorderWidth+lpcki->x)) && (LOWORD(lParam) <= ((lpcki->nBorderWidth+lpcki->x)+((lpcki->ckBitmapInfo.nSquareWidth+lpcki->ckBitmapInfo.nSquareBorderWidth)*8))) ) && ((HIWORD(lParam) >= (lpcki->nBorderHeight+lpcki->y)) && (HIWORD(lParam) <= ((lpcki->nBorderHeight+lpcki->y)+((lpcki->ckBitmapInfo.nSquareHeight+lpcki->ckBitmapInfo.nSquareBorderHeight)*8)))) )
			{
				// Get square position
				if ((x = ((LOWORD(lParam) - (lpcki->nBorderWidth+lpcki->x)) / (lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth)) ) > 7) x = 7;
				if ((y = ((HIWORD(lParam) - (lpcki->nBorderHeight+lpcki->y)) / (lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight)) ) > 7) y = 7;
				x++; y++;	// Board positions
			} else { x = y = 0; }

			
			// Set drop position
			lpcki->DropRow = y; lpcki->DropCol = x;
			
			// If not a legal move, send 'illegal move' action message, and drop the piece
			if (((t1 = GetCkDropStatus(lpcki->hckGame, y, x)) & CKM_MOVE) == 0)
			{
				if (t1 == CK_ERROR) return 0;
				
				// Send sound message
				SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), WCKN_ILLEGALMOVE), (LPARAM)hWnd);
				
				// Get held original position
				lTemp = GetCkHeldPiecePos(lpcki->hckGame); x = (HIWORD(lTemp) - 1); y = (LOWORD(lTemp) - 1);
				
				// Drop the piece, then redraw the square
				DropCkPiece(lpcki->hckGame, 0, 0, NULL);
				DrawCkSquare(lpcki->hbmpBoard, &lpcki->ckBitmapInfo, lpcki->hckGame, lpcki->hColorScheme, x, y);
				goto MoveCkUpdateDisplay;
			}

			
			// Send 'move piece' action message, and drop the piece to its original position if returned -1
			if (t1 & CK_ENDGAME)  { lTemp = WCKN_ENDGAME; }
			else if (t1 & CK_KINGED)  { lTemp = WCKN_KINGED; }
			else if ((t1 & CKM_MOVE) == CK_MULTIJUMP)  { lTemp = WCKN_MULTIJUMPPIECE; }
			else if ((t1 & CKM_MOVE) == CK_JUMP)  { lTemp = WCKN_JUMPPIECE; }
			else  { lTemp = WCKN_MOVEPIECE; }

			if (SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(GetWindowLong(hWnd, GWL_ID), lTemp), (LPARAM)hWnd))
			{
				// Get held original position
				lTemp = GetCkHeldPiecePos(lpcki->hckGame); x = (LOWORD(lTemp) - 1); y = HIWORD((lTemp) - 1);
				
				// Drop the piece, then redraw the square
				DropCkPiece(lpcki->hckGame, 0, 0, NULL);
				DrawCkSquare(lpcki->hbmpBoard, &lpcki->ckBitmapInfo, lpcki->hckGame, lpcki->hColorScheme, x, y);
				goto MoveCkUpdateDisplay;
			}
			

			// Move to new position
			t2 = ((t1 = DropCkPiece(lpcki->hckGame, y, x, NULL)) & CKM_MOVE);
			lpcki->DropRow = 0; lpcki->DropCol = 0;		// Update drop position
			x--; y--;	// Index position

			// Redraw square (or board, if jumping)
			if (((t2 == CK_JUMP) || (t2 == CK_MULTIJUMP)))
			{
				// !!!!! Redraw only those squares being jumped
				// Initialize drawing
				hDC = CreateCompatibleDC(NULL);
				hbmpTemp = (HBITMAP)SelectObject(hDC, lpcki->hbmpBoard);
				
				// Draw board
				DrawCkBoard(hDC, &lpcki->ckBitmapInfo, lpcki->hckGame, lpcki->hColorScheme);

				// Clean up
				SelectObject(hDC, hbmpTemp); DeleteDC(hDC);
			} else
			{ DrawCkSquare(lpcki->hbmpBoard, &lpcki->ckBitmapInfo, lpcki->hckGame, lpcki->hColorScheme, x, y); }
			

			// Display update
			MoveCkUpdateDisplay:
			
			// Paint new square
			GetClientRect(hWnd, &rt);
			rt.left += ((lpcki->nBorderWidth+lpcki->x) + ((x * (lpcki->ckBitmapInfo.nSquareWidth + lpcki->ckBitmapInfo.nSquareBorderWidth)) + lpcki->ckBitmapInfo.nSquareBorderWidth)); rt.right = (rt.left + lpcki->ckBitmapInfo.nSquareWidth);
			rt.top += ((lpcki->nBorderHeight+lpcki->y) + ((y * (lpcki->ckBitmapInfo.nSquareHeight + lpcki->ckBitmapInfo.nSquareBorderHeight)) + lpcki->ckBitmapInfo.nSquareBorderHeight)); rt.bottom = (rt.top + lpcki->ckBitmapInfo.nSquareHeight);

			// Restore the original cursor
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)hcurNormal);
			SetCursor(hcurNormal);

			// Window Painting
			lprt = (((t2 == CK_JUMP) || (t2 == CK_MULTIJUMP))?(NULL):(&rt));
			InvalidateRect(hWnd, lprt, FALSE); UpdateWindow(hWnd);

			break;

		case WM_DESTROY:

			if (lpcki)
			{
				// Clean up
				DestroyCkGame(lpcki->hckGame);				// Destroy the game (forcefully, without stopping)
				DeleteObject(lpcki->hbmpBoard);				// Delete board bitmap
				DestroyColorScheme(lpcki->hColorScheme);	// Destroy Color Scheme
				delete lpcki; lpcki = NULL;					// Delete local data
			}
			
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



// Local Functions
// ----------------

// Creates the checkers board's bitmap
LOCAL HBITMAP CreateCkBitmap (LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme, INT *lpnWidth, INT *lpnHeight)
{
	INT cx, cy;
	BITMAPINFO bmi;
	HBITMAP hbmpResult;
	HBITMAP hbmpTemp;
	HDC hdcTemp;


	cx = (((lpckBitmapInfo->nSquareWidth + lpckBitmapInfo->nSquareBorderWidth) * 8) + lpckBitmapInfo->nSquareBorderWidth);
	cy = (((lpckBitmapInfo->nSquareHeight + lpckBitmapInfo->nSquareBorderHeight) * 8) + lpckBitmapInfo->nSquareBorderHeight);


	// Set up bitmap
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = -cy; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;

	
	// Create DC and bitmap
	hdcTemp = CreateCompatibleDC(NULL);
	hbmpResult = CreateDIBSection(hdcTemp, &bmi, DIB_RGB_COLORS, NULL, NULL, NULL);

	// Set up drawing
	hbmpTemp = (HBITMAP)SelectObject(hdcTemp, hbmpResult);


	// Draw board
	DrawCkBoard(hdcTemp, lpckBitmapInfo, hckGame, hColorScheme);

	
	// Clean up
	SelectObject(hdcTemp, hbmpTemp); DeleteDC(hdcTemp);	// Delete DC

	if (lpnWidth) { (*lpnWidth) = cx; }
	if (lpnHeight) { (*lpnHeight) = cy; }

	return hbmpResult;
}

// Draws the board on a DC
LOCAL BOOL DrawCkBoard (HDC hDC, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme)
{
	RECT rt;
	int x, y, i;
	INT nSquareWidth, nSquareHeight;
	INT nSquareBorderWidth, nSquareBorderHeight;

	if (!hckGame) return FALSE;


	rt.left = 0; rt.top = 0;
	rt.right = ((( (nSquareWidth = lpckBitmapInfo->nSquareWidth) + (nSquareBorderWidth = lpckBitmapInfo->nSquareBorderWidth) ) * 8) + nSquareBorderWidth);
	rt.bottom = ((( (nSquareHeight = lpckBitmapInfo->nSquareHeight) + (nSquareBorderHeight = lpckBitmapInfo->nSquareBorderHeight) ) * 8) + nSquareBorderHeight);
	FillRect(hDC, &rt, (HBRUSH)GetSchemeColorObj(hColorScheme, CKC_SQUAREBORDERCOLOR));

	// !!!!! Copy from board bitmap ([this is the game bitmap])
	for (y = 0, i = 0; y < 8; y++, i = ~i)
	{
		for (x = 0; x < 8; x++, i = ~i)
		{
			rt.left = ((x * (nSquareWidth + nSquareBorderWidth)) + nSquareBorderWidth); rt.right = (rt.left + nSquareWidth);
			rt.top = ((y * (nSquareHeight + nSquareBorderHeight)) + nSquareBorderHeight); rt.bottom = (rt.top + nSquareHeight);
			FillRect(hDC, &rt, (HBRUSH)GetSchemeColorObj(hColorScheme, ((i)?(CKC_BOARDCOLOR2):(CKC_BOARDCOLOR1))));

			// Draw the piece
			DrawCkPiece(hDC, lpckBitmapInfo, hckGame, x, y);
		}
	}

	return TRUE;
}

// Dras a checkers piece on the board at a given pos
LOCAL BOOL DrawCkPiece (HDC hDC, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, INT x, INT y)
{
	RECT rt;
	HICON hicoTemp;
	HPEN hpenTemp; HBRUSH hbrTemp;
	INT nSquareWidth, nSquareHeight;
	INT nSquareBorderWidth, nSquareBorderHeight;
	UINT uRank;
	
	if (!hckGame) return FALSE;


	if ((IsCkPeice(hckGame, (y+1), (x+1))) && (!IsCkHeldPiecePos(hckGame, (y+1), (x+1))))
	{
		if (uRank = GetCkPieceRank(hckGame, (y+1), (x+1)) != 0)
		{ hicoTemp = lpckBitmapInfo->hicoaPieces[(uRank-1)][(GetCkPieceTeam(hckGame, (y+1), (x+1))-1)]; }
		else { hicoTemp = NULL; }

		rt.left = ((x * ((nSquareWidth = lpckBitmapInfo->nSquareWidth) + (nSquareBorderWidth = lpckBitmapInfo->nSquareBorderWidth))) + nSquareBorderWidth); rt.right = (rt.left + nSquareWidth);
		rt.top = ((y * ((nSquareHeight = lpckBitmapInfo->nSquareHeight) + (nSquareBorderHeight = lpckBitmapInfo->nSquareBorderHeight))) + nSquareBorderHeight); rt.bottom = (rt.top + nSquareHeight);

		// !!!!! Use bitmaps
		if ((hicoTemp == NULL) || (!DrawIcon(hDC, rt.left, rt.top, hicoTemp)))	// Draw piece
		{
			// Initialize drawing
			hpenTemp = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 0, ((hicoTemp)?(0xFFAA88):(0x88AAFF)) ));
			hbrTemp = (HBRUSH)SelectObject(hDC, CreateSolidBrush((hicoTemp)?(0xAA8800):(0x0022CC)) );
					
			// Draw piece	// !!!!! Draw according to team and rank
			Ellipse(hDC, ((nSquareWidth >= CKSIZE_WIDTH)?(rt.left + ((nSquareWidth-CKSIZE_WIDTH)/2)):(rt.left)), ((nSquareHeight >= CKSIZE_HEIGHT)?(rt.top + ((nSquareHeight-CKSIZE_HEIGHT)/2)):(rt.top)), ((nSquareWidth >= CKSIZE_WIDTH)?(rt.left + ((nSquareWidth+CKSIZE_WIDTH)/2)):(rt.right)), ((nSquareHeight >= CKSIZE_HEIGHT)?(rt.top + ((nSquareHeight+CKSIZE_HEIGHT)/2)):(rt.bottom)));
					
			// Clean up
			DeleteObject(SelectObject(hDC, hbrTemp));
			DeleteObject(SelectObject(hDC, hpenTemp));
		}
	}

	return TRUE;
}

LOCAL BOOL DrawCkSquare (HBITMAP hbmpBoard, LPCKBITMAPINFO lpckBitmapInfo, HCKGAME hckGame, HSCHEME hColorScheme, INT x, INT y)
{
	HDC hDC;
	RECT rt;
	HBITMAP hbmpTemp;
	INT nSquareWidth, nSquareHeight;
	INT nSquareBorderWidth, nSquareBorderHeight;
	
	if (!hckGame) return FALSE;

	
	// Initialize drawing
	hDC = CreateCompatibleDC(NULL);
	hbmpTemp = (HBITMAP)SelectObject(hDC, hbmpBoard);

	// Draw square
	rt.left = ((x * ((nSquareWidth = lpckBitmapInfo->nSquareWidth) + (nSquareBorderWidth = lpckBitmapInfo->nSquareBorderWidth))) + nSquareBorderWidth); rt.right = (rt.left + nSquareWidth);
	rt.top = ((y * ((nSquareHeight = lpckBitmapInfo->nSquareHeight) + (nSquareBorderHeight = lpckBitmapInfo->nSquareBorderHeight))) + nSquareBorderHeight); rt.bottom = (rt.top + nSquareHeight);
	FillRect(hDC, &rt, (HBRUSH)GetSchemeColorObj(hColorScheme, ((x & 1)?( ((y & 1)?(CKC_BOARDCOLOR1):(CKC_BOARDCOLOR2)) ):( ((y & 1)?(CKC_BOARDCOLOR2):(CKC_BOARDCOLOR1)) ))));
	DrawCkPiece(hDC, lpckBitmapInfo, hckGame, x, y);
	
	// Clean up
	SelectObject(hDC, hbmpTemp); DeleteDC(hDC);

	return TRUE;
}
