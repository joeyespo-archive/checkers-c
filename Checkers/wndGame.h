// wndGame.h - Checkers
// Game Window Header File
// By Joe Esposito


#pragma once



// Public Macros
// --------------

// Window messages
#define WM_DRAWBACKGROUND       (WM_USER+0)   // Sent to redraw the background

// Players
#define GAME_1PLAYER            0x0001
#define GAME_2PLAYER            0x0002

// Default board colors
#define COLOR_BOARD_RED         0x8080F0
#define COLOR_BOARD_WHITE       0xF0F0F0
#define COLOR_BOARD_BLACK       0x5050A0
#define COLOR_BOARD_STANDARD    0x8080C0
#define COLOR_BOARD_STANDARDBK  0xF0F0FA
#define COLOR_BOARD_BORDER      0x000000
#define COLOR_BOARD_BACKGROUND  0x404060



// Public Declarations
// --------------------

// Game window functions
BOOL DoGame ( UINT uGame );   // Starts the game window
VOID EndGame ();              // Ends the game window

// Game window procedure
LRESULT CALLBACK wndGameProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



// Implementation File:
// "wndGame.cpp"
