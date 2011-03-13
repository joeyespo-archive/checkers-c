// MarqueeBox.cpp - MarqueeBox
// MarqueeBox Library Implementation File
// By Joe Esposito


#pragma once



// Public Functions
// -----------------

// Registers the MarqueeBox windows class
BOOL WINAPI RegisterMarqueeBox (HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	// Set internal info
	if (m_MarqueeBoxInfo == NULL) {
		if ((m_MarqueeBoxInfo = new MARQUEEBOXCLASSINFO) == NULL) return FALSE;
		
		// Set info
		m_MarqueeBoxInfo->uRegisterCount = 0;				// Register count starts at 0
	}

	// Set MarqueeBox window info
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = ID_MARQUEEBOX_CLASSNAME;
	wcex.hInstance = hInstance;
	wcex.style = (0);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hCursor = (HCURSOR)LoadCursor(NULL, (LPSTR)IDC_ARROW);
	wcex.lpfnWndProc = (WNDPROC)_MarqueeBoxProc;
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 4;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	

	// Register window class
	if (RegisterClassEx(&wcex) != NULL) { 
		m_MarqueeBoxInfo->uRegisterCount++;
		return TRUE;
	}

	return FALSE;
}

// Unregisters the MarqueeBox windows class
BOOL WINAPI UnregisterMarqueeBox (HINSTANCE hInstance)
{
	if (!m_MarqueeBoxInfo) return FALSE;

	// Decrease register count, and unregister if last decrement
	if ((--m_MarqueeBoxInfo->uRegisterCount) == 0) {
		if (!UnregisterClass(ID_MARQUEEBOX_CLASSNAME, hInstance))
		{ m_MarqueeBoxInfo->uRegisterCount++; return FALSE; }
		
		delete m_MarqueeBoxInfo;
		m_MarqueeBoxInfo = NULL;
	}

	return TRUE;
}
