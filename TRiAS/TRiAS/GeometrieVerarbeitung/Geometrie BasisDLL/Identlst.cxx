// Liste aller Identifikatoren der PBD
// File: IDENTLST.CXX
// H. Kaiser


#include "GeometrP.hxx"

#include "identlst.hxx"		// IdentList



extern "C" {

	extern HINSTANCE g_hInstance;

	BOOL _XTENSN_EXPORT PASCAL FillIdentsList (ulong ulIdent, BOOL fNotLast, void *pData)
	{
	PBDDATA pbdData;
	char KText[64];

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = ulIdent;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;

	// RückkehrCode ausgewertet
		if (DEX_GetPBDData (pbdData) == EC_OKAY)
			return ((IdentList *)pData) -> AddIdent (ulIdent, KText);

	// trotzdem weitermachen, wenn nicht der letzte
		if (fNotLast) return true;

	return false;
	}

} 	// extern "C"




// ------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT IdentList :: IdentList (void)
						   : COptTree (GetIdentKey, ULongCmp)
{
	// wenn noch kein Projekt eröffnet ist, dann wieder raus
	if (! DEX_TestActiveProject()) return;

ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsList;
	ELK.ePtr = (void *)this;
	DEX_EnumPBDData (ELK);
}


// ------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT IdentList :: ~IdentList (void)
{
	EveryDelete();
}


// ------------------------------------------------------------------------------------------------
bool IdentList :: AddIdent (ulong ulIdent, char *pDesc)
{
IdentListEntryOptCreator IELCr (*this);

	return ContCreate (IELCr, IdentListEntry) (ulIdent, pDesc) != NULL;
}


// ------------------------------------------------------------------------------------------------
// Eintrag erneuern, wenn PBD geändert wurde
bool _GEOMETR_EXPORT IdentList :: UpdateEntry (ulong ulIdent)
{
CTable t(*this);

	if (t.Find (&ulIdent)) 
		t.Delete();

return FillIdentsList (ulIdent, false, this);
}


// ------------------------------------------------------------------------------------------------
void IdentList :: UserDelete (void *pObj)
{
	((IdentListEntry *)pObj) -> ~IdentListEntry();
}


// ------------------------------------------------------------------------------------------------
int ULongCmp (void *pObj1, void *pObj2)
{
ULONG l1 = *(ULONG *)pObj1;
ULONG l2 = *(ULONG *)pObj2;

	if (l1 > l2) return 1;
	if (l1 < l2) return -1;
	return 0;
}


// ------------------------------------------------------------------------------------------------
void *GetIdentKey (void *pObj)
{
	return & ((IdentListEntry *)pObj) -> _ulIdent;
}


// ------------------------------------------------------------------------------------------------
// Memberfuntkionen für Elemente der Liste
IdentListEntry :: IdentListEntry (ulong ulIdent, char *pKText)
{
	_ulIdent = ulIdent;
	if (pKText)
	{
		_pKText = new char [strlen (pKText) + 1];
		if (_pKText)
		{
#if defined(_DEBUG)
			memset (_pKText, '\0', strlen(pKText)+1);	// 03.08.98 (wegen BoundsChecker); Korrektur am 14.01.99
#endif // _DEBUG
			strcpy (_pKText, pKText);
		}
	}
	else
		_pKText = NULL;
}


// ------------------------------------------------------------------------------------------------
IdentListEntry :: ~IdentListEntry (void)
{
	DELETE_VEC (_pKText);	// bis zum 14.01.99    DELETE_OBJ (_pKText);
}
