// Initialisierungsdatei für Geometrie-DLL
// File: DLLINIT.CXX


#include "GeometrP.hxx"
	
#include <initguid.h>
#include <eonrguid.h>



// globale Parameter
HWND __hWndM = 0;
UINT __DexNotify = 0;
UINT __DexCmd = 0;

    

void _GEOMETR_EXPORT pascal InitGeometrie (HWND hWndm, UINT DexNotify, UINT DexCmd)
{
	__hWndM = hWndm;
	__DexNotify = DexNotify;
	__DexCmd = DexCmd;
}
