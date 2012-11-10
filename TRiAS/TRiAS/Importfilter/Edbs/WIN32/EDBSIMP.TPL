; Moduldefinitionsdatei fuer BSCRIPT.EXT/32

; LIBRARY		BSCRIPT

DESCRIPTION	'TRiAS(R) - Erweiterung zur Makroprogrammierung V@A.@B (Build @C), (C) #@D'

CODE		DISCARDABLE MOVEABLE LOADONCALL
DATA		MOVEABLE PRELOAD

EXPORTS
        DllGetClassObject       = _DllGetClassObject@12         @1
        DllCanUnloadNow         = _DllCanUnloadNow@0            @2
        DllRegisterServer       = _DllRegisterServer@0          @3
        DllUnregisterServer     = _DllUnregisterServer@0        @4
	Init							@5
	Term							@6
	RuntimeCallback						@7
