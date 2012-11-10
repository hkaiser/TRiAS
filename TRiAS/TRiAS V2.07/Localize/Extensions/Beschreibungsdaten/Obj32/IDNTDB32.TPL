; Moduldefinitionsdatei für PBD-Handling

; LIBRARY		IDENTSDB

DESCRIPTION	'TRIAS(R)-Erweiterung zur Verwaltung von Beschreibungsdaten V@A.@B.@C, (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2
	DllRegisterServer	= _DllRegisterServer@0		@3
	DllUnregisterServer	= _DllUnregisterServer@0	@4
