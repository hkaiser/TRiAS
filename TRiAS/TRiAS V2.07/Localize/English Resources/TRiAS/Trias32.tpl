; Left definition file for TRIAS -- Version for Windows 95 etc.
; File: TRIAS32.DEF

; NAME  TRIAS32

DESCRIPTION     'Territoriales Raumbezogenes Informations- und Abfragesystem V@A.@B (Build @C), (C) #@D'

EXPORTS 
;	DEXEXTENSIONPROC		= _DexExtensionProcOld@8	@1
	DEXEXTENSIONPROC		= _DexExtensionProc@8		@1
	DEXXEXTENSIONPROC		= _DexxExtensionProc@8		@2
	DEXNOTIFICATIONPROC		= _DexNotificationProc@8	@3
	DEXPOSTNOTIFICATIONPROC		= _DexPostNotificationProc@8	@4
	DEXNOTIFICATIONPROCEX		= _DexNotificationProcEx@12	@5
	DEFTRIASEXTENSIONPROC		= _DefTriasExtensionProc@16	@6
	DEXDISPATCHPROC			= _DexDispatchProc@16		@7
	DEXEXTENSIONPROC2		= _DexExtensionProc2@12		@8
	DEXXEXTENSIONPROC2		= _DexxExtensionProc2@12	@9