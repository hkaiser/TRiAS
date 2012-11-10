; Linker-Definitionsfile für TRIAS -- Version für Windows 95 etc.
; File: TRIAS32.DEF

; NAME	TRIAS32

DESCRIPTION	'Territoriales Raumbezogenes Informations- und Abfragesystem V@A.@B (Build @C), (C) #@D'

EXPORTS 
;	DEXEXTENSIONPROC		= _DexExtensionProcOld@8	@1
	DEXEXTENSIONPROC		= _DexExtensionProc@8		@1	PRIVATE
	DEXXEXTENSIONPROC		= _DexxExtensionProc@8		@2	PRIVATE
	DEXNOTIFICATIONPROC		= _DexNotificationProc@8	@3	PRIVATE
	DEXPOSTNOTIFICATIONPROC		= _DexPostNotificationProc@8	@4	PRIVATE
	DEXNOTIFICATIONPROCEX		= _DexNotificationProcEx@12	@5	PRIVATE
	DEFTRIASEXTENSIONPROC		= _DefTriasExtensionProc@16	@6	PRIVATE
	DEXDISPATCHPROC			= _DexDispatchProc@16		@7	PRIVATE
	DEXEXTENSIONPROC2		= _DexExtensionProc2@12		@8	PRIVATE
	DEXXEXTENSIONPROC2		= _DexxExtensionProc2@12	@9	PRIVATE
