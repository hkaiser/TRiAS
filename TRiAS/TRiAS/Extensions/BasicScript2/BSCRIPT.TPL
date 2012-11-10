; Moduldefinitionsdatei fuer BSCRIPT.EXT/32

; LIBRARY		BSCRIPT

DESCRIPTION	'TRiAS® - Erweiterung zur Makroprogrammierung  V@A.@B.@C, Copyright© #@D'

EXPORTS
    DllGetClassObject       = _DllGetClassObject@12         @1 PRIVATE
    DllCanUnloadNow         = _DllCanUnloadNow@0            @2 PRIVATE
    DllRegisterServer       = _DllRegisterServer@0          @3 PRIVATE
    DllUnregisterServer     = _DllUnregisterServer@0        @4 PRIVATE
	Init							@5
	Term							@6
	RuntimeCallback					@7
