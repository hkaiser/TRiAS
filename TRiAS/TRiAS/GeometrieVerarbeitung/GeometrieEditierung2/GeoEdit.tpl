; Moduldefinitionsdatei für geoedit.ext

; LIBRARY         GEOEDIT

DESCRIPTION     'TRiAS®-Erweiterung zur Geometrie-Editierung V@A.@B (Build @C), © #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
	Init				= _Init@4					@5
	Term				= _Term@4					@6
	RuntimeCallback		= _RuntimeCallback@16		@7
