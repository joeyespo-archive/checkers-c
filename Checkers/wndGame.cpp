// wndGame.cpp - Checkers
// Game Window Implementation File
// By Joey Esposito


#pragma once


// Header File:
#include "Main.h"



// Local Macros
// -------------

#define BG_GB_COLOR_TL      0xC0F0C0
#define BG_GB_COLOR_BL      0x608060
#define BG_GB_COLOR_TR      0xE0FFE0
#define BG_GB_COLOR_BR      0x80A080

#define NUM_BOARD_TOP       14
#define NUM_BOARD_LEFT      14

#define ID_GAMEBOARD        1000
#define ID_BTN_START        1001
#define ID_BTN_QUIT         1006



// Local Variables
// ----------------

LOCAL HWND hwndGameWnd = NULL;
LOCAL HWND hwndGameBoard = NULL;
LOCAL HWND hwndGameButton = NULL;
LOCAL HBITMAP hbmpBackground = NULL;
LOCAL HBITMAP hGameBoard;
LOCAL INT nClientHeight, nClientWidth;
LOCAL UINT uGame;
LOCAL HICON hicoPawn_Red, hicoKing_Red;
LOCAL HICON hicoPawn_Black, hicoKing_Black;
LOCAL HCURSOR hcurPawn_Red, hcurKing_Red;
LOCAL HCURSOR hcurPawn_Black, hcurKing_Black;



// wndGame Window Procedure
// -------------------------

