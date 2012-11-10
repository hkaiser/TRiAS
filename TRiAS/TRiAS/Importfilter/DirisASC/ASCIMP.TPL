; Moduldefinitionsdatei für DIRIS-ASC Import

; LIBRARY		ASCIMP

DESCRIPTION	'TRiAS(R)-Erweiterung zum Import aus dem DIRIS-ASC Austauschformat V@A.@B (Build @C), (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
