// Main.cpp - Checkers
// Entry Point of Application
// By Joe Esposito


// !!!!! ToDo !!!!!
// ------------------------------------------------------------------------------------------
// 
// - Main window
//   - Icons and such
// - Game window
// - About window
//   - Organize
// 
// ------------------------------------------------------------------------------------------


// Header File:
#include "Main.h"



// Source Files
// -------------

#include <eLibWin.cpp>
#include <eGradient\Main.cpp>


// Globals
// --------

// Instance variables
HINSTANCE hInstance = NULL;            // Application's current hInstance

// Application Variables
HWND hDialogWnd = NULL;              // Current [focused] dialog window
HFONT hFont_Main = NULL;            // Main Font (Normal)
HFONT hFont_MainBold = NULL;          // Main Font (Bold)
APPOPTIONS oOptions;              // Application Options



// Entry Point of Application
// ---------------------------

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  MSG msg;


  // Initialize Application
  // -----------------------

  if (Init(hInstance, lpCmdLine, nShowCmd) != 0)
  { msg.wParam = -1; }
  else {
    
    // Main Message Loop
    // ------------------
    
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
      if (!IsDialogMessage(hDialogWnd, &msg)) {  // Check for dialog messages
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }



  // Clean up
  // ---------

  Terminate ();


  return msg.wParam;  // Return OK
}



// Public Functions
// -----------------

// Initializes application
INT Init (HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HWND hWnd;


  // Initialize Globals
  // -------------------
  
  ::hInstance = hInstance;



  // Register Classes
  // -----------------
  
  WNDCLASSEX wcex;
  
  // Main window
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.lpszClassName = ID_MAINWND_CLASSNAME;
  wcex.hInstance = hInstance;
  wcex.style = (0);
  wcex.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
  wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icsMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
  wcex.hCursor = (HCURSOR)LoadCursor(NULL, (LPSTR)IDC_ARROW);
  wcex.lpfnWndProc = (WNDPROC)wndMainProc;
  wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
  wcex.hbrBackground = NULL;
  wcex.lpszMenuName = NULL;
  if (!RegisterClassEx(&wcex)) return AppFailed("Could not register window");  // Register main window
  
  // Game window
  wcex.lpszClassName = ID_GAMEWND_CLASSNAME;
  wcex.lpfnWndProc = (WNDPROC)wndGameProc;
  if (!RegisterClassEx(&wcex)) return AppFailed("Could not register window");  // Register game window

  // About window
  wcex.lpszClassName = ID_ABOUTWND_CLASSNAME;
  wcex.hIcon = NULL; wcex.hIconSm = NULL;
  wcex.lpfnWndProc = (WNDPROC)wndAboutProc;
  wcex.cbWndExtra = DLGWINDOWEXTRA;
  if (!RegisterClassEx(&wcex)) return AppFailed("Could not register window");  // Register about window



  // Create Fonts
  // -------------
  
  // Main fonts
  hFont_Main = CreateFont(8, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "MS Sans Serif");
  hFont_MainBold = CreateFont(8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "MS Sans Serif");


  // Load Options
  // -------------
  
  if (!LoadAppOptions(&oOptions)) return AppFailed("Could not load options");



  // Create Main Window
  // -------------------
  
  // Create the window
  if ((hWnd = CreateMainWindow()) == NULL) return AppFailed("Could not create main window");
  ShowWindow(hWnd, nShowCmd);  // Show the window


  return 0;
}



// Terminates application
INT Terminate ()
{
  
  // Clean up
  // ---------
  
  // Delete font objects
  DeleteObject(hFont_MainBold);      // Delete Font Object
  DeleteObject(hFont_Main);        // Delete Font Object
  
  // Unregister windows classes
  UnregisterClass(ID_ABOUTWND_CLASSNAME, hInstance);
  UnregisterClass(ID_GAMEWND_CLASSNAME, hInstance);
  UnregisterClass(ID_MAINWND_CLASSNAME, hInstance);

  return 0;
}



// Called when loading fails
INT AppFailed(char *lpszError) {
  MsgBox( ((lpszError == NULL) ? ("Application could not be loaded.") : (lpszError)), "Application Error");
  PostQuitMessage(-1);

  return -1;
}


// Loads application options
BOOL LoadAppOptions (LPAPPOPTIONS lpOptions)
{
  if (lpOptions == NULL) return FALSE;

  // !!! Check to see if options exist in hard memory; if not, create it

  // Set the options
  lpOptions->bShowQuitConfirm = false;
  lpOptions->bStartLastPosition = false;
  lpOptions->lastX = 0;
  lpOptions->lastY = 0;
  lpOptions->crSquare1 = 0; //COLOR_BOARDCOLOR_RED;
  lpOptions->crSquare2 = 0; //COLOR_BOARDCOLOR_WHITE;
  

  return TRUE;
}
