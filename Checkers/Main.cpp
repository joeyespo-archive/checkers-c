// Main.cpp - Checkers
// Entry Point of Application
// By Joe Esposito

// Checkers:
// A Computer-Based Checkers game,
// play with a friend, online, or alone

// !!!!! ToDo !!!!!
// ----------------------------------------------------------------------------------------
// 
// - eCheckers:
//   - Create SendCkMessage() and messages
//   - Make game rules
//   - Return HGAME as an ID, not a pointer to actual LPGAME
// 
// - frmGame:  Create controls (use color scheme)
// - frmAbout: Create controls ("Esposito Software" static, eye icon, credits [?], etc)
// - frmMain:  "&Select a game..."  -->  have it select "Single Player" when ALT+S is pressed
//   - Use an accelerator
// 
// ----------------------------------------------------------------------------------------


// Header File:
#include "Main.h"



// Globals
// --------

HINSTANCE hInstance;			// Application's current hInstance

HWND hDialogWnd;				// Current [focused] dialog window

HFONT hFont_Main;				// Main Font (Normal)
HFONT hFont_MainBold;			// Main Font (Bold)

APPOPTIONS oOptions;			// Application Options



// Entry Point of Application
// ---------------------------

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hWnd;
	HMODULE hRichEdit;


	// Initialize Globals
	// -------------------

	::hInstance = hInstance;



	// Register Classes
	// -----------------

	WNDCLASSEX wcex;
	
	// frmMain
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = ID_MAINWND_CLASSNAME;
	wcex.hInstance = hInstance;
	wcex.style = (CS_HREDRAW | CS_VREDRAW);
	wcex.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
	wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icsMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
	wcex.hCursor = (HCURSOR)LoadCursor(NULL, (LPSTR)IDC_ARROW);
	wcex.lpfnWndProc = (WNDPROC)frmMainProc;
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	
	if (!RegisterClassEx(&wcex))
		AppFailed("Could not register window");
	

	// frmGame
	wcex.lpszClassName = ID_GAMEWND_CLASSNAME;
	wcex.lpfnWndProc = (WNDPROC)frmGameProc;

	if (!RegisterClassEx(&wcex))
		AppFailed("Could not register window");


	// frmAbout
	wcex.lpszClassName = ID_ABOUTWND_CLASSNAME;
	wcex.hIcon = NULL; wcex.hIconSm = NULL;
	wcex.lpfnWndProc = (WNDPROC)frmAboutProc;

	if (!RegisterClassEx(&wcex))
		AppFailed("Could not register window");

	// Checkers board window
	if (!RegisterCheckersBoard(hInstance))
		AppFailed("Could not register window");

	
	
	// Create Fonts
	// -------------

	hFont_Main = CreateFont(8, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "MS Sans Serif");
	hFont_MainBold = CreateFont(8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "MS Sans Serif");



	// Load Libraries
	// ---------------

	if ((hRichEdit = LoadLibrary("RICHED32.DLL")) == NULL)
		AppFailed("Could not load library: RICHED32.DLL");



	// Load Options
	// -------------
	
	LoadAppOptions(&oOptions);


	// Create Main Window
	// -------------------
	
	if ((hWnd = CreateMainWindow()) == NULL) AppFailed("Could not create window");
	ShowWindow(hWnd, nShowCmd);


	// Main Message Loop
	// ------------------

	MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (!IsDialogMessage(hDialogWnd, &msg)) {	// Check for dialog messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	
	// Clean up
	// ---------

	DeleteObject(hFont_Main);				// Delete Font Object
	DeleteObject(hFont_MainBold);			// Delete Font Object
	FreeLibrary(hRichEdit);					// Free Rich Edit Library


	return msg.wParam;	// Return OK
}




INT AppFailed(char *lpszError) {
	MsgBox( ((lpszError == NULL) ? ("Application could not be loaded.") : (lpszError)), "Application Error");
	PostQuitMessage(-1);

	return -1;
}

void LoadAppOptions (LPAPPOPTIONS lpOptions)
{
	if (lpOptions == NULL) return;

	// !!! Check to see if options exist in hard memory; if not, create it

	// Set the options
	lpOptions->bShowQuitConfirm = false;
	lpOptions->bStartLastPosition = false;
	lpOptions->lastX = 0;
	lpOptions->lastY = 0;
	lpOptions->crSquare1 = 0; //COLOR_BOARDCOLOR_RED;
	lpOptions->crSquare2 = 0; //COLOR_BOARDCOLOR_WHITE;
	
}
