// CSkin.h
// CSkin Library Header File
// By Joe Esposito



// Import Library
// ---------------

#if ( (!defined(CSKIN_INCLUDE)) && (!defined(CSKIN_SOURCE)) && (!defined(CSKIN_NOLIB)) )
#ifdef _DEBUG
#pragma comment ( lib, "CSkinD.lib" )
#else
#pragma comment ( lib, "CSkin.lib" )
#endif
#endif

#ifdef CSKIN_INCLUDE
#include "CSkin\Main.h"
#endif
#ifdef CSKIN_SOURCE
#define CSKIN_INCLUDE
#include "CSkin\Main.cpp"
#endif



#if ( (!defined(CSKIN_INCLUDE)) && (!defined(CSKIN_SOURCE)) && (!defined(_CSKIN_)) )

#define _CSKIN_



// Public Macros
// --------------

#define LWA_COLORKEY  0x00000001
#define WS_EX_LAYERED  0x00080000



// Public Types
// -------------

typedef BOOL (WINAPI *LPFNSLWA)( HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags );



// Public Classes
// ---------------

class CSkin
{

public:

	// Construction
	// -------------
	
	CSkin ();										// Default constructor
	CSkin ( HBITMAP hBitmap, COLORREF crColorKey );	// Creates an initial skin
	CSkin ( CSkin *lpSkin );						// Duplicates a skin
	virtual ~CSkin ();								// Destructor


protected:

	// Protected Variables
	// --------------------
	
	COLORREF m_crColorKey;			// Color key of the bitmap
	HBITMAP m_hbmpBitmap;			// Bitmap from the device context
	HBITMAP m_hbmpOriginal;			// Original bitmap image
	HRGN m_hSkinRgn;				// Skin region (if using windows 9x)


public:

	// Public Functions
	// -----------------
	
	// CSkin functions
	BOOL Create ( HBITMAP hBitmap, COLORREF crColorKey );		// Creates a skin
	BOOL Create ( CSkin *lpSkin );			// Duplicates a skin
	BOOL SkinExists ();						// Returns true if a skin was created
	BOOL Destroy ();						// Destroys the skin
	
	
	// Windows functions
	HRGN GetRgn () { return ((m_hbmpBitmap)?(m_hSkinRgn):(0)); }
	HBITMAP GetBitmap () { return (m_hbmpBitmap); }
	HBITMAP GetBltBitmap () { return ((m_hbmpBitmap)?(m_hbmpOriginal):(0)); }
	COLORREF GetColorKey () { return ((m_hbmpBitmap)?(m_crColorKey):(0)); }
	
	// Bitmap functions
	INT GetWidth () { BITMAP bm;  if (!m_hbmpBitmap) return 0;  GetObject(m_hbmpBitmap, sizeof(BITMAP), &bm); return bm.bmWidth; }
	INT GetHeight () { BITMAP bm;  if (!m_hbmpBitmap) return 0;  GetObject(m_hbmpBitmap, sizeof(BITMAP), &bm); return bm.bmHeight; }


	// Friend Functions
	// -----------------
	
	// Skin window procedure, where the class will handle the WM_PAINT and the WM_LBUTTONDOWN automatically
    friend LRESULT CALLBACK CSkinWndProc ( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );
};



// CSkinWindow class
class CSkinWindow
{

public:

	// Construction
	// -------------
	
	CSkinWindow ();													// Default constructor
	CSkinWindow ( HWND hWnd );										// Subclasses in constructor
	CSkinWindow ( HWND hWnd, CSkin *lpSkin );						// Subclasses and creates skin in constructor
	CSkinWindow ( HWND hWnd, HBITMAP hBitmap, COLORREF crColorKey );// Subclasses and sets skin in constructor
	virtual ~CSkinWindow ();										// Destructor


protected:

	// Protected Variables
	// --------------------
	
	// CSkin variables
	CSkin *m_lpSkin;				// The CSkin of the window
	
	// Window veriables
	HWND m_hWnd;					// The associated window handle
	WNDPROC m_WndProc;				// The window procedure of the window
	
	// CSkinWindow variables
	bool m_bEnabled;				// Holds enabled value


public:

	// Public Functions
	// -----------------
	
	// CSkin functions
	BOOL SetSkin ( CSkin *lpSkin );	// Sets the skin
	BOOL SetSkin ( HBITMAP hBitmap, COLORREF crColorKey );	// Sets the skin from a bitmap
	CSkin *GetSkin ();				// Returns the current skin
	BOOL IsSkinSet ();				// Returns true if a skin was set
	BOOL RemoveSkin ();				// Removes the skin
	
	// Skin subclassing
	BOOL Hook ( HWND hWnd );		// Subclasses the window, then enables it
	BOOL Hook ( HWND hWnd, BOOL bEnable );	// Subclasses the window
	BOOL IsHooked ();				// Returns true if window is already subclassed
	BOOL UnHook ();					// Unsubclass the subclassed window
	
	// Skin enable
	BOOL Enable ( BOOL bEnable );	// Toggle skin on/off
	BOOL IsEnabled ();				// Returns true if skin is enabled
	
	// Operators
	operator CSkin * () { return m_lpSkin; }



	// Friend Functions
	// -----------------
	
	// Skin window procedure, where the class will handle the WM_PAINT and the WM_LBUTTONDOWN automatically
    friend LRESULT CALLBACK CSkinWndProc ( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );
};



// Public Functions
// -----------------

// CSkin functions
BOOL SetWindowTransparency ( HWND hWnd, CSkin *lpSkin, DWORD dwTransparencyType, BOOL bEnableTransparency );
BOOL TransparentWindowBitmapBlt ( HDC hDC, CSkin *lpSkin );

// Layered window functions
BOOL SetTransparentWindowColor ( HWND hWnd, COLORREF crColorKey );	// Sets the transparent attributes on a window
BOOL ClearTransparentWindowColor ( HWND hWnd );		// Clears the transparent attributes of a window
BOOL IsLayeredWindowsAvailable ();			// Returns TRUE if layered windows is available
HRGN CreateRegionFromBitmap ( HBITMAP hBitmap, COLORREF crColorKey );	// Creates a region from a bitmap
HRGN CreateRegionFromDIBitmap ( LPVOID lpBits, LONG lWidth, LONG lHeight, COLORREF crColorKey );	// Creates a region from a device-independent bitmap (32-bit bitmaps only)


#endif
