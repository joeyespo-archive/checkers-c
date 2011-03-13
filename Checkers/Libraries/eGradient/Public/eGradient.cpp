// eGradient.cpp
// eGradient Library Implementation File
// By Joe Esposito


#pragma once



// Bitmap Functions
// -----------------

// Creates a gradiented bitmap
HBITMAP ESTDCALL CreateGradientBitmap (int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight)
{
	HDC hDC;
	BITMAPINFO bmi;
	HBITMAP hBitmap;
	LPDWORD lpBits, lpDIBits = NULL;
	LPVOID lpTemp, lpEnd;
	int nSize = (cy * cx);
	int i;

	if (((cy <= 0) || (cx <= 0)) || ((cy > 0xFFFF) || (cx > 0xFFFF))) return NULL;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = -cy; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((cTopLeft & 0xFF000000) == 0x80000000) { cTopLeft = GetSysColor((cTopLeft & 0xFFFFFF)); cTopLeft = (((cTopLeft & 0x0000FF) << 16) | (cTopLeft & 0x00FF00) | ((cTopLeft & 0xFF0000) >> 16)); }
	if ((cBottomLeft & 0xFF000000) == 0x80000000) { cBottomLeft = GetSysColor((cBottomLeft & 0xFFFFFF)); cBottomLeft = (((cBottomLeft & 0x0000FF) << 16) | (cBottomLeft & 0x00FF00) | ((cBottomLeft & 0xFF0000) >> 16)); }
	if ((cTopRight & 0xFF000000) == 0x80000000) { cTopRight = GetSysColor((cTopRight & 0xFFFFFF)); cTopRight = (((cTopRight & 0x0000FF) << 16) | (cTopRight & 0x00FF00) | ((cTopRight & 0xFF0000) >> 16)); }
	if ((cBottomRight & 0xFF000000) == 0x80000000) { cBottomRight = GetSysColor((cBottomRight & 0xFFFFFF)); cBottomRight = (((cBottomRight & 0x0000FF) << 16) | (cBottomRight & 0x00FF00) | ((cBottomRight & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if ((cTopLeft == cBottomLeft) && (cTopRight == cBottomRight) && (cTopLeft == cTopRight))
	{ _GradientFillBits(lpBits, nSize, cTopLeft); }
	else if ((cy == 1) && (cx == 1))
	{
		if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
		if (cTopRight > cBottomRight) { i = cTopRight; cTopRight = cBottomRight; cBottomRight = i; }
	
		cTopLeft = ((cBottomLeft / 2) + cTopLeft);
		cBottomLeft = ((cBottomRight / 2) + cTopRight);
		if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
	
		// Set to a mix of all colors
		(*lpBits) = ((cBottomLeft / 2) + cTopLeft);
	}
	else if ((cy == 1) || (cx == 1)) {
		if (cy == 1) {
			if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
			if (cTopRight > cBottomRight) { i = cTopRight; cTopRight = cBottomRight; cBottomRight = i; }
			
			cTopLeft = ((cBottomLeft / 2) + cTopLeft);
			cBottomLeft = ((cBottomRight / 2) + cTopRight);
		} else {
			if (cTopLeft > cTopRight) { i = cTopLeft; cTopLeft = cTopRight; cTopRight = i; }
			if (cBottomLeft > cBottomRight) { i = cBottomLeft; cBottomLeft = cBottomRight; cBottomRight = i; }
		
			cTopLeft = ((cTopRight / 2) + cTopLeft);
			cBottomLeft = ((cBottomRight / 2) + cBottomLeft);
		}
	}
	else {
		_GradientBoxBits(lpBits, cx, cy, cTopLeft, cBottomLeft, cTopRight, cBottomRight);
	}


	// Create the bitmap
	hDC = CreateCompatibleDC(NULL);
	hBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (VOID **)&lpDIBits, NULL, NULL);
	memcpy(lpDIBits, lpBits, (nSize*sizeof(DWORD)));
	DeleteDC(hDC);
	
	// Clean up
	delete [nSize] lpBits;


	// Finished  =)
	return hBitmap;
}

// Creates a horizontal (1 pixel height) gradient bitmap
HBITMAP ESTDCALL CreateGradientHorizBitmap (int cx, COLORREF crStart, COLORREF crEnd)
{
	HDC hDC;
	BITMAPINFO bmi;
	HBITMAP hBitmap;
	LPDWORD lpBits, lpDIBits = NULL;
	LPVOID lpTemp, lpEnd;
	int nSize = cx;
	int i;

	if ((cx <= 0) || (cx > 0xFFFF)) return FALSE;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = 1; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if (crStart == crEnd)
	{ _GradientFillBits(lpBits, nSize, crStart); }
	if (cx == 1)
	{
		if (crStart > crEnd) { i = crStart; crStart = crEnd; crEnd = i; }
		(*lpBits) = ((crEnd / 2) + crStart);
	}
	else {
		_GradientBits(lpBits, cx, crStart, crEnd);
	}


	// Create the bitmap
	hDC = CreateCompatibleDC(NULL);
	hBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (VOID **)&lpDIBits, NULL, NULL);
	memcpy(lpDIBits, lpBits, (nSize*sizeof(DWORD)));
	DeleteDC(hDC);
	
	// Clean up
	delete [nSize] lpBits;

	return hBitmap;
}

// Creates a verticle (1 pixel width) gradient bitmap
HBITMAP ESTDCALL CreateGradientVertBitmap (int cy, COLORREF crStart, COLORREF crEnd)
{
	HDC hDC;
	BITMAPINFO bmi;
	HBITMAP hBitmap;
	LPDWORD lpBits, lpDIBits = NULL;
	LPVOID lpTemp, lpEnd;
	int nSize = cy;
	int i;

	if ((cy <= 0) || (cy > 0xFFFF)) return FALSE;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 1; bmi.bmiHeader.biHeight = -cy; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if (crStart == crEnd)
	{ _GradientFillBits(lpBits, nSize, crStart); }
	if (cy == 1)
	{
		if (crStart > crEnd) { i = crStart; crStart = crEnd; crEnd = i; }
		(*lpBits) = ((crEnd / 2) + crStart);
	}
	else {
		_GradientBits(lpBits, cy, crStart, crEnd);
	}


	// Create the bitmap
	hDC = CreateCompatibleDC(NULL);
	hBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (VOID **)&lpDIBits, NULL, NULL);
	memcpy(lpDIBits, lpBits, (nSize*sizeof(DWORD)));
	DeleteDC(hDC);
	
	// Clean up
	delete [nSize] lpBits;

	return hBitmap;
}



// Drawing Functions
// ------------------

// Draws a gradiented rectangle
BOOL ESTDCALL DrawGradientRect (HDC hDC, int x, int y, int cx, int cy, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight)
{
	BITMAPINFO bmi;
	LPDWORD lpBits;
	LPVOID lpTemp, lpEnd;
	int nSize = (cy * cx);
	int i;

	if (((cy <= 0) || (cx <= 0)) || ((cy > 0xFFFF) || (cx > 0xFFFF))) return FALSE;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = -cy; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((cTopLeft & 0xFF000000) == 0x80000000) { cTopLeft = GetSysColor((cTopLeft & 0xFFFFFF)); cTopLeft = (((cTopLeft & 0x0000FF) << 16) | (cTopLeft & 0x00FF00) | ((cTopLeft & 0xFF0000) >> 16)); }
	if ((cBottomLeft & 0xFF000000) == 0x80000000) { cBottomLeft = GetSysColor((cBottomLeft & 0xFFFFFF)); cBottomLeft = (((cBottomLeft & 0x0000FF) << 16) | (cBottomLeft & 0x00FF00) | ((cBottomLeft & 0xFF0000) >> 16)); }
	if ((cTopRight & 0xFF000000) == 0x80000000) { cTopRight = GetSysColor((cTopRight & 0xFFFFFF)); cTopRight = (((cTopRight & 0x0000FF) << 16) | (cTopRight & 0x00FF00) | ((cTopRight & 0xFF0000) >> 16)); }
	if ((cBottomRight & 0xFF000000) == 0x80000000) { cBottomRight = GetSysColor((cBottomRight & 0xFFFFFF)); cBottomRight = (((cBottomRight & 0x0000FF) << 16) | (cBottomRight & 0x00FF00) | ((cBottomRight & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if ((cTopLeft == cBottomLeft) && (cTopRight == cBottomRight) && (cTopLeft == cTopRight))
	{ _GradientFillBits(lpBits, nSize, cTopLeft); }
	if ((cy == 1) && (cx == 1))
	{
		if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
		if (cTopRight > cBottomRight) { i = cTopRight; cTopRight = cBottomRight; cBottomRight = i; }
		
		cTopLeft = ((cBottomLeft / 2) + cTopLeft);
		cBottomLeft = ((cBottomRight / 2) + cTopRight);
		if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
		
		// Set to a mix of all colors
		(*lpBits) = ((cBottomLeft / 2) + cTopLeft);
	}
	else if ((cy == 1) || (cx == 1)) {
		if (cy == 1) {
			if (cTopLeft > cBottomLeft) { i = cTopLeft; cTopLeft = cBottomLeft; cBottomLeft = i; }
			if (cTopRight > cBottomRight) { i = cTopRight; cTopRight = cBottomRight; cBottomRight = i; }
		
			cTopLeft = ((cBottomLeft / 2) + cTopLeft);
			cBottomLeft = ((cBottomRight / 2) + cTopRight);
		} else {
			if (cTopLeft > cTopRight) { i = cTopLeft; cTopLeft = cTopRight; cTopRight = i; }
			if (cBottomLeft > cBottomRight) { i = cBottomLeft; cBottomLeft = cBottomRight; cBottomRight = i; }
		
			cTopLeft = ((cTopRight / 2) + cTopLeft);
			cBottomLeft = ((cBottomRight / 2) + cBottomLeft);
		}
	}
	else {
		_GradientBoxBits(lpBits, cx, cy, cTopLeft, cBottomLeft, cTopRight, cBottomRight);
	}


	// Create the bitmap
	SetDIBitsToDevice(hDC, x, y, cx, cy, 0, 0, 0, cy, lpBits, &bmi, DIB_RGB_COLORS);
	
	// Clean up
	delete [nSize] lpBits;

	return TRUE;
}

// Draws a horizontal (1 pixel height) gradient line
BOOL ESTDCALL DrawGradientHoriz (HDC hDC, int x, int y, int cx, COLORREF crStart, COLORREF crEnd)
{
	BITMAPINFO bmi;
	LPDWORD lpBits;
	LPVOID lpTemp, lpEnd;
	int nSize = cx;
	int i;

	if ((cx <= 0) || (cx > 0xFFFF)) return FALSE;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = cx; bmi.bmiHeader.biHeight = 1; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if (crStart == crEnd)
	{ _GradientFillBits(lpBits, nSize, crStart); }
	if (cx == 1)
	{
		if (crStart > crEnd) { i = crStart; crStart = crEnd; crEnd = i; }
		(*lpBits) = ((crEnd / 2) + crStart);
	}
	else {
		_GradientBits(lpBits, cx, crStart, crEnd);
	}


	// Create the bitmap
	SetDIBitsToDevice(hDC, x, y, cx, 1, 0, 0, 0, 1, lpBits, &bmi, DIB_RGB_COLORS);
	
	// Clean up
	delete [nSize] lpBits;

	return TRUE;
}

// Draws a verticle (1 pixel width) gradient line
BOOL ESTDCALL DrawGradientVert (HDC hDC, int x, int y, int cy, COLORREF crStart, COLORREF crEnd)
{
	BITMAPINFO bmi;
	LPDWORD lpBits;
	LPVOID lpTemp, lpEnd;
	int nSize = cy;
	int i;

	if ((cy <= 0) || (cy > 0xFFFF)) return FALSE;


	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 1; bmi.bmiHeader.biHeight = -cy; bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB; bmi.bmiHeader.biSizeImage = 0;


	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }


	if ((lpBits = new DWORD [nSize]) == NULL) return NULL;	// Create bits
	
	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	if (crStart == crEnd)
	{ _GradientFillBits(lpBits, nSize, crStart); }
	if (cy == 1)
	{
		if (crStart > crEnd) { i = crStart; crStart = crEnd; crEnd = i; }
		(*lpBits) = ((crEnd / 2) + crStart);
	}
	else {
		_GradientBits(lpBits, cy, crStart, crEnd);
	}


	// Create the bitmap
	SetDIBitsToDevice(hDC, x, y, 1, cy, 0, 0, 0, cy, lpBits, &bmi, DIB_RGB_COLORS);
	
	// Clean up
	delete [nSize] lpBits;

	return TRUE;
}



// Color Calculation Functions
// ----------------------------

// Gets a single pixel in a gradient line
COLORREF ESTDCALL GetGradientPixel (int cLen, int nPos, COLORREF crStart, COLORREF crEnd)
{
	COLORREF crResult;

	if ((cLen <= 0) || (cLen > 0xFFFF)) return 0;
	if ((nPos < 0) || (nPos >= cLen)) return 0;

	if ((crStart & 0xFF000000) == 0x80000000) { crStart = GetSysColor((crStart & 0xFFFFFF)); crStart = (((crStart & 0x0000FF) << 16) | (crStart & 0x00FF00) | ((crStart & 0xFF0000) >> 16)); }
	if ((crEnd & 0xFF000000) == 0x80000000) { crEnd = GetSysColor((crEnd & 0xFFFFFF)); crEnd = (((crEnd & 0x0000FF) << 16) | (crEnd & 0x00FF00) | ((crEnd & 0xFF0000) >> 16)); }

	_GetGradientBits ((LPDWORD)&crResult, cLen, nPos, crStart, crEnd);

	return crResult;
}

COLORREF ESTDCALL GetGradientRectPixel (int cx, int cy, int x, int y, COLORREF cTopLeft, COLORREF cBottomLeft, COLORREF cTopRight, COLORREF cBottomRight)
{
	COLORREF crTop, crBottom;
	COLORREF crResult;

	if ((cx <= 0) || (cx > 0xFFFF)) return 0;  if ((cy <= 0) || (cy > 0xFFFF)) return 0;
	if ((x < 0) || (x > cx)) return 0;  if ((y < 0) || (y > cy)) return 0;

	if ((cTopLeft & 0xFF000000) == 0x80000000) { cTopLeft = GetSysColor((cTopLeft & 0xFFFFFF)); cTopLeft = (((cTopLeft & 0x0000FF) << 16) | (cTopLeft & 0x00FF00) | ((cTopLeft & 0xFF0000) >> 16)); }
	if ((cBottomLeft & 0xFF000000) == 0x80000000) { cBottomLeft = GetSysColor((cBottomLeft & 0xFFFFFF)); cBottomLeft = (((cBottomLeft & 0x0000FF) << 16) | (cBottomLeft & 0x00FF00) | ((cBottomLeft & 0xFF0000) >> 16)); }
	if ((cTopRight & 0xFF000000) == 0x80000000) { cTopRight = GetSysColor((cTopRight & 0xFFFFFF)); cTopRight = (((cTopRight & 0x0000FF) << 16) | (cTopRight & 0x00FF00) | ((cTopRight & 0xFF0000) >> 16)); }
	if ((cBottomRight & 0xFF000000) == 0x80000000) { cBottomRight = GetSysColor((cBottomRight & 0xFFFFFF)); cBottomRight = (((cBottomRight & 0x0000FF) << 16) | (cBottomRight & 0x00FF00) | ((cBottomRight & 0xFF0000) >> 16)); }


	_GetGradientBits ((LPDWORD)&crTop, cx, x, cTopLeft, cTopRight);				// Get top
	_GetGradientBits ((LPDWORD)&crBottom, cx, x, cBottomLeft, cBottomRight);	// Get bottom
	
	_GetGradientBits ((LPDWORD)&crResult, cy, y, crTop, crBottom);				// Get result

	return crResult;
}
