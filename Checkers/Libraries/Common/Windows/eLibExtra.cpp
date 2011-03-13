// eLibExtra.cpp
// Extra routines for eLib
// By Joe Esposito



typedef WINUSERAPI BOOL (WINAPI *ANIMATEWINDOW) ( HWND hWnd, DWORD dwTime, DWORD dwFlags );

#define AW_HOR_POSITIVE             0x00000001
#define AW_HOR_NEGATIVE             0x00000002
#define AW_VER_POSITIVE             0x00000004
#define AW_VER_NEGATIVE             0x00000008
#define AW_CENTER                   0x00000010
#define AW_HIDE                     0x00010000
#define AW_ACTIVATE                 0x00020000
#define AW_SLIDE                    0x00040000
#define AW_BLEND                    0x00080000


// Animates the window
BOOL AnimateWindow (HWND hWnd, DWORD dwTime, DWORD dwFlags)
{
  HMODULE hModule;
  ANIMATEWINDOW AnimateWindow;
  
  BOOL bResult;
  
  
  // Load the library
  hModule = LoadLibrary("User32");
  AnimateWindow = (ANIMATEWINDOW)GetProcAddress(hModule, "AnimateWindow");
  
  // Animate the window
  bResult = AnimateWindow(m_pr_hWnd, 400, (AW_CENTER | (( cxValue != FALSE )?( 0 ):( SW_HIDE ))));
  
  // Clean up
  FreeLibrary(hModule);
}


void inline WriteLog( char *ch,... )
{
  char buf[1024];
  
  va_list arg_list;
  
  va_start(arg_list, ch);
  wvsprintf(buf, ch, arg_list);
  va_end(arg_list);
  
  FILE *file;
  
  file = fopen("log.txt","a+");
  fprintf( file, "%s", buf );
  fclose( file );
}

// Usage
// WriteLog( "int value=%d \n str value=%s", 19, "test" );
