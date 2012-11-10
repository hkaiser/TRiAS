// DLL-Endecode ---------------------------------------------------------------
// File: WEP.CXX


#include "trias01p.hxx"

extern "C" void WINAPI ShutdownInterruptHandler (void);

extern "C" VOID __export PASCAL _WEP (int nPar) 
{
#if !defined(WIN32)
	ShutdownInterruptHandler();
#endif // !WIN32
}


