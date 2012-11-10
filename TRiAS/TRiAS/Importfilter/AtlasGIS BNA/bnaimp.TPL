; Moduldefinitionsdatei für PolyGIS-BNA-Import

; LIBRARY		BNAIMP

DESCRIPTION	'TRiAS(R)-Erweiterung zum Import aus dem PolyGIS-BNA Austauschformat V@A.@B (Build @C), (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
