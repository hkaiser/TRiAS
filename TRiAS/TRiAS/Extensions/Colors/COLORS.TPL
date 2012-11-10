; Colors.def : Declares the module parameters.

DESCRIPTION 'TRiAS(R) Farbregelung und Farbkonvertierungsobjekte, V@A.@B (Build @C), (C) #@D'

; LIBRARY      COLORS

EXPORTS
	DllCanUnloadNow     @1 PRIVATE
	DllGetClassObject   @2 PRIVATE
	DllRegisterServer   @3 PRIVATE
	DllUnregisterServer	@4 PRIVATE
	Init				@5 PRIVATE
	Term				@6 PRIVATE
	RuntimeCallback		@7 PRIVATE

