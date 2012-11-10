#include "stdafx.h"

#include "resource.h"
				
// Herausfinden , ob Obj sel. wurden , die Textobj. , Menüpunkt
// danach "grau", wenn ein Textobj. sel.
				
extern "C"
{

BOOL FAR PASCAL _XTENSN_EXPORT EnumSelObjectsFuerMenue (long lObjNr, BOOL, void *pvCnt)
{
		if (DEX_GetObjectType(lObjNr) == OGText) {
			(*(short*)pvCnt)++;
			return TRUE;
		}
		
return TRUE;
}

}
