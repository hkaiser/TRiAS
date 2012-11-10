// Objektenumeratoren innerhalb von TRIAS -------------------------------------
// File ENUMOBJ.CXX

#include "triaspre.hxx"

#include <ospace/com/iterenum.h>
#include <ienumobj.hxx>
#include <eonrguid.h>

#include "tenums.h"

static bool FillEnumWithActivatedObjects (IEnum<LONG> *pEnum, DWORD dwData);

// Funktion, welche einen gewünschten Enumerator generiert und einen Pointer
// auf sein Interface liefert

BOOL EXPORTTRIAS WINAPI CreateObjEnumerator (
		IEnum<LONG> **ppIEnum, ENUMOBJECTTYPE eOT, DWORD dwData) 
{
	if (ppIEnum == NULL) return FALSE;

// Erzeugen der Klasse, die gewünschtes Interface implementiert hat
	switch (eOT) {
	case ENUMOBJECTTYPE_ACTIVATED:	// alle aktivierten Objekte
		{
		HRESULT hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER, 
									   IID_IEnumLONG, (LPVOID *)ppIEnum);
			if (SUCCEEDED(hr)) {
				if (!FillEnumWithActivatedObjects (*ppIEnum, dwData)) {
					(*ppIEnum) -> Release();
					*ppIEnum = NULL;
					return false;
				}
			}
		}
		break;
		
	case ENUMOBJECTTYPE_IDENT:	// alle Objekte eines Idents
	case ENUMOBJECTTYPE_VIEW:	// alle Objekte einer Sicht
	case ENUMOBJECTTYPE_SELECTED:	// alle selektierten Objekte
	case ENUMOBJECTTYPE_LISTED:	// alle recherchierten Objekte
	case ENUMOBJECTTYPE_INCOMPLEX:	// alle Objekte eines Komplexobjektes
	case ENUMOBJECTTYPE_RELATION:	// alle Objekte mit einer Relation
	case ENUMOBJECTTYPE_REGION:	// alle Objekte innerhalb eines Bereiches
	case ENUMOBJECTTYPE_FEATURE:	// alle Objekte mit einem Merkmalswert
		return false;	// sorry, not implemented
	}

return *ppIEnum != NULL;
}

// Alle aktivierten Objekte eines ORFensters enumerieren ----------------------
extern "C"
BOOL EXPORTTRIAS WINAPI FillONrEnum (long lONr, BOOL, void *pData)
{
	return SUCCEEDED(((IEnum<LONG> *)pData) -> AddItem(lONr));
}

static bool FillEnumWithActivatedObjects (IEnum<LONG> *pIEnum, DWORD dwData)
{
// alle ObjektNummern des Fensters besorgen
ENUMLONGKEY ELK;

	ELK.eKey = dwData;
	ELK.eFcn = (ENUMLONGKEYPROC)FillONrEnum;
	ELK.ePtr = pIEnum;

return DEX_EnumSelectedObjects (ELK);
}

