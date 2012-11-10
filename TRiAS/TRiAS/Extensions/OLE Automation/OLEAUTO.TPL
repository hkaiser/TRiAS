; Moduldefinitionsdatei fuer OLEAUTO.EXT

; LIBRARY		OLEAUTO

DESCRIPTION	'TRiAS® OLE-Automation Server V@A.@B (Build @C), (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
	Init							@5
	Term							@6
	RuntimeCallback						@7
