// WinFx.cpp
// Windows Basic FX Implementation File
// By Joe Esposito


#pragma once


// Include Header:
#include "eWinFx.h"



// Private Structs
// ----------------

typedef struct _ENUMWINDOWSADV
{
	DWORD dwTargetProcessId;		// The process to be associated with
	LPSTR lpszTargetClass;			// The class of the window
	LPSTR lpszTargetTitle;			// The title of the window
	LPSTR lpszTemp1;				// Temp string (class string)
	LPSTR lpszTemp2;				// Temp string (title string)
	LPARAM lParam;					// Extra data
	HWND hResult;					// hWnd result
} ENUMWINDOWSADV, *LPENUMWINDOWSADV;



// Local Declarations
// -------------------

LOCAL BOOL CALLBACK EnumWindowsAdvProc1 ( HWND hWnd, LPARAM lParam );
LOCAL BOOL CALLBACK EnumWindowsAdvProc2 ( HWND hWnd, LPARAM lParam );



// Public Functions
// -----------------

// Window finding
HWND FindWindowAdv (LPSTR lpClass, LPSTR lpTitle, DWORD dwProcessId)
{
	ENUMWINDOWSADV eaw;
	UINT uLen1, uLen2;


	// Set up struct
	eaw.hResult = NULL;
	eaw.lpszTemp1 = NULL; eaw.lpszTemp2 = NULL;
	eaw.dwTargetProcessId = dwProcessId;
	eaw.lpszTargetClass = NULL; eaw.lpszTargetTitle = NULL;
	eaw.lpszTemp1 = NULL; eaw.lpszTemp2 = NULL;


	// Set up strings
	if (lpClass) {		// Set up target class string
		uLen1 = strlen(lpClass);

		if ((eaw.lpszTargetClass = new char [(uLen1+1)]) == NULL) return NULL;
		if ((eaw.lpszTemp1 = new char [(uLen1+1)]) == NULL) {  delete [(uLen1+1)] eaw.lpszTargetClass; return NULL;  }

		memcpy(eaw.lpszTargetClass, lpClass, uLen1);
		eaw.lpszTargetClass[(uLen1)] = NULL;
	}
	if (lpTitle) {		// Set up target title string
		uLen2 = strlen(lpTitle);

		if ((eaw.lpszTargetTitle = new char [(uLen2+1)]) == NULL) {  if (lpClass) { delete [(uLen1+1)] eaw.lpszTargetClass; delete [(uLen1+1)] eaw.lpszTemp1; }  return NULL;  }
		if ((eaw.lpszTemp2 = new char [(uLen2+1)]) == NULL) {  delete [(uLen2+1)] eaw.lpszTemp2;  if (lpClass) { delete [(uLen1+1)] eaw.lpszTargetClass; delete [(uLen1+1)] eaw.lpszTemp1; }  return NULL;  }

		memcpy(eaw.lpszTargetTitle, lpTitle, uLen2);
		eaw.lpszTargetTitle[(uLen2)] = NULL;
	}
	
	// Search for window
	EnumWindows(EnumWindowsAdvProc1, (LPARAM)&eaw);


	// Clean up
	if (lpClass) {		// Clean up target class data
		delete [(uLen1+1)] eaw.lpszTemp1;
		delete [(uLen1+1)] eaw.lpszTargetClass;
	}
	if (lpTitle) {		// Clean up target class data
		delete [(uLen2+1)] eaw.lpszTemp2;
		delete [(uLen2+1)] eaw.lpszTargetTitle;
	}


	return eaw.hResult;		// Success
}



// Window enumerating
BOOL EnumWindowsAdv (LPSTR lpClass, LPSTR lpTitle, DWORD dwProcessId, WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	ENUMWINDOWSADV eaw;
	UINT uLen1, uLen2;


	// Set up struct
	eaw.lpszTemp1 = NULL; eaw.lpszTemp2 = NULL;
	eaw.dwTargetProcessId = dwProcessId;
	eaw.lpszTargetClass = NULL; eaw.lpszTargetTitle = NULL;
	eaw.lpszTemp1 = NULL; eaw.lpszTemp2 = NULL;
	eaw.hResult = (HWND)lpEnumFunc;
	eaw.lParam = lParam;


	// Set up strings
	if (lpClass) {		// Set up target class string
		uLen1 = strlen(lpClass);

		if ((eaw.lpszTargetClass = new char [(uLen1+1)]) == NULL) return FALSE;
		if ((eaw.lpszTemp1 = new char [(uLen1+1)]) == NULL) {  delete [(uLen1+1)] eaw.lpszTargetClass; return FALSE;  }

		memcpy(eaw.lpszTargetClass, lpClass, uLen1);
		eaw.lpszTargetClass[(uLen1)] = NULL;
	}
	if (lpTitle) {		// Set up target title string
		uLen2 = strlen(lpTitle);

		if ((eaw.lpszTargetTitle = new char [(uLen2+1)]) == NULL) {  if (lpClass) { delete [(uLen1+1)] eaw.lpszTargetClass; delete [(uLen1+1)] eaw.lpszTemp1; }  return FALSE;  }
		if ((eaw.lpszTemp2 = new char [(uLen2+1)]) == NULL) {  delete [(uLen2+1)] eaw.lpszTemp2;  if (lpClass) { delete [(uLen1+1)] eaw.lpszTargetClass; delete [(uLen1+1)] eaw.lpszTemp1; }  return FALSE;  }

		memcpy(eaw.lpszTargetTitle, lpTitle, uLen2);
		eaw.lpszTargetTitle[(uLen2)] = NULL;
	}
	
	// Search for window
	EnumWindows(EnumWindowsAdvProc2, (LPARAM)&eaw);


	// Clean up
	if (lpClass) {		// Clean up target class data
		delete [(uLen1+1)] eaw.lpszTemp1;
		delete [(uLen1+1)] eaw.lpszTargetClass;
	}
	if (lpTitle) {		// Clean up target class data
		delete [(uLen2+1)] eaw.lpszTemp2;
		delete [(uLen2+1)] eaw.lpszTargetTitle;
	}


	return TRUE;		// Success
}



