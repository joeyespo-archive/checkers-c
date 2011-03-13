// eSkinCore.cpp
// eSkin Core Implmentation File
// By Joe Esposito


#include "Main.h"



// Library Functions
// ------------------

// Returns whether or not layered windows are available
BOOL IsLayeredWindowsAvailable ()
{
	bool bResult;
	HMODULE hmodUser32;
	OSVERSIONINFO osVer = { sizeof(osVer) }; GetVersionEx(&osVer);
	
	// Windows version'ed result
	bResult = ((osVer.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osVer.dwMajorVersion >= 5));
	
	// User32 function failsafe check
	if ((hmodUser32 = GetModuleHandle("user32.dll")) == NULL) return FALSE;
	if (GetProcAddress(hmodUser32, "SetLayeredWindowAttributes") == NULL) { FreeLibrary(hmodUser32); return FALSE; }
	FreeLibrary(hmodUser32);	// Free the library

	return (BOOL)bResult;
}
