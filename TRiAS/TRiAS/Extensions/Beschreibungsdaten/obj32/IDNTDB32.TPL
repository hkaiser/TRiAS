; Moduldefinitionsdatei für PBD-Handling

; LIBRARY		IDENTSDB

DESCRIPTION	'TRIAS(R)-Erweiterung zur Verwaltung von Beschreibungsdaten V@A.@B.@C, (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE
