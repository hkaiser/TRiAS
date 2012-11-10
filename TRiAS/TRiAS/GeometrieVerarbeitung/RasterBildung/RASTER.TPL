; Moduldefinitionsdatei für raster.ext

; LIBRARY         RASTER

DESCRIPTION     'TRiAS®-Erweiterung für Rasterbildung V@A.@B (Build @C), © #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