// Local Functions
// ----------------

// FindWindowAdv()
BOOL CALLBACK EnumWindowsAdvProc1 (HWND hWnd, LPARAM lParam)
{
	bool bFound = true;
	DWORD dwTargetProcess, dwTemp;
	LPSTR lpszTargetClass, lpszTargetTitle;
	LPSTR lpszTemp;
	UINT uLen;

	// Get target info
	dwTargetProcess = ((LPENUMWINDOWSADV)lParam)->dwTargetProcessId;
	lpszTargetClass = ((LPENUMWINDOWSADV)lParam)->lpszTargetClass;
	lpszTargetTitle = ((LPENUMWINDOWSADV)lParam)->lpszTargetTitle;


	// Test Process IDs
	if (dwTargetProcess) {
		GetWindowThreadProcessId(hWnd, &dwTemp);
		bFound &= (dwTemp == dwTargetProcess);
	}

	// Test Class
	if (lpszTargetClass) {
		lpszTemp = ((LPENUMWINDOWSADV)lParam)->lpszTemp1;

		// Get length of target strings
		uLen = (strlen(lpszTargetClass) + 1);

		// Get current class
		GetClassName(hWnd, lpszTemp, uLen);

		// Compare current to target
		bFound &= (strnicmp(lpszTemp, lpszTargetClass, uLen) == 0);
	}

	// Test Title
	if (lpszTargetTitle) {
		lpszTemp = ((LPENUMWINDOWSADV)lParam)->lpszTemp2;

		// Get length of target strings
		uLen = (strlen(lpszTargetTitle) + 1);

		// Get current class
		GetClassName(hWnd, lpszTemp, uLen);

		// Compare current to target
		bFound &= (strnicmp(lpszTemp, lpszTargetTitle, uLen) == 0);
	}

	if (bFound) {
		((LPENUMWINDOWSADV)lParam)->hResult = hWnd;
		return FALSE;	// Found
	}

	return TRUE;		// Keep searching
}


// EnumWindowsAdv()
BOOL CALLBACK EnumWindowsAdvProc2 (HWND hWnd, LPARAM lParam)
{
	bool bFound = true;
	DWORD dwTargetProcess, dwTemp;
	LPSTR lpszTargetClass, lpszTargetTitle;
	LPSTR lpszTemp;
	UINT uLen;

	// Get target info
	dwTargetProcess = ((LPENUMWINDOWSADV)lParam)->dwTargetProcessId;
	lpszTargetClass = ((LPENUMWINDOWSADV)lParam)->lpszTargetClass;
	lpszTargetTitle = ((LPENUMWINDOWSADV)lParam)->lpszTargetTitle;


	// Test Process IDs
	if (dwTargetProcess) {
		GetWindowThreadProcessId(hWnd, &dwTemp);
		bFound &= (dwTemp == dwTargetProcess);
	}

	// Test Class
	if (lpszTargetClass) {
		lpszTemp = ((LPENUMWINDOWSADV)lParam)->lpszTemp1;

		// Get length of target strings
		uLen = (strlen(lpszTargetClass) + 1);

		// Get current class
		GetClassName(hWnd, lpszTemp, uLen);

		// Compare current to target
		bFound &= (strnicmp(lpszTemp, lpszTargetClass, uLen) == 0);
	}

	// Test Title
	if (lpszTargetTitle) {
		lpszTemp = ((LPENUMWINDOWSADV)lParam)->lpszTemp2;

		// Get length of target strings
		uLen = (strlen(lpszTargetTitle) + 1);

		// Get current class
		GetClassName(hWnd, lpszTemp, uLen);

		// Compare current to target
		bFound &= (strnicmp(lpszTemp, lpszTargetTitle, uLen) == 0);
	}

	if (bFound)
		return ((WNDENUMPROC)((LPENUMWINDOWSADV)lParam)->hResult)(hWnd, (LPARAM)((LPENUMWINDOWSADV)lParam)->lParam);

	return TRUE;		// Keep searching
}
