// Baum aller Merkmale eines Objektes -----------------------------------------
// File: OBJMLIST.CXX

#include "objclipp.hxx"

#include "objmlist.hxx"

// Ein ObjektMerkmal ----------------------------------------------------------
ObjMerkmal :: ObjMerkmal (long lMCode, char *pText)
{
	_lMCode = lMCode;
	_iSelected = FALSE;
	if (pText) {
		_pMText = new char [strlen (pText) +1];
		if (_pMText)
			strcpy (_pMText, pText);
	} else
		_pMText = NULL;
}

ObjMerkmal :: ~ObjMerkmal (void)
{
	DELETE (_pMText);
}

void ObjMerkmal :: ResetMWert (void) 
{
	DELETE (_pMText);
}


// Alle ObjektMerkmale --------------------------------------------------------
ObjMerkmalsListe :: ObjMerkmalsListe (long lONr)
		  : CTree (GetMCodeKey, LongCmp)
{
	_lONr = lONr;
}

ObjMerkmalsListe :: ~ObjMerkmalsListe (void)
{
	EveryDelete ();
}

void _XTENSN_EXPORT ObjMerkmalsListe :: UserDelete (void *pObj)
{
	((ObjMerkmal *)pObj) -> ~ObjMerkmal ();
}

void ObjMerkmalsListe :: SetSelection (long lMCode)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjMerkmalLock l(t);

		if (!l) continue;
		if (lMCode == -1L || l -> MCode() == lMCode)
			l -> isSelected() = TRUE;
	}
}

void ObjMerkmalsListe :: ResetSelection (void)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjMerkmalLock l(t);

		if (l) l -> isSelected() = FALSE;
	}
}


void *GetMCodeKey (void *pObj)
{
	return & ((ObjMerkmal *)pObj) -> MCode();
}

int LongCmp (void *pObj1, void *pObj2)
{
long lKey1 = *(long *)pObj1;
long lKey2 = *(long *)pObj2;

	if (lKey1 > lKey2) return 1;
	if (lKey1 == lKey2) return 0;

return -1;
}

