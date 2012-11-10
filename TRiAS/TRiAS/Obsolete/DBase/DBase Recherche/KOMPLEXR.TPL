DESCRIPTION     'TRIAS(R)-Erweiterung zur Recherche in dBASE-Dateien V@A.@B.@C, (C) #@D'

; Die vierFunktionen müssen exportiert sein -------------------------------
EXPORTS
	DllGetClassObject	= _DllGetClassObject@12		@1
	DllCanUnloadNow		= _DllCanUnloadNow@0		@2
	DllRegisterServer	= _DllRegisterServer@0		@3
	DllUnregisterServer	= _DllUnregisterServer@0	@4
