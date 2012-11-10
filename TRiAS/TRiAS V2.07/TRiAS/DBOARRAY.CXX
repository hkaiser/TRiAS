// ArrayContainer, der alle derzeit geöffneten Projekte enthält ---------------
// File: DBOARRAY.CXX

#include "triaspre.hxx"

#include "dboarray.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
CDBOArray :: CDBOArray (void)
	   : CArrayContainer (5)
{
	m_pActDBO = NULL;
	m_iActDB = -1;
}

CDBOArray :: ~CDBOArray (void)
{
	DELETE (m_pActDBO);
	EveryDelete();
}

void EXPORTTRIAS CDBOArray :: UserDelete (void *pObj)
{
	((DatenBasisObjekt *)pObj) -> ~DatenBasisObjekt();
}

short CDBOArray :: FAddItem (const GeoDB &DB, unsigned int MTyp, 
			     pPen pP, pBrush pB, bool fActivate)
{
CSyncThread Sync (this);
DatenBasisObjektCreator CDBOCr (*this);
DatenBasisObjekt *pDBO = ContCreate (CDBOCr, DatenBasisObjekt)(DB, MTyp, pP, pB);

	CDBOCr.Insert();	// wegspeichern
	
	if (!fActivate) return short (Count()-1);
		
	if (pDBO) {
	CRing r(*this);
	
		DELETE (m_pActDBO);
		m_iActDB = short(Count()-1);
		r.Goto (m_iActDB);	// neues Objekt ist das letzte im Array
		m_pActDBO = new DatenBasisObjektLock (r);
		if (m_pActDBO)
			return m_iActDB;
		m_iActDB = -1;
	}
	
return -1;	// Fehler
}

short CDBOArray :: FAddItem (bool fActivate)
{
CSyncThread Sync (this);
DatenBasisObjektCreator CDBOCr (*this);
DatenBasisObjekt *pDBO = ContCreate (CDBOCr, DatenBasisObjekt);

	CDBOCr.Insert();	// wegspeichern
	
	if (!fActivate) return short(Count()-1);
	
	if (pDBO) {
	CRing r(*this);
	
		DELETE (m_pActDBO);
		if (r.Goto (m_iActDB = short(Count()-1))) {	// neues Objekt ist das letzte im Array
			m_pActDBO = new DatenBasisObjektLock (r);
			if (m_pActDBO) return m_iActDB;
		}
		m_iActDB = -1;
	}
	
return -1;	// Fehler
}

bool CDBOArray :: FDelItem (short iIndex)
{
CSyncThread Sync (this);
bool fDelActive = false;
	
	if (iIndex == -1)
		iIndex = m_iActDB;
	if (iIndex == -1) return false;

	if (iIndex == m_iActDB) {
		DELETE (m_pActDBO);	// aktiven Lock aufheben
		m_iActDB = -1;
		fDelActive = true;
	}
	
CRing r(*this);

	if (r.Goto (iIndex)) {
		r.Delete();		// jetzt kann gelöscht werden

		if (fDelActive) {
			if (Count()) 
				FActivateItem (0);	// erstbestes aktivieren
			else
				FActivateItem (-1);	// hebt Lock auf
		}
	}
	
return true;	
}

short CDBOArray :: FActivateItem (short iIndex)
{
CSyncThread Sync (this);
short iOldIndex = m_iActDB;
CRing r(*this);

	if (m_iActDB != -1) {
		DELETE (m_pActDBO);
		m_iActDB = -1;
	}
	if (iIndex != -1 && r.Goto (iIndex)) {
		m_iActDB = iIndex;
		m_pActDBO = new DatenBasisObjektLock (r);
	} 

return iOldIndex;
}

DatenBasisObjekt &CDBOArray :: DBO (short iIndex)
{
CSyncThread Sync (this);

	if (-1 == iIndex) {		// derzeit aktuelles auswählen
		if (m_pActDBO != NULL) {
		DatenBasisObjekt *pDBO = (DatenBasisObjekt *)(*m_pActDBO);
		
			return *pDBO;
		} else {
			iIndex = m_iActDB;
			if (iIndex == -1) 
				iIndex = 0;	// also das erst beste auswählen
		}
	}

// ein bestimmtes DBO auswählen
	{
	CRing r(*this);
	
		r.Goto (iIndex);
	
	DatenBasisObjektLock l(r);
		
	return *l;		// oioioi !
	}
}

DatenBasisObjekt &CDBOArray::DBO (HPROJECT hPr)
{
CSyncThread Sync (this);
int iIndex = -1;

	if (NULL == hPr) {		// derzeit aktuelles auswählen
		if (m_pActDBO != NULL) {
		DatenBasisObjekt *pDBO = (DatenBasisObjekt *)(*m_pActDBO);
		
			return *pDBO;
		} else 
			iIndex = m_iActDB;
	} else
		iIndex = FFindItem (hPr);

	if (iIndex == -1) 
		iIndex = 0;	// also das erst beste auswählen

// ein bestimmtes DBO auswählen
	{
	CRing r(*this);
	
		r.Goto (iIndex);
	
	DatenBasisObjektLock l(r);
		
	return *l;		// oioioi !
	}
}

short CDBOArray :: FFindItem (HPROJECT iDBDesc)
{
CSyncThread Sync (this);
CRing r(*this);
short iCnt = 0;

	for (r.First(); r.Valid(); iCnt++, r.Next()) {
	DatenBasisObjektLock l(r);
	
		if (!l) continue;
		if (l -> DB().DBDesc() == iDBDesc)
			return iCnt;
	}
	
return -1;	// not found
}

// FEststellen, ob eine GeoDB bereits in der Liste ist
HPROJECT CDBOArray::IsOpened (LPCSTR pcName)
{
CSyncThread Sync (this);
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	DatenBasisObjektLock l(r);
	
		if (!l) continue;
		if (!stricmp (l -> DB().GetDBName(), pcName))
			return l -> DB().DBDesc();
	}
	
return NULL;	// not found
}

