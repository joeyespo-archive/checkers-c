// ButtonAdv.cpp
// ButtonAdv Library Implementation File
// By Joe Esposito


#pragma once



// Public Functions
// -----------------

// Registers the ButtonAdv windows class
BOOL WINAPI RegisterButtonAdv (HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	// Get button info
	wcex.cbSize = sizeof(WNDCLASSEX);
	GetClassInfoEx(NULL, "button", &wcex);

	// Set internal information
	if (m_ButtonAdvInfo == NULL) {
		if ((m_ButtonAdvInfo = new BUTTONADVCLASSINFO) == NULL) return FALSE;
		
		// Set info
		m_ButtonAdvInfo->uRegisterCount = 0;				// Register count starts at 0
		m_ButtonAdvInfo->lpButtonProc = DefButtonAdvProc();	// Get button window procedure
		
		// Index for local window info (on a DWORD-aligned address)
		m_ButtonAdvInfo->uWindowIndex = (wcex.cbWndExtra + (4 - (wcex.cbWndExtra % 4)));
	}

	// Set ButtonAdv information
	wcex.lpszClassName = ID_BUTTONADV_CLASSNAME;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = (WNDPROC)_ButtonAdvProc;
	wcex.cbWndExtra += (4 + (4 - (wcex.cbWndExtra % 4)));
	

	// Register window class
	if (RegisterClassEx(&wcex) != NULL) { 
		m_ButtonAdvInfo->uRegisterCount++;
		return TRUE;
	}

	return FALSE;
}

// Unregisters the ButtonAdv windows class
BOOL WINAPI UnregisterButtonAdv (HINSTANCE hInstance)
{
	if (!m_ButtonAdvInfo) return FALSE;

	// Decrease register count, and unregister if last decrement
	if ((--m_ButtonAdvInfo->uRegisterCount) == 0) {
		if (!UnregisterClass(ID_BUTTONADV_CLASSNAME, hInstance))
		{ m_ButtonAdvInfo->uRegisterCount++; return FALSE; }
		
		delete m_ButtonAdvInfo;
		m_ButtonAdvInfo = NULL;
	}

	return TRUE;
}


WNDPROC WINAPI DefButtonAdvProc ()
{
	WNDCLASSEX wcex;

	// Get button info
	wcex.cbSize = sizeof(WNDCLASSEX);
	GetClassInfoEx(NULL, "button", &wcex);
	
	return wcex.lpfnWndProc;
}
