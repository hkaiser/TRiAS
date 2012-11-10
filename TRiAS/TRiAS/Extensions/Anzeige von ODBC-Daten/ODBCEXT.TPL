; LIBRARY         ODBCEXT

DESCRIPTION     'TRiAS®-Erweiterung zum Anbinden von ODBC-Daten V@A.@B.@C, (C) #@D'

; Die beiden Funktionen müssen exportiert sein -------------------------------
EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1 PRIVATE
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2 PRIVATE
	DllRegisterServer	= _DllRegisterServer@0		@3 PRIVATE
	DllUnregisterServer	= _DllUnregisterServer@0	@4 PRIVATE

        
