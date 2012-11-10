// ArrayContainer, der alle derzeit geöffneten Projekte enthält ---------------
// File: DBOARRAY.CXX

#include "triaspre.hxx"

#include "dboarray.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor -----------------------------------------------------
CDBOArray::CDBOArray (void)
	   : CArrayContainer (5, CONTFLAG(CFDefault & ~CFAutoDelete))		
{
	m_pActDBO = NULL;
	m_iActDB = -1;
}

CDBOArray::~CDBOArray (void)
{
	if (NULL != m_pActDBO) {	// aktiven Lock aufheben
		(*m_pActDBO) -> SetActive (false);
		delete m_pActDBO;
		m_pActDBO = NULL;
	}
	EveryDelete();
}

void EXPORTTRIAS CDBOArray::UserDelete (void *pObj)
{
	TX_ASSERT(NULL != pObj);
	((ITRiASConnectionEvents *)(DatenBasisObjekt *)pObj) -> Release();
}

int CDBOArray::FAddItem (bool fActivate)
{
CSyncThread Sync (this);
CComObject<DatenBasisObjekt> *pDBO = NULL;

	m_iActDB = -1;		// für alle Fälle
	{
	DatenBasisObjektCreator CDBOCr (*this);

		if (FAILED(CComObject<DatenBasisObjekt>::CreateInstance (&pDBO)))
			return -1;
		if (!CDBOCr.InsertPtr (pDBO))
			return -1;
		((ITRiASConnectionEvents *)(pDBO)) -> AddRef();	// RefCnt == 1
	} // wegspeichern
	
	if (!fActivate) return int(Count()-1);
	
	TX_ASSERT(NULL != pDBO);
	{
	CRing r(*this);
	
		if (NULL != m_pActDBO) {
			(*m_pActDBO) -> SetActive (false);
			delete m_pActDBO;
			m_pActDBO = NULL;
		}
		m_iActDB = int(Count()-1);
		
		if (r.Goto (m_iActDB)) {	// neues Objekt ist das letzte im Array
			TX_TRY(m_pActDBO = new DatenBasisObjektLock (r));
			if (NULL != m_pActDBO) {
				(*m_pActDBO) -> SetActive();
				return m_iActDB;
			}
		}
	}
	return -1;	// Fehler
}

bool CDBOArray::FDelItem (int iIndex)
{
CSyncThread Sync (this);
bool fDelActive = false;
	
	if (iIndex == -1)
		iIndex = m_iActDB;
	if (iIndex == -1) return false;

	if (iIndex == m_iActDB) {
		if (NULL != m_pActDBO) {	// aktiven Lock aufheben
			(*m_pActDBO) -> SetActive (false);
			delete m_pActDBO;
			m_pActDBO = NULL;
		}
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

int CDBOArray::FActivateItem (int iIndex)
{
CSyncThread Sync (this);
int iOldIndex = m_iActDB;
CRing r(*this);

	if (m_iActDB != -1) {
		if (NULL != m_pActDBO) {	// aktiven Lock aufheben
			(*m_pActDBO) -> SetActive (false);
			delete m_pActDBO;
			m_pActDBO = NULL;
		}
		m_iActDB = -1;
	}
	if (iIndex != -1 && r.Goto (iIndex)) {
		m_iActDB = iIndex;
		TX_TRY(m_pActDBO = new DatenBasisObjektLock (r));
		if (NULL != m_pActDBO)
			(*m_pActDBO) -> SetActive();
	} 

	return iOldIndex;
}

DatenBasisObjekt &CDBOArray::DBO (int iIndex)
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

	if (HACTPROJECT == hPr) {		// derzeit aktuelles auswählen
		if (m_pActDBO != NULL) {
		DatenBasisObjekt *pDBO = (DatenBasisObjekt *)(*m_pActDBO);
		
			return *pDBO;
		} else 
			iIndex = m_iActDB;
	} else
		iIndex = FFindItem (hPr);

	if (-1 == iIndex) 
		iIndex = 0;	// also das erst beste auswählen

// ein bestimmtes DBO auswählen
	{
	CRing r(*this);
	
		r.Goto (iIndex);
	
	DatenBasisObjektLock l(r);
		
		return *l;		// oioioi !
	}
}

int CDBOArray::FFindItem (HPROJECT iDBDesc)
{
CSyncThread Sync (this);
CRing r(*this);
int iCnt = 0;

	for (r.First(); r.Valid(); iCnt++, r.Next()) {
	DatenBasisObjektLock l(r);
	
		if (!l) continue;
		if (l -> DBDesc() == iDBDesc)
			return iCnt;
	}
	return -1;	// not found
}

// Feststellen, ob eine GeoDB bereits in der Liste ist
HPROJECT CDBOArray::IsOpened (LPCSTR pcName)
{
CSyncThread Sync (this);
CRing r(*this);
char cbBuffer[_MAX_PATH];

	for (r.First(); r.Valid(); r.Next()) {
	DatenBasisObjektLock l(r);
	
		if (!l) continue;
		if (!stricmp (l -> GetDBName(cbBuffer), pcName))
			return l -> DBDesc();
	}
	return NULL;	// not found
}

