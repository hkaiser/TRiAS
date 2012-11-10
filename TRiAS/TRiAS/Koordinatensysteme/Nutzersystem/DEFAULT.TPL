; Moduldefinitionsdatei für eine Koordinatentransformation

; LIBRARY		DEFAULT

DESCRIPTION	'Standardkoordinatentransformation V@A.@B.@C, (C) #@D'

EXPORTS
	DllRegisterServer		= _DllRegisterServer@0		@1 PRIVATE
	DllUnregisterServer		= _DllUnregisterServer@0	@2 PRIVATE
	DllCanUnloadNow			= _DllCanUnloadNow@0		@3 PRIVATE
	DllGetClassObject		= _DllGetClassObject@12		@4 PRIVATE
