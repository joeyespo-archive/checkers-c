// frmAbout.cpp - Checkers
// About Window Implementation File
// By Joey Esposito


#pragma once


// Header File:
#include "Main.h"



// Local Macros
// -------------

// Gradient colors
#define BG_GB_COLOR_TL      0x8888E0
#define BG_GB_COLOR_BL      0x404040
#define BG_GB_COLOR_TR      0x80000018
#define BG_GB_COLOR_BR      0x5050A0

// Window IDs
#define ID_BTN_OK           0x1001



// frmMain Window Procedure
// -------------------------

LRESULT CALLBACK wndAboutProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LPABOUTWNDINFO lpAboutInfo;
  HDC hDC, hDC2;
  PAINTSTRUCT ps;
  HBITMAP hbmTemp;
  HFONT hftTemp;
  HWND hwndTemp;
  RECT rt;


  // Get Window Info
  // ----------------
  
  lpAboutInfo = (LPABOUTWNDINFO)GetWindowLong(hWnd, GWL_USERDATA);



  // Event Switch
  // -------------

  switch (uMsg)
  {
    case WM_CREATE:
      
      // Window Startup Position
      // ------------------------
      
      // Get dimensions
      ((LPCREATESTRUCT)lParam)->cx = (NCWidth(hWnd) + 344);
      ((LPCREATESTRUCT)lParam)->cy = (NCHeight(hWnd) + 178);
      
      GetWindowRect(GetDesktopWindow(), &rt);
      Reposition(hWnd, (((rt.right-rt.left)-((LPCREATESTRUCT)lParam)->cx) / 2), (((rt.bottom-rt.top) - ((LPCREATESTRUCT)lParam)->cy) / 2), ((LPCREATESTRUCT)lParam)->cx, ((LPCREATESTRUCT)lParam)->cy);
      
      
      // Initialize Window
      // ------------------
      
      // Create window info structure
      if ((lpAboutInfo = new ABOUTWNDINFO) == NULL) return -1;
      
      // Set window info
      lpAboutInfo->hicoLogo = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icoMain), IMAGE_ICON, 0, 0, (LR_CREATEDIBSECTION));
      lpAboutInfo->hBackground = CreateGradientBitmap(ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)lpAboutInfo);
      
      
      // Create Window
      // --------------
      
      hwndTemp = CreateButton("OK", (WS_CHILD | WS_GROUP | WS_TABSTOP | WS_VISIBLE), 258, 8, 73, 25, hWnd, ID_BTN_OK, hInstance);
       SendMessage(hwndTemp, WM_SETFONT, (WPARAM)hFont_Main, 0);
      
      break;
    
    case WM_ACTIVATE:
      
      if ((LOWORD(wParam) != WA_INACTIVE) && (HIWORD(wParam) == FALSE))
      { SetFocus(GetDlgItem(hWnd, ID_BTN_OK)); SendMessage(hWnd, DM_SETDEFID, ID_BTN_OK, NULL); return 0; }
      
      break;
    
    case DM_GETDEFID:
      
      return (MAKELONG(ID_BTN_OK, DC_HASDEFID));
    
    case WM_PAINT:
      
      // Failsafe
      if (!lpAboutInfo) break;
      
      
      // Setup Painting
      // ---------------
      
      hDC = BeginPaint(hWnd, &ps);
      
      
      // Paint Background
      // -----------------
      
      if (lpAboutInfo->hBackground) {
        // Paint background bitmap
        hDC2 = CreateCompatibleDC(NULL);
        hbmTemp = (HBITMAP)SelectObject(hDC2, lpAboutInfo->hBackground);
        BitBlt(hDC, ps.rcPaint.left, ps.rcPaint.top, (ps.rcPaint.right - ps.rcPaint.left), (ps.rcPaint.bottom - ps.rcPaint.top), hDC2, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
        SelectObject(hDC2, hbmTemp); DeleteDC(hDC2);
      } else { FillRect(hDC, &ps.rcPaint, (HBRUSH)GetStockObject(LTGRAY_BRUSH)); }
      
      
      // Draw Window
      // ------------
      
      // Draw icon
      rt.left = 8; rt.top = 8; rt.right = 44; rt.bottom = 44; DrawEdge(hDC, &rt, (BDR_SUNKENOUTER), (BF_RECT | BF_MONO));
      DrawIcon(hDC, 10, 10, lpAboutInfo->hicoLogo);
      
      // Set up text drawing
      SetBkMode(hDC, TRANSPARENT); hftTemp = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
      
      // Draw window text
      SelectObject(hDC, hFont_MainBold);
      rt.left = 52; rt.top = 10; rt.right = 232; rt.bottom = 50; DrawText(hDC, "Checkers", -1, &rt, 0);
      rt.left = 52; rt.top = 26; rt.right = 232; rt.bottom = 58; DrawText(hDC, "By Joe Esposito", -1, &rt, 0);
      
      
      // Clean up
      // ---------
      
      SelectObject(hDC, hftTemp);
      EndPaint(hWnd, &ps);
      
      return TRUE;
    
    case WM_SYSCOLORCHANGE:
      
      // Redraw background
      hDC = CreateCompatibleDC(NULL); hbmTemp = (HBITMAP)SelectObject(hDC, lpAboutInfo->hBackground);
      DrawGradientRect(hDC, 0, 0, ClientWidth(hWnd), ClientHeight(hWnd), BG_GB_COLOR_TL, BG_GB_COLOR_BL, BG_GB_COLOR_TR, BG_GB_COLOR_BR);
      SelectObject(hDC, hbmTemp); DeleteDC(hDC);
      break;
    
    case WM_COMMAND:
      
      if (lParam != NULL)
      {
        // Control Notification
        // ---------------------
        
        switch (LOWORD(wParam)) {
        case (ID_BTN_OK | BN_CLICKED):      // OK button
          
          switch (HIWORD(wParam)) {
          case BN_CLICKED:
          
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            return 0;
          }
        }
      }
      
      break;
    
    case WM_CLOSE:
      
      // End the dialog
      EndDialog(hWnd, 0);
      return 0;
    
    case WM_DESTROY:
      
      // Clean up
      // ---------
      
      // Clean up window info
      if (lpAboutInfo) {
        // Destroy windows objects
        DestroyIcon(lpAboutInfo->hicoLogo);      // Destroy logo icon
        DeleteObject(lpAboutInfo->hBackground);    // Destroy background bitmap
        
        // Delete window info
        delete lpAboutInfo;
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)(lpAboutInfo = NULL));
      }
      
      // Failsafe
      EndDialog(hWnd, 0);
      
      break;
  }

  return DefDlgProc(hWnd, uMsg, wParam, lParam);
}



// Public Functions
// -----------------

void DoAbout (HWND hParent)
{ CreateDialogBox((WS_EX_CONTROLPARENT | WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE), ID_ABOUTWND_CLASSNAME, "About Checkers", (WS_VISIBLE | WS_POPUPWINDOW | WS_DLGFRAME | WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | DS_NOIDLEMSG | DS_SETFOREGROUND), CW_USEDEFAULT, CW_USEDEFAULT, 344, 178, hParent, NULL, 0, hInstance, NULL, NULL, true); }
