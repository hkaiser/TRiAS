// Routinen fuer temporaeren Baum der PBD_Data-Items --------------------------
// File: PBDTEMP.CXX

#include "trias02p.hxx"

#include <pbd.hxx>
#include <pbdtemp.hxx>


// PBDTempTree *PBD_Data :: pTempTree = NULL;	// globaler Pointer auf den TempBaum

// Konstruktor ----------------------------------------------------------------
PBDTempTree :: PBDTempTree (void) 
	     : CTree (PBD_DataKey, PBD_DataCmp) 
{
	// nothing else to do
}

PBDTempTree :: ~PBDTempTree (void) 
{
	EveryDelete ();
}

void EXPORT02 PBD_DB :: ReleasePBDTempTree (void) 
{
	DELETE (m_pPbdTemp);
}


// HandlingFunktionen ---------------------------------------------------------
bool PBD_DB :: AddToTempTree (PBD_Data &rData) 
{
// evtl. Baum anlegen
	if (m_pPbdTemp == NULL) {
		m_pPbdTemp = new PBDTempTree ();
		if (m_pPbdTemp == NULL) {
			db_error (EC_NOMEMORY, RC_AddToTempTree);
			return false;
		}
	}

// nachsehen, ob dieses Element schon im Baum ist
	{
	CTable t(*m_pPbdTemp);

		if (t.Find (&rData)) return true;
	}

// In den Baum einfügen
	{
	PBD_DataCreator PCr (*m_pPbdTemp);

		return ContCreate (PCr, PBD_Data) (rData.m_pDB, rData.m_rgTyp, 
					       rData.m_lCode, 
					       rData.m_cbKurzText, true) != NULL;
	}
}

bool EXPORT02 PBD_DB :: RemoveFromTempTree (PBD_Data &rData) 
{
	if (m_pPbdTemp == NULL) return false;

// nachsehen, ob dieses Element überhaupt drin ist
	{
	CTable t(*m_pPbdTemp);

		if (t.Find (&rData)) t.Delete();
	}

// wenn Baum leer ist, dann beseitigen
	if (m_pPbdTemp -> Count() == 0) 
		DELETE (m_pPbdTemp);

return true;
}

bool EXPORT02 PBD_DB :: FillFromTempTree (PBD_Data &rData) 
{
	if (m_pPbdTemp == NULL) return false;

// nachsehen, ob dieses Element drin ist
	{
	CTable t(*m_pPbdTemp);

		if (t.Find (&rData)) {
		PBD_DataLock l(t);

			if (!l) return false;

		// Member umkopieren
			rData.m_pDB = l -> m_pDB;
			rData.m_rgTyp = l -> m_rgTyp;
			rData.m_lCode = l -> m_lCode;
			rData.m_fTemp = true;
			rData.m_dbaSatz = -1;
			rData.m_rgStatus = l -> m_rgStatus;
			strcpy (rData.m_cbKurzText, l -> m_cbKurzText);
			rData.m_pLangText = NULL;
		} else
			return false;
	}

return true;
}

// BaumFunktionen -------------------------------------------------------------
void *PBD_DataKey (void *pObj) 
{ 
	return pObj; 
}


int PBD_DataCmp (void *pObj1, void *pObj2) 
{
ulong lCode1 = ((PBD_Data *)pObj1) -> m_lCode;
ulong lCode2 = ((PBD_Data *)pObj2) -> m_lCode;

	if (lCode1 > lCode2) return 1;
	if (lCode1 < lCode2) return -1;

return 0;
}

	

