// frmMain.cpp - Checkers
// Main Window Implementation File
// By Joe Esposito


#pragma once


// Header File:
#include "Main.h"



// Local Macros
// -------------

// Gradient colors
#define BG_GB_COLOR_TL      0xFF8080
#define BG_GB_COLOR_BL      0x343434
#define BG_GB_COLOR_TR      0x8000000F
#define BG_GB_COLOR_BR      0x505050

// Window IDs
#define ID_BTN_1PLAYER      1001
#define ID_BTN_2PLAYER      1002
#define ID_BTN_ONLINE       1003
#define ID_BTN_OPTIONS      1004
#define ID_BTN_ABOUT        1005
#define ID_BTN_QUIT         1006



// Local Variables
// ----------------

LOCAL HWND hMainWnd = NULL;
LOCAL BOOL bAppEnding;



// frmMain Window Procedure
// -------------------------

LRESULT CALLBACK wndMainProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LPMAINWNDINFO lpMainInfo;
  HWND hwndTemp;
  HDC hDC, hDC2;
  PAINTSTRUCT ps;
  HBITMAP hbmTemp;
  HFONT hftTemp;
  RECT rt;
  char lpClass [7];


  // Get Window Info
  // ----------------
  
  lpMainInfo = (LPMAINWNDINFO)GetWindowLong(hWnd, GWL_USERDATA);



  // Event Switch
  // -------------
  
  switch (uMsg)
  {
    case WM_CREATE:
      
      bAppEnding = TRUE;  // In case the system decides to destroy this window to end the project
      if (hMainWnd != NULL) return -1;
      hDialogWnd = (hMainWnd = hWnd);
      
      
      // Window Startup Position
      // ------------------------
      
      // Get dimensions
      ((LPCREATESTRUCT)lParam)->cx = (NCWidth(hWnd) + 261);
      ((LPCREATESTRUCT)lParam)->cy = (NCHeight(hWnd) + 129);
      
      if (oOptions.bStartLastPosition)
      {  Reposition(hWnd, oOptions.lastX, oOptions.lastY, (((LPCREATESTRUCT)lParam)->cx), (((LPCREATESTRUCT)lParam)->cy));  }
      else {
        GetWindowRect(GetDesktopWindow(), &rt);
        Reposition(hWnd, (((rt.right-rt.left)-((LPCREATESTRUCT)lParam)->cx) / 2), (((rt.bottom-rt.top) - ((LPCREATESTRUCT)lParam)->cy) / 2), ((LPCREATESTRUCT)lParam)->cx, ((LPCREATESTRUCT)lParam)->cy);
      }
      
      
      // Initialize Window
      // ------------------
      
      // Create window info structure
      if ((lpMainInfo = new MAINWNDINFO) == NULL) return -1;
      
      // Set window info
      lpMainInfo->hicoLogo = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hico1Player = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ico1Player), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hico2Player = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ico2Player), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hicoOnline = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoOnline), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hico1Player_Over = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ico1Player_Over), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hico2Player_Over = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ico2Player_Over), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hicoOnline_Over = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoOnline_Over), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpMainInfo->hBackground = CreateGradientBitmap(ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)lpMainInfo);
      
      
      
      // Create Window
      // --------------
      
      // Create game buttons
      hwndTemp = CreateButton(NULL, (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON | BS_NOTIFY), 8, 80, 45, 42, hWnd, ID_BTN_1PLAYER, hInstance);
       SendMessage(hwndTemp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico1Player);
      hwndTemp = CreateButton(NULL, (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON | BS_NOTIFY), 60, 80, 45, 42, hWnd, ID_BTN_2PLAYER, hInstance);
       SendMessage(hwndTemp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico2Player);
      hwndTemp = CreateButton(NULL, (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON | BS_NOTIFY), 120, 80, 45, 42, hWnd, ID_BTN_ONLINE, hInstance);
       SendMessage(hwndTemp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hicoOnline);
      
      // Create menu buttons
      hwndTemp = CreateButton("&Options...", (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON), 184, 96, 69, 25, hWnd, ID_BTN_OPTIONS, hInstance);
       SendMessage(hwndTemp, WM_SETFONT, (WPARAM)hFont_Main, 0);
      hwndTemp = CreateButton("&About...", (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON), 184, 4, 73, 25, hWnd, ID_BTN_ABOUT, hInstance);
       SendMessage(hwndTemp, WM_SETFONT, (WPARAM)hFont_Main, 0);
      hwndTemp = CreateButton("&Quit", (WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON), 184, 32, 73, 25, hWnd, ID_BTN_QUIT, hInstance);
       SendMessage(hwndTemp, WM_SETFONT, (WPARAM)hFont_Main, 0);
      
      break;
    
    case WM_ACTIVATE:
      
      // Focus correct button
      if ((LOWORD(wParam) != WA_INACTIVE) && (HIWORD(wParam) == FALSE))
      {
        for (hwndTemp = GetWindow(hWnd, GW_CHILD); hwndTemp != NULL; hwndTemp = GetNextWindow(hwndTemp, GW_HWNDNEXT)) {
          if ((GetWindowLong(hwndTemp, GWL_STYLE) & (BS_DEFPUSHBUTTON | WS_TABSTOP)) == (BS_DEFPUSHBUTTON | WS_TABSTOP))
            if (GetClassName(hwndTemp, lpClass, 7) == 6) if (!strnicmp(lpClass, "button", 7))
            {  SetFocus(hwndTemp); return 0;  }
        }
        
        if (hwndTemp == NULL) {
          for (hwndTemp = GetWindow(hWnd, GW_CHILD); hwndTemp != NULL; hwndTemp = GetNextWindow(hwndTemp, GW_HWNDNEXT)) {
            if ((GetWindowLong(hwndTemp, GWL_STYLE) & (WS_TABSTOP)) == (WS_TABSTOP)) {
              if (GetClassName(hwndTemp, lpClass, 7) == 6) if (!strnicmp(lpClass, "button", 7)) SendMessage(hwndTemp, BM_SETSTYLE, BS_DEFPUSHBUTTON, TRUE);
              SetFocus(hwndTemp);
              return 0;
            }
          }
        }
      }
      
      break;
    
    case WM_PAINT:
      
      // Failsafe
      if (!lpMainInfo) break;
      
      
      // Setup Painting
      // ---------------
      
      hDC = BeginPaint(hWnd, &ps);
      GetClientRect(hWnd, &rt);
      
      
      // Paint Background
      // -----------------
      
      if (lpMainInfo->hBackground) {
        // Paint background bitmap
        hDC2 = CreateCompatibleDC(NULL);
        hbmTemp = (HBITMAP)SelectObject(hDC2, lpMainInfo->hBackground);
        BitBlt(hDC, ps.rcPaint.left, ps.rcPaint.top, (ps.rcPaint.right - ps.rcPaint.left), (ps.rcPaint.bottom - ps.rcPaint.top), hDC2, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
        SelectObject(hDC2, hbmTemp); DeleteDC(hDC2);
      } else { FillRect(hDC, &ps.rcPaint, (HBRUSH)GetStockObject(LTGRAY_BRUSH)); }
      
      
      // Draw Window
      // ------------
      
      // Draw logo icon
      DrawIcon(hDC, 8, 8, lpMainInfo->hicoLogo);
      
      // Set up text drawing
      SetBkMode(hDC, TRANSPARENT); hftTemp = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
      
      // Draw window text
      SelectObject(hDC, hFont_MainBold);
      rt.left = 52; rt.top = 8; rt.right = 232; rt.bottom = 40; DrawText(hDC, "Checkers", -1, &rt, 0);
      rt.left = 52; rt.top = 24; rt.right = 232; rt.bottom = 56; DrawText(hDC, "By Joe Esposito", -1, &rt, 0);
      SelectObject(hDC, hFont_Main);
      rt.left = 8; rt.top = 60; rt.right = 188; rt.bottom = 92; DrawText(hDC, "&Select a game...", -1, &rt, 0);
      
      
      // Clean up
      // ---------
      
      SelectObject(hDC, hftTemp);
      EndPaint(hWnd, &ps);
      
      return TRUE;
    
    case WM_SYSCOLORCHANGE:
      
      hDC = CreateCompatibleDC(NULL); hbmTemp = (HBITMAP)SelectObject(hDC, lpMainInfo->hBackground);
      DrawGradientRect(hDC, 0, 0, ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
      SelectObject(hDC, hbmTemp); DeleteDC(hDC);
      UpdateWindow(hWnd);
      break;
    
    case WM_COMMAND:
      
      if (lParam != NULL)
      {
        // Control Notification
        // ---------------------
        
        // !!!!! Rearrange switches
        switch (HIWORD(wParam))
        {
        case BN_MOUSEENTER:        // Mouse Enter
          
          switch (LOWORD(wParam)) {
          case ID_BTN_1PLAYER: SendMessage(GetDlgItem(hWnd, ID_BTN_1PLAYER), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico1Player_Over); break;
          case ID_BTN_2PLAYER: SendMessage(GetDlgItem(hWnd, ID_BTN_2PLAYER), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico2Player_Over); break;
          case ID_BTN_ONLINE: SendMessage(GetDlgItem(hWnd, ID_BTN_ONLINE), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hicoOnline_Over); break;
          } break;
        
        case BN_MOUSEEXIT:        // Mouse Exit
          
          switch (LOWORD(wParam)) {
          case ID_BTN_1PLAYER: SendMessage(GetDlgItem(hWnd, ID_BTN_1PLAYER), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico1Player); break;
          case ID_BTN_2PLAYER: SendMessage(GetDlgItem(hWnd, ID_BTN_2PLAYER), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hico2Player); break;
          case ID_BTN_ONLINE: SendMessage(GetDlgItem(hWnd, ID_BTN_ONLINE), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (WPARAM)lpMainInfo->hicoOnline); break;
          } break;
        
        case BN_CLICKED:
          
          // Button Clicked
          // ---------------
          
          if (GetFocus() != (HWND)lParam) {
            if (GetClassName(hwndTemp = GetFocus(), lpClass, 7) == 6) if (!strnicmp(lpClass, "button", 7))
            { SetWindowLong(hwndTemp, GWL_STYLE, (GetWindowLong(hwndTemp, GWL_STYLE) & (~BS_DEFPUSHBUTTON))); }
            
            // Give button focus
            SetFocus((HWND)lParam);
            SetWindowLong((HWND)lParam, GWL_STYLE, (GetWindowLong((HWND)lParam, GWL_STYLE) | BS_DEFPUSHBUTTON));
            InvalidateRect((HWND)lParam, NULL, FALSE); UpdateWindow((HWND)lParam);
          }
          
          switch (LOWORD(wParam)) {
          case ID_BTN_1PLAYER:    // 1 Player game
            
            if (!DoGame(GAME_1PLAYER)) AppFailed("Could not load game window");
            bAppEnding = FALSE; DestroyWindow(hWnd);
            break;
          
          case ID_BTN_2PLAYER:    // 2 Player game
            
            MsgBox("2 Player mode not yet available.", "Checkers", MB_OK, hWnd);
            break;
          
          case ID_BTN_ONLINE:      // Online game
            
            MsgBox("Online mode not yet available.", "Checkers", MB_OK, hWnd);
            break;
          
          case ID_BTN_OPTIONS:    // Show Options window
            
            //!!!!! DoOptions();
            break;
          
          case ID_BTN_ABOUT:      // Show About window
            
            DoAbout(hWnd);
            break;
          
          case ID_BTN_QUIT:      // Quit Checkers
            
            SendMessage(hWnd, WM_CLOSE, NULL, NULL);
            break;
          }
        }
      }
      
      break;
    
    case WM_CLOSE:    // Quit Checkers
      if (oOptions.bShowQuitConfirm) if (MsgBox("Quit Checkers?", "Checkers", (MB_YESNO | MB_ICONQUESTION), hWnd) == IDNO)
        return 0;
      
      bAppEnding = TRUE;
      break;
    
    case WM_DESTROY:
       
      // Clean up
      // ---------
      
      // Clean up window info
      if (lpMainInfo) {
        // Destroy windows objects
        SAFE_DESTROYICON(lpMainInfo->hicoLogo);    // Destroy logo icon
        SAFE_DELETEOBJ(lpMainInfo->hBackground);  // Destroy background bitmap
        
        // Delete icons
        SAFE_DESTROYICON(lpMainInfo->hico1Player); SAFE_DESTROYICON(lpMainInfo->hico1Player_Over);
        SAFE_DESTROYICON(lpMainInfo->hico2Player); SAFE_DESTROYICON(lpMainInfo->hico2Player_Over);
        SAFE_DESTROYICON(lpMainInfo->hicoOnline); SAFE_DESTROYICON(lpMainInfo->hicoOnline_Over);
        
        
        // Delete window info
        delete lpMainInfo;
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)(lpMainInfo = NULL));
      }
      
      // Clear sound buffer
      PlaySound(NULL, NULL, (SND_PURGE));
      
      // End application
      hMainWnd = NULL;
      if (bAppEnding) PostQuitMessage(0);
      break;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



// Public Functions
// -----------------

HWND CreateMainWindow ()
{ if (hMainWnd != NULL) return NULL;  return CreateWindowEx((WS_EX_APPWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT), ID_MAINWND_CLASSNAME, "Checkers", (WS_FIXEDWINDOW), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, 0); }
