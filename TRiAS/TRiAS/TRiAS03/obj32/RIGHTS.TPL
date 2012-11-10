  
PAGE  59,132
  
;лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл								         лл
;лл			        WINSTUB				         лл
;лл								         лл
;лл      Created:   1-Jun-90					         лл
;лл      Passes:    5	       Analysis Flags on: H		         лл
;лл								         лл
;лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
  
  
;--------------------------------------------------------------	seg_a  ----
  
seg_a		segment	para public
		assume cs:seg_a , ds:seg_a , ss:stack_seg_b
  
  
;лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;
;			Program Entry Point
;
;лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
  
  
winstub		proc	far
  
start:
		call	sub_1			; (0056)
		db	'TRIAS03 - '
		db	'CustomControls, OwnerDrawControls V@A.@B.@C', 0Dh, 0Ah
		db	'Copyright (C) 1991 - 1998 uve GmbH Fernerkundungszentrum Potsdam, #@D', 0Dh, 0Ah
		db	'Dieses Programm erfordert Windows NT, Windows 95 ', 0Dh, 0Ah
		db	'oder Windows V3.1 mit Win32s.', 0Dh, 0Ah, '$'
winstub		endp
  
;пппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппппп
;			       SUBROUTINE
;мммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммммм
  
sub_1		proc	near
		pop	dx
		push	cs
		pop	ds
		mov	ah,9
		int	21h			; DOS Services  ah=function 09h
						;  display char string at ds:dx
		mov	ax,4C01h
		int	21h			; DOS Services  ah=function 4Ch
						;  terminate with al=return code
sub_1		endp
  
  
seg_a		ends
  
  
  
;--------------------------------------------------------- stack_seg_b  ---
  
stack_seg_b	segment	para stack
  
		db	256 dup (0)
  
stack_seg_b	ends
  
  
  
		end	start
