// Objektenumeratoren innerhalb von TRIAS -------------------------------------
// File ENUMOBJ.CXX

#include "triaspre.hxx"

#include <ienumobj.hxx>
#include <eonrguid.h>

#include "ienumonr.hxx"
#include "tenums.h"

static bool FillEnumWithActivatedObjects (CEnumObjectsByNumber *pEnum, DWORD dwData);

// Funktion, welche einen gewünschten Enumerator generiert und einen Pointer
// auf sein Interface liefert
extern "C"
bool EXPORTTRIAS WINAPI CreateObjEnumerator (LPENUMLONG *ppEnum, 
			ENUMOBJECTTYPE eOT, DWORD dwData) 
{
	if (ppEnum == NULL) return FALSE;

// Erzeugen der Klasse, die gewünschtes Interface implementiert hat
	switch (eOT) {
	case ENUMOBJECTTYPE_ACTIVATED:	// alle aktivierten Objekte
		{
		CEnumObjectsByNumber *pEnum = CEnumObjectsByNumber :: CreateInstance();

			if (pEnum && !FillEnumWithActivatedObjects (pEnum, dwData)) {
				pEnum -> Release();
				return false;
			}

			*ppEnum = NULL;		
			pEnum -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppEnum);
			pEnum -> Release();
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
		return FALSE;	// sorry, not implemented
	}

return *ppEnum != NULL;
}

// Alle aktivierten Objekte eines ORFensters enumerieren ----------------------
extern "C"
BOOL EXPORTTRIAS WINAPI FillONrEnum (long lONr, BOOL, void *pData)
{
	return ((CEnumObjectsByNumber *)pData) -> AddObject(lONr);
}

static bool FillEnumWithActivatedObjects (CEnumObjectsByNumber *pEnum, DWORD dwData)
{
// alle ObjektNummern des Fensters besorgen
ENUMLONGKEY ELK;

	ELK.eKey = dwData;
	ELK.eFcn = (ENUMLONGKEYPROC)FillONrEnum;
	ELK.ePtr = pEnum;

return DEX_EnumSelectedObjects (ELK);
}

