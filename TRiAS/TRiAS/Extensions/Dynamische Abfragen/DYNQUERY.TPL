; Moduldefinitionsdatei fuer DYNQUERY.EXT

; LIBRARY		DYNQUERY

DESCRIPTION	'TRiAS(R) - Verwaltung dynamischer Abfragen V@A.@B (Build @C), (C) #@D'

EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2
	DllRegisterServer	= _DllRegisterServer@0		@3
	DllUnregisterServer	= _DllUnregisterServer@0	@4

