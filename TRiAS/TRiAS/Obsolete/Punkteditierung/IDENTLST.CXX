// Liste aller Identifikatoren der PBD ----------------------------------------
// File: IDENTLST.CXX

#include "editobjp.hxx"

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillIdentsList (long Ident, BOOL, void *pData)
{
PBDDATA pbdData;
char KText[33];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	if (EC_OKAY == DEX_GetPBDData (pbdData))
		((IdentList *)pData) -> AddIdent (Ident, KText);

return true;	 // weitermachen
}


IdentList :: IdentList (void)
	   : CTree (GetIdentKey, ULongCmp)
{
// wenn noch kein Projekt eröffnet ist, dann wieder raus
char cbBuffer[_MAX_PATH+1];

	if (NULL == DEX_GetActiveProject (cbBuffer)) 
		return;	// nichts eröffnet

ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsList;
	ELK.ePtr = (void *)this;
	DEX_EnumPBDData (ELK);
}

IdentList :: ~IdentList (void)
{
	EveryDelete();
}


Bool IdentList :: AddIdent (long Ident, char *pDesc)
{
IdentListEntryCreator IELCr (*this);

	return NULL != ContCreate (IELCr, IdentListEntry) (Ident, pDesc);
}


// Eintrag erneuern, wenn PBD geändert wurde ----------------------------------
Bool IdentList :: UpdateEntry (long Ident)
{
CTable t(*this);

	if (t.Find (&Ident)) 
		t.Delete();

return FillIdentsList (Ident, FALSE, this);
}


void IdentList :: UserDelete (void *pObj)
{
	((IdentListEntry *)pObj) -> ~IdentListEntry();
}


int ULongCmp (void *pObj1, void *pObj2)
{
ULONG l1 = *(ULONG *)pObj1;
ULONG l2 = *(ULONG *)pObj2;

	if (l1 > l2) return 1;
	if (l1 < l2) return -1;
	return 0;
}


void *GetIdentKey (void *pObj)
{
	return & ((IdentListEntry *)pObj) -> _Ident;
}


// Memberfuntkionen für Elemente der Liste ------------------------------------
IdentListEntry :: IdentListEntry (long Ident, char *pKText)
{
	_Ident = Ident;
	if (pKText) {
		_pKText = new char [strlen (pKText) +1];
		if (_pKText) strcpy (_pKText, pKText);
	} else
		_pKText = NULL;
}


IdentListEntry :: ~IdentListEntry (void)
{
	DELETE (_pKText);
}

