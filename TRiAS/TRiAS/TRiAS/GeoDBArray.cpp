///////////////////////////////////////////////////////////////////////////////
// ArrayContainer, der alle derzeit geöffneten DatenBanken enthält 
// File: CGeoDBArray.cpp

#include "triaspre.hxx"

#include "GeoDBArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor -----------------------------------------------------
CGeoDBArray::CGeoDBArray (void)
	   : CArrayContainer (5)
{
	m_pActDB = NULL;
	m_iActDB = -1;
}

CGeoDBArray::~CGeoDBArray (void)
{
	DELETE_OBJ (m_pActDB);
	EveryDelete();
}

void EXPORTTRIAS CGeoDBArray::UserDelete (void *pObj)
{
	TX_ASSERT(NULL != pObj);
	((GeoDB *)pObj) -> ~GeoDB();
}

int CGeoDBArray::FAddItem (bool fActivate)
{
CSyncThread Sync (this);
GeoDBCreator CDBCr (*this);
GeoDB *pDB = ContCreate (CDBCr, GeoDB);

	CDBCr.Insert();	// wegspeichern

	if (!fActivate) return int(Count()-1);
	
	if (pDB) {
	CRing r(*this);

		DELETE_OBJ (m_pActDB);
		if (r.Goto (m_iActDB = int(Count()-1))) {	// neues Objekt ist das letzte im Array
			TX_TRY(m_pActDB = new GeoDBLock (r));
			if (NULL != m_pActDB) return m_iActDB;
		}
		m_iActDB = -1;
	}
	return -1;	// Fehler
}

bool CGeoDBArray::FDelItem (int iIndex)
{
CSyncThread Sync (this);
bool fDelActive = false;

	if (iIndex == -1)
		iIndex = m_iActDB;
	if (iIndex == -1) return false;

	if (iIndex == m_iActDB) {
		DELETE_OBJ (m_pActDB);
		m_iActDB = -1;
		fDelActive = true;
	}
	
CRing r(*this);

	if (r.Goto (iIndex)) {
	int iNewIndex = -1;

		if (fDelActive) {
			if (Count() > 0) {
			// erste geöffnete DB aktivieren
			CRing r1(*this);

				r1.First();
				for (long i = 0; i < Count() && r1.Valid(); i++, r1.Next()) {
				GeoDBLock l(r1);

					if (!!l && l -> isOpened() && iIndex != i) {
						iNewIndex = i;
						break;
					}
				}
			} else
				FActivateItem (-1);	// hebt Lock auf
		} else if (iIndex < m_iActDB) {
			iNewIndex = m_iActDB-1;
			FActivateItem(-1);
		}

		if (!r.Delete())			// jetzt kann gelöscht werden
			return false;

		if (-1 != iNewIndex) 
			FActivateItem(iNewIndex);
	}
	return true;	
}

int CGeoDBArray::FActivateItem (int iIndex)
{
CSyncThread Sync (this);
int iOldIndex = m_iActDB;
CRing r(*this);

	if (m_iActDB != -1) {
		DELETE_OBJ (m_pActDB);
		m_iActDB = -1;
	}
	if (iIndex != -1 && r.Goto (iIndex)) {
		m_iActDB = iIndex;
		TX_TRY(m_pActDB = new GeoDBLock (r));
	} 
	return iOldIndex;
}

GeoDB &CGeoDBArray::DB (int iIndex)
{
CSyncThread Sync (this);

	if (-1 == iIndex) {		// derzeit aktuelles auswählen
		if (m_pActDB != NULL) {
		GeoDB *pDB = (GeoDB *)(*m_pActDB);
		
			return *pDB;
		} else {
			iIndex = m_iActDB;
			if (iIndex == -1) {
				TX_ASSERT(-1 == iIndex);	// ist wohl doch nicht ganz das, was gewollt wurde
				iIndex = 0;		// also das erste (und hoffentlich) beste auswählen
			}
		}
	}

// ein bestimmtes DBO auswählen
	{
	CRing r(*this);
	
		r.Goto (iIndex);
	
	GeoDBLock l(r);
		
		return *l;		// oioioi !
	}
}

GeoDB &CGeoDBArray::DB (HPROJECT hPr)
{
	_ASSERTE(HACTPROJECT != hPr);		// es darf hier nicht das Projekt geucht werden!

CSyncThread Sync (this);
int iIndex = -1;

	if (HACTCONNECTION == hPr) {		// derzeit aktuelles auswählen
		if (m_pActDB != NULL) {
		GeoDB *pDB = (GeoDB *)(*m_pActDB);
		
			return *pDB;
		} else 
			iIndex = m_iActDB;
	} else
		iIndex = FFindItem (hPr);

	if (iIndex == -1) {
		TX_ASSERT(-1 == iIndex);	// ist wohl doch nicht ganz das, was gewollt wurde
		iIndex = 0;	// also das erst beste auswählen
	}

// ein bestimmtes DBO auswählen
	{
	CRing r(*this);
	
		r.Goto (iIndex);
	
	GeoDBLock l(r);
		
		return *l;		// oioioi !
	}
}

int CGeoDBArray::FFindItem (HPROJECT iDBDesc)
{
	_ASSERTE(HACTPROJECT != iDBDesc);		// es darf hier nicht das Projekt geucht werden!

CSyncThread Sync (this);

	if (HACTCONNECTION == iDBDesc)
		return m_iActDB;

CRing r(*this);
int iCnt = 0;

	for (r.First(); r.Valid(); iCnt++, r.Next()) {
	GeoDBLock l(r);
	
		if (!l || !l -> isOpened()) 
			continue;

		if (l -> DBDesc() == iDBDesc)
			return iCnt;
	}
	return -1;	// not found
}

// Feststellen, ob eine bestimmte GeoDB bereits in der Liste ist
HPROJECT CGeoDBArray::IsOpened (LPCSTR pcName)
{
CSyncThread Sync (this);
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);
	
		if (!l || !l -> isOpened()) 
			continue;

		if (!stricmp (l -> GetDBName(), pcName))
			return l -> DBDesc();
	}
	return NULL;	// not found
}

// Feststellen, ob überhaupt eine GeoDB geöffnet ist
bool CGeoDBArray::HasOpenDB (void)
{
CSyncThread Sync (this);
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);
	
		if (!l) continue;
		if (l -> isOpened()) 
			return true;
	}
	return false;	// no open GeoDB's
}

// Feststellen, ob überhaupt eine GeoDB geöffnet ist
UINT CGeoDBArray::GetOpenCount(void)
{
CSyncThread Sync (this);
CRing r(*this);
UINT uiCnt = 0;

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);
	
		if (!l) continue;
		if (l -> isOpened()) 
			uiCnt++;
	}
	return uiCnt;		// count of open GeoDB's
}