LRESULT CALLBACK wndGameProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  UNION { COLORREF crTemp1; INT x; };
  UNION { COLORREF crTemp2; INT y; };
  UNION { COLORREF crTemp3; PAINTSTRUCT ps; };
  UNION { COLORREF crTemp4; HFONT hftTemp; };
  HDC hDC, hdcTemp;
  HBITMAP hbmpTemp;
  INT nWidth, nHeight;
  RECT rt;
  
  switch (uMsg)
  {
    case WM_CREATE:
      
      if (hwndGameWnd != NULL) return -1;
      hDialogWnd = (hwndGameWnd = hWnd);
      
      
      // Initialize Window
      // ------------------
      
      // Load icons
      //hicoPawn_Red = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoPawn_Red), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      //hicoKing_Red = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoKing_Red), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      //hicoPawn_Black = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoPawn_Black), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      //hicoKing_Black = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoKing_Black), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      
      // Load cursors
      //hcurPawn_Red = (HCURSOR)LoadImage(hInstance, MAKEINTRESOURCE(curPawn_Red), IMAGE_CURSOR, 0, 0, (LR_CREATEDIBSECTION));
      //hcurKing_Red = (HCURSOR)LoadImage(hInstance, MAKEINTRESOURCE(curKing_Red), IMAGE_CURSOR, 0, 0, (LR_CREATEDIBSECTION));
      //hcurPawn_Black = (HCURSOR)LoadImage(hInstance, MAKEINTRESOURCE(curPawn_Black), IMAGE_CURSOR, 0, 0, (LR_CREATEDIBSECTION));
      //hcurKing_Black = (HCURSOR)LoadImage(hInstance, MAKEINTRESOURCE(curKing_Black), IMAGE_CURSOR, 0, 0, (LR_CREATEDIBSECTION));
      
      
      
      // Window Startup Position
      // ------------------------
      
      ((LPCREATESTRUCT)lParam)->cx = NCWidth(hWnd) + 445;
      ((LPCREATESTRUCT)lParam)->cy = NCHeight(hWnd) + 293;
      
      if (oOptions.bStartLastPosition)
      {  Reposition(hWnd, oOptions.lastX, oOptions.lastY, ((LPCREATESTRUCT)lParam)->cx, ((LPCREATESTRUCT)lParam)->cy);  }
      else {
        GetWindowRect(GetDesktopWindow(), &rt);
        Reposition(hWnd, (((rt.right-rt.left)-((LPCREATESTRUCT)lParam)->cx) / 2), (((rt.bottom-rt.top) - ((LPCREATESTRUCT)lParam)->cy) / 2), ((LPCREATESTRUCT)lParam)->cx, ((LPCREATESTRUCT)lParam)->cy);
      }
      
      
      // Create Window
      // --------------
      
      // Create controls
      hwndGameButton = CreateWindow("button", "Start &Game", (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON), 320, 8, 80, 30, hWnd, (HMENU)ID_BTN_START, hInstance, NULL);
       SendMessage(hwndGameButton, WM_SETFONT, (WPARAM)hFont_Main, 0);
      
      // Create board
      hwndGameBoard = CreateWindowEx((WS_EX_CONTROLPARENT), "eckwindow", NULL, (WS_CHILD | WS_VISIBLE | CKS_AUTOSIZE | CKS_NOAUTOUPDATE), 8, 8, 0, 0, hWnd, (HMENU)ID_GAMEBOARD, hInstance, NULL);
       SendMessage(hwndGameBoard, WCKM_SETSCHEMECOLOR, CSI_BACKGROUND, COLOR_BOARD_BACKGROUND);
       SendMessage(hwndGameBoard, WCKM_SETSQUAREBORDERCOLOR, 0, COLOR_BOARD_BORDER);
       SendMessage(hwndGameBoard, WCKM_SETBOARDCOLOR1, NULL, COLOR_BOARD_STANDARD); SendMessage(hwndGameBoard, WCKM_SETBOARDCOLOR2, NULL, COLOR_BOARD_STANDARDBK);
       SendMessage(hwndGameBoard, WCKM_SETPIECEPIC, MAKELONG(CKR_PAWN, 1), (LPARAM)hicoPawn_Red); SendMessage(hwndGameBoard, WCKM_SETPIECEPIC, MAKELONG(CKR_KING, 1), (LPARAM)hicoKing_Red);
       SendMessage(hwndGameBoard, WCKM_SETPIECEPIC, MAKELONG(CKR_PAWN, 2), (LPARAM)hicoPawn_Black); SendMessage(hwndGameBoard, WCKM_SETPIECEPIC, MAKELONG(CKR_KING, 2), (LPARAM)hicoKing_Black);
       SendMessage(hwndGameBoard, WCKM_SETPIECECURSOR, MAKELONG(CKR_PAWN, 1), (LPARAM)hcurPawn_Red); SendMessage(hwndGameBoard, WCKM_SETPIECECURSOR, MAKELONG(CKR_KING, 1), (LPARAM)hcurKing_Red);
       SendMessage(hwndGameBoard, WCKM_SETPIECECURSOR, MAKELONG(CKR_PAWN, 2), (LPARAM)hcurPawn_Black); SendMessage(hwndGameBoard, WCKM_SETPIECECURSOR, MAKELONG(CKR_KING, 2), (LPARAM)hcurKing_Black);
       ModifyStyle(hwndGameBoard, CKS_NOAUTOUPDATE, NULL, 0);
      
      // Create background
      SendMessage(hWnd, WM_DRAWBACKGROUND, NULL, NULL);
      break;
    
    case WM_ACTIVATE:
      
      if ((LOWORD(wParam) != WA_INACTIVE) && (HIWORD(wParam) == FALSE))
      { SetFocus(hwndGameButton); return 0; }
      
      break;
    
    case WM_DRAWBACKGROUND:
      
      // Get/create bitmap
      if (hbmpBackground) {
        hDC = CreateCompatibleDC(NULL); hbmpTemp = (HBITMAP)SelectObject(hDC, hbmpBackground);
        DrawGradientRect(hDC, 0, 0, nClientWidth, nClientHeight, BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
      }
      else {
        if ((hbmpBackground = CreateGradientBitmap((nClientWidth = ClientWidth(hWnd)), (nClientHeight = ClientHeight(hWnd)), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR)) == NULL) return FALSE;
        
        hDC = CreateCompatibleDC(NULL);
        hbmpTemp = (HBITMAP)SelectObject(hDC, hbmpBackground);
      }
      
      
      // Initialize drawing
      SendMessage(hwndGameBoard, WCKM_GETSIZE, NULL, (LPARAM)&rt);  // Get new size
      rt.top = 4; rt.left = 4; rt.bottom = 40; rt.top = 40;
      nWidth = (rt.right-rt.left); nHeight = (rt.bottom-rt.top);
      GetWindowRect(hwndGameBoard, &rt); MapWindowPoints(NULL, hWnd, (LPPOINT)&rt, 2);
      rt.left -= 2; rt.top -= 2; nWidth += 4; nHeight += 4;
      
      
      // Draw Board Frame Border
      // ------------------------
      
      // !!!!! ?? Get pixels on bg for highlighting and shadowing (frame border)
      crTemp1 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left), (rt.top), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      crTemp2 = GetGradientPixel(100, 90, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+1), (rt.top+1), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      crTemp3 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left), (rt.top+rt.bottom), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      crTemp4 = GetGradientPixel(100, 90, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+1), (rt.top+rt.bottom-1), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      
      // !!!!! ?? Draw verticle borders
      DrawGradientVert(hDC, (rt.left), (rt.top), (nHeight-1), crTemp1, crTemp3);
      DrawGradientVert(hDC, (rt.left+1), (rt.top+1), (nHeight-3), crTemp2, crTemp4);
      
      
      // !!!!! Get ??
      crTemp3 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right-1), (rt.top), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      crTemp4 = GetGradientPixel(100, 90, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right-2), (rt.top+1), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0x000000);
      
      // !!!!! ?? Draw ..
      DrawGradientHoriz(hDC, (rt.left), (rt.top), (nWidth-1), crTemp1, crTemp3);
      DrawGradientHoriz(hDC, (rt.left+1), (rt.top+1), (nWidth-3), crTemp2, crTemp4);
      
      // !!!!! ?? Draw ..
      crTemp1 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right), (rt.top+rt.bottom), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      crTemp2 = GetGradientPixel(100, 0, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right-1), (rt.top+rt.bottom-1), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      crTemp3 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right), (rt.top), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      crTemp4 = GetGradientPixel(100, 0, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left+rt.right-1), (rt.top+2), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      
      // !!!!! ?? Draw ..
      DrawGradientVert(hDC, (rt.left+nWidth-1), (rt.top), (nHeight), crTemp3, crTemp1);
      DrawGradientVert(hDC, (rt.left+nWidth-2), (rt.top+2), (nHeight-3), crTemp4, crTemp2);
      
      // !!!!! ?? Draw ..
      crTemp3 = GetGradientPixel(100, 50, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left), (rt.top+rt.bottom), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      crTemp4 = GetGradientPixel(100, 0, GetGradientRectPixel(nClientWidth, nClientHeight, (rt.left-2), (rt.top+rt.bottom-1), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR), 0xFFFFFF);
      
      // !!!!! ?? Draw ..
      DrawGradientHoriz(hDC, (rt.left), (rt.top+nHeight-1), (nWidth), crTemp3, crTemp1);
      DrawGradientHoriz(hDC, (rt.left+2), (rt.top+nHeight-2), (nWidth-3), crTemp4, crTemp2);
      
      
      // Clean up
      SelectObject(hDC, hbmpTemp); DeleteDC(hDC);
      
      // Redraw window
      if (HasStyle(hWnd, WS_VISIBLE)) {
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
      }

      return TRUE;
    
    case WM_PAINT:
      
      // Setup painting
      hDC = BeginPaint(hWnd, &ps);
      
      // Setup background
      hdcTemp = CreateCompatibleDC(NULL);
      hbmpTemp = (HBITMAP)SelectObject(hdcTemp, hbmpBackground);
      
      
      // Paint background
      BitBlt(hDC, 0, 0, nClientWidth, nClientHeight, hdcTemp, 0, 0, SRCCOPY);
      
      
      // Draw Text
      SetBkMode(hDC, TRANSPARENT); hftTemp = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
      
      
      // Clean up
      SelectObject(hdcTemp, hbmpTemp); DeleteDC(hdcTemp);
      SelectObject(hDC, hftTemp);
      EndPaint(hWnd, &ps);
      return TRUE;
    
    case WM_SYSCOLORCHANGE:
      
      SendMessage(hWnd, WM_DRAWBACKGROUND, NULL, NULL);
      break;
    
    case WM_COMMAND:
      
      if (lParam != NULL)
      {
        // Control Notification
        // ---------------------
        
        switch (LOWORD(wParam)) {
        case ID_BTN_START:      // Game button
          
          if (!SendMessage(hwndGameBoard, WCKM_STARTED, NULL, (CKG_NORMAL)))
          {
            // Start the game
            SetWindowText(hwndGameButton, "End &Game");
            if (!SendMessage(hwndGameBoard, WCKM_STARTGAME, NULL, (CKG_NORMAL)))
            { SetWindowText(hwndGameButton, "Start &Game"); }
          }
          else {
            // End the game
            SetWindowText(hwndGameButton, "Start &Game");
            if (!SendMessage(hwndGameBoard, WCKM_STOPGAME, NULL, FALSE))
            { SetWindowText(hwndGameButton, "End &Game"); }
          }
          break;
        
        case ID_BTN_QUIT:      // Quit Game
          
          ModifyStyle((HWND)lParam, BS_DEFPUSHBUTTON, NULL, NULL);
          SendMessage(hWnd, WM_CLOSE, NULL, NULL);
          break;
        
        case ID_GAMEBOARD:      // Checkers gameboard messages
          
          // Gameboard Messages
          // -------------------
          
          switch (HIWORD(wParam)) {
          case WCKN_STARTGAME:    sndPlaySound("Sounds\\StartGame.wav", (SND_ASYNC)); return 0;
          case WCKN_PICKUPPIECE:    sndPlaySound("Sounds\\Select.wav", (SND_ASYNC)); return 0;
          case WCKN_NOPICKUPPIECE:  sndPlaySound("Sounds\\NoSelect.wav", (SND_ASYNC)); return 0;
          case WCKN_ILLEGALMOVE:    sndPlaySound( ((SendMessage((HWND)lParam, WCKM_GETHELDORIGIN, NULL, NULL) == SendMessage((HWND)lParam, WCKM_GETDROPPOSITION, NULL, NULL))?("Sounds\\Select.wav"):("Sounds\\Illegal.wav")), (SND_ASYNC)); return 0;
          case WCKN_MOVEPIECE:    sndPlaySound("Sounds\\Drop.wav", (SND_ASYNC)); return 0;
          case WCKN_JUMPPIECE:    sndPlaySound("Sounds\\Jump.wav", (SND_ASYNC)); return 0;
          case WCKN_MULTIJUMPPIECE:  sndPlaySound("Sounds\\DblJump.wav", (SND_ASYNC)); return 0;
          case WCKN_KINGED:      sndPlaySound("Sounds\\King.wav", (SND_ASYNC)); return 0;
          case WCKN_ENDGAME:      sndPlaySound("Sounds\\EndGame.wav", (SND_ASYNC)); return 0;
          } return 0;
        }
      }
      
      break;
    
    case WM_LBUTTONDOWN:  // Check for board click
      
      /*
      if (((LOWORD(lParam) >= NUM_BOARD_LEFT) && (LOWORD(lParam) < (NUM_BOARD_LEFT+NUM_BOARD_WIDTH))) && ((HIWORD(lParam) >= NUM_BOARD_TOP) && (HIWORD(lParam) < (NUM_BOARD_TOP+NUM_BOARD_HEIGHT))))
      {  // Board clicked
        //SendCkMessage()
        //ClickCkPos(LOWORD(lParam), HIWORD(lParam));
      }*/
      break;
    
    case WM_CLOSE:    // Quit Checkers
      //if ( playing ) if (MsgBox("Quit current game?", "Checkers", (MB_YESNO | MB_ICONQUESTION), hWnd) == IDNO)
      //  return 0;
      
      EndGame();
      return 0;
    
    case WM_DESTROY:
      
      // Clean up
      DeleteObject(hGameBoard); hGameBoard = NULL;
      DeleteObject(hbmpBackground); hbmpBackground = NULL;
      DestroyIcon(hicoPawn_Red); DestroyIcon(hicoKing_Red);
      DestroyIcon(hicoPawn_Black); DestroyIcon(hicoKing_Black);
      DestroyCursor(hcurPawn_Red); DestroyCursor(hcurKing_Red);
      DestroyCursor(hcurPawn_Black); DestroyCursor(hcurKing_Black);
      
      hwndGameWnd = NULL;
      
      EndGame();  // Failsafe
      break;
  }


  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// Starts the game window
BOOL DoGame (UINT param_uGame)
{
  HWND hWnd;

  if (hwndGameWnd != NULL) return FALSE;

  
  uGame = param_uGame;  // !!!!! Type of game (1player, 2player, etc)
  
  // !!!!! Caption: display mode
  if ((hWnd = CreateWindowEx((WS_EX_DLGMODALFRAME | WS_EX_CONTROLPARENT | WS_EX_WINDOWEDGE), ID_GAMEWND_CLASSNAME, "Checkers Game", (WS_FIXEDWINDOW), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL)) == NULL) return FALSE;
  ShowWindow(hWnd, SW_SHOW);
  
  return TRUE;
}

// Ends the game window
VOID EndGame ()
{ HWND hWnd = CreateMainWindow(); ShowWindow(hWnd, SW_SHOW); if (hwndGameWnd) DestroyWindow(hwndGameWnd); }
