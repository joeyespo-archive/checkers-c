// Gradient.cpp
// Gradient Functions Implementation File
// By Joe Esposito


#pragma once



// Gradient box [rect] bits
// -------------------------

LOCAL VOID _GradientBoxBits (LPDWORD lpBits, int nWidth, int nHeight, COLORREF crTopLeft, COLORREF crBottomLeft, COLORREF crTopRight, COLORREF crBottomRight)
{
	LPVOID lpTemp, lpEnd;
	int nSize = (nHeight * nWidth);
	int nScanLineSize = (nWidth * 4);

	lpTemp = lpBits;					// Point to first middle pixel
	lpEnd = &(lpBits[(nSize - 1)]);		// Point to end pixel

	__asm {

		PUSH ES					; Store extra segment
		PUSH EDI				; Store data offset


		; Step 1: gradient the left side
		; -------------------------------

		; Set up basic registers
		mov  ecx,nHeight		; Get height
		mov  esi,nScanLineSize	; Get scan line size

		AND  ecx,0FFFFh			; Use only first word


		; Store gradient settings for RGB values
		PUSH ebp				; Store BP

		xor  eax,eax			; Zero AX
		PUSH ax					; AH = 0h  -  No more settings
		
		mov  ax,0FFFFh			; AH = 0FFFFh

		; Store gradient for right side
		mov  edi,lpBits			; DI stores bits
		add  edi,esi			; Point to right side
		dec  edi				;
		dec  edi
		dec  edi
		dec  edi

		mov  ebx,crTopRight		; Get starting color value
		mov  edx,crBottomRight	; Get end color value

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK

		; Store gradient for left side
		mov  edi,lpBits			; DI stores bits
		
		mov  ebx,crTopLeft		; Get starting color value
		mov  edx,crBottomLeft	; Get end color value

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store scan lines count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK


GB_GRADIENT_LOOP:

		; Check gradient settings
		POP  ax					; Get settings header
		TEST ax,ax				; Is setting OK?
		jz   GB_GRADIENT_MIDDLE	;  ..no more settings

		; Get gradient settings
		POP  cx					; Get setting: step count
		POP  esi				; Store scan lines count
		POP  ebp				; Get setting: Bits pointer
		POP  bx					; Get setting: starting color value
		POP  dx					; Get setting: ending color value

		xor  eax,eax			; Clear EAX
		
		; Decide which loop to enter
		cmp  bl,dl				; Compare
		je   GB_GRADIENT_EQUAL	; Jump if (bl == dl)
		ja   GB_GRADIENT_ABOVE	; Jump if (bl > dl)


		; Set up loop
		mov  al,dl				; AL holds ending color
		sub  al,bl				; Get difference (al - bl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator
		mov  edi,edx			; Hold starting numerator value

GB_GRADIENT_LOOP1:

		; Update color value
		mov  byte ptr [ebp],bl	; Set pixel color value
		add  ebp,esi			; Point to next pixel color value

		add  bl,bh				; Increase by the step value

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK1	; Jump if no fraction check is required
		add  edi,edx			; Increase numerator
		cmp  edi,eax			; Compare numerator to denominator
		jb   GB_GRADIENT_OK1	; Jump if !(di > dx) -- not a whole number
		sub  edi,eax			; Reset value
		inc  bl					; Increase BL once more

		GB_GRADIENT_OK1:
		LOOP GB_GRADIENT_LOOP1	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again


GB_GRADIENT_LOOP2:

		; Update color value
		mov  byte ptr [ebp],bl	; Set pixel color value
		add  ebp,esi			; Point to next pixel color value

		sub  bl,bh				; Increase by the step value

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK2	; Jump if no fraction check is required
		add  edi,edx			; Increase numerator
		cmp  edi,eax			; Compare numerator to denominator
		jb   GB_GRADIENT_OK2	; Jump if !(di > dx) -- not a whole number
		sub  edi,eax			; Reset value
		dec  bl					; Increase BL once more

		GB_GRADIENT_OK2:
		LOOP GB_GRADIENT_LOOP2	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again


GB_GRADIENT_ABOVE:

		; Set up loop
		mov  al,bl				; AL holds starting color
		sub  al,dl				; Get difference (al - dl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator
		mov  edi,edx			; Hold starting numerator value

		jmp GB_GRADIENT_LOOP2	; Begin loop


GB_GRADIENT_EQUAL:				; Special case: starting and ending colors are equal		

		; Update color value
		mov  byte ptr [ebp],bl	; Set pixel color value
		add  ebp,esi			; Point to next pixel color value

		LOOP GB_GRADIENT_EQUAL	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again


GB_GRADIENT_MIDDLE:

		POP  ebp				; Restore BP

		; Set up gradient for middle (left-to-right)
		mov  edi,lpTemp			; DI stores bits
		mov  esi,nScanLineSize	; Get scan line size
		mov  ecx,nWidth			; CX holds count

		mov  eax,edi			; AX holds current middle bits
		mov  ebx,eax			; BX holds current middle bits
		mov  edx,eax			; DX holds current middle bits
		
		dec  edx				; Point to last color on previous row
		dec  edx				; 
		dec  edx				
		dec  edx
		cmp  edx,lpEnd			; Compare to bitmap's final color
		je   GB_END				; Jump to end if no more colors available
		
		add  eax,esi			; Point to next color position
		mov  lpTemp,eax			; Store for next time

		add  edx,esi			; Point to last color position; BX holds first
		
		mov  ebx,dword ptr [ebx]	; Get starting color value
		mov  edx,dword ptr [edx]	; Get end color value

		inc  edi				; Point to first color value to change
		inc  edi				; 
		inc  edi
		inc  edi

		dec  ecx				; Decrease to fit middle
		dec  ecx				; 
		
		mov  esi,4				; SI holds increase value (4-byte ranges)


		; Store gradient settings for middle (left-to-right)
		PUSH ebp				; Store BP

		xor  eax,eax			; Zero AX
		PUSH ax					; AH = 0h  -  No more settings
		
		mov  ax,0FFFFh			; AH = 0FFFFh

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store byte count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store byte count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH edi				; Store original Bits pointer
		PUSH esi				; Store byte count
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		jmp  GB_GRADIENT_LOOP	; Return to gradient loop


GB_END:

		POP  EDI				; Restore data offset
		POP  ES					; Restore extra segment

	}
}



// Gradient bits
// --------------

LOCAL VOID _GradientBits (LPDWORD lpBits, int nSize, COLORREF crStart, COLORREF crEnd)
{
	__asm {

		PUSH ES					; Store extra segment
		PUSH EDI				; Store data offset


		; Step 1: gradient the left side
		; -------------------------------

		; Set up basic registers
		mov  ecx,nSize			; Get height

		AND  ecx,0FFFFh			; Use only first word


		; Store gradient settings for RGB values
		xor  eax,eax			; Zero AX
		PUSH ax					; AH = 0h  -  No more settings
		
		mov  ax,0FFFFh			; AH = 0FFFFh

		; Store gradient
		mov  edi,lpBits			; DI stores bits
		
		mov  ebx,crStart		; Get starting color value
		mov  edx,crEnd			; Get end color value

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH edi				; Store original Bits pointer
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH edi				; Store original Bits pointer
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		inc  edi				; Point to next color value
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH edi				; Store original Bits pointer
		PUSH cx					; Store step count
		PUSH ax					; AX = FFFFh  -  Setting OK


GB_GRADIENT_LOOP:

		; Check gradient settings
		POP  ax					; Get settings header
		TEST ax,ax				; Is setting OK?
		jz   GB_END				;  ..no more settings

		; Get gradient settings
		POP  cx					; Get setting: step count
		POP  esi				; Get setting: Bits pointer
		POP  bx					; Get setting: starting color value
		POP  dx					; Get setting: ending color value

		xor  eax,eax			; Clear EAX
		
		; Decide which loop to enter
		cmp  bl,dl				; Compare
		je   GB_GRADIENT_EQUAL	; Jump if (bl == dl)
		ja   GB_GRADIENT_ABOVE	; Jump if (bl > dl)


		; Set up loop
		mov  al,dl				; AL holds ending color
		sub  al,bl				; Get difference (al - bl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator
		mov  edi,edx			; Hold starting numerator value

GB_GRADIENT_LOOP1:

		; Update color value
		mov  byte ptr [esi],bl	; Set pixel color value
		add  esi,4				; Point to next pixel color value

		add  bl,bh				; Increase by the step value

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK1	; Jump if no fraction check is required
		add  edi,edx			; Increase numerator
		cmp  edi,eax			; Compare numerator to denominator
		jb   GB_GRADIENT_OK1	; Jump if !(di > dx) -- not a whole number
		sub  edi,eax			; Reset value
		inc  bl					; Increase BL once more

		GB_GRADIENT_OK1:
		LOOP GB_GRADIENT_LOOP1	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again


GB_GRADIENT_LOOP2:

		; Update color value
		mov  byte ptr [esi],bl	; Set pixel color value
		add  esi,4				; Point to next pixel color value

		sub  bl,bh				; Increase by the step value

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK2	; Jump if no fraction check is required
		add  edi,edx			; Increase numerator
		cmp  edi,eax			; Compare numerator to denominator
		jb   GB_GRADIENT_OK2	; Jump if !(di > dx) -- not a whole number
		sub  edi,eax			; Reset value
		dec  bl					; Increase BL once more

		GB_GRADIENT_OK2:
		LOOP GB_GRADIENT_LOOP2	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again


GB_GRADIENT_ABOVE:

		; Set up loop
		mov  al,bl				; AL holds starting color
		sub  al,dl				; Get difference (al - dl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator
		mov  edi,edx			; Hold starting numerator value

		jmp GB_GRADIENT_LOOP2	; Begin loop


GB_GRADIENT_EQUAL:				; Special case: starting and ending colors are equal		

		; Update color value
		mov  byte ptr [esi],bl	; Set pixel color value
		add  esi,4				; Point to next pixel color value

		LOOP GB_GRADIENT_EQUAL	; Loop until CX is 0
		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again

GB_END:

		POP  EDI				; Restore data offset
		POP  ES					; Restore extra segment

	}
}



// Gradient fill bits
// -------------------

LOCAL VOID _GradientFillBits (LPDWORD lpBits, int nSize, COLORREF cColor)
{
	_asm {
		mov  ebx,lpBits				; Load bits into BX
		mov  ecx,nSize				; Size into CX
		mov  edx,cColor			; Color in DX

		GB_FILL:
		mov  dword ptr [ebx],edx	; Fill
		inc  ebx					; Point to next DWORD
		inc  ebx					;
		inc  ebx
		inc  ebx
		LOOP GB_FILL				; Loop until filled
	}
}




// Gradient bits retreival
// ------------------------

LOCAL VOID _GetGradientBits (LPDWORD lpColor, int nSize, int nPos, COLORREF crStart, COLORREF crEnd)
{
	__asm {

		PUSH ES					; Store extra segment
		PUSH EDI				; Store data offset


		; Step 1: gradient the left side
		; -------------------------------

		; Set up basic registers
		mov  ecx,nSize			; Get height
		AND  ecx,0FFFFh			; Use only first word
		mov  esi,lpColor		; Get bits pointer
		inc  esi				; Point to reversed beginning byte
		inc  esi


		; Store gradient settings for RGB values		
		xor  eax,eax			; Zero AX
		PUSH ax					; AH = 0h  -  No more settings
		
		mov  ax,0FFFFh			; AH = 0FFFFh

		; Store gradient
		mov  ebx,crStart		; Get starting color value
		mov  edx,crEnd			; Get end color value

		PUSH dx					; Store ending 'red' value
		PUSH bx					; Store starting 'red' value
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'green' value
		PUSH bx					; Store starting 'green' value
		PUSH ax					; AX = FFFFh  -  Setting OK
		
		shr  ebx,8				; BH now holds EBX's higher word's lower byte
		shr  edx,8				; BH now holds EBX's higher word's lower byte

		PUSH dx					; Store ending 'blue' value
		PUSH bx					; Store starting 'blue' value
		PUSH ax					; AX = FFFFh  -  Setting OK


GB_GRADIENT_LOOP:

		; Check gradient settings
		POP  ax					; Get settings header
		TEST ax,ax				; Is setting OK?
		jz   GB_END				;  ..no more settings

		; Get gradient settings
		POP  bx					; Get setting: starting color value
		POP  dx					; Get setting: ending color value

		xor  eax,eax			; Clear EAX
		
		; Decide which loop to enter
		cmp  bl,dl				; Compare
		je   GB_GRADIENT_EQUAL	; Jump if (bl == dl)
		ja   GB_GRADIENT_ABOVE	; Jump if (bl > dl)


		; Set up loop
		mov  al,dl				; AL holds ending color
		sub  al,bl				; Get difference (al - bl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder: original numerator (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator

		
		
		; Get the color
		mov  edi,eax			; Store AX (denominator) for a moment
		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index
		AND  eax,0FFFFh			; Use only first word

		mul  bh					; Get actual position by the step value ()
		add  bl,al				; Add with starting color to get the desired color

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK1	; Jump if no fraction check is required

		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index (ax is now [will be] the numerator)

		mul  dx					; Get total increase numerator (original * desired position)
		add  ax,dx				; Increase numerator (desired numerator + current [original])

		cmp  ax,di				; Compare numerator to denominator
		jb   GB_GRADIENT_OK1	; Jump if (ax < di) -- not a whole number
		
		div  di					; Get increase value (numerator / denominator)
		add  bl,al				; Add numerator to color value

		GB_GRADIENT_OK1:
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)
		jmp GB_GRADIENT_LOOP	; Do next color value


GB_GRADIENT_LOOP2:

		; Get the color
		mov  edi,eax			; Store AX (denominator) for a moment
		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index
		AND  eax,0FFFFh			; Use only first word

		mul  bh					; Get actual position by the step value ()
		sub  bl,al				; Add with starting color to get the desired color

		; Check fraction
		TEST dx,dx				; Test for denominator
		jz   GB_GRADIENT_OK2	; Jump if no fraction check is required

		xor  eax,eax			; Zero AX
		mov  eax,nPos			; Get position index (ax is now [will be] the numerator)

		mul  dx					; Get total increase numerator (original * desired position)
		add  ax,dx				; Increase numerator (desired numerator + current [original])

		cmp  ax,di				; Compare numerator to denominator
		jb   GB_GRADIENT_OK2	; Jump if (ax < di) -- not a whole number
		
		div  di					; Get increase value (numerator / denominator)
		sub  bl,al				; Add numerator to color value

		GB_GRADIENT_OK2:
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)
		jmp GB_GRADIENT_LOOP	; Do next color value


GB_GRADIENT_ABOVE:

		; Set up loop
		mov  al,bl				; AL holds starting color
		sub  al,dl				; Get difference (al - dl) into AL

		xor  edx,edx			; Clear dx
		div  cx					; Get color step: (ax / cx) --> ax = step value (byte); dx = remainder: original numerator (byte)
		mov  bh,al				; BH holds the [increase] step value; BL holds current color
		mov  ax,cx				; AX holds denominator

		jmp GB_GRADIENT_LOOP2	; Begin loop


GB_GRADIENT_EQUAL:				; Special case: starting and ending colors are equal		

		; Update color value
		mov  byte ptr [esi],bl	; Set the color value
		dec  esi				; Point to next byte (color value)

		jmp  GB_GRADIENT_LOOP	; Jump back to the beginning and check settings again

GB_END:

		POP  EDI				; Restore data offset
		POP  ES					; Restore extra segment

	}
}
