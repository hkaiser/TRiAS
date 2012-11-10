; TriasDB.def : Declares the module parameters.

; DESCRIPTION 'Einheitliche DB-Schnittstelle für TRiAS eigene Projekte V@A.@B.@C, Copyright© #@D'

EXPORTS
	DllCanUnloadNow			PRIVATE
	DllGetClassObject		PRIVATE
	DllRegisterServer		PRIVATE
	DllUnregisterServer		PRIVATE
	DllRegisterPerfMon		@5 PRIVATE
	DllUnregisterPerfMon	@6 PRIVATE
