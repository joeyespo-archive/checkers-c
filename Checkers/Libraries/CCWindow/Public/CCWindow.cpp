// CCWindow.cpp
// Control Container Implementation File
// By Joe Esposito



// Public Functions
// -----------------

// Registers the Control Container window classes
BOOL WINAPI RegisterCCWindow (HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	// CCFrame
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = ID_CCFRAME_CLASSNAME;
	wcex.hInstance = hInstance;
	wcex.style = (0);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hCursor = (HCURSOR)LoadCursor(NULL, (LPSTR)IDC_ARROW);
	wcex.lpfnWndProc = (WNDPROC)_CCFrameProc;
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 4;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	
	if (!RegisterClassEx(&wcex)) return FALSE;
	

	// CCClient
	wcex.lpszClassName = ID_CCCLIENT_CLASSNAME;
	wcex.lpfnWndProc = (WNDPROC)_CCClientProc;
	wcex.cbWndExtra = 4;

	if (!RegisterClassEx(&wcex)) { UnregisterClass(ID_CCFRAME_CLASSNAME, hInstance); return FALSE; }
	
	return TRUE;
}
// Unregisters the Control Container window classes
BOOL WINAPI UnregisterCCWindow (HINSTANCE hInstance)
{ return (UnregisterClass(ID_CCFRAME_CLASSNAME, hInstance) && UnregisterClass(ID_CCCLIENT_CLASSNAME, hInstance)); }
