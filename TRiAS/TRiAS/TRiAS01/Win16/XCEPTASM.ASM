	title xceptasm.asm

	.model small
	.286p
	.287
;
; public und extrn Deklarationen
PUBLIC 	EXCEPTIONHANDLER		; Make EXCEPTIONHANDLER public
EXTRN 	_CExceptionHandler:near

;
; CodeSegment
XCEPTION_TEXT	SEGMENT  WORD PUBLIC 'CODE'
	ASSUME	CS: XCEPTION_TEXT

; The EXCEPTIONHANDLER proc is called directly from TOOLHELP.  It sets up a
; stackframe, and calls the 'C' function CExceptionHandler.
; On entry, the stack looks like this:

;		------------
;	 BP---->|  Old BP  |  [BP + 00h]
;		|  Ret IP  |  [BP + 02h]
;		|  Ret CS  |  [BP + 04h]
;		|    AX    |  [BP + 06h]
;		|Exception#|  [BP + 08h]
;		|  Handle  |  [BP + 0Ah]
;		|    IP    |  [BP + 0Ch]
;		|    CS    |  [BP + 0Eh]
;		|   Flags  |  [BP + 10h]
;		------------

EXCEPTIONHANDLER proc near

	push	bp			; Make a stack frame
	mov	bp,sp
	pusha				; Save all registers
	push	ds
	push	es

	mov	ax, @data
	mov	ds, ax
	
	call    _CExceptionHandler

	pop	es			; Chain on to next fault handler
	pop	ds
	popa
	pop	bp
	retf

EXCEPTIONHANDLER 	endp

XCEPTION_TEXT      	ENDS

	END
