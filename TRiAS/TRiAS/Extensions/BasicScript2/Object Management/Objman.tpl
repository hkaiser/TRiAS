; ObjMan.def : Declares the module parameters.

; LIBRARY      "OBJMAN.DLL"

DESCRIPTION	'TRiAS® - ObjektManagement V@A.@B.@C, Copyright© #@D'

EXPORTS
	DllCanUnloadNow     @1 PRIVATE
	DllGetClassObject   @2 PRIVATE
	DllRegisterServer   @3 PRIVATE
	DllUnregisterServer	@4 PRIVATE
